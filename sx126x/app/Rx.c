#include "radio.h"
#include "sx126x-board.h"
#include "sx126x.h"
#include <wiringPi.h>
#include "stdio.h"

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

#define TX_OUTPUT_POWER                             12
static RadioEvents_t RadioEvents;
void OnRxDone( uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr );
void OnRxTimeout(void);
uint8_t packet[] = {'h','e','l','l','o'};

RadioStatus_t status;
uint16_t Interrupt;
RadioError_t error;

int main(){
  // put your setup code here, to run once:
  SX126xIoInit();
  pinMode(LED,OUTPUT);
  printf("Begin\r\n");
  
  SX126xCalibrateImage(868000000);
  CalibrationParams_t calibParam;

  calibParam.Value = 0x7F;
  SX126xCalibrate( calibParam );

  RadioEvents.RxDone = OnRxDone;
  RadioEvents.RxTimeout = OnRxTimeout;

  Radio.Init( &RadioEvents );
  printf("Init events\r\n");
  
  Radio.SetChannel( RF_FREQUENCY );
  printf("Set rf frequency\r\n");

  Radio.SetPublicNetwork(true);
  
  Radio.SetRxConfig( MODEM_LORA, LORA_BANDWIDTH, LORA_SPREADING_FACTOR,
                     LORA_CODINGRATE, 0, LORA_PREAMBLE_LENGTH, 
                     LORA_SYMBOL_TIMEOUT, LORA_FIX_LENGTH_PAYLOAD_ON,
                     0, 1, 0, 0, LORA_IQ_INVERSION_ON, 1);
  printf("Set Rx config\r\n");

  //Radio.Rx(0);
  printf("Receive\r\n");

  while(1)
  {
    Interrupt = SX126xGetIrqStatus();
    printf("interrupt in main :%#02x\r\n",Interrupt);
    delay(2000);
  }
}
  
void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr)
{
  printf("Rx finish\r\n");
  printf("Packet size %d : ", size);
  for (int i  = 0; i < size; ++i)
	printf ("%c",payload[i]);

  printf ("\r\n");
  printf ("RSSI : %d, SNR: %d\r\n", rssi, snr);
  //Radio.Rx(0);
}

void OnRxTimeout()
{
  printf("rx timeout\r\n");
  //Radio.Rx(0);
}


