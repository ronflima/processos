# Exemplo 2: Threads em kernel space

Este exemplo, assim como o exemplo 1, é escrito em C para demonstrar como
funcionam as threads em kernel space em um nível um pouco mais baixo. O GCD da
Apple baseia-se nas threads POSIX, criando uma camada de abstração que
simplifica sobremaneira a forma de trabalhar com programação paralela.

Ao contrário do exemplo 1, aqui as coisas funcionam de forma imprevisível. Não é
possível saber quando haverá mudança de contexto, apesar de ser possível para
uma thread abrir mão de seu time sharing de forma cooperativa.

Pelo fato de ser assíncrono, invariantes compartilhadas precisam ser protegidas
em seções críticas, de forma que estejam sempre válidas durante todo o ciclo de
vida do programa.

## O programa

Trata-se de um programa extremamente simples: ele dispara duas threads que
dormem de forma independente no intuito de simular algum trabalho. Em teoria, a
primeira thread deverá retornar primeiro, ajustando uma invariante e, por fim,
notificando a main thread que retornou através de uma condition variable.

Observe a dificuldade em ajustar o invariante _stop_ em cada thread. É
necessário trabalhar com uma seção crítica para garantir que as alterações serão
atômicas. O _sleep_ pode ser interrompido espuriamente pela recepção de um
sinal, o que faria com que uma das threads acordasse involuntariamente. Como não
há como garantir quando cada thread irá trocar de contexto, são necessários o
sincronismo e a notificação via condition variable.

# Como construir o exemplo

Basta configurar a árvore de fontes e, por fim, compilar:

```shellscript
./configure
make
```
