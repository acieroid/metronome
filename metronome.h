#ifndef METRONOME_H
#define METRONOME_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "tics.h"

/* Each beat have specifics options, so we can distinguish beats 
 * if we want */
typedef struct beat_t {
  noise_params_t noise; /* What does the beep looks like ? */
  light_params_t light; /* What does the lights looks like ? */ 
  text_params_t text; /* What does the text looks like ? */
  int len;
} beat_t ;

typedef struct bar_t {
  int n_beats;
  beat_t *beats; /* One bar is made of multiple beats */
} bar_t ;

beat_t make_beat(int len, int noise_freq,
                 unsigned char leds, const char *text);

void play_beat(beat_t beat);

void play_bar(int bpm, bar_t bar);
#endif
