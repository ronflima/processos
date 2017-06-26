// -*-swift-*-
// The MIT License (MIT)
//
// Copyright (c) 2017 - Nineteen
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// Created: 2017-06-26 by Ronaldo Faria Lima
// This file purpose: Exemplo de criação de processos filhos em swift

#if os(Linux)
    import Glibc
#else
    import Darwin.C
#endif

import Foundation

let isChild = CommandLine.arguments.contains("child")
let executable = CommandLine.arguments[0]
let maxChildren = 20
var runningChildren = 0
var stop = false

if !isChild {
    signal(SIGCHLD) { (_) in
        var status: Int32 = 0
        wait(&status)
        runningChildren -= 1
        print ("[Parent] Got child returning. Now running \(runningChildren) children processes.")
    }
    signal(SIGTERM) { (_) in
        print ("[Parent] Stopping...")
        stop = true
    }
    mainLoop: while !stop {
        if runningChildren < maxChildren {
            var args = CommandLine.arguments
            args.append("child")
            let _ = Process.launchedProcess(launchPath: executable, arguments: args)
            runningChildren += 1
            sleep(1)
            continue mainLoop
        } else {
            print ("[Parent] Sat up \(runningChildren) child processes.")
        }
        sleep(1)
    }
    print("[Parent] Waiting running children to return...")
    var retries = 0
    synchLoop: while runningChildren > 0 && retries < 30 {
        // Espera todos os processos-filhos retornarem para evitar zumbis. O
        // sincronismo é feito pelo handle de sinal. Observe que há um limite de
        // tentativas de sincronismo. Isto é devido ao fato da função signal não
        // enfileirar sinais que podem chegar simultaneamente, perdendo o
        // processamento de algum sinal.
        sleep(1)
        print ("[Parent] Running children: \(runningChildren).")
        retries += 1
    }
    if retries == 30 {
        print("[Parent] Timed out waiting for synchronization.")
    }
    print("[Parent] Exiting...")
} else {
    // Aqui é o processo filho. Apenas dorme por 30s. 
    sleep(30)
}
