#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTTYPE DHT11   // DHT 11
#define ssid "Chung Manucian" 
#define password "chung1995" 
// Thông tin về MQTT Broker
#define mqtt_server "m11.cloudmqtt.com"
#define mqtt_topic_pub "Temp_Hum"   
#define mqtt_topic_sub "Temp_Hum"
#define mqtt_user "fljvvifw"    
#define mqtt_pwd "HdV1D8tIoWXl"

const uint16_t mqtt_port = 19463; //Port của MQTT


WiFiClient espClient;
PubSubClient client(espClient);

const int DHTPin1 = D2;       


long lastMsg = 0;
char msg[50];
int value = 0;
// Timers auxiliar variables
long now = millis();
long lastMeasure = 0;

// Thiet Lap cam bien DHT.
DHT dht1(DHTPin1, DHTTYPE);


void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port); 
  dht1.begin();
  

}
// Hàm kết nối wifi
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
// Hàm reconnect thực hiện kết nối lại khi mất kết nối với MQTT Broker
void reconnect() {
  // Chờ tới khi kết nối
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Thực hiện kết nối với mqtt user và pass
    if (client.connect("ESP8266Client",mqtt_user, mqtt_pwd)) {
      Serial.println("connected");
      // Khi kết nối sẽ publish thông báo
      client.publish(mqtt_topic_pub, "ESP_reconnected");
      // ... và nhận lại thông tin này
      client.subscribe(mqtt_topic_sub);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Đợi 5s
      delay(5000);
    }
  }
}
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect("ESP8266Client");

  now = millis();

  if (now - lastMeasure > 1000) {
    lastMeasure = now;
    Data();
  }
}

void Data()
{
  Serial.println("Collecting temperature data.");
  int h1 = dht1.readHumidity();
  int t1 = dht1.readTemperature();
 

  
  if (isnan(h1) || isnan(t1)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h1);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t1);
  Serial.print(" *C ");
  
  String Temperature = String(t1);
  String Humidity = String(h1);

  // Prepare a JSON payload string
  String n = "{";
  n += "\"Temperature\": "; n += Temperature; n+=",";
  n += "\"Humidity\": "; n += Humidity; 
  n += "}";

  // Send payload
  char a[100];
  n.toCharArray( a, 100 );
  client.publish( "Temp_Hum", a );
  Serial.println( a ); 

  delay(5000);
}
