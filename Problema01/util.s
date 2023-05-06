
switchLogicValuePin:
        LDR R2, [R0, #12]                       @ offset do registrador de dados do pino
        LDR R3, [R8, R2]                        @ referencia do registrador de dados do pino
        MOV R4, #1                              @ mascara de bits
        LSL R4, R7                              @ transporta o bit para a posicao correta do pino no registrador de dados
        CMP R1, #1                              @ compara valor de R1
        BEQ pinHIGH                             @ desvia se R1 é igual a 1
        BLT pinLOW                              @ desvia se R1 é menor que 1

pinHIGH:
        ORR R3, R4                              @ armazena no registrador de dados o bit que foi transportado
        STR R3, [R8, R2]                        @ atualiza na memoria novo valor do registrador de dados
        BX LR                                   @ faz o desvio

pinLOW:
        BIC R3, R4                              @ altera o bit que foi transportado no registrador de dados
        STR R3, [R8, R2]                        @ atualiza na memoria o valor do registrador de dados
        BX LR                                   @ faz o desvio

.macro sleep seconds nanoSeconds
        mov r7, #162                            @ define r7 como código da chamada do sistema (syscall) nanosleep
        ldr r0, =\seconds                       @ define r0 para tempo de espera em segundos
        ldr r1, =\nanoSeconds                   @ define r1 para tempo de espera em nano segundos
        svc 0                                   @ efetua chamada de sistema (syscall) para finalizar execução
.endm

.macro GPIOmap fileName pageSize baseAddress    @ macro de mapeamento GPIO
        LDR R0, =\fileName                      @ obtém nome de arquivo de mapeamento de memória virtual
        MOV R1, #2                              @ define R1 como somente leitura
        MOV R7, #5                              @ define R7 com código de abertura de arquivo
        SWI 0                                   @ efetua chamada de sistema
        MOV R4, R0                              @ salva descritor do arquivo
        MOV R0, #0                              @ define em nulo o endereço virtual, fazendo com que o linux escolha automaticamente
        LDR R1, =\pageSize                      @ define comprimento de paginação de arquivo
        MOV R2, #3                              @ define proteção de escrita
        MOV R3, #1                              @ define indicativo de que a memória é compartilhada
        LDR R5, =\baseAddress                   @ carrega o endereço do offset
        LDR R5, [R5]                            @ carrega o offset
        MOV R7, #192                            @ define R7 com código de mapeamento de memória
        SVC 0                                   @ efetua chamada de sistema
        ADD R8, R0, #0x800                      @ define a adição do offset exato para acesso aos pinos
.endm

.macro setGPIOinputPin pin                      @ define o pino da GPIO como modo de entrada
        LDR R0, =\pin                           @ lê o endereco de memoria de pino
        LDR R1, [R0, #0]                        @ offset do registrador de funcao do pino
        LDR R2, [R0, #4]                        @ offset do pino no registrador de funcao (LSB)
        LDR R5, [R8, R1]                        @ valor do registrador de dados do pino
        MOV R0, #0b111                          @ mascara de bits para limpar 3 bits
        LSL R0, R2                              @ transporta @111 para posicao do pino no registrador de funcao
        BIC R5, R0                              @ limpar os 3 bits da posicao
        STR R5, [R8, R1]                        @ atualiza na memoria o valor do registrador de funcao
.endm
@ faz backup dos valores contidos nos registradores r7 e r0        
.macro setGPIOoutputPin pin                     @ define o pino da GPIO como modo de saída
        ldr r0, =\pin                           @ lê o endereco de memoria de pino
        ldr r1, [r0, #0]                        @ offset do registrador de funcao do pino
        ldr r2, [r0, #4]                        @ offset do pino no registrador de funcao (LSB)
        ldr r5, [r8, r1]                        @ valor do registrador de dados do pino
        mov r0, #0b111                          @ mascara de bits para limpar 3 bits
        lsl r0, r2                              @ deslocamento em r0 com r2 vezes
        bic r5, r0                              @ limpa os 3 bits da posição
        mov r0, #1                              @ move 1 para r0
        lsl r0, r2                              @ deslocamento em r0 com r2 vezes
        orr r5, r0                              @ soma 1 na posicao que foi transportada
        str r5, [r8, r1]                        @ atualiza na memoria o valor do registrador de funcao
.endm

.macro GPIOpinLOW pin                           @ configura o pino com sinal baixo (zero)
        ldr r0, =\pin                           @ lê o endereco de memoria de pino
        ldr r2, [r0, #8]                        @ offset do pino no registrador de dados
        ldr r1, [r0, #12]                       @ offset do registrador de dados do pino
        ldr r5, [r8, r1]                        @ endereco base + registrador de dados
        mov r4, #1                              @ move 1 para r4
        lsl r4, r2                              @ transporta para r4, r2 vezes
        bic r3, r5, r4                          @ soma 1 na posicao que foi transportada
        str r3, [r8, r1]                        @ atualiza na memoria o valor do registrador de dados
.endm

.macro GPIOpinHIGH pin                          @ configura o pino com sinal alto (um)
        ldr r0, =\pin                           @ lê o endereco de memoria de pino
        ldr r2, [r0, #8]                        @ offset do pino no registrador de dados
        ldr r1, [r0, #12]                       @ offset do registrador de dados do pino
        ldr r5, [r8, r1]                        @ endereco base + registrador de dados
        mov r4, #1                              @ move 1 para r4
        lsl r4, r2                              @ transporta para r4, r2 vezes
        orr r3, r5, r4                          @ soma 1 na posicao que foi transportada
        str r3, [r8, r1]                        @ atualiza na memoria o valor do registrador de dados
.endm

.macro checkButton pin                          @ checa o valor lógico do botão no pino conectado ao botão e armazena este valor lógico em um registrador
        LDR R0, =\pin                           @ lê o endereco de memoria de pino
        LDR R2, [R0, #8]                        @ offset do pino no registrador de dados
        LDR R1, [R0, #12]                       @ offset do registrador de dados do pino
        LDR R3, [R8, R1]                        @ endereco base + registrador de dados
        MOV R4, #1                              @ move 1 para R4
        LSL R4, R2                              @ transporta para r4, r2 vezes
        AND R3, R4                              @ leitura do bit
        LSR R1, R3, R2                          @ transporte do bit para o LSB
.endm
@ fim do arquivo
