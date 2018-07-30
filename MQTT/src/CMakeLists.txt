include_directories(${PROJECT_SOURCE_DIR}/inc)
set (MQTTSOURCE mqtt.c mqtt_pal.c)
add_library (MQTT ${MQTTSOURCE})
