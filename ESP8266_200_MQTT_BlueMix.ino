//include the ESP8266 library for WiFI connectivity
#include <ESP8266WiFi.h>

//include MQTT support library
#include <PubSubClient.h>

//Include DHT22 support library
#include <DHT.h>

//DHT configuration and initialization
#define DHTTYPE DHT22 //Identify the sensor type (uncomment one line)
//#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

#define DHTPIN D1 //Identify the ESP8266 pin connected to the DHT22 data line

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor.

//initialize LED pin for visual cue of data sent
#define LEDPIN D0

//-------- WiFi Connection values -----------
const char* ssid = "your-wifi-ssid";
const char* password = "your-password";

//-------- BlueMix IoT configuration-----------
#define ORG "your-org-here"
#define DEVICE_TYPE "device-type-here"
#define DEVICE_ID "device-id-here"
#define TOKEN "bluemix-token"
//-------- Customise the above values --------

char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char topic[] = "iot-2/evt/status/fmt/json";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

WiFiClient wifiClient;
PubSubClient client(server, 1883, NULL, wifiClient);

void setup() {
 Serial.begin(115200);
 Serial.println();

 // connect to the the WiFi network, retry on error
 Serial.print("Connecting to "); Serial.print(ssid);
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
 } 
 Serial.println("");

 Serial.print("WiFi connected, IP address: "); Serial.println(WiFi.localIP());

 //start the DHT22
 dht.begin();

 //initialize LED pin
 pinMode(LEDPIN, OUTPUT);

// Setting the onboard LED to OFF
// On-board LED on NodeMCU 1.0 (v2) is connected in sink mode (inverse)
 digitalWrite(LEDPIN, HIGH); 
}

unsigned int counter = 0;

void loop() {

 if (!!!client.connected()) {
   Serial.print("Reconnecting client to ");
   Serial.println(server);
   while (!!!client.connect(clientId, authMethod, token)) {
      Serial.print(".");
      delay(500);
   }
   Serial.println();
 }

  // blink the LED to indicate sensor read
  digitalWrite(LEDPIN, LOW);
  delay(250);
  digitalWrite(LEDPIN, HIGH);
  
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old'
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

 //Create the JSON payload message
 String payload = "{\"d\":{\"Temperature\":"; 
 payload += t;
 payload += ",\"Humidity\":";
 payload += h;
 payload += ",\"Sensor\":\"DHT22\"";
 payload += ",\"Counter\":";
 payload += counter;
 payload += "}}";
 
 Serial.print("Sending payload: ");
 Serial.println(payload);
 
 if (client.publish(topic, (char*) payload.c_str())) {
   Serial.println("Publish ok");
   
   // blink the LED to indicate data sent OK
   digitalWrite(LEDPIN, LOW);
   delay(2000);
   digitalWrite(LEDPIN, HIGH);
   
 } else {
   Serial.println("Publish failed");
 }

//increment counter
  ++counter;

 //if (counter == 4294967295) {counter = 0;} //counter reset, do something here if needed...
 //else { ++counter;}
  
 delay(10000);
}
