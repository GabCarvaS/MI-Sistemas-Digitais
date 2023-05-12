#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdbool.h>
#include <lcd.h>
#include <stdlib.h>
#include <string.h>


/* Definindo os valores de Nodes */
#define todasNodes 0b100010 //34
#define Node01 0b00100011 // 35
#define Node02 0b00100100
#define Node03 0b00100101
#define Node04 0b00100110
#define Node05 0b00100111
#define Node06 0b00101000
#define Node07 0b00101001
#define Node08 0b00101010
#define Node09 0b00101011
#define Node10 0b00101100
#define Node11 0b00101101
#define Node12 0b00101110
#define Node13 0b00101111
#define Node14 0b00110000
#define Node15 0b00110001
#define Node16 0b00110010
#define Node17 0b00110011
#define Node18 0b00110100
#define Node19 0b00110101
#define Node20 0b00110110
#define Node21 0b00110111
#define Node22 0b00111000
#define Node23 0b00111001
#define Node24 0b00111010
#define Node25 0b00111011
#define Node26 0b00111100
#define Node27 0b00111101
#define Node28 0b00111110
#define Node29 0b00111111
#define Node30 0b01000000
#define Node31 0b01000001
#define Node32 0b01000010 // 66

/* Definindo os valores de Comandos */
#define situacaoSensor  0b00000001 // 01
#define entradaAnalogica  0b00010001 //17
#define entradaDigital0  0b00010010 //18
#define entradaDigital1  0b00010011
#define entradaDigital2  0b00010100
#define entradaDigital3  0b00010101
#define entradaDigital4  0b00010110
#define entradaDigital5  0b00010111
#define entradaDigital6  0b00011000
#define entradaDigital7  0b00011001
#define entradaDigital8  0b00011010
#define entradaDigital9  0b00011011
#define entradaDigital10  0b00011100
#define entradaDigital11  0b00011101
#define entradaDigital12  0b00011110
#define entradaDigital13  0b00011111 //31
#define acenderLed  0b00100001 // 33

/* Definindo os valores de Respostas */
#define	problemaNode 0b00000001 // 1
#define okNode 0b00000010 // 2
#define estadoSensorDigital 0b00010010 // 18

/* LED's */
#define PA8 20
#define PA9 22 

/* LCD */
#define LCD_D4 21
#define LCD_D5 24
#define LCD_D6 26
#define LCD_D7 27
#define LCD_E  18
#define LCD_RS 13

/* Botões do Menu */
#define B1 25
#define B2 23
#define B3 19

/* Funções */
void showDisplaySup(char dados[], int lcd);
void showDisplayInf(char dados[], int lcd);
void send(char dados, int fd);
unsigned char read(int fd);

