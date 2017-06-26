# Parte I: Processos

O processo é uma abstração do sistema operacional que representa um programa
arbitrário em execução. O processo pode conter:

- descritores de arquivo, que referem-se aos arquivos abertos pelo programa;
- arenas de memória, se o programa solicitou mais memória do sistema
  operacional;
- código executável;
- dados e texto.

É importante destacar que os conceitos apresentados aqui aplicam-se a sistemas
unix e unix-like, incluindo-se os sistemas da Apple (macOS, iOS, tvOS e watchOS)
e sistemas de código aberto como o Linux e sistemas baseados no kernel Unix BSD
e sistemas unix baseados nos kernels AT&T.

## Como os processos são organizados

Os sistemas baseados em Unix normalmente organizam os processos em
hierarquias. Cada processo recebe dois número que o identificam ao sistema:

- PID, ou _process identification_, que identifica univocamente um processo;
- PPID, ou _parent process identification_, que identifica univocamente o
processo-pai.

O número do PID é um número inteiro e é gerado em uma lista circular, ou seja,
os números são reaproveitados. A ideia é permitir que uma instância de uma
imagem, o seu programa, seja identificada enquanto está em execução.

Essa instância comunica-se com o kernel através de _chamadas de sistema_ e
_sinais_. As chamadas de sistema são invocadas pelo seu programa no intuito de
realizar alguma tarefa, como obter mais memória, comunicar-se com o mundo
externo através de _sockets_ TCP ou abrir um arquivo. Os sinais são eventos que
ocorrem no sistema que precisam ser entregues ao seu processo para que o seu
processo tome alguma medida.

Os sinais são de vital importância para a correta integração do seu software com
o sistema operacional. Normalmente, o seu processo recebe sinais quando:

- um processo-filho está retornando, no intuito de propiciar ao processo-pai a
oportunidade de sincronizar-se e obter o status de retorno do processo-filho;
- o sistema operacional recebeu ordem para desligar e sinaliza seu processo que
isto está acontecendo;
- o seu processo faz alguma bobagem com a memória e corrompe a própria
  pilha. Neste caso o sistema operacional informa ao seu processo, através de
  sinais, que seu processo fez uma bobabem com a memória e precisa ser
  finalizado.
- algum processo arbitrário e com autorização para tal envia um sinal para o seu
  processo no intuito de solicitar alguma coisa: finalização, reinício, término
  forçado, etc.

Um processo pode criar quantos processos quiser. O processo criado por um
processo é chamado de processo-filho. O processo-filho, além do seu PID, também
recebe o PPID que é, necessariamente, o PID do processo-pai.

Todo processo tem sempre um processo-pai associado a ele. Isto é efeito da forma
como os sistemas Unix funcionam. Quando você executa alguma coisa no shell, o
PPID do processo disparado será, necessariamente, o PID do shell em execução. Os
processos de mais baixo nível todos têm no processo de inicialização do Unix, o
_init_, o seu pai. Por exemplo, os _daemons_ iniciados em _boot time_ são todos
filhos do _init_.

## Processos zumbis e adoção de processos

Quando um processo dispara processos-filhos, é necessário que este realize o
sincronismo quando o processo-filho retornar. Se não for feito o sincronismo,
ocorre o que se chama de _processo zumbi_. O processo zumbi não ocupa memória,
não consome arquivos, não ocupa espaço em disco, mas ocupa a tabela de
processos, segurando o número do seu PID.

Sempre que um processo filho finaliza sua execução, ele envia ao processo pai um
sinal chamado _SIGCLD_, que indica que o mesmo está retornando. É nesta
oportunidade que o processo-pai precisa sincronizar-se com o processo-filho para
que ele libere a tabela de processos. É importante ter em mente que a tabela de
processos do sistema operacional é um recurso finito. Se a tabela de processos
encher, não será mais possível executar absolutamente nada no seu sistema
operacional. Esta é uma característica construtiva do Unix.

Mas, e se o processo-pai finalizar sua execução antes de sincronizar com todos
os processos-filhos? Neste caso, ocorre um fenômeno que é chamado de _adoção de
processos_. O sistema de inicialização, ou _processo init_, adota os processos
órfãos e sincroniza-se com eles para evitar que surjam zumbis no sistema.

# Prática

Mostre-me o código pelo amor de Deus!

- [Demonstração de um processo criando processos-filhos e sincronizando-os.](example-01)
- [Demonstração de um gerador de zumbis](example-02)
- [Demonstração de um programa que exaure a tabela de processos.](example-03)
- [Como criar sub-processos com Swift](example-04)
