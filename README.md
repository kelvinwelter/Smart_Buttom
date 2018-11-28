# Tutorial para Smart Buttom usando Nanofox IoT

Essa página apresenta um passo a passo do procedimento necessário para realizar seu primeiro projeto Nanofox IoT: um Smart Buttom usando Nanofox IoT! 

## Recomendações:
- [Arduino IDE instalada no computador.](https://www.arduino.cc/en/Guide/HomePage)
- [Conta cadastrada na plataforma Tago.](https://tago.io/)
- [Ativação do kit Nanofox IoT.](https://github.com/Gridya/NANOFOX-Activate/blob/master/README.md)

## Aplicação do Projeto:
  O projeto trata-se de um tutorial para criar sua primeira aplicação usando Nanofox IoT: um Smart Buttom! Um Smart Buttom usando Nanofox IoT é algo que pode ser aplicado nas mais diversas situações. No nosso tutorial usaremos como exemplo um Smart Buttom que quando acionado, dispara um email através da plataforma Tago. Sinta-se livre para buscar outras aplicações após aprender como fazer um Smart Buttom através desse tutorial!

## Resumo das etapas:
  O nosso projeto será dividido em 4 etapas principais, além de etapas que não fazem parte do projeto em si mas que são necessárias para a execução de tal.
  
## Primeiro passo: Implementação do hardware
  Na nossa primeira etapa do projeto, iremos realizar a integração da placa Nanofox IoT com o botão. Faremos isso a partir do uso de um botão conectado no pino D2. O projeto será alimentado via USB mas pode ser alimentado por bateria também. Na imagem abaixo o esquemático está descrito junto da bateria, caso queira deixar seu projeto mais portátil, basta seguir o esquemático.
  
  [![1543442720432.png](https://i.postimg.cc/mDjwbqTb/1543442720432.png)](https://postimg.cc/njs723s5)
  
  A montagem é simples e pode ser feita rapidamente. Feita a montagem, pode-se ir para a próxima etapa: a programação.
  
## Segundo passo: Programação do firmware para o projeto
  Em nossa segunda etapa trabalharemos com programação dentro do Arduino IDE. O código fonte está disponibilizado para download aqui e também está disponível a seguir.
  ```
  /**
  **************************************************************************************************
  * @file    NANOFOX_Activate_v0.ino
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

uint8_t Uplink_Buffer[12];		//Buffer for uplink Payload
uint8_t Downlink_Buffer[8];		//Buffer for Downlink Payload


/*------Objects -----------------------------------------------------------------------------------*/
Nanofox MyNanofox;		//Nanofox Object Instance

void setup() {

  Serial.begin(9600);   //Initi Debug serial port
  
  MyNanofox.Init_ArduinoNano_IO(); 	//Setup arduino Nano IO
  MyNanofox.Init_Modem_WISOL(RC2);  //Initialize WISOL Sigfox Modem
  Serial.println("Welcome to NANOFOX IoT Kit!");
  Serial.println("Welcome to NANOFOX IoT Kit!");
  Serial.println("Smartbuttom com Nanofox IoT");
  Serial.println("Pressione o botão por 2 segundos para ativar");
  
  timeref_ms = millis();	// Init time reference 
}

void loop() {
  
	delay(10);
	
	if((millis() - timeref_ms) > 20000) //Prints PAC and Device ID every 20s
	{ 
		timeref_ms = millis(); //restart time reference
    
		MyNanofox.Print_PAC_WISOL();
		MyNanofox.Print_DEVICE_ID_WISOL();
	}
  
	if(digitalRead(Buttom) == 0) //Send Sigfox msg when button pressed
	{
		Serial.println("Button pressed!");
		
		MyNanofox.Send_Payload_Sigfox(&Uplink_Buffer[0],2,&Downlink_Buffer[0],0);
	} 
}
  ```
  Seguem algumas breves explicações sobre o código.
  #### Bibliotecas necessárias:
  Para nosso simples projeto, precisamos incluir apenas a biblioteca [Nanofox.h](https://github.com/Gridya/nanofox), que será necessária para a transmissão de dados para a rede Sigfox.
  #### Função Setup:
  Finalmente em nossa função setup, iniciaremos nossa lógica propriamente dita. Como necessitamos da leitura de um botão no nosso projeto devemos tratar o pino correspondente a esse botão como *input*, juntamente disso escolhemos o pino que usaremos para esse botão. Nesse caso, iremos escolher o pino D2. 
Além da nossa configuração necessária para o projeto, devemos adicionar mais algumas coisas como a configuração do Arduino Nano IO e a inicialização do Modem Sigfox WISOL. Além disso, no código fornecido configuramos algumas mensagens para serem mostradas no monitor serial, essa parte é totalmente opcional e o código funciona sem ela.
  #### Função Loop: 
  Temos agora a parte principal do código. Nosso loop trabalha da seguinte forma: o botão é constantemente lido, se caso o valor lido no botão saía de 1 e vá para 0, ou seja, o botão for apertado. Nosso código entra no while e confere a leitura do botão 2 segundos depois através do delay. Se o botão continua apertado, então é enviado um sinal para a rede Sigfox através de funções da biblioteca Nanofox. Caso o botão não continue apertado após esses dois segundos, o código trata tal fato como se fosse um aperto acidental e não toma nenhuma atitude além de enviar uma mensagem no monitor serial. 
  
## Terceiro passo: Integração da plataforma Tago com o Backend Sigfox
  Essa etapa é muito bem relatada e explicada a partir de um [tutorial escrito pela própria Tago](https://tago.elevio.help/en/articles/33). Nesse tutorial está relatado tanto a parte feita na plataforma Tago quanto a criação de Callbacks no Backend Sigfox para essa integração, tudo muito bem detalhado, vale a pena conferir.
  Após a conclusão de toda integração, podemos seguir para a última etapa.
  
## Quarto passo: Configuração para envio de e-mail via plataforma Tago
  Após concluída a integração da plataforma Tago com o backend Sigfox e antes de começarmos o código no Arduino IDE, temos mais um passo necessário na plataforma Tago: configurarmos a plataforma para enviar um e-mail de emergência. Para começarmos, acessaremos a opção **Action** no menu lateral da página de desenvolvedor na Tago. Após entrarmos em **Action**, clicamos no botão **Add Action** no canto superior direito. Assim, entramos em uma nova ação a ser criada. Na aba **General Information** damos um nome a nossa ação, escolhemos a ação a ser tomada (**Send Email**) e preenchemos com o destinatário, título e conteúdo do email. A configuração nessa aba deve ficar assim:
  
	[![general-information.png](https://i.postimg.cc/kXxqs3F1/general-information.png)](https://postimg.cc/3dJsrqqm)
  
  A seguir, precisamos ir para a aba **Trigger**, nessa aba iremos configurar quando a plataforma Tago deve enviar o e-mail. Queremos que ela envie sempre que um sinal Sigfox chegue na plataforma, portanto, devemos configurar a condição de acionamento da ação como **Any** e também devemos escolher uma variável que será monitorado para a condição de acionamento, no caso, escolheremos a variável **data**. Além disso, devemos **desativar a opção Lock trigger after action is taken**. Feito isso, a configuração deve ficar da seguinte maneira:
  
	[![trigger.png](https://i.postimg.cc/XY01jJXn/trigger.png)](https://postimg.cc/CzmsJwj2)
  
  Após isso, nossa ação já está pronta para ser salva e usada!
  

