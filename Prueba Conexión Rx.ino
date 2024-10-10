#include <WiFi.h>
#include <ESP32Servo.h>

const char* ssid = "Prueba";
const char* password = "Contraseña_Servidor";
WiFiServer server(80);
Servo miServo1;
#define servoPin1 26
int value2;
int i;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  miServo1.write(0);
  miServo1.attach(servoPin1);
  WiFi.softAP(ssid, password);
 pinMode(2,OUTPUT);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
 digitalWrite(2,HIGH);
  server.begin();
  Serial.println("Server started");
}

void loop() {
  // put your main code here, to run repeatedly:
  
    WiFiClient client = server.available();
 
  if (client) {
    while (client.connected()) {
 
      //String response = String(buttonState) + "," + String(analogRead(A0)) + "," + String(random(100));
      //client.println(response);
 
      if (client.available()) {
        String request = client.readStringUntil('\r');
        Serial.print("Client says: ");
        Serial.println(request);
        int value1 = request.toInt();
        if(value1 > 1900 && value1 < 3100)
        {
          
            value2 = map(value1,2000,3000,0,180);
        }
      

        miServo1.write(value2);
        client.stop();
 
 
    }
    //Serial.println("Client disconnected");
  }
}
}
