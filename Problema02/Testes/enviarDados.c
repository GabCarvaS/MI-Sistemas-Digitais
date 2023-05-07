#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdbool.h>
#include <lcd.h>
 
#define PA9 22

int main()
{
    int fd;
    if(wiringPiSetup() < 0)return 1;
    if((fd = serialOpen("/dev/ttyS3",9600)) < 0)return 1;
    printf("serial test start ...\n");
    serialPutchar(fd, 0x01);
    bool resposta = true;
    //pinMode(PA9,OUTPUT); //led

    while(resposta)
    {
        while(serialDataAvail (fd))
        {
            printf ("%c", serialGetchar (fd));
            digitalWrite(PA9, 1);
            delay(1000);
            fflush (stdout) ;
            resposta = false;
        }
        
    }
    digitalWrite(PA9,0);
    printf("\nComunicação fechada! \n");
    serialClose(fd);
    return 0;
}