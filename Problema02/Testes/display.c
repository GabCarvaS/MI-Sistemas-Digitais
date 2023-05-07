#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <lcd.h>

#define PA9 22 //LED

#define LCD_D4 21
#define LCD_D5 24
#define LCD_D6 26
#define LCD_D7 27
#define LCD_E  18
#define LCD_RS 13

int main (void)
{
    wiringPiSetup(); 
    pinMode(D0,INPUT);
    pinMode(LCD_D4, OUTPUT); 
    pinMode(LCD_D5, OUTPUT); 
    pinMode(LCD_D6, OUTPUT); 
    pinMode(LCD_D7, OUTPUT); 
    pinMode(LCD_E, OUTPUT); 
    pinMode(LCD_RS, OUTPUT); 
    pinMode(PA9, OUTPUT); 

    int lcd;
    lcd = lcdInit (2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);

    while(1){
        if(digitalRead(D0) == HIGH)
        {
            digitalWrite(led_pin, HIGH);
            char msg[] = "Sinal recebido";
            lcdPosition(lcd, 0, 0); // Seleciona a linha superior;
            lcdPrintf(lcd, "%s", msg); // Mostra a msg
        }
        else 
        {
            digitalWrite(led_pin, LOW);
            char msg[] = "Sem dados";
            lcdPosition(lcd, 0, 0); // Seleciona a linha superior;
            lcdPrintf(lcd, "%s", msg); // Mostra a msg
        }
        // Espera
        delay(1000);
    }
    return 0;
}
