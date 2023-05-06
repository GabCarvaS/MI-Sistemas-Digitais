#include <stdio.h>
#include <wiringPi.h>

#define PA9 22

int main (void)
{
    wiringPiSetup();
    pinMode(PA9, OUTPUT);
    while(1){
        // Liga
        digitalWrite(PA9, 1); 
        // Espera   
        delay(1000);
        // Desliga
        digitalWrite(PA9, 0);
        // Espera
        delay(1000);
    }
    return 0;
}