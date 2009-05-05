#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
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

void parse_args(int argc, char **argv)
{
	int opt, *optindex;
	/* TODO: pouvoir différencier des beats, ne pas se limiter au 4/4 */
	static struct option opts[] = {
		/* Le beep, paramètre opt. : la fréquence */
		{"noise", 2, NULL, 'n'}, 
		/* Le texte, paramètre opt. : le texte à afficher */
		{"text", 2, NULL, 't'}, 
		/* Les leds, paramètre op. : la/les leds à allumer (1, 2, 4)*/
		{"leds", 2, NULL, 'l'},
		/* bpm, paramètre : le nombre de bpm */
		{"bpm", 1, NULL, 'b'}, 
	};
	while ((opt = getopt_long(argc, argv, "n::t::l::b:", opts, NULL)) != -1) { 
		switch (opt) {
			case 'n':
				printf("We will make noise\n");
				if (optarg)
					printf("We got a frequence : %s\n", optarg);
				break;
			case 't':
				printf("We will ouptut text\n");
				if (optarg)
					printf("Precisely that text : %s\n", optarg);
				break;
			case 'l':
				printf("We will light some leds\n");
				if (optarg)
					printf("Those leds : %s\n", optarg);
				break;
			case 'b':
				printf("The bpm is %s\n", optarg);
				break;
			default:
				/*usage();*/
				break;
		}
	}
}





int main(int argc, char **argv) {
  beat_t b;
  bar_t bar;

  signal(SIGINT, sigint_handle);

  /*open_console();
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

	*/
	parse_args(argc, argv);
  return 0;

}
