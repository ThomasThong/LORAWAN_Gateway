#include <stdio.h>
#include <mqtt.h>

#define MQTTSERVER  m11.cloudmqtt.com
#define PORT        12234

void publish_callback(void** unused, struct mqtt_response_publish * published);

int main()
{ 
  struct mqtt_client client;
  

  mqtt_init(&client, 
  return 0;
}
