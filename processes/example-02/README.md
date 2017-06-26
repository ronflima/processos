# Exemplo 2: Gerador de zumbis

Este exemplo foi escrito em C por questão de simplicidade. Para compilar é
necessário seguir o passo-a-passo:

- certifique-se que você tem instalado no seu sistema um compilador C.
- execute o shell script _configure_. Este script é gerado pelos autotools e
  será responsável por gerar os makefiles.
- execute: `make -j 4` para construir o executável.

O executável _example-02_ estará na raiz do código-fonte. Basta executá-lo para
ver a estrutura de processos criados usando o comando _ps_.

Ao contrário do exemplo 1, este programa cria os processos-filhos e simplesmente
ignora os seus retornos. Você poderá verificar os processos zumbis executando o
comando _ps_. Dependendo do seu sistema, os processos filhos aparecerão como
_defunct_ ou _zombie_ na lista de processos. No macOS, os processos zumbis serão
marcados com status **Z** na lista de processos.

O processo-pai, ao finalizar sem sincronizar-se com os processos zumbis que
criou, força a adoção dos processos zumbis pelo _init_, o que faz com que sejam,
finalmente, sincronizados, liberando a tabela de processos.
