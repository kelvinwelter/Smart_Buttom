/**
**************************************************************************************************
* @file    smart_buttom.ino
* @author  Edson Jeske e Kelvin Welter / Gridya Tecnologia
* @brief   Smart Buttom usando Nanofox IoT.
* 
*     - Envia um sinal através da rede Sigfox quando pressionado um botão por 2 segundos
  *            
* License: Public Domain
**************************************************************************************************
*/


/*-----HEADER FILES--------------------------------------------------------------------------------*/
#include <Nanofox.h>   //Nanofox Library

/*------Global Variables---------------------------------------------------------------------------*/
uint16_t Counter_Sig = 0;        //Counter for testing 
unsigned long timeref_ms;        //Reference time for delay calculations

uint8_t Uplink_Buffer[12];    //Buffer for uplink Payload
uint8_t Downlink_Buffer[8];   //Buffer for Downlink Payload


/*------Objects -----------------------------------------------------------------------------------*/
Nanofox MyNanofox;    //Nanofox Object Instance

void setup() {

Serial.begin(9600);   //Initi Debug serial port

MyNanofox.Init_ArduinoNano_IO();  //Setup arduino Nano IO
MyNanofox.Init_Modem_WISOL(RC2);  //Initialize WISOL Sigfox Modem
Serial.println("Welcome to NANOFOX IoT Kit!");
Serial.println("Welcome to NANOFOX IoT Kit!");
Serial.println("Smartbuttom com Nanofox IoT");
Serial.println("Pressione o botão por 2 segundos para ativar");

timeref_ms = millis();  // Init time reference 
}

void loop() {

  delay(10);
  
  while(digitalRead(Buttom) == 0){
    
    Serial.println("Button pressed!");
    delay(2000);

    if(digitalRead(Buttom) == 0){
      MyNanofox.Send_Payload_Sigfox(&Uplink_Buffer[0],2,&Downlink_Buffer[0],0);
    }
    else{}
  }
}
