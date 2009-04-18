#include "tics.h"

void open_console(void)
{
  fd = open(CONSOLE_FILE, O_RDWR);
  if (fd == -1) {
    fprintf(stderr, "Couldn't open %s\n", CONSOLE_FILE);
    perror("open");
    exit(1);
  }
}

void beep(noise_params_t b)
{
  /* Why 1193180 ? Good question, it just works with that number */
  if (ioctl(fd, KDMKTONE, (b.len << 16) + 1193180/b.freq) == -1) {
    fprintf(stderr, "Error while setting tone state");
    perror("ioctl");
    close(fd);
    exit(1);
  }
}

unsigned char save_light_state()
{
  unsigned char state;
  /* TODO: It doesn't get the real state, why ? */
  if (ioctl(fd, KDGETLED, &state) == -1) {
    fprintf(stderr, "Error while getting leds state");
    perror("ioctl");
    close(fd);
    exit(1);
  }
  return state;
}

void set_light_state(unsigned char state)
{
  if (ioctl(fd, KDSETLED, state) == -1) {
    fprintf(stderr, "Error while setting leds state");
    perror("ioctl");
    close(fd);
    exit(1);
  }
}

void light(light_params_t l)
{
  set_light_state(l.leds);
  usleep(l.len*1000);
  set_light_state(0);
}


void text(text_params_t t)
{
  printf("%s", t.text);
  fflush(stdout);
}

