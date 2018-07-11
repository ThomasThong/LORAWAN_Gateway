#include "LoRa.h"
#include <stdlib.h>
#include <pthread.h>

#define NUMTHREADS	2

void* LoraReceive(void *arg)
{
  LoraConfig* config = (LoraConfig*) arg;

  printf("LoRa Receiver at %d \r\n",config->Freq);

  if (!config->Lora->begin(config->Freq)) {
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
    printf("Freq:%d Received packet '",config->Freq);

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
  LoRaClass* LoRa[NUMTHREADS];
  for (int i = 0 ; i < NUMTHREADS; ++i)
	LoRa[i] = new LoRaClass(i);
  //LoRa[0] = new LoRaClass(30,21,22,0);
  //LoRa[1] = new LoRaClass(0,2,3,1);

  int rc;
  LoraConfig config[NUMTHREADS];
  for (int i = 0; i < NUMTHREADS; ++i)
  {
	 config[i].Lora = LoRa[i];
 	 config[i].Freq = 868000000;
 	 config[i].Bandwidth = 500000;
 	 config[i].CodingRate = 5;
 	 config[i].SF = 12;
 	 config[i].PreambleLength = 8;
  }
  config[1].Freq = 868100000;
  pthread_t thrs[NUMTHREADS];

  for (int i = 0 ; i < NUMTHREADS; ++i)
  {
	if ((rc = pthread_create(&thrs[i], NULL, LoraReceive, &config[i])))
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
