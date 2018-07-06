#include "LoRa.h"
//#include <stdio.h>
#include <iostream>

LoRaClass LoRa ;

int main()
{
  int counter = 0;
  printf("LoRa Sender\r\n");

  if (!LoRa.begin(915E6)) {
    printf("Starting LoRa failed!\r\n");
    while (1);
  }

  while (1)
{
  printf("Sending packet: %d\r\n", counter);

  // send packet
  LoRa.beginPacket();
  LoRa.write((const uint8_t*)"hello ",6);
  LoRa.write((const uint8_t)counter);
  LoRa.endPacket();

  counter++;

  sleep(5);
}
  return 0;
}
