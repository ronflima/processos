# Exemplo 3: Uso do GCD com Swift

Este exemplo demonstra o quanto o uso do GCD simplifica a criação de software
multi-threading. Como o GCD provê uma interface melhor e de mais alto nível, a
maioria das operações que foram executadas no exemplo C tornam-se desnecessárias
por serem tratadas pelo framework.

É importante, no entanto, ter em mente que o uso do GCD tem um custo: apesar de
ser muito otimizado, o GCD é menos eficiente que o uso de POSIX threads
diretamente. No entanto, é importante ter em mente que o overhead que as POSIX
threads causam em termos de escrita de código e o grande poder de processamento
dos processadores atuais fazem com que a ligeira diminuição na eficiência seja
desprezível.

# Como construir o exemplo

Este exemplo usa o `swift package manager`. Assim, é necessário usá-lo para
construir o executável:

```shellscript
swift build
```

O executável estará em `.build/debug/example-03`.
