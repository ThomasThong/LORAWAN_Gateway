#include "LoRa.h"

int main() {
  int channel, freq;
  printf("LoRa Receiver\r\n");
  printf("Choose channel (0 or 1)\r\n");
  scanf("%d",&channel);
  //printf("Choose fre\r\n");
  //scanf("%d", &freq);
  LoRaClass LoRa(channel);
  if (!LoRa.begin(868000000)) {
    printf("Starting LoRa failed!\r\n");
    while (1);
  }

  LoRa.setSignalBandwidth(500000);
  LoRa.setCodingRate4(5);
  LoRa.setSpreadingFactor(12); 
  LoRa.setPreambleLength(8);
  LoRa.setSyncWord(0x24);
  // try to parse packet
  while(1)
{
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    printf("Received packet '");

    // read packet
    while (LoRa.available()) {
      printf("%c",(char)LoRa.read());
    }
    // print RSSI of packet
    printf("' with RSSI ");
    printf("%d \r\n",LoRa.packetRssi());
  }
  //sleep(1);
}
}
