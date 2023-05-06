
@ abrir terminal na pasta do projeto e executar com o comando 'make'. precisa informar senha de usuário sudo.
@ outra alternativa é o comando 'sh run.sh'. também precisa informar senha de usuário sudo.
.include "util.s"
.include "lcd.s"
.global _start

_start:
        GPIOmap fileName, pageSize, baseAddress
        setGPIOinputPin PA7toStartButton
        setGPIOinputPin PA10toPauseButton
        setGPIOinputPin PA20toResetButton
        setGPIOoutputPin PA8toRedLED
        setGPIOoutputPin PA9toBlueLED
        .ltorg @ PARA CORRIGIR O ERRO: "Error: invalid literal constant: pool needs to be closer"
        startLCD
        GPIOpinLOW PA8toRedLED
        GPIOpinLOW PA9toBlueLED
        MOV R10, #9
        b startsIFpressButton

startsIFpressButton:
        checkButton PA7toStartButton            @ verifica se o botao de iniciar (PA7) foi pressionado
        CMP R1, #0
        BEQ while
        b startsIFpressButton

while:
        checkButton PA10toPauseButton           @ verifica se o botao de pausar (PA10) está pressionado
        CMP R1, #0
        BEQ pausesIFbuttonISpressed
        checkButton PA20toResetButton           @ verifica se o botao de reiniciar (PA20) está pressionado
        CMP R1, #0
        BEQ resetCountIFbuttonISpressed
        clearLCD
        writeLCD R10
        sleep oneSecond, zeroMILLIsecond
        SUB R10, R10, #1
        CMP R10, #-1
        BNE while        
        GPIOpinHIGH PA8toRedLED
        GPIOpinHIGH PA9toBlueLED
        b exit

pausesIFbuttonISpressed:
        sleep oneSecond, zeroMILLIsecond
        b while

resetCountIFbuttonISpressed:
        MOV R10, #9
        b while

exit:
        sleep oneSecond, zeroMILLIsecond        @ espera um segundo antes de finalizar execução
        GPIOpinLOW PA8toRedLED                  @ deixa LED vermelhor apagado para nao iniciar acesso na próxima execução
        clearLCD                                @ apaga também o LCD
        mov r7, #1
        mov r0, #0
        svc 0
@               As Labels seguintes tem QUATRO ".words":
@               VALORES PODEM ESTAR NO SISTEMA HEXADECIMAL (0xF) OU DECIMAIS (15).
@               primeira '.word' é o offset do registrador de função do pino (serve para alterar o modo do pino I/O)
@               segunda '.word' é o offset do pino no registrador de função (lsb, serve para identificar o tríade do pino)
@               terceira '.word' é o offset do pino no registrador de dados (serve para apontar a posição no registrador de dados)
@               quarta '.word' é o offset do registrador de dados do pino (serve para acessar o registrador de dados do pino)
.data
        PA7toStartButton:       @ pino PA7 da GPIO conectado a um botão de apertar (push button) para iniciar a contagem
                .word 0x0
                .word 0x1C
                .word 0x7
                .word 0x10
        PA10toPauseButton:      @ pino PA10 da GPIO conectado a um botão de apertar (push button) para pausar a contagem
                .word 0x4
                .word 0x8
                .word 0xA
                .word 0x10
        PA20toResetButton:      @ pino PA20 da GPIO conectado a um botão de apertar (push button) para reiniciar a contagem
                .word 0x8
                .word 0x10
                .word 0x14
                .word 0x10
        PA8toRedLED:            @ pino PA8 da GPIO conectado a um LED vermelho
                .word 0x4
                .word 0x0
                .word 0x8
                .word 0x10
        PA9toBlueLED:           @ pino PA9 da GPIO conectado a um LED azul
                .word 0x4
                .word 0x4
                .word 0x9
                .word 0x10        
        PA18toENABLE:           @ pino PA18 da GPIO conectado ao terminal ENABLE do LCD
                .word 0x8
                .word 0x8
                .word 0x12
                .word 0x10
        PA2toRS:                @ pino PA2 da GPIO conectado ao terminal RS do LCD
                .word 0x0
                .word 0x8
                .word 0x2
                .word 0x10
        PG6toDB6:               @ pino PG6 da GPIO conectado ao terminal DB6 do LCD
                .word 0xD8
                .word 0x18
                .word 0x6
                .word 0xE8
        PG7toDB7:               @ pino PG7 da GPIO conectado ao terminal DB7 do LCD
                .word 0xD8
                .word 0x1C
                .word 0x7
                .word 0xE8
        PG8toDB4:               @ pino PG8 da GPIO conectado ao terminal DB4 do LCD
                .word 0xDC
                .word 0x0
                .word 0x8
                .word 0xE8
        PG9toDB5:               @ pino PG9 da GPIO conectado ao terminal DB5 do LCD
                .word 0xDC
                .word 0x4
                .word 0x9
                .word 0xE8
        fileName: .asciz "/dev/mem"             @ Caminho do arquivo para mapeamento da memória virtual
        baseAddress: .word 0x1C20               @ Endereco base GPIO (encontrado no datasheet do allwinner h3) 0x01C20800 / 0x1000 (4096) = 0x1C20 @Endereço base do GPIO / 0x1000
        pageSize: .word 0x1000                  @ tamanho da página virtual
        micro150seconds: .word 150000
        fiveMILLIseconds: .word 5000000
        oneSecond: .word 1
        zeroSecond: .word 0
        oneMILLIsecond: .word 1000000
        zeroMILLIsecond: .word 0
@ fim do arquivo
