#include <WiFi.h>
#include <ESP32Servo.h>

const char* ssid = "Prueba";
const char* password = "Contraseña_Servidor";
WiFiServer server(80);


Servo servoPulgar;
#define pinPulgar 25
int valorPulgar;

Servo servoIndice;
#define pinIndice 26
int valorIndice;

Servo servoCorazon;
#define pinCorazon 27
int valorCorazon;

Servo servoAnular;
#define pinAnular 14
int valorAnular;

Servo servoMenyique;
#define pinMenyique 12
int valorMenyique;



int i;

// Codigo separar mensajes

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  servoPulgar.write(0);
  servoPulgar.attach(pinPulgar);
  
  servoIndice.write(0);
  servoIndice.attach(pinIndice);

  servoCorazon.write(0);
  servoCorazon.attach(pinCorazon);

  servoAnular.write(0);
  servoAnular.attach(pinAnular);

  servoMenyique.write(0);
  servoMenyique.attach(pinMenyique);
  
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
 
      //client.println(response);
 
      if (client.available()) {

        Serial.println("\n");
        for(int j = 0; j < 5; j++)
        {
        int request = client.readStringUntil('.').toInt();
        // c = client.readStringUntil('.').to();
        Serial.print("Client says: ");
        Serial.println(request);

        if(j==0)
        {Serial.print("Pulgar: ");
        Serial.println(request);
        valorPulgar = map(request,500,2095,0,180); 
        servoPulgar.write(valorPulgar);
        }
        else if(j==1)
        {Serial.print("Indice: ");
        Serial.println(request);
        valorIndice = map(request,500,2095,0,180); 
        servoIndice.write(valorIndice);
        }
        else if(j==2)
        {Serial.print("Corazon: ");
        Serial.println(request);
        valorCorazon = map(request,500,2095,0,180); 
        servoCorazon.write(valorCorazon);
        }
        else if(j==3)
        {Serial.print("Anular: ");
        Serial.println(request);
        valorAnular = map(request,500,2095,0,180); 
        servoAnular.write(valorAnular);
        }
        else if(j==4)
        {Serial.print("Menyique: ");
        Serial.println(request);
        valorPulgar = map(request,500,2095,0,180); 
        servoMenyique.write(valorMenyique);
        }
        else{
          Serial.println("NO DATA");
        }
        }
        

        client.stop();
 
 
    }
    //Serial.println("Client disconnected");
  }
}
}
