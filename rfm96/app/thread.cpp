#include "LoRa.h"
#include <stdlib.h>
#include <pthread.h>

#define NUMTHREADS	1

void* LoraReceive(void *arg)
{
  LoraConfig* config = (LoraConfig*) arg;

  printf("LoRa Receiver\r\n");

  if (!config->Lora->begin(868000000)) {
    printf("Starting LoRa failed!\r\n");
    pthread_exit(NULL);
  }

  config->Lora->setSignalBandwidth( config->Bandwidth );
  config->Lora->setCodingRate4( config->CodingRate );
  config->Lora->setSpreadingFactor( config->SF ); 
  config->Lora->setPreambleLength( config->PreambleLength );

  // try to parse packet
  while(1)
  {
  int packetSize = config->Lora->parsePacket();
  if (packetSize) {
    // received a packet
    printf("Received packet '");

    // read packet
    while (config->Lora->available()) {
      printf("%c",(char)config->Lora->read());
    }
    // print RSSI of packet
    printf("' with RSSI : ");
    printf("%d\r\n",config->Lora->packetRssi());
  }
  }

}

int main()
{
  LoRaClass LoRa;
  int rc;
  LoraConfig config1, config2;
  config1.Lora = &LoRa;
  config1.Bandwidth = 500000;
  config1.CodingRate = 5;
  config1.SF = 12;
  config1.PreambleLength = 8;

  pthread_t thrs[NUMTHREADS];

  for (int i = 0 ; i < NUMTHREADS; ++i)
  {
	if ((rc = pthread_create(&thrs[i], NULL, LoraReceive, &config1)))
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
