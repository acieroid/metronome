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

#include "tics.h"

void open_console(void)
{
  fd = open(CONSOLE_FILE, O_RDWR);
  if (fd == -1) {
    fprintf(stderr, "Couldn't open %s\n", CONSOLE_FILE);
    perror("open");
    exit(1);
  }
}

void beep(noise_params_t b)
{
  /* Why 1193180 ? Good question, it just works with that number */
  if (ioctl(fd, KDMKTONE, (b.len << 16) + 1193180/b.freq) == -1) {
    fprintf(stderr, "Error while setting tone state\n");
    perror("ioctl");
    close(fd);
    exit(1);
  }
}

unsigned char save_light_state()
{
  unsigned char state;
  /* TODO: It doesn't get the real state, why ? */
  if (ioctl(fd, KDGETLED, &state) == -1) {
    fprintf(stderr, "Error while getting leds state\n");
    perror("ioctl");
    close(fd);
    exit(1);
  }
  return state;
}

void set_light_state(unsigned char state)
{
  if (ioctl(fd, KDSETLED, state) == -1) {
    fprintf(stderr, "Error while setting leds state\n");
    perror("ioctl");
    close(fd);
    exit(1);
  }
}

void light(light_params_t l)
{
  set_light_state(l.leds);
  usleep(l.len*1000);
  set_light_state(0);
}


void text(text_params_t t)
{
  printf("%s", t.text);
  fflush(stdout);
}

