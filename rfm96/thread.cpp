#include "LoRa.h"
#include <stdlib.h>
#include <pthread.h>

#define NUMTHREADS	1

void* LoraReceive(void *arg)
{
  LoRaClass *LoRa = (LoRaClass*) arg;
  
  printf("LoRa Receiver\r\n");

  if (!LoRa->begin(868000000)) {
    printf("Starting LoRa failed!\r\n");
    pthread_exit(NULL);
  }

  LoRa->setSignalBandwidth(500000);
  LoRa->setCodingRate4(5);
  LoRa->setSpreadingFactor(12); 
  LoRa->setPreambleLength(8);

  // try to parse packet
  while(1)
{
  int packetSize = LoRa->parsePacket();
  if (packetSize) {
    // received a packet
    printf("Received packet '");

    // read packet
    while (LoRa->available()) {
      printf("%c",(char)LoRa->read());
    }
    // print RSSI of packet
    printf("' with RSSI : ");
    printf("%d\r\n",LoRa->packetRssi());
  }
}

}

LoRaClass LoRa;

int main()
{
  //LoRaClass LoRa;
  int rc;
  pthread_t thrs[NUMTHREADS];

  for (int i = 0 ; i < NUMTHREADS; ++i)
  {
	if ((rc = pthread_create(&thrs[i], NULL, LoraReceive, &LoRa)))
	{
	  printf ("create thread didn't success\r\n");
	  return EXIT_FAILURE;
	}
  }

  for (int i = 0; i < NUMTHREADS; ++i)
  {
  	pthread_join(thrs[i],NULL);
  }

  return 0;
}
