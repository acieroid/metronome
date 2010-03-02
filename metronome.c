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

#include "metronome.h"

beat_t make_beat(int len, int noise_freq,
                 unsigned char leds, const char *text)
{
  noise_params_t n;
  light_params_t l;
  text_params_t t;
  beat_t b;

  n.freq = noise_freq;
  n.len = len;
  l.leds = leds;
  l.len = len;
  t.text = malloc(strlen(text) * sizeof(char));
  strncpy(t.text, text, strlen(text));

  b.noise = n;
  b.light = l;
  b.text = t;

  return b;
}

void play_beat(beat_t beat)
{
  if (beat.noise.len != 0) 
    beep(beat.noise);
  text(beat.text);
  if (beat.light.len != 0)
    light(beat.light);
}
  
void play_bar(int bpm, bar_t bar)
{
  int i;
  for (i = 0; i < bar.n_beats; i++) {
    play_beat(bar.beats[i]);
    /* little imprecision here, because of the leds lights (they sleep a bit) */
    usleep(6e7/bpm);
  }
}

beat_t void_beat(void) {
  return make_beat(0, NOISE_FREQ_DEFAULT, 0, "");
}

