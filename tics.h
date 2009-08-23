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

#ifndef TICS_H
#define TICS_H

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <linux/kd.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int usleep(__useconds_t usec); /* To avoid warnings */

#define CONSOLE_FILE "/dev/console"

/* We have to use a global variable for the SIGINT signal (if we
 * don't use on, the leds/lights will stay on when the user hits
 * ^C) */
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
  char *text; /* text to display */
} text_params_t ;

void open_console(void);
void beep(noise_params_t b);
unsigned char save_light_state();
void set_light_state(unsigned char state);
void light(light_params_t t);
void text(text_params_t t);

#endif
