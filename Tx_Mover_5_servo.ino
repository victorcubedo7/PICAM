#include <WiFi.h>
#include <BTAddress.h>
#include <BTAdvertisedDevice.h>
#include <BTScan.h>
#include <BluetoothSerial.h>
#include <ESP32Servo.h>

//Definicion de todos los pines asociados a los sensores flex
#define pulgar  36 //Pulgar
#define indice  39 //Indice
#define corazon 34 //Corazon
#define anular  35 //Anular
#define menique 32 //Meñique

//Configuración para la rede WiFi
const char* ssid = "Prueba"; // Nombre de la red
const char* password = "Contraseña_Servidor"; // Contraseña de la red
const char* serverIP = "192.168.4.1"; // IP del servidor
const int serverPort = 80; //Puerto que se usa para Protocolo de transferencia de hipertexto (HTTP)

void setup() {
  
  Serial.begin(115200); //Inicia el monitor serial
  
  Serial.println("Conectándose a la red WiFi...");
  WiFi.begin(ssid, password); //Comienza la red WiFi
 
  while (WiFi.status() != WL_CONNECTED) { //Se queda aqui hasta que se crea
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.print("Conectado a la red WiFi. Dirección IP: ");
  Serial.println(WiFi.localIP()); //Muestra la IP

  //Declaración de los sensores como entradas 
  pinMode(pulgar,INPUT);
  pinMode(indice,INPUT);
  pinMode(corazon,INPUT);
  pinMode(anular,INPUT);
  pinMode(menique,INPUT);
}
 
void loop() {

  // lee todos los valores de los sensores
  int valorPul = analogRead(pulgar);
  int valorInd = analogRead(indice);
  int valorCor = analogRead(corazon);
  int valorAnu = analogRead(anular);
  int valorMen = analogRead(menique);
    
  // Contrucción del mensaje para mandarlo al otro ESP32 separado por "." cada dedo 
  String request;
  request += String(valorPul);
  request += ".";

  request += String(valorInd);
  request += ".";

  request += String(valorCor);
  request += ".";

  request += String(valorAnu);
  request += ".";

  request += String(valorMen);

 
  Serial.print("Enviando solicitud al servidor: ");
  Serial.println(request); //Muestra el mensaje que envia
 
  // Establecer la conexión con el servidor
  WiFiClient client;
  if (client.connect(serverIP, serverPort)) {
    // Enviar la solicitud al servidor
    
    client.println(request); //Lo manda
  }
   
  // Esperar 1 segundos antes de enviar una nueva solicitud
  delay(1000);
}