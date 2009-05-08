#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <limits.h>

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

static void usage(char *progname) 
{
	printf("%s [OPTIONS]\n", progname);
	printf("\t-n[freq], --noise=[freq]\t" 
				 "Make noise. The frequence can be precised (%d if not)\n",
				 NOISE_FREQ_DEFAULT);
	printf("\t-l[leds], --leds=[leds] \t"
				 "Light leds. The leds can be precised (see `man %s') (%d by default)\n",
				 progname, LEDS_DEFAULT);
	printf("\t-t[text], --text=[text] \t"
			 	 "Output text. The text can be precised (%s by default)\n", 
				 TEXT_DEFAULT);
	printf("\t-b[speed], --bpm=[speed]\t"
				 "The beats per minute (%d by default)\n", 
				 BPM_DEFAULT);
}

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

void parse_args(int argc, char **argv, beat_t *b, int *bpm)
{
	int opt;
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
				b->noise.len = BEAT_LEN_DEFAULT;
				if (optarg) {
					b->noise.freq = strtol(optarg, NULL, 10);
					if (b->noise.freq == LONG_MIN || b->noise.freq == LONG_MAX) {
						perror("strtol");
						exit(1);
					}
				}
				break;
			case 't':
				if (optarg) {
					b->text.text = malloc(strlen(optarg)*sizeof(char));
					strncpy(b->text.text, optarg, strlen(optarg));
				}
				else {
					b->text.text = malloc(strlen(TEXT_DEFAULT)*sizeof(char));
					strncpy(b->text.text, TEXT_DEFAULT, strlen(TEXT_DEFAULT));
				}
				break;
			case 'l':
				b->light.len = BEAT_LEN_DEFAULT;
				b->light.leds = 7;
				if (optarg) {
					b->light.leds = strtol(optarg, NULL, 10);
					if (b->light.leds == LONG_MAX || b->light.leds == LONG_MIN) {
						perror("strtol");
						exit(1);
					}
				}
				break;
			case 'b':
				*bpm = strtol(optarg, NULL, 10);
				if (*bpm == LONG_MAX || *bpm == LONG_MIN) { 
					perror("strtol");
					exit(1);
				}
				if (*bpm <= 0) {
					fprintf(stderr, "Can't have negative or zero beats per minute !"
						 			" (got %d bpm)\n", *bpm);
					exit(1);
				}
				break;
			default:
				usage(argv[0]);
				exit(1);
				break;
		}
	}
}

int main(int argc, char **argv) {
  beat_t b;
  bar_t bar;
	int i, bpm = BPM_DEFAULT;

  signal(SIGINT, sigint_handle);

  open_console();
  init_light_state = save_light_state();

	b = void_beat();
	parse_args(argc, argv, &b, &bpm);
	bar.n_beats = 4;
	bar.beats = malloc(sizeof(beat_t)*bar.n_beats);
	for(i=0; i < bar.n_beats; i++) {
		bar.beats[i] = b;
	}

	if (! (!b.noise.len && !b.light.len && !strcmp(b.text.text, ""))) {
		while(1) {
			play_bar(bpm, bar);
		}
	}
	else 
		usage(argv[0]);

  set_light_state(init_light_state);

  return 0;

}
