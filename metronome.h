/*
 * Copyright (c) 2009 Quentin Stievenart 
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * * Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef METRONOME_H
#define METRONOME_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include "tics.h" 

#define BEAT_LEN_DEFAULT 50
#define NOISE_FREQ_DEFAULT 440
#define LEDS_DEFAULT LED_CAP|LED_SCR|LED_NUM 
#define TEXT_DEFAULT "TIC "
#define BPM_DEFAULT 120

int usleep(__useconds_t usec); /* To avoid warnings */

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

