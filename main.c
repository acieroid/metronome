#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <linux/kd.h>

#define CONSOLE_FILE "/dev/console"

/* We have to use a global variable for the SIGINT signal (if we
 * don't use on, the leds/lights will stay on when the users hits
 * C-c) */
int fd = -1; 

typedef struct noise_params_t {
  int freq; /* The frequence of the beep */
  int len; /* The length of the beep */
} noise_params_t;

typedef struct light_params_t {
  unsigned char leds; /* Which leds does the light switch on? */
  int len; /* What time does the light stay on ? (in ms) */
} light_params_t;

typedef struct text_params_t { 
  char *text; /* Le texte à afficher */
} text_params_t ;

typedef struct options_t {
  int noise; /* Does the metronome make moise ? (PC beep) */
  int light; /* Does the metrenome make light ? (keyboard LEDS) */
  int bpm; /* Beats per minute */
  noise_params_t noise_p; /* What does the beep looks like ? */
  light_params_t light_p; /* What does the lights looks like ? */ 
  text_params_t text_p; /* What does the text looks like ? */
} options_t ;

int open_console(void)
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
}

void sigint_handle(int signum) 
{
  /* Deactivate the beep and the lights, and close the file
   * descriptor */
  if (signum == SIGINT) {
    if (fd != -1) {
      ioctl(fd, KDMKTONE, 0);
      ioctl(fd, KDSETLED, 0);
      close(fd);
    }
    exit(SIGINT);
  }
}
int main(int argc, char **argv) {
  //options_t *options = malloc(sizeof options_t);
  unsigned char init_light_state = 0;
  noise_params_t b;
  light_params_t l;
  text_params_t t;

  signal(SIGINT, sigint_handle);

  //parse_args(argc, argv, options);

  open_console();
  init_light_state = save_light_state();

  //play_metronome(options);
  b.len = 1000;
  b.freq = 440;
  beep(b);

  t.text = malloc(4*sizeof(char));
  strncpy(t.text, "TIC ", 4);
  text(t);

  l.leds = LED_CAP | LED_SCR | LED_NUM;
  l.len = 1000;
  light(l);

  set_light_state(init_light_state);

  return 0;

}
