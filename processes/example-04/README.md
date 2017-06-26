# Exemplo 4: Criando processos em Swift

A criação de processos em linguagem Swift não é tão trivial como ocorre com a
linguagem C. A Apple invalidou o uso do system call _fork_ em programas swift. A
justificativa são os problemas que a duplicação de um processo e a consequente
herança de recursos causa no biblioteca Foundation.

Para criar sub-processos em Swift é necessário usar a classe _Process_, classe
que cujo nome original era _NSTask_. A Apple implementa um serviço de
inicialização de daemons chamado XPC e estas classes foram projetadas para
integrarem-se a este sistema. Porém, o linux usa um sistema bem diferente, como
o System V e o upstart no caso do Ubuntu, o que tornam as integrações quase
desnecessárias nestes sistemas.

Porém, com pouco esforço é possível realizá-las. No exemplo a seguir há algumas
considerações interessantes:

- A criação do processo-filho necessariamente realiza a recarga da imagem do
  processo, o que não era observado com os exemplos anteriores. Isto é feito
  desta forma por que não é possível realizar uma chamada ao system call _fork_
  de dentro do swift. De certa forma isto é um pouco ineficiente pois exige a
  abertura, leitura e fechamento do arquivo executável sempre que um
  processo-filho é criado.
- É possível usar o subsistema de sinalização para capturar sinais. Isto é
  importante por que permite uma boa integração do sistema operacional com o
  processo. O exemplo, para efeito de simplicidade, usa _signal_ para isto. No
  entanto, num sistema de produção, é interessante usar _sigaction_. O problema
  de usar-se _sigaction_ está na implementação da Apple que esconde alguns
  campos de uma estrutura usada pela função através de macros. A linguagem Swift
  não compreende macros C e é preciso, neste caso, criar um wrapper em C para
  integra-se com o swift de maneira portável. Ou pode-se usar diretivas de
  compilação para este fim.
- O exemplo dispara um certo número de processos-filhos. Sempre que um processo
  filho é finalizado, o exemplo dispara um novo. Para finalizar o exemplo é
  necessário realizar o envio de um sinal da linha de comando:

```shellscript
kill -TERM 123
```

onde _123_ é o PID do processo-pai.

## Compilando

Para compilar o exemplo, basta executar o compilador swift:

```shellscript
swift build
```

O executável estará em `./.build/debug/example-04`.
