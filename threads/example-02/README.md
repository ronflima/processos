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
