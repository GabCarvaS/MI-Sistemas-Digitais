# Problema #1 – 2023.1 Linguagem Assembly

## Tópicos

:small_blue_diamond: [Descrição do Projeto](#descrição-do-projeto-e-requisitos)

:small_blue_diamond: [Ambiente de Desenvolvimento](#ambiente-de-desenvolvimento)

:small_blue_diamond: [Ambiente de Execução](#instalação-configuração-de-ambiente-e-execução)

:small_blue_diamond: [Funcionamento](#funcionamento)

:small_blue_diamond: [Testes e Resultados](#testes-e-resultados)

:small_blue_diamond: [Desenvolvedores](#desenvolvedores)

## Conteúdo

:heavy_check_mark: Códigos detalhadamente comentados;

:heavy_check_mark: Script de compilação tipo Makefile para geração do código executável;

:heavy_check_mark: Detalhamento dos software usados no trabalho, incluindo softwares básicos;

:heavy_check_mark: Arquitetura do computador usado nos testes.

## Descrição do Projeto e Requisitos

Este projeto consiste em uma solução desenvolvida em Assembly para a Orange Pi PC Plus.

O objetivo é desenvolver um aplicativo de temporização (timer) que apresente a contagem num display LCD 16x2. O tempo inicial deverá ser configurado diretamente no código. Além disso, deverão ser usados 2 botões de controle: 1 para iniciar/parar a contagem e outro para reiniciar a partir do tempo definido.

Com o objetivo de desenvolver uma biblioteca para uso futuro em conjunto com um programa em linguagem C, a função para enviar mensagem para o display deve estar separada como uma biblioteca (.o), e permitir no mínimo as seguinte operações: Limpar display; Escrever caractere; Posicionar cursor (linha e coluna).

O código deve ser escrito em Assembly, permitindo configurar o tempo de contagem e usando botões para controlar início/parada e reinício do temporizador.

## Ambiente de desenvolvimento

### Softwares utilizados para desenvolvimento e testes

A solução foi desenvolvida utilizando de editores de texto. Seja direto na placa ou o disponibilizado pelo próprio sistema operacional.

### Arquitetura do computador

Os computadores utilizados para desenvolvimento e testes foram os presentes no LEDS.

## Instalação, configuração de ambiente e execução

<>

## Execução e Testes

Para testar o sistema, basta compilar o código e executá-lo na Orange Pi. É possível usar um osciloscópio ou multímetro para verificar o funcionamento correto dos botões e da contagem de tempo.

## Funcionamento

O funcionamento do sistema consiste em: o usuário inicia a contagem pressionando o botão. Durante a contagem, o usuário pode pausar ou reiniciar o temporizador pressionando os botões correspondentes.

### Arquitetura

O sistema foi desenvolvido para a Orange Pi PC Plus, utilizando a arquitetura ARM v7. Para compilar o código, é necessário usar o utilitário Makefile, que está incluído no projeto.

### Descrição dos tipos de instruções utilizadas;

    - ADD
    - MOV
    - LDR
    - STR
    - CMP
    - B
    - BL
    - BGT
    - SVC
    - POP
    - PUSH
    - SUB
    - AND
    - LSL
    - LSR
    - BIC
    - ORR
    - BEQ
    - BLT
    - BX

#### ADD

ADD é uma instrução que executa a soma de valores que estão em registradores ou denifidos de forma imediata. A sintaxe é:

    ADD Rdestino, Rtermo1, Rtermo2
    ou
    ADD Rdestino, Rtermo1, #valorImediato

Onde, Rdestino é o registrador de destino. Rtermo1 é o registrador que contém o primeiro operando. Rtermo2 é um segundo operando e #valorImediato é qualquer valor no intervalo 0-4095.

#### MOV

A instrução MOV copia o valor de Operand2 em Rd. A sintaxe é:

    MOV Rd, Operand2
    ou
    MOV Rd, #valorImediato

Onde, Rd é o registrador de destino. Operand2 é um segundo operando e #valorImediato é qualquer valor no intervalo 0-65535.

#### LDR

A instrução LDR carrega um registrador com um valor da memória. A sintaxe é:

    LDR Rd, [Rn, Rm]

Onde, Rd especifica o registro a ser carregado. Rn especifica o registro no qual o endereço de memória é baseado. Rm especifica o registro que contém um valor a ser usado como deslocamento

#### STR

A instrução STR armazenam um valor de registro na memória. A sintaxe é:

    LDR Rd, [Rn, Rm]

Onde, Rd especifica o registro a ser armazenado. Rn especifica o registro no qual o endereço de memória é baseado. Rm especifica o registro que contém um valor a ser usado como deslocamento

#### CMP

A instrução CMP é uma instrução de comparação que compara dois valores e atualiza o registro de status (flag) do processador para refletir o resultado da comparação. A sintaxe é:

    CMP{cond} Rn, Operand2
    ou
    CMP{cond} Rn, #valorImediato

Onde, cond é um código de condição opcional. Rn é o registrador ARM contendo o primeiro operando. Operand2 é um segundo registrador. #valorImediato é qualquer valor no intervalo 0-255.

#### B

A instrução B causa um desvio incondicional para o rótulo criado. A sintaxe é:

     B label

Onde, label é um rótulo criado para marcar onde o programa continuará a execução depois do desvio.

#### BL

A instrução BL faz com que um desvio incondicional seja rotulado e copia o endereço da próxima instrução em LR (R14, o registrador de link). A sintaxe é:

     BL label

Onde, label é um rótulo criado para marcar onde o programa continuará a execução depois do desvio.

#### BGT

A instrução BGT causa um desvio condicional para o rótulo criado. A sintaxe é:

     B{cond} label

Onde, label é um rótulo criado para marcar onde o programa continuará a execução depois do desvio. GT (greater than) significa maior que. Desvia se o vaor do primeiro registrador for maior do que o valor do segundo registrador.

#### svc

A instrução SVC (Supervisor Call) é uma instrução usada em sistemas operacionais para fazer chamadas do sistema. A sintaxe é:

        SVC #valorImediato

Onde, #valorImediato é um valor imediato que identifica o serviço do sistema a ser chamado. A instrução SVC interrompe a execução do programa e transfere o controle para o sistema operacional, que então lida com a chamada do sistema

#### pop

A instrução POP é usada para retirar valores da pilha. A sintaxe é:

        POP {RlistaReg}

Onde, RlistaReg é uma lista separada por vírgulas de registradores a serem retirados da pilha. A instrução POP é útil para restaurar o estado dos registradores após um salvamento de estado usando a instrução PUSH.

#### push

A instrução PUSH é usada para colocar valores na pilha. A sintaxe é:

        PUSH {RlistaReg}

Onde, RlistaReg é uma lista separada por vírgulas de registradores a serem colocados na pilha. A instrução PUSH é útil para salvar o estado dos registradores antes de fazer uma chamada do sistema ou uma operação que possa modificar o estado dos registradores

#### SUB

SUB é uma instrução que executa a subtração de valores que estão em registradores ou denifidos de forma imediata. A sintaxe é:

        SUB Rdestino, Rtermo1, Rtermo2

Onde, Rdestino é o registrador de destino. Rtermo1 é o registrador que contém o primeiro operando e Rtermo2 é um segundo operando.

A instrução SUB subtrai o valor do registrador Rtermo2 ou o valor imediato do valor no registrador Rtermo1 e armazena o resultado no registrador de destino Rdestino. O resultado pode ser positivo, negativo ou zero. Caso o resultado seja negativo, a flag N (negativo) é ativada. Caso o resultado seja zero, a flag Z (zero) é ativada.

#### AND

AND é uma instrução lógica que faz a operação AND bit a bit entre dois registradores e armazena o resultado em um registrador de destino. A sintaxe é:

        AND Rdestino, Rtermo1, Rtermo2

Onde, Rdestino é o registrador de destino. Rtermo1 e Rtermo2 são os registradores que contém os operandos para a operação AND.

A instrução AND executa uma operação AND bit a bit entre os valores dos registradores Rtermo1 e Rtermo2 e armazena o resultado no registrador de destino Rdestino. O resultado final contém um bit '1' em cada posição em que ambos os operandos tenham um bit '1'.

#### LSL

LSL é uma instrução de deslocamento lógico à esquerda (Logical Shift Left) que desloca os bits de um valor de um registrador em uma determinada quantidade de posições para a esquerda. A sintaxe é:

        LSL Rdestino, Rfonte, #quantidade

Onde, Rdestino é o registrador de destino. Rfonte é o registrador que contém o valor a ser deslocado. #quantidade é a quantidade de posições que o valor deve ser deslocado.

A instrução LSL desloca o valor do registrador Rfonte em #quantidade de posições para a esquerda e armazena o resultado no registrador de destino Rdestino. Os bits que saem pela esquerda são perdidos, e os bits que entram na direita são preenchidos com zeros.

#### LSR

LSR é uma instrução de deslocamento lógico à direita (Logical Shift Right) que desloca os bits de um valor de um registrador em uma determinada quantidade de posições para a direita. A sintaxe é:

        LSR Rdestino, Rfonte, #quantidade

Onde, Rdestino é o registrador de destino. Rfonte é o registrador que contém o valor a ser deslocado. #quantidade é a quantidade de posições que o valor deve ser deslocado.

A instrução LSR desloca o valor do registrador Rfonte em #quantidade de posições para a direita e armazena o resultado no registrador de destino Rdestino. Os bits que saem pela direita são perdidos, e os bits que entram pela esquerda são preenchidos com zeros.

#### BIC

BIC é uma instrução lógica que executa uma operação bit a bit de "bit clear" (limpar bit). Ela limpa os bits de um registrador que correspondem a um segundo registrador (que age como máscara), armazenando o resultado em um terceiro registrador. A sintaxe é:

        BIC Rdestino, Rfonte, Rmascara

Onde, Rdestino é o registrador de destino. Rfonte é o registrador que contém o valor a ser limpo. Rmascara é o registrador que contém a máscara.

A instrução BIC executa uma operação bit a bit de "bit clear" entre os valores dos registradores Rfonte e Rmascara e armazena o resultado no registrador de destino Rdestino. Os bits no Rdestino são os mesmos que no Rfont

#### ORR

ORR é uma instrução lógica que executa uma operação bit a bit de "bitwise OR" (ou bit a bit) entre dois registradores e armazena o resultado em um terceiro registrador. A sintaxe é:

        ORR Rdestino, Rtermo1, Rtermo2

Onde, Rdestino é o registrador de destino. Rtermo1 e Rtermo2 são os registradores que contém os operandos para a operação OR.

A instrução ORR executa uma operação bit a bit de "bitwise OR" entre os valores dos registradores Rtermo1 e Rtermo2 e armazena o resultado no registrador de destino Rdestino. O resultado final contém um bit '1' em cada posição em que pelo menos um dos operandos tenha um bit '1'.

#### BEQ

BEQ é uma instrução de salto condicional (branch equal) que salta para um endereço de memória especificado se a última comparação (normalmente com a instrução CMP) indicar que dois valores são iguais. A sintaxe é:

        BEQ label

Onde, label é o rótulo da instrução para a qual o salto deve ser feito se a comparação for verdadeira.

A instrução BEQ salta para a instrução rotulada pelo label somente se a última comparação (normalmente com a instrução CMP) indicar que dois valores são iguais. Caso contrário, a execução continua com a próxima instrução após a instrução BEQ.

#### BLT

BLT é uma instrução de salto condicional (branch less than) que salta para um endereço de memória especificado se a última comparação (normalmente com a instrução CMP) indicar que o primeiro valor é menor que o segundo. A sintaxe é:

        BLT label

Onde, label é o rótulo da instrução para a qual o salto deve ser feito se a comparação for verdadeira.

A instrução BLT salta para a instrução rotulada pelo label somente se a última comparação (normalmente com a instrução CMP) indicar que o primeiro valor é menor que o segundo. Caso contrário, a execução continua com a próxima instrução após a instrução BLT.

#### BX

BX é uma instrução de salto que alterna o processador para executar código em um endereço de memória especificado. A sintaxe é:

        BX Rfonte

Onde, Rfonte é o registrador que contém o endereço de memória para o qual o processador deve saltar.

A instrução BX alterna o processador para executar código em um endereço de memória especificado pelo valor do registrador Rfonte. Isso é útil para implementar saltos para funções em código de assembly.

### Mapeamento de Pinos

Esta seção apresenta o mapeamento dos pinos de entrada/saída (GPIO) com as conexões do display utilizado no projeto. O mapeamento é essencial para garantir a correta comunicação entre o microcontrolador da GPIO e o display, possibilitando o correto funcionamento da interface de usuário.

#### Mapeamento dos Pinos da GPIO para o DISPLAY

O mapeamento entre a GPIO e o display LCD 16x2 no modo 4 bits é feito por meio da conexão de 7 pinos do microcontrolador com 7 pinos do display. Esses 7 pinos são divididos em 4 bits de dados e 3 bits de controle.

Os 4 bits de dados (D4 a D7) são responsáveis por enviar as informações que serão exibidas no display. Já os 3 bits de controle (RS, E e RW) são responsáveis por indicar ao display qual informação está sendo enviada (dados ou instruções), quando uma nova informação deve ser lida (sinal de enable) e se a operação será de escrita ou leitura (neste caso, o bit RW é configurado como leitura ou escrita).Neste contexto, o bit referente ao RW é sempre setado como escrita.

Para o mapeamento, são utilizados os pinos GPIO do microcontrolador, que são configurados como saídas e conectados aos pinos correspondentes no display.

O mapeamento apresentado na tabela abaixo é realizado por meio da identificação dos pinos do microcontrolador que serão utilizados e a correspondência com os pinos do display.

        | GPIO | DISPLAY |
        |------|---------|
        | 40   | D7      |
        | 38   | D6      |
        | 36   | D5      |
        | 32   | D4      |
        | 28   | E       |
        | 22   | RS      |
        | 20   | GND(RW) |

Os pinos do microcontrolador estão conectados aos pinos correspondentes do display para que seja possível exibir as informações corretamente.

## Testes e Resultados

<>

## Desenvolvedores

| [<img src="https://avatars.githubusercontent.com/u/58979991?v=4" width=115><br><sub>Gabriel Carvalho</sub>](https://github.com/GabCarvaS) | [<img src="https://avatars.githubusercontent.com/u/7541966?v=4" width=115><br><sub>Vinicius Vieira</sub>](https://github.com/vini-insight) | [<img src="https://avatars.githubusercontent.com/u/37885125?v=4" width=115><br><sub>Everton Bruno Silva dos Santos</sub>](https://github.com/evertonbrunosds) |
| :---------------------------------------------------------------------------------------------------------------------------------------: | :----------------------------------------------------------------------------------------------------------------------------------------: | :-----------------------------------------------------------------------------------------------------------------------------------------------------------: |
