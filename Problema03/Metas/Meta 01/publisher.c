#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MQTTClient.h"
 
#define ADDRESS     "tcp://10.0.0.101:1883@@luno*123"
#define CLIENTID    "fedorento"
#define USERNAME	"aluno"
#define PASSWORD	"@luno*123"
/*
#define MQTT_PUBLISH_TOPIC     "aoba/node"
#define MQTT_SUBSCRIBE_TOPIC   "aoba/digital"
*/
#define TOPIC       "aoba"
#define PAYLOAD     "franchesco virgulini"
#define QOS         1
#define TIMEOUT     10000L
 
int main(int argc, char* argv[])
{
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;

    MQTTClient_create(&client, ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    conn_opts.username = USERNAME;
    conn_opts.password = PASSWORD;

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }
 
    pubmsg.payload = PAYLOAD;
    pubmsg.payloadlen = (int)strlen(PAYLOAD);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
 
    printf("Waiting for up to %d seconds for publication of %s\n"
            "on topic %s for client with ClientID: %s\n",
            (int)(TIMEOUT/1000), PAYLOAD, TOPIC, CLIENTID);
    rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    printf("Message with delivery token %d delivered\n", token);
    rc = MQTTClient_disconnect(client, 10000);

    MQTTClient_destroy(&client);
    return rc;
}