#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tics.h"
#include "metronome.h"

/* With that, we can restore the initial state of the keyboards
 * led */
unsigned char init_light_state;

typedef struct options_t {
  int noise; /* Does the metronome make moise ? (PC beep) */
  int light; /* Does the metrenome make light ? (keyboard LEDS) */
  int bpm; /* Beats per minute */
} options_t ;


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
  beat_t b;
  bar_t bar;

  signal(SIGINT, sigint_handle);

  open_console();
  init_light_state = save_light_state();

  b = make_beat(50, 640, LED_NUM, "TIC ");
  bar.n_beats = 2;
  bar.beats = malloc(sizeof(beat_t)*2);
  bar.beats[0] = b;
  b.noise.freq = 440;
  b.light.leds = LED_CAP;
  bar.beats[1] = b;

  while(1) {
    play_bar(60, bar);
  }

  set_light_state(init_light_state);

  return 0;

}
