import paho.mqtt.client as mqtt
import time

ACCESS_TOKEN='me7dfpG5F12tq3NSlcVZ'                 #Token of your device
broker="localhost"   			    #host name
port=1883 
topic = "v1/devices/me/telemetry"

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc) :
    if (rc==0) :
        print("connected OK Returned code = ", rc)
    else :
        print("Bad connection Returned code = ", rc)

def on_message(client, userdata, msg) :
    print (msg.topic + " " + str(msg.payload))    


client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.username_pw_set(ACCESS_TOKEN)
client.connect(broker , port, 60)
client.subscribe(topic)

client.loop_forever()
