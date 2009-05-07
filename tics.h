#ifndef TICS_H
#define TICS_H

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <linux/kd.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define CONSOLE_FILE "/dev/console"

/* We have to use a global variable for the SIGINT signal (if we
 * don't use on, the leds/lights will stay on when the users hits
 * C-c) */
int fd; 

typedef struct noise_params_t {
  int freq; /* The frequence of the beep */
  int len; /* The length of the beep */
} noise_params_t;

typedef struct light_params_t {
  unsigned char leds; /* Which leds does the light switch on?
                         (LED_CAP, LED_SCR, LED_NUM) */
  int len; /* What time does the light stay on ? (in ms) */
} light_params_t;

typedef struct text_params_t { 
  char *text; /* Le texte à afficher */
} text_params_t ;

void open_console(void);
void beep(noise_params_t b);
unsigned char save_light_state();
void set_light_state(unsigned char state);
void light(light_params_t t);
void text(text_params_t t);

#endif
