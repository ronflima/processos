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

   Created: 2017-06-25 by Ronaldo Faria Lima

   This file purpose: Exemplo de criação e sincronização de processos usando C.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int
main(void)
{
  register int i;
  
  while (1)
    {
      pid_t pid = fork();
      if (pid < 0)
        {
          /* Conseguimos exaurir a tabela de processos. Nada mais executa na sua
             máquina enquanto este programa não retornar. */
          break;
        }
      if (pid == 0)
        {
          /* Este é o processo filho. Simplesmente retorna para forçar a
             finalização imediata. */
          return 0;
        }
    }
  sleep(60);
  printf("[Parent] Exiting...\n");
  return 0;
}

