// No se requieren librerías adicionales para este código

const int MAX_NUMEROS = 10; // Tamaño máximo del vector
String inputString = "1234.5678.91011"; // Cadena de entrada
int numeros[MAX_NUMEROS]; // Vector para almacenar los números
int contador = 0; // Contador de números guardados

void setup() {
  Serial.begin(9600);

  // Analizar la cadena
  String numeroActual = ""; // Variable temporal para el número actual
  for (int i = 0; i < inputString.length(); i++) {
    char c = inputString.charAt(i);
    
    if (c == '.') {
      // Si se encuentra un punto, almacenar el número actual
      if (numeroActual.length() > 0 && contador < MAX_NUMEROS) {
        numeros[contador++] = numeroActual.toInt(); // Convertir a entero y guardar
        numeroActual = ""; // Reiniciar para el siguiente número
      }
    } else {
      // Si no es un punto, agregar el carácter al número actual
      numeroActual += c;
    }
  }

  // Guardar el último número si no termina con un punto
  if (numeroActual.length() > 0 && contador < MAX_NUMEROS) {
    numeros[contador++] = numeroActual.toInt();
  }

 
}

void loop() {
   // Imprimir los números guardados
  Serial.println("Números encontrados:");
  for (int i = 0; i < contador; i++) {
    Serial.println(numeros[i]);
  }
}