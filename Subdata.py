import paho.mqtt.client as mqtt
from Get_Data_to_DB import Sensor
import pymysql

MQTT_Broker = "m11.cloudmqtt.com"
MQTT_Port = 19463
Keep_Alive_Interval = 60
MQTT_Topic= "Temp_Hum"

def on_connect(client, userdata, flags, rc): #may khach, du lieu nguoi dung, bien co,bien hien loi
    if rc != 0:
       pass
       print ("Ket noi voi MQTT Broker that bai !")
    else:
       print("Ket noi thanh cong toi MQTT Broker : " + str(MQTT_Broker))
    client.subscribe(MQTT_Topic,0)
def on_message(client, userdata, msg):
    print("MQTT DATA RECEVICED...")
    print("MQTT Topic: " + msg.topic)
    print("Data: " + str(msg.payload)) #thong diep duoc xuat ban payload
    Sensor(msg.payload) 

client = mqtt.Client() 
client.on_connect = on_connect 
client.on_message = on_message
client.connect(MQTT_Broker, MQTT_Port, Keep_Alive_Interval)
client.username_pw_set(username="fljvvifw",password="HdV1D8tIoWXl")
client.loop_forever()

