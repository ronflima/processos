# Exemplo 1: threads em user space

Este exemplo, escrito em C, dá uma dimensão do quanto é difícil escrever um
programa multi-thread com threads em user space. O programa usa _jumps_ para
troca de contexto. Antes de cada jump, o estado da pilha é salvo e o contexto de
destino tem sua pilha restaurada.

Usou-se a [libdill](https://github.com/sustrik/libdill) para demonstrar o uso de
threads em user space. A criação de um scheduler, por mais simples que seja, é
uma tarefa suficientemente complexa para tornar esta apresentação um projeto por
si só. Por este motivo optou-se por usar a libdill para demonstrar o conceito.

## Benefícios

O principal benefício da thread em user space, ou co-rotina, é a falta de
necessidade de realizar o sincronismo entre duas ou mais threads. É garantido
que uma estrutura de dados será acessada por uma, e somente uma, thread por
vez. Dado que a troca de contexto é previsível, não há por que haver sincronismo
entre threads neste caso.

Um fato inescapável é que a troca de contextos em user space é muito mais
eficiente do que a troca de contextos em kernel space. A libdill é capaz de
realizar uma troca de contexto em um tempo típico de 6ns. Em um linux,
dependendo do processador, a troca de contexto pode demorar um tempo típico de
50ns ou mais.

# Malefícios

Nem tudo são flores. É muito complicado criar um scheduler para trabalhar em
user space. Além disso, qualquer thread que bloqueie o processamento por tempo
indeterminado irá bloquear todas as outras. É preciso, por exemplo, criar
wrappers para todas as chamadas de sistema que podem bloquear uma rotina, para
que estas chamadas sejam realizadas de forma a não bloquear. Isso pode levar a
uma incompatibilidade em sistemas nos quais não há forma de não haver chamadas
assíncronas.
