![logo](img/nineteen-logo.png)

# Processos, Threads e Fibers

Este repositório é o material de apoio à palestra sobre processos, threads e
fibras. São apresentados textos com mais detalhamentos sobre o que foi
apresentado pela palestra.

## Por que processos e threads?

Apesar da computação comercial focar-se, basicamente, em resolver problemas de
negócio, é preciso compreender como os sistemas operacionais funcionam no
intuito de tirar o máximo proveito de suas características. O conhecimento sobre
processos e threads permitem ao programador desenhar melhor sua solução,
tornando-a mais tolerante à intempéries.

Todos os sistemas operacionais comerciais implementam algum tipo de
multi-processamento e multi-threading. O que muda é basicamente as APIs de
programação disponíveis aos programadores. No entanto, de nada adianta o
conhecimento das APIs sem que se conheça os conceitos sobre os quais as mesmas
foram construídas.

# Organização deste material

Este material foi organizado da mesma forma como a palestra, ou seja, em duas
partes à saber:

- [Processos](processes), o que são, como funcionam e o que é a concorrência.
- [Threads](threads), como funcionam e como são implementadas em kernel space e user space.

Os exemplos são apresentados através de duas linguagens diferentes: Linguagem C
e Swift. Escolheu-se a linguagem C para demonstrar o uso de system calls pela
facilidade com a qual a linguagem integra-se aos sistemas unix.

Os exemplos em C são compilados com o GCC em plataformas linux ou clang no
macOS. O código já tem tudo o que é preciso para compilar. Normalmente basta
executar o script de configuração `config` e depois executar `make` para
realizar a compilação.

Mais instruções estarão nos respectivos diretórios dos exemplos. 

A linguagem Swift foi utilizada no intuito de demonstrar como a Apple implementa
algumas facilidades através da sua biblioteca Foundation. Instruções de
compilação estarão disponíveis nos diretórios dos exemplos.

Os exemplos em swift podem ser compilados em Linux usando o Swift para
linux. [Veja aqui](https://swift.org/download/#using-downloads) como instalar o
compilador Swift no seu linux para poder executar os exemplos.

# Licença

Este material de apoio é distribuído sob a [licença MIT](LICENSE).
