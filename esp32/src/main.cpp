#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <MySQL_Connection.h>

byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
const int trigPin1 = 4;   // Pin TRIG del primer sensor
const int echoPin1 = 5;   // Pin ECHO del primer sensor
const int trigPin2 = 22;   // Pin TRIG del segundo sensor
const int echoPin2 = 23;   // Pin ECHO del segundo sensor

const int trigPin3 = 15;   // Pin TRIG del primer sensor
const int echoPin3 = 18;   // Pin ECHO del primer sensor
const int trigPin4 = 19;   // Pin TRIG del segundo sensor
const int echoPin4 = 21;   // Pin ECHO del segundo sensor

WiFiClient client; // Declaración de la variable client

IPAddress server_ip(145,14,144,212); // Dirección IP del hostname "files.000webhost.com"
MySQL_Connection conn((Client *)&client);

/*char user[] = "id21164697_hector";
char password[] = "Sam06128989@@";
char db[] = "id21164697_aforos";
*/

char user[] = "id21160849_cborja";
char password[] = "Cborja21@.";
char db[] = "id21160849_db";

const float thresholdDistance = 15.0;  // Umbral de distancia en centímetros

// IPAddress server_addr(192,168,100,126); // IP de tu laptop
IPAddress server_addr(192, 168, 100, 29);

char ssid[] = "HOMEBORJA";    // your SSID
char pass[] = "calebnicolas1";       // your SSID Password


void setup() {
  Serial.begin(115200);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
  

  // Begin WiFi section
  WiFi.begin(ssid, pass);
  delay(4000);
  if ( WiFi.status() != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    while(true);
  }
  // print out info about the connection:
  else {
    Serial.println("Connected to network");
    IPAddress ip = WiFi.localIP();
    Serial.print("My IP address is: ");
    Serial.println(ip);
    }
  }


void enviarAccion(String action) {
  HTTPClient http;

  String datos_a_enviar = "accion=" + action;

  http.begin(client, "http://aplicacionaforo.000webhostapp.com/EspPost.php");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int codigo_respuesta = http.POST(datos_a_enviar);
  if (codigo_respuesta > 0) {
    Serial.println("Código HTTP: " + String(codigo_respuesta));
    if (codigo_respuesta == 200) {
      String cuerpo_respuesta = http.getString();
      Serial.println("El servidor respondió: ");
      Serial.println(cuerpo_respuesta);
    }
  } else {
    Serial.print("Error enviado POST, código: ");
    Serial.println(codigo_respuesta);
  }

  http.end(); // libero recursos
}

void sumarAforo1() {
  enviarAccion("sumar1");
}
void sumarAforo2() {
  enviarAccion("sumar2");
}

void restarAforo1() {
  enviarAccion("restar1");
}
void restarAforo2() {
  enviarAccion("restar2");
}
  
  


float getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;  // Calcular la distancia en centímetros
  return distance;
}


void loop() {

  float distance1 = getDistance(trigPin1, echoPin1);
  float distance2 = getDistance(trigPin2, echoPin2);

  float distance3 = getDistance(trigPin3, echoPin3);
  float distance4 = getDistance(trigPin4, echoPin4);

  Serial.println(distance1);
  Serial.println(distance2);
  Serial.println(distance3);
  Serial.println(distance4);

  if ( distance1 > 1 && distance1 < thresholdDistance) {
    restarAforo1();
    Serial.println("Persona entrando y restando al aforo disponible de FADCOM.");
  } else { int va1=0;
  }
   
  if (distance2 > 1 && distance2 < thresholdDistance) {
    sumarAforo1();
    Serial.println("Persona saliendo y sumando al aforo disponible de FADCOM.");
  } else { int va1=0;
  }

  if ( distance3 > 1 && distance3 < thresholdDistance) {
    restarAforo2();
    Serial.println("Persona entrando y restando al aforo disponible de CELEX.");
  } else { int va1=0;
  }
   
  if (distance4 > 1 && distance4 < thresholdDistance) {
    sumarAforo2();
    Serial.println("Persona saliendo y sumando al aforo disponible de CELEX.");
  } else { int va1=0;
  }
  Serial.println("SALTO");
  
  delay(1000);
}