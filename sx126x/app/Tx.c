#include "radio.h" 
#include "sx126x-board.h" 
#include "sx126x.h" 
#include <wiringPi.h> 
#include "stdio.h"

//#define DEBUG
#define LED 9

#define USE_MODEM_LORA

#define RF_FREQUENCY                                868000000 // Hz

#define LORA_BANDWIDTH                              2         // [0: 125 kHz,
                                                              //  1: 250 kHz,
                                                              //  2: 500 kHz,
                                                              //  3: Reserved]
#define LORA_SPREADING_FACTOR                       12        // [SF7..SF12]
#define LORA_CODINGRATE                             1         // [1: 4/5,
                                                              //  2: 4/6,
                                                              //  3: 4/7,
                                                              //  4: 4/8]
#define LORA_SYMBOL_TIMEOUT                         5         // Symbols
#define LORA_PREAMBLE_LENGTH                        8         // Same for Tx and Rx
#define LORA_FIX_LENGTH_PAYLOAD_ON                  false
#define LORA_IQ_INVERSION_ON                        false

#define TX_OUTPUT_POWER                             15
static RadioEvents_t RadioEvents;
void OnRxDone( uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr );
void OnTxDone(void);
void OnTxTimeout(void);
uint8_t packet[] = {'h','e','l','l','o'};

RadioStatus_t status;
uint16_t Interrupt;
RadioError_t error;

int main(){
  // put your setup code here, to run once:
  SX126xIoInit();
  pinMode(LED,OUTPUT);
  printf("Begin\r\n");
  
  printf("Sx126x Calibrate image \r\n");
  SX126xCalibrateImage(868000000);
  CalibrationParams_t calibParam;

  printf("sx126x Calibrate\r\n");
  calibParam.Value = 0x7F;
  SX126xCalibrate( calibParam );

  RadioEvents.TxDone = OnTxDone;
  RadioEvents.TxTimeout = OnTxTimeout;

  printf("Init event\r\n");
  Radio.Init( &RadioEvents );
  
  printf("set rf frequency \r\n");
  Radio.SetChannel( RF_FREQUENCY );
  //printf("Set rf frequency\r\n");

  printf ("set public network\r\n");
  Radio.SetPublicNetwork(true);
  /*
  printf ("set Tx Config\r\n");
  Radio.SetTxConfig( MODEM_LORA, TX_OUTPUT_POWER, 0, LORA_BANDWIDTH,
                                   LORA_SPREADING_FACTOR, LORA_CODINGRATE,
                                   LORA_PREAMBLE_LENGTH, LORA_FIX_LENGTH_PAYLOAD_ON,
                                   true, 0, 0, LORA_IQ_INVERSION_ON, 3000000 );
  //printf("Set Tx config\r\n");

  SX126xSetDio2AsRfSwitchCtrl(true);

  printf ("Send\r\n");
  Radio.Send(packet,5);
*/
  SX126xSetDio2AsRfSwitchCtrl(true);
  Radio.SetTxContinuousWave(RF_FREQUENCY, TX_OUTPUT_POWER, 10);
  
  //printf("Sent\r\n");
  while(1)
  {
    Interrupt = SX126xGetIrqStatus();
    printf("interrupt in main :%#02x\r\n",Interrupt);
    error = SX126xGetDeviceErrors();
    printf("device error : %#02x\r\n", error.Value);
    delay(2000);
  }
}
  
void OnTxDone(void)
{
  digitalWrite(LED,HIGH);
  delay(2000);
  printf("tx finish\r\n");
  Radio.Send(packet,5);
  digitalWrite(LED,LOW);
}

void OnTxTimeout()
{
  printf("tx timeout\r\n");
  Radio.SetTxContinuousWave(RF_FREQUENCY, TX_OUTPUT_POWER, 10);
}


