#include<Wire.h>
#include <Adafruit_GFX.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(D6,D5); // RX, TX 
// connect yellow wire to D5 and White wire to D6

unsigned char data[4]={};
float distance;
void setup()
{
 Serial.begin(115200);
 mySerial.begin(9600); 
  delay(1000);
}

void loop()
{
    do{
     for(int i=0;i<4;i++)
     {
       data[i]=mySerial.read();
     }
  }while(mySerial.read()==0xff);

  mySerial.flush();

  if(data[0]==0xff)
    {
      int sum;
      sum=(data[0]+data[1]+data[2])&0x00FF;
      if(sum==data[3])
      {
        distance=(data[1]<<8)+data[2];
         distance=distance / 10;
  Serial.println(distance);
      }
     }
     delay(100);
}




/*
For Arduino
#include <Adafruit_GFX.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(11,10); // RX, TX 
// connect yellow wire to D10 and White wire to D11

unsigned char data[4]={};
float distance;
void setup()
{
 Serial.begin(115200);
 mySerial.begin(9600); 
  delay(1000);
}

void loop()
{
    do{
     for(int i=0;i<4;i++)
     {
       data[i]=mySerial.read();
     }
  }while(mySerial.read()==0xff);

  mySerial.flush();

  if(data[0]==0xff)
    {
      int sum;
      sum=(data[0]+data[1]+data[2])&0x00FF;
      if(sum==data[3])
      {
        distance=(data[1]<<8)+data[2];
         distance=distance / 10;
  Serial.println(distance);
      }
     }
     delay(100);
}
*/
