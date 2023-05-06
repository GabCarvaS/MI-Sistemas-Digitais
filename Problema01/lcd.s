
@ este arquivo utiliza as macros previamente definidas no arquivo "util.s". os comentários dessas macros já está lá

.macro habilitarLCD                             @ executa os passos para habilitar LCD
        GPIOpinLOW PA18toENABLE
        sleep zeroSecond oneMILLIsecond
        GPIOpinHIGH PA18toENABLE
        sleep zeroSecond oneMILLIsecond
        GPIOpinLOW PA18toENABLE
.endm

.macro clearLCD                                 @ executa os passos para limpar LCD

        GPIOpinLOW PA2toRS

        GPIOpinLOW PG7toDB7
        GPIOpinLOW PG6toDB6
        GPIOpinLOW PG9toDB5
        GPIOpinLOW PG8toDB4
        habilitarLCD

        GPIOpinHIGH PG8toDB4
        habilitarLCD
.endm

.macro startLCD                         @ inicializa o display 16x2 LCD HD44780 de acordo com os passos informandos em sua Ficha de Dados (datasheet)

        setGPIOoutputPin PA2toRS
        setGPIOoutputPin PA18toENABLE
        setGPIOoutputPin PG7toDB7
        setGPIOoutputPin PG6toDB6
        setGPIOoutputPin PG6toDB6
        setGPIOoutputPin PG9toDB5
        setGPIOoutputPin PG8toDB4

        GPIOpinLOW PA2toRS

        GPIOpinLOW PG7toDB7
        GPIOpinLOW PG6toDB6
        GPIOpinHIGH PG9toDB5
        GPIOpinHIGH PG8toDB4
        habilitarLCD
        sleep zeroSecond, fiveMILLIseconds

        GPIOpinLOW PG7toDB7
        GPIOpinLOW PG6toDB6
        GPIOpinHIGH PG9toDB5
        GPIOpinHIGH PG8toDB4
        habilitarLCD
        sleep zeroSecond, micro150seconds

        GPIOpinLOW PG7toDB7
        GPIOpinLOW PG6toDB6
        GPIOpinHIGH PG9toDB5
        GPIOpinHIGH PG8toDB4
        habilitarLCD

        GPIOpinLOW PG7toDB7
        GPIOpinLOW PG6toDB6
        GPIOpinHIGH PG9toDB5
        GPIOpinLOW PG8toDB4
        habilitarLCD

        GPIOpinLOW PG7toDB7
        GPIOpinLOW PG6toDB6
        GPIOpinHIGH PG9toDB5
        GPIOpinLOW PG8toDB4
        habilitarLCD

        GPIOpinLOW PG7toDB7
        GPIOpinLOW PG6toDB6
        GPIOpinLOW PG9toDB5
        GPIOpinLOW PG8toDB4
        habilitarLCD

        habilitarLCD
        GPIOpinHIGH PG7toDB7
        GPIOpinLOW PG6toDB6
        GPIOpinLOW PG9toDB5
        GPIOpinLOW PG8toDB4
        habilitarLCD

        GPIOpinLOW PG7toDB7
        habilitarLCD

        GPIOpinHIGH PG8toDB4
        habilitarLCD

        GPIOpinLOW PG8toDB4
        habilitarLCD

        GPIOpinLOW PG7toDB7
        GPIOpinHIGH PG6toDB6
        GPIOpinHIGH PG9toDB5
        habilitarLCD

        GPIOpinLOW PG6toDB6
        GPIOpinLOW PG9toDB5
        habilitarLCD

        GPIOpinHIGH PG7toDB7
        GPIOpinHIGH PG6toDB6
        GPIOpinHIGH PG9toDB5
        habilitarLCD

        GPIOpinLOW PG7toDB7
        GPIOpinLOW PG6toDB6
        GPIOpinLOW PG9toDB5
        GPIOpinLOW PG8toDB4
        habilitarLCD

        GPIOpinLOW PG7toDB7
        GPIOpinHIGH PG6toDB6
        GPIOpinHIGH PG9toDB5
        GPIOpinLOW PG8toDB4
        habilitarLCD
        .ltorg
.endm

.macro prefixNumberLCD
        GPIOpinLOW PG7toDB7
        GPIOpinLOW PG6toDB6
        GPIOpinHIGH PG9toDB5
        GPIOpinHIGH PG8toDB4
        habilitarLCD
.endm

.macro writeLCD number          @ executa os passos para escrever no LCD
        GPIOpinHIGH PA2toRS
        prefixNumberLCD
        
        MOV R1, #0b00001        @ para DB4
        AND R1, \number         @ 0001 & 0011 -> 0001
        LDR R0, =PG8toDB4
        LDR R7, [R0, #8]
        BL switchLogicValuePin

        MOV R1, #0b00010        @ para DB5
        AND R1, \number         @ 0010 & 0011 -> 0010
        LSR R1, #1              @ Desloca o bit uma vez para direita  -> 0001
        LDR R0, =PG9toDB5
        LDR R7, [R0, #8]
        BL switchLogicValuePin
        
        MOV R1, #0b00100        @ para DB6
        AND R1, \number         @ 0100 & 0101 -> 0100
        LSR R1, #2              @ Desloca o bit duas vezes para direita  -> 0001
        LDR R0, =PG6toDB6
        LDR R7, [R0, #8]
        BL switchLogicValuePin
        
        MOV R1, #0b01000        @ para DB7
        AND R1, \number         @ 01000 & 01000 -> 01000
        LSR R1, #3              @ Desloca o bit três vezes para direita  -> 00001
        LDR R0, =PG7toDB7
        LDR R7, [R0, #8]
        BL switchLogicValuePin
        habilitarLCD
.endm
@ fim do arquivo
