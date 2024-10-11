#include <WiFi.h>
#include <BTAddress.h>
#include <BTAdvertisedDevice.h>
#include <BTScan.h>
#include <BluetoothSerial.h>
#include <ESP32Servo.h>
#define potPin1 34
const char* ssid = "Prueba"; // Reemplaza con el SSID de tu red
const char* password = "Contraseña_Servidor"; // Reemplaza con la contraseña de tu red
const char* serverIP = "192.168.4.1"; // Reemplaza con la dirección IP del servidor
const int serverPort = 80;

void setup() {
  
  Serial.begin(115200);
  
  Serial.println("Conectándose a la red WiFi...");
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.print("Conectado a la red WiFi. Dirección IP: ");
  Serial.println(WiFi.localIP());
  pinMode(potPin1,INPUT);
}
 
void loop() {
  // Simular dos valores enteros para enviar al servidor
  int valorPot1 = analogRead(potPin1);
    
  // Construir la solicitud al servidor en el formato "value1,value2"
  String request = String(valorPot1);
 
  Serial.print("Enviando solicitud al servidor: ");
  Serial.println(request);
 
  // Establecer la conexión con el servidor
  WiFiClient client;
  if (client.connect(serverIP, serverPort)) {
    // Enviar la solicitud al servidor
    
    client.println(request);
  }
   
  // Esperar 5 segundos antes de enviar una nueva solicitud
  delay(1000);
}
