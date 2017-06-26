# Threads

As _threads_ podem ser de dois tipos:

- **kernel space**: quem controla a thread é o sistema operacional. A principal
  vantagem deste tipo de thread é que o tempo de execução e a mudança de
  contexto da thread são automáticos, não necessitando de intervenção do
  programador para este fim. No entanto, por ser uma entidade do kernel, as
  threads em _kernel space_ tendem a ser mais caras que as threads em _user
  space_.
- **user space**: quem controla a thread é você, programador. O kernel ignora
  completamente a thread em _user space_ e não faz nenhuma assunção a este
  respeito. Quem precisa tomar conta do agendamento é o programador e isto nem
  sempre é uma tarefa simples. A principal vantagem é o custo consideravelmente
  menor que impõe ao sistema operacional. A principal desvantagem é que este
  modo do exige a cooperação explícita entre as threads para que possam mudar de
  contexto. Outro problema é a necessidade de criação de wrappers para chamadas
  de sistema que podem causar o bloqueio do processo.

Normalmente as threads em **user space** são conhecidas como fibras
(terminologia da Microsoft) ou co-rotinas. As fibras contam com apoio de todo um
run-time desenvolvido pela Microsoft para lhes dar suporte. Como a troca de
contexto é previsível, a programação de um software, de uma forma geral, acaba
ficando mais simples pois torna-se desnecessário realizar o sincronismo entre
diversas threads.

As threads em user space também apresentam uma limitação: por estarem confinadas
dentro de um processo, não conseguem tirar proveito de um sistema
multi-processado. Assim, todas as threads em user space acabam executando uma de
cada vez dentro do mesmo processador. O que as threads em user space fazem é,
basicamente, concorrência, e não paralelismo.

As threads em kernel space, por outro lado, conseguem tirar proveito de sistemas
multi-processados podendo, efetivamente, funcionar paralelamente. No entanto, é
preciso compreender a diferença entre concorrência e paralelismo.

# Concorrência x Paralelismo

Para entender a diferença dos dois conceitos, imagine que um determinado sistema
hipotético tenha apenas um único processador que conta com apenas um único
núcleo. Em um sistema como este, tanto threads em user space quanto threads em
kernel space serão _concorrentes_. Isto quer dizer que cada thread será
executada no processador, uma de cada vez. Como só há um único processador, não
é possível paralelizar os processos e, como consequência, também as threads.

Assim, tanto as threads quanto os processos concorrerão para executar no mesmo
processador. Este efeito é verificado, inclusive, em sistemas multi-processados
nos quais há mais processos e threads do que processadores disponíveis.

Se tivermos três threads A, B e C, o sistema operacional executará algunas
instruções de A por um tempo. Depois trocará o contexto e executará algumas
instruções de B, repetindo o processo com a thread C. A mudança de contexto é
tão rápida que tem-se a impressão que tudo acontece de forma paralela. Na
verdade, tudo se processará de forma serial.

O _paralelismo_ é conseguido quando uma ou mais threads em kernel space executam
cada uma em um processador diferente. Esta afirmativa é verdadeira quando cada
uma das threads ganha tempo para executar cada uma em um processador ou núcleo
diferente. Aqui as threads em kernel space diferenciam-se drasticamente das
threads em user space pois as primeiras serão capazes de usar vários
processadores enquanto as segundas não.

# Prática

Mostre-me o código! Os exemplos são simples. Os códigos em C demonstram o uso de
threads POSIX enquanto que os exemplos em Swift demonstram o uso da GCD para
obtenção de paralelismo. Um dos exemplos em C demonstra threads em user space e
a dificuldade que é a sua implementação. A troca de contexto é realizada através
do uso de rewind de pilha, obtido através de saltos incondicionais
não-locais. Este método é muito perigoso pois se a pilha não for devidamente
salva, haverá vazamento de memória.

- [Exemplo 1: Threads em user space](example-01)
- [Exemplo 2: Threads em kernel space](example-02)
- [Exemplo 3: Uso do GCD em Swift](example-03)
