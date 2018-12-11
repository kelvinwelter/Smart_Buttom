/**
**************************************************************************************************
* @file    smart_buttom.ino
* @author  Edson Jeske e Kelvin Welter / Gridya Tecnologia
* @brief   Smart Button using Nanofox IoT.
* 
*     - Sends a signal to Sigfox network when the button is pressed for more than 2 seconds
*            
* License: Public Domain
**************************************************************************************************
*/


/*-----HEADER FILES--------------------------------------------------------------------------------*/
#include <Nanofox.h>   //Nanofox Library

/*------Global Variables---------------------------------------------------------------------------*/
uint16_t Counter_Sig = 0;        // Counter for testing
unsigned long timeref_ms;        // Time reference to calculate delays

uint8_t Uplink_Buffer[12];    //Buffer for payload uplink
uint8_t Downlink_Buffer[8];   //Buffer for payload downlink


/*------Objects -----------------------------------------------------------------------------------*/
Nanofox MyNanofox;    //Nanofox Object Instance

void setup() {

Serial.begin(9600);   // Serial initialization

MyNanofox.Init_ArduinoNano_IO();  //Configuração do Arduino Nano IO
MyNanofox.Init_Modem_WISOL(RC2);  //Inicialização do WISOL Sigfox Modem
Serial.println("Welcome to NANOFOX IoT Kit!");
Serial.println("Smartbutton with Nanofox IoT");
Serial.println("Press the button for 2 seconds to activate");
pinMode(2, INPUT_PULLUP);

Uplink_Buffer[0] = 01;

timeref_ms = millis();  // Time reference initialization
}

void loop() {

  delay(10);
  
  while(digitalRead(2) == LOW){ // reading D2 Pin
    
    delay(2000); // 2 seconds delay to read the button again and confirm if it is pressed

    if(digitalRead(2) == LOW){ // If the button is pressed for more than 2 seconds, the Nanofox IoT sends a signal to Sigfox network
      Serial.println("Button pressed! Sending message to Sigfox network");  
      MyNanofox.Send_Payload_Sigfox(&Uplink_Buffer[0],1,&Downlink_Buffer[0],0);
    }
  }
}
