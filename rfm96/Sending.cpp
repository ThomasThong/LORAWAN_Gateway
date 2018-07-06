#include "LoRa.h"
#include <iostream>
#include <string.h>

LoRaClass LoRa ;

int main()
{
  int counter = 0;
  printf("LoRa Sender\r\n");

  if (!LoRa.begin(868E6)) {
    printf("Starting LoRa failed!\r\n");
    while (1);
  }

  LoRa.setSignalBandwidth(500000);
  LoRa.setCodingRate4(5);
  LoRa.setSpreadingFactor(12); 
  LoRa.setPreambleLength(8);

  char number[3] ;
  while (1)
{
  printf("Sending packet: %d\r\n", counter);

  // send packet
  LoRa.beginPacket();
  LoRa.write((const uint8_t*)"hello ",6);
  sprintf(number, "%d", counter);
  LoRa.write((const uint8_t*)number,strlen(number) );
  LoRa.endPacket();

  counter++;

  sleep(5);
}
  return 0;
}
