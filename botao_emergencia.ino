/*-----HEADER FILES--------------------------------------------------------------------------------*/
#include <Nanofox.h> //Nanofox Library

/*------Global Variables---------------------------------------------------------------------------*/
uint16_t Counter_Sig = 0;        //Counter for testing 
unsigned long timeref_ms;        //Reference time for delay calculations

uint8_t Uplink_Buffer[12];    //Buffer for uplink Payload
uint8_t Downlink_Buffer[8];   //Buffer for Downlink Payload

int buttomState = 0;

/*------Objects -----------------------------------------------------------------------------------*/
Nanofox MyNanofox;    //Nanofox Object Instance

void setup() {

  Serial.begin(9600);   //Initi Debug serial port

  pinMode(2, INPUT_PULLUP); //Botão
  
  MyNanofox.Init_ArduinoNano_IO();  //Setup arduino Nano IO
  MyNanofox.Init_Modem_WISOL(RC2);  //Initialize WISOL Sigfox Modem
  Serial.println("Welcome to NANOFOX IoT Kit!");
  Serial.println("Pressione e segure o botão por 2 segundos para enviar uma mensagem!");
  Serial.println("");
  MyNanofox.Print_PAC_WISOL();  //Prints Modem PAC Number in serial Debug
  MyNanofox.Print_DEVICE_ID_WISOL();  //Prints Modem Device ID in serial Debug
  
  digitalWrite(LED, HIGH); //Blink general use LED (LD1) 
  delay(2000);
  digitalWrite(LED, LOW);
  
  timeref_ms = millis();  // Init time reference 
}

void loop() {
    while(digitalRead(Buttom) == 0){ //Send Sigfox msg when button pressed
      delay(2000);
      if(digitalRead(Buttom) == 0){
        Serial.println("Botão de emergência pressionado");
    
        Uplink_Buffer[0] = Counter_Sig++;
        Uplink_Buffer[1] = Counter_Sig++;
    
        MyNanofox.Send_Payload_Sigfox(&Uplink_Buffer[0],2,&Downlink_Buffer[0],0);
      }
      else{
        Serial.println("Pressione o botão por pelo menos 2 segundos para enviar um sinal de emergência!");
      }
    }

    buttomState = digitalRead(2);
    while(buttomState == 0){
      delay(2000);
      if(buttomState == 0){
        Serial.println("Botão de emergência pressionado");
    
        Uplink_Buffer[0] = Counter_Sig++;
        Uplink_Buffer[1] = Counter_Sig++;
    
        MyNanofox.Send_Payload_Sigfox(&Uplink_Buffer[0],2,&Downlink_Buffer[0],0);
      }
      else{
        Serial.println("Pressione o botão por pelo menos 2 segundos para enviar um sinal de emergência!");
      }
    }
}