int main()
{
    /* Configura os botões */
    pinMode(B1,INPUT); // ok
    pinMode(B2,INPUT); // anterior
    pinMode(B3,INPUT); // proximo

    /* Configura os leds */
    pinMode(PA8,OUTPUT);
    pinMode(PA9,OUTPUT);

    /* Configura pinos do LCD */
    pinMode(LCD_D4, OUTPUT); 
    pinMode(LCD_D5, OUTPUT); 
    pinMode(LCD_D6, OUTPUT); 
    pinMode(LCD_D7, OUTPUT); 
    pinMode(LCD_E, OUTPUT); 
    pinMode(LCD_RS, OUTPUT);  

    /* Inicializa Display*/
    int lcd;
    lcd = lcdInit (2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);

    int fd;
    int comandoCont = 0, nodeCont=0;
    char unidade[16];
    char comandos[3][20];
    char menu[3][20];

    /* Desliga os leds */
    digitalWrite(PA8, 0);
    digitalWrite(PA9, 0);

    // opções do menu
    strcpy(menu[0], "Selecionar Node");
    strcpy(menu[1], "Op 02");
    strcpy(menu[2], "OP 03");

    // comandos
    strcpy(comandos[0], "Ler sensor digital");
    strcpy(comandos[1], "Ler sensor analogico");
    strcpy(comandos[2], "Acender LED");

    if(wiringPiSetup() < 0){
        printf("Unable to start wiringPi");
        return 1 ;
    }
    if((fd = serialOpen("/dev/ttyS3",9600)) < 0){
        printf("Unable to open serial device");
        return 1 ;
    }

    printf("Iniciando ...\n");
    lcdClear(lcd);
    showDisplaySup("PBL 02", lcd);
    showDisplayInf("Sist. Digitais",lcd);
    delay(2000);
    lcdClear(lcd);

    while(1){
        sprintf(unidade,"%d", nodeCont);
        showDisplaySup("Escolha uma Node: ", lcd);
        showDisplayInf(unidade, lcd);
        delay(500);
        if(digitalRead(B1) == LOW){ // ok
                switch(nodeCont){
                    case 0:
                        lcdClear(lcd);                
                        while(1){    
                            showDisplaySup("Comando: ",lcd); 
                            showDisplayInf(comandos[comandoCont],lcd); 
                            delay(500);                     
                            if(digitalRead(B2) == LOW){ // prox
                                comandoCont++;
                                if(comandoCont > 2){
                                    comandoCont = 2;
                                }
                                lcdClear(lcd);
                            }
                            else if(digitalRead(B3) == LOW){ // anterior
                                comandoCont--;
                                if(cont < 0){
                                    comandoCont = 0;
                                }
                                lcdClear(lcd);
                            }
                            else if(digitalRead(B1) == LOW){ // ok
                                switch(comandoCont){
                                    case 0:
                                        lcdClear(lcd);
                                        showDisplaySup("primeira opc",lcd);
                                        delay(2000);
                                        lcdClear(lcd);
                                        break;
                                    case 1:
                                        lcdClear(lcd);
                                        showDisplaySup("segunda opc",lcd);
                                        delay(2000);
                                        lcdClear(lcd);
                                        break;
                                    case 2:
                                        lcdClear(lcd);
                                        showDisplaySup(comandos[cont],lcd);
                                        send(acenderLed,fd);
                                        delay(1000);
                                        lcdClear(lcd);
                                        break;
                                }
                            }
                        }
                        delay(2000);
                        lcdClear(lcd);
                        break;
                    case 1:
                        lcdClear(lcd);
                        sprintf(unidade, "%d", nodeCont);
                        showDisplaySup(unidade,lcd);
                        delay(2000);
                        lcdClear(lcd);
                        break;
                    case 2:
                        lcdClear(lcd);
                        sprintf(unidade, "%d", nodeCont);
                        showDisplaySup(unidade,lcd);
                        delay(2000);
                        lcdClear(lcd);
                        break;
                }
        }  
        else if(digitalRead(B2)== LOW){ // anterior
            nodeCont--;
            if(nodeCont < 0){
                nodeCont = 0;
            }
            lcdClear(lcd);
        }
        else if(digitalRead(B3)== LOW){ // proximo
            nodeCont++;
            if(nodeCont > 31){
                nodeCont = 0;
            }
            lcdClear(lcd);
        }
    }
    return 0;
}

void showDisplaySup(char dados[], int lcd){
    lcdPosition(lcd, 0, 0); // Seleciona a linha superior
    lcdPrintf(lcd, "%s", dados); // Mostra a msg
    return;
}

void showDisplayInf(char dados[], int lcd){
    lcdPosition(lcd, 0, 1);//Seleciona a linha inferior
    lcdPrintf(lcd, "%s", dados);// Mostra a msg
    return;
}

/* Função para enviar dados para a UART */
void send(char dados, int fd){
    char mensagem[30];
    // Envio do TX - Uart
    serialPutchar(fd, dados);
   
    //serialPrintf(fd,dados);// Testar
    
    sprintf(mensagem,"Enviando dados para a UART: %c",dados);

    printf("%s", mensagem);
    return;
}

/* Função para ler dados da UART + timeout 20ms */
unsigned char read(int fd){
    delay(20);
    if(serialDataAvail (fd) > 0)
    {
        msg = serialGetchar (fd);
        fflush (stdout);
        return msg;
    }       
    return '';
}