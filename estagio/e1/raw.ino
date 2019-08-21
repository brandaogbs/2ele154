/**
  ******************************************************************************
  * @file    lab1.ino
  * @brief   Experimento de acionamento de rele, transistor como 
  *          chave e display 7 segmentos.
  * @authors 
  ******************************************************************************
  */

/******************************************************************************
 *                              INCLUDES
 ******************************************************************************/
 #include <Arduino.h>

/******************************************************************************
 *                              DEFINES
 ******************************************************************************/

#define PIN_BUTTON 3
// #1.  TODO: Defina a constante do pino do LED13

#define PIN_A 5
#define PIN_B 6
#define PIN_C 7
#define PIN_D 8
#define PIN_E 9
#define PIN_F 10
#define PIN_G 11

/******************************************************************************
 *                              PRIVATE VARIABLES
 ******************************************************************************/
// #1.  TODO: Defina constante de tempo para ser utilizada no delay em msm 
const int delay_ms = 10;

/******************************************************************************
 *                         PRIVATE FUNCTIONS PROTOTYPE
 ******************************************************************************/
// Debug
void debugLD(int);


// Botao
int isButtonPressed();

// Rele
void setLightOn();
void setLightOff();


// Display
void setDisplayOff();
void setDisplayCount();
void setDisplayDigit(int digit);


/******************************************************************************
 *                              PRIVATE USER CODE
 ******************************************************************************/

/**
  * @brief  Inicializacao dos perifericos e das entradas e saidas utilizadas.
  * @param  None
  * @retval None
  */
void setup() 
{  
  // 2#. TODO: Inicializar o LD13    

  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_C, OUTPUT);
  pinMode(PIN_D, OUTPUT);
  pinMode(PIN_E, OUTPUT);
  pinMode(PIN_F, OUTPUT);
  pinMode(PIN_G, OUTPUT);

}

/**
  * @brief Loop embarcado.
  * @param  None
  * @retval None
  */
void loop() 
{
    debugLD(delay_ms);
}



/******************************************************************************
 *                                   DEBUG
 ******************************************************************************/

// #3. TODO: Fazer cabecalho da funcao que pisca o LD13
/**
  * @brief  O que essa função faz?
  * @param  Quais os parametros de entrada?
  * @retval Qual o retorno?
  */
void debugLD(int delay_ms)
{
    // 4#. TODO: Implementar uma funcao que pisque o LD13 conforme o tempo_ms.
    // Utilize a funcao 'delay()' e 'digitalWrite()'
}



/******************************************************************************
 *                                   BOTAO
 ******************************************************************************/
/**
  * @brief  Verifica se o botao esta pressionado
  * @param  None
  * @retval int: estado do botao: 1- pressionado e 0- caso contrario
  */
int isButtonPressed()
{
    return 0;
}

/******************************************************************************
 *                                   RELE
 ******************************************************************************/

/**
  * @brief  Aciona a lampada atraves do acionamento digital do rele
  * @param  None
  * @retval None 
  */
void setLightOn()
{

}

/**
  * @brief  Desliga a lampada atraves do acionamento digital do rele
  * @param  None
  * @retval None 
  */
void setLightOff()
{

}


/******************************************************************************
 *                                   DISPLAY
 ******************************************************************************/

/**
  * @brief  Realiza o acionamento do display 7seg conforme a entrada.
  * @param  digit: um inteiro de 0-9.
  * @retval None
  */
void setDisplayDigit(int digit)
{
    if(digit != 1 && digit != 4)
    digitalWrite(PIN_A,HIGH);

    if(digit != 5 && digit != 6)
    digitalWrite(PIN_B,HIGH);

    if(digit != 2)
    digitalWrite(PIN_C,HIGH);

    if(digit != 1 && digit != 4 && digit != 7)
    digitalWrite(PIN_D,HIGH);

    if(digit == 2 || digit == 6 || digit == 8 || digit == 0)
    digitalWrite(PIN_E,HIGH);

    if(digit != 1 && digit != 2 && digit != 3 && digit != 7)
    digitalWrite(PIN_F,HIGH);

    if (digit != 0 && digit != 1 && digit != 7)
    digitalWrite(PIN_G,HIGH);
}

/**
  * @brief  Desliga individualmente todos os LEDs do display 7seg
  * @param  None
  * @retval None
  */
void setDisplayOff()
{
}

/**
  * @brief  Realiza o acionamento do display de forma a exibir uma
  *         contagem crescente de 0-9
  * @param  None
  * @retval None
  */
void setDisplayCount()
{
}
