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
  beep(beat.noise);
  text(beat.text);
  light(beat.light);
}
  
void play_bar(int bpm, bar_t bar)
{
  int i;
  for (i = 0; i < bar.n_beats; i++) {
    play_beat(bar.beats[i]);
    /* TODO little imprecision here */
    usleep(500*1000);
  }
}
