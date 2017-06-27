/* -*-c-*-
   The MIT License (MIT)

   Copyright (c) 2016 - Ronaldo Faria Lima

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.

   Created: 2017-06-27 by Ronaldo Faria Lima

   This file purpose: Demonstração de threads em kernel space.
*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

typedef struct data_t {
  pthread_mutex_t mutex;
  pthread_cond_t cond;
  int stop;
} data_t;

static void *
thread1(void *);

static void *
thread2(void *);

int
main(int argc, char **argv)
{
  data_t data = {PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, 0};
  pthread_t thread_1, thread_2;
  pthread_create(&thread_1, NULL, thread1, (void *)&data);
  pthread_create(&thread_2, NULL, thread2, (void *)&data);
  pthread_mutex_lock(&data.mutex);
  while((data.stop & 0x3) != 0x3)
    {
      fprintf(stderr, "[main] waiting for threads to finish\n");
      pthread_cond_wait(&data.cond, &data.mutex);
    }
  fprintf(stderr, "[main] exiting...\n");
  return 0;
}

static void *
thread1(void *arg)
{
  data_t *data = (data_t *) arg;
  sleep(10);
  pthread_mutex_lock(&data->mutex);
  data->stop |= 0x1;
  pthread_cond_signal(&data->cond);
  pthread_mutex_unlock(&data->mutex);
  fprintf(stderr, "[thread 1] Exiting...\n");
  return NULL;
}

static void *
thread2(void *arg)
{
  data_t *data = (data_t *) arg;
  sleep(15);
  pthread_mutex_lock(&data->mutex);
  data->stop |= 0x2;
  pthread_cond_signal(&data->cond);
  pthread_mutex_unlock(&data->mutex);
  fprintf(stderr, "[thread 2] Exiting...\n");
  return NULL;
}
