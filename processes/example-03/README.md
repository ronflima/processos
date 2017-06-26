# Exemplo 3: Exaurindo a tabela de processos

Este exemplo foi escrito em C por questão de simplicidade. Para compilar é
necessário seguir o passo-a-passo:

- certifique-se que você tem instalado no seu sistema um compilador C.
- execute o shell script _configure_. Este script é gerado pelos autotools e
  será responsável por gerar os makefiles.
- execute: `make -j 4` para construir o executável.

O executável _example-03_ estará na raiz do código-fonte. Basta executá-lo para
ver a estrutura de processos criados usando o comando _ps_.

Este programa causará a exaustão da tabela de processos ao criar processos-filho
em demasia. Você será incapaz de iniciar qualquer outro processo no seu sistema
enquanto este programa estiver em execução. Depois de um tempo, o programa
finaliza e libera a tabela de processos.

O princípio usado aqui é o mesmo do exemplo 2, ou seja, o processo-pai ignora o
retorno dos processos-filhos, mantendo-os ativos na tabela de processos como
zumbis. Aqui demonstra-se como um bug no seu software pode causar a exaustão da
tabela de processos, colocando todo o sistema em xeque.

Em um sistema de produção, a quantidade de processos que podem ser criados devem
ser, necessariamente, limitados. Assim, evita-se que bugs ou até mesmos ataques
externos tornem seu servidor inacessível.
