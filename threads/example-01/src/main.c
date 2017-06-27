/* -*-c-*-
   The MIT License (MIT)

   Copyright (c) 2016 - Ronaldo Faria Lima

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.

   Created: 2017-06-26 by Ronaldo Faria Lima

   This file purpose: Demonstração de threads em user space
*/

#include <setjmp.h>
#include <stdio.h>
#include "libdill.h"

coroutine static void
thread_01(void);

coroutine static void
thread_02(void);

static int finish = 0x0;
int
main(void)
{
  go(thread_01());
  go(thread_02());
  while ((finish & 0x3) != 0x3)
    {
      msleep(now() + 1000);
    }
  return 0;
}

coroutine static void
thread_01(void)
{
  register int i;
  for (i=0; i<100; ++i)
    {
      fprintf(stderr, "> thread_01 yielding: %d\n", i);
      yield();
      fprintf(stderr, "> thread_01 resuming\n");
    }
  finish |= 0x1;
}

coroutine static void
thread_02(void)
{
  register int i;
  for (i=0; i<100; ++i)
    {
      fprintf(stderr, "\t> thread_02 yielding: %d\n", i);
      yield();
      fprintf(stderr, "\t> thread_02 resuming...\n");
    }
  finish |= 0x2;
}
