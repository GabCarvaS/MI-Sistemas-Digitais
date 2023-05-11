#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdbool.h>
#include <lcd.h>
#include <stdlib.h>
#include <string.h>


//........Nodes - Unidades........

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

//........Tabela 02 - Comandos........
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

//........Tabela 03 - Respostas........

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
void send(char dados[], int fd);
void read(int fd);

int main()
{
    wiringPiSetup(); 

    /* Configura os botões */
    pinMode(B1,INPUT); // ok
    pinMode(B2,INPUT); // anterior
    pinMode(B3,INPUT); // proximo

    /* Configura pinos do LCD */
    pinMode(LCD_D4, OUTPUT); 
    pinMode(LCD_D5, OUTPUT); 
    pinMode(LCD_D6, OUTPUT); 
    pinMode(LCD_D7, OUTPUT); 
    pinMode(LCD_E, OUTPUT); 
    pinMode(LCD_RS, OUTPUT); 
    pinMode(PA9, OUTPUT); 

    /* Inicializa Display*/
    int lcd;
    lcd = lcdInit (2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);

    int fd;
    int cont = 0;
    int unidade = 0;
    char unidadeEscolhida[];
    char option[];
    char options[3][20];

    // copia as strings para a matriz
    strcpy(options[0], "Ler sensor digital");
    strcpy(options[1], "Ler sensor analogico");
    strcpy(options[2], "Acender LED");

    if(wiringPiSetup() < 0)return 1;
    if((fd = serialOpen("/dev/ttyS3",9600)) < 0)return 1;

    printf("Iniciando ...\n");

    lcdClear(lcd);
    showDisplaySup("Menu", lcd);
    showDisplayInf("Escolha uma opção: ", lcd); //Alterar... primeiro escolhe a node, depois escolhe oq fazer na node
    delay(3000);
    lcdClear(lcd);
    while(1){
        //sprintf(option, "%s", options[cont]);
        //strcat(mensagem, nome);
        showDisplaySup("Escolha uma opção: ", lcd);
        showDisplayInf(options[cont], lcd);
        delay(500);
        if(digitalRead(B1) == LOW){ // ok
                switch(cont){
                    case 0:
                        lcdClear(lcd);
                        delay(1000);
                        showDisplaySup(options[cont]);
                        sprintf(unidadeEscolhida, "%d", unidade);
                        showDisplayInf();
                    case 1:

                    case 2:

                }
        }  
        else if(digitalRead(B2)== LOW){ // anterior
            if(cont <= 0){
                cont = 0;
            }
            else{
                cont--;
            }
        }
        else if(digitalRead(B3)== LOW){ // proximo
            if(cont >= 2){
                cont = 0;
            }
            else{
                cont++;
            }
        }
    }
    return 0;
}

void showDisplaySup(char dados[], int lcd){
    lcdPosition(lcd, 0, 0); // Seleciona a linha superior
    lcdPrintf(lcd, "%s", dados); // Mostra a msg
}

void showDisplayInf(char dados[], int lcd){
    lcdPosition(lcd, 0, 1);//Seleciona a linha inferior
    lcdPrintf(lcd, "%s", dados);// Mostra a msg
}

/* Função para enviar dados para a UART */
void send(char dados[], int fd){
    char mensagem[] = "Enviando dados para a UART: ";
    // Envio do TX - Uart
    serialPutchar(fd, dados);
   
    serialPrintf(fd,dados);// Testar
    
    //sprintf(mensagem,"Enviando dados para a UART: ",dados);
    strcat(mensagem, dados);
    printf("%s", mensagem);
}

/* Função para ler dados da UART */
unsigned char read(int fd){
    bool resposta = true;
    char msg[] = "";
    while(resposta)
    {
        while(serialDataAvail (fd))
        {
            msg = serialGetchar (fd);
            fflush (stdout);
            resposta = false;
        }       
    }
    return msg;
}