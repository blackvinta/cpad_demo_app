import os
from time import sleep
from random import randrange


while True:
	temp = 30+randrange(1,3)
	hum = 60+randrange(1,7)
	ripeness = 'half way there'
	rip = 50
	os.system('mosquitto_pub -d -h "broker.mqttdashboard.com" -t "/cpadgroup12" -m "{"State":'+str(rip)+', "Temperature":'+str(temp)+', "Humidity": '+str(hum)+'}"')
	os.system('mosquitto_pub -d -h "localhost" -t "v1/devices/me/telemetry" -u "cXcw9PksjTXRqMlmoR93" -m "{"State":'+str(rip)+', "Temperature": '+str(temp)+', "Humidity": '+str(hum)+'}"')
	sleep(5)

