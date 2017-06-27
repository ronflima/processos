# Exemplo 1: threads em user space

Este exemplo, escrito em C, dá uma dimensão do quanto é difícil escrever um
programa multi-thread com threads em user space. O programa usa _jumps_ para
troca de contexto. Antes de cada jump, o estado da pilha é salvo e o contexto de
destino tem sua pilha restaurada.

O scheduler apresentado nada mais é que um rabisco feito com a intenção de
demonstrar a ideia. A [libdill](https://github.com/sustrik/libdill) é uma
biblioteca que implementa threads em user space. Trata-se de uma biblioteca
bastante complexa.

Mesmo em um exemplo feito para demonstrar o princípio, a implementação é
bastante complexa e difícil de entender. Por este motivo que threads em kernel
space são mais populares, ou seja, são mais simples de trabalhar.

