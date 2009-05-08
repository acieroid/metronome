#ifndef METRONOME_H
#define METRONOME_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "tics.h" 

#define BEAT_LEN_DEFAULT 50
#define NOISE_FREQ_DEFAULT 440
#define LEDS_DEFAULT LED_CAP|LED_SCR|LED_NUM 
#define TEXT_DEFAULT "TIC "
#define BPM_DEFAULT 120

/* Each beat have specifics options, so we can distinguish beats 
 * if we want */
typedef struct beat_t {
  noise_params_t noise; /* What does the beep looks like ? */
  light_params_t light; /* What does the lights looks like ? */ 
  text_params_t text; /* What does the text looks like ? */
} beat_t ;

typedef struct bar_t {
  int n_beats;
  beat_t *beats; /* One bar is made of multiple beats */
} bar_t ;

beat_t make_beat(int len, int noise_freq,
                 unsigned char leds, const char *text);

void play_beat(beat_t beat);
void play_bar(int bpm, bar_t bar);
/* Return a beat that doesn't output anything, a `void beat' */
beat_t void_beat(void);

#endif

