/***************************************************************************
 *************************************************************************** 
 ** Conexion con un servidor MQTT utilizando una ESP32 Devkit V1_1        **  
 ** Oscar Alberto Valles Limas                                            **
 ** Oscar Beltran                                                         **
 ** Instituto tecnológico de Chihuahua                                    **
 ***************************************************************************
 ***************************************************************************
*/
#include <Arduino.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic
#include <PubSubClient.h>
#include <ControlLed.h> //Libreria para el control de los leds 

 //MQTT Setup
const char* mqttServer = "192.168.1.79"; //esta es la Ip del broker rabbitmq, si se esta ejecutando de manera local usa la ip de la maquina del broker
const int mqttPort = 3883;
const char* clientID = "ESP_1"; // Client ID username
const char* topic = "tec1.a1.entrada.error"; // Publish topic

WiFiClient espClient;
PubSubClient client(espClient);

//-------------------- Publicar errores ---------------------
void publishError(const char* msg) {
  client.publish(topic, msg);
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Intentando conexión MQTT...");
    if (client.connect(clientID)) {
      Serial.println("MQTT conectado");
      client.subscribe("tec1.a1.entrada.error");
      client.subscribe("tec1.a1.entrada.on");
      client.subscribe("tec1.a1.entrada.off");
      client.subscribe("A1");
      Serial.println("Tópicos suscritos");
    }
    else {
      Serial.print("Fallo en conexión MQTT, rc=");
      Serial.print(client.state());
      Serial.println(" intentando de nuevo en 5 segundos");
      publishError("ERROR: Fallo en conexión MQTT");
      delay(5000);  // wait 5sec and retry
    }
  }
}


void callback(char* topic, byte* payload, unsigned int length) {
    String valTpc = String(topic);
    Serial.print("Mensaje recibido en el tópico: ");
    Serial.println(valTpc);
    
    if (valTpc == "tec1/a1/entrada/on") {
        Serial.println("LED encendido: tec1.a1.entrada.on");
        turnLed(1);
    }
    
    if (valTpc == "tec1/a1/entrada/off") {
        Serial.println("LED apagado: tec1.a1.entrada.off");
        turnLed(0);
    }
    String data = "";
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
        data += (char)payload[i];
    }
    Serial.println("");
}



void setup() {
  
  Serial.begin(115200);

  WiFiManager wifiManager;
  //wifiManager.resetSettings(); //Esto solo es para modo de prueba, en el codigo final, hay que comentar
  //first parameter is name of access point, second is the password
  wifiManager.autoConnect("ESP32_Prueba", "Itch1234"); //Nombre del hotspot que se va a crear y su contrasena
  Serial.println("Ya estas conectado"); //Impresion de mensaje

  if (WiFi.status() != WL_CONNECTED) {
    publishError("ERROR: No hay conexión WiFi");
  } else {
    publishError("INFO: Conectado a WiFi");
  }

  client.setServer(mqttServer, mqttPort); 
  client.setCallback(callback); // Define function which will be called when a message is received.
  setup_(); //Invoca a setup_ que se encuentra en la libreria ControlLed.h

  publishError("INFO: ESP32 iniciada correctamente");
}

void loop() {

  if (!client.connected()) { // If client is not connected
    publishError("ERROR: Cliente MQTT desconectado");
    reconnect(); // Try to reconnect
  }

  client.loop();

  //-------------------------Entrada serial----------------------------------------------
  if (Serial.available() > 0) { //Si el puerto serial esta disponible
    String str = Serial.readString(); //Se lee una cadena de caracteres
    str.trim();
    Serial.println(str);
    publishError("INFO: Mensaje recibido por puerto serial");

    if(str == "led=on") //Si la cadena de caracteres es led=on 
      turnLed(1); //Enciendo el led 

    if(str == "led=off") //Si la cadena de caracteres es led=off
      turnLed(0);  //El led se va a apgar 
  }

  //-----------------------------Entrada del boton --------------------------------------
  evalBtn(); //Se invoca la funcion para evaluar el boton 
}
