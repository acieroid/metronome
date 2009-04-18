#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tics.h"

/* With that, we can restore the initial state of the keyboards
 * led */
unsigned char init_light_state;

void sigint_handle(int signum) 
{
  /* Deactivate the beep, reset the lights at their initial state, 
   * and close the file descriptor */
  if (signum == SIGINT) {
    if (fd != -1) {
      ioctl(fd, KDMKTONE, 0);
      ioctl(fd, KDSETLED, init_light_state);
      close(fd);
    }
    exit(SIGINT);
  }
}
int main(int argc, char **argv) {
  noise_params_t b;
  light_params_t l;
  text_params_t t;

  signal(SIGINT, sigint_handle);

  open_console();
  init_light_state = save_light_state();

  b.len = 50;
  b.freq = 440;

  t.text = malloc(4*sizeof(char));
  strncpy(t.text, "TIC ", 4);

  l.leds = LED_NUM;
  l.len = 50;

begin:
  l.leds = LED_SCR;
  b.freq = 300;
  strncpy(t.text, "TAC ", 4);

  beep(b);
  text(t);
  light(l);
  usleep(1000*400);

  strncpy(t.text, "TIC ", 4);
  l.leds = LED_NUM;
  b.freq = 440;

  beep(b);
  text(t);
  light(l);
  usleep(1000*400);

  beep(b);
  text(t);
  light(l);
  usleep(1000*400);

  beep(b);
  text(t);
  light(l);
  usleep(1000*400);

goto begin;

  set_light_state(init_light_state);

  return 0;

}
