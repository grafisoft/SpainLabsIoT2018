/*
 CURSO BASICO IOT DE LA COMUNIDAD SPAINLABS.COM
 Firmware basico para el hardware: ESP8266 IoT Nodo v1rA.
 Compatible con las versiones del modulo ESP8266: esp-07/12/12E.
 Enlace: https://www.spainlabs.com/foros/tema-SpainLabsIoT2018-Caso-real-Nodos-ESP8266
 Firmware para el hardware desarrollado en el curso SpainLabsIoT2018.
 Enlace: https://www.spainlabs.com/foros/tema-SpainLabs-con-el-IoT-para-tod-s

 Este software realiza de forma esquematica lo siguiente:
 Lee el sensor BME280 y nivel de bateria -> Envia las tramas MQTT -> Duerme.
 El sensor BME280 nos da parametros de tipo temperatura, humedad y presion.

 Se usa el protocolo MQTT que crea topics en funcion del nombre del nodo y el
 valor que vamos a publicar del sensor o nivel de bateria. Los topics son
 similares a: "sensor/NodeName/temp".

 Diseño: Grafisoft.
 Fecha: 25/2/2018.
 Version: 2 revA.
*/


#include <Arduino.h>
//Todas las funciones e includes de librerias estan en funciones.h
#include "funciones.h"
float battery;
//----------------------- CONFIG PARAMETERS------------------------
//Con este parametro se construye todos los topics para el protocolo MQTT.
// Nombre del nodo.
String NodeName = "Testing";
String TopicMQTT; //Variable para construir el Topic de MQTT.
//El tiempo de sueño se especifica en el fichero funciones.h (sleeptime).
//-----------------------------------------------------------------

void setup() {

  Serial.begin(115200); //Velocidad del UART.
  setup_wifi();
  //Configuracion conexion a MQTT.
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  Serial.println(F("SpainLabsIoT2018 Firm ESP8266 esp-07/12/12E"));
  Serial.println(F("Firmware version: v2 revA"));

  //Inicializamos el sensor bme280.
  bool status;
  
  // I2C Addres configurada en 0x76. Hay sensores(plaquitas con el sensor integrado)
  //que estan en 0x77. Desde bme.begin(I2C_ADDRESS) se puede cambiar.
  status = bme.begin(0x76);
  delay(1000); // let sensor boot up
  if (!status) {
      Serial.println("Could not find a valid BME280 sensor, check wiring!");
      while (1);
  }

  Serial.println("-- Default Test --");
  //Lectura del nivel de bateria.
  Serial.print("Battery Status: ");
  //El ADC del ESP8266 solo lee hasta 1V.
  //Se usa un divisor resistivo con Rs de 470K-100K.
  //Valores altos de las Rs para tener un consumo minimo.
  battery = (analogRead(0)/1024.0)*5.55;
  Serial.print(battery);
  Serial.println(" V ");
  Serial.println();
}

void loop() {

  //Lectura del sensor y envio de datos al monitor serie.
  leerbme();

  //Conexión con el broker MQTT.
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 75, "Prueba trama #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);

    //Bloque para el envio del valor temperatura.
    char valTemperature[5];
    dtostrf(bme.readTemperature(), 3, 1, valTemperature);
    String payload; //Variable para contener la info de la trama que se envia.
    //Creamos la trama. Sera del estilo: "sensors/NodeName/temp"
    TopicMQTT = "sensors/" + NodeName + "/temp";
    //Creamos el mensaje. Sera del estilo: "NodeName temperature=";
    payload = ""; //Limpiamos la variable.
    payload += NodeName;
    payload += " temperature=";
    payload += valTemperature;
    //Enviamos la trama via MQTT.
    client.publish((char*) TopicMQTT.c_str(), (char*) payload.c_str());
    delay(3000);

    //Bloque para el envio del valor humedad.
    char valHumidity[5];
    dtostrf(bme.readHumidity(), 3, 1, valHumidity);
    //Creamos la trama. Sera del estilo: "sensors/NodeName/humidity"
    TopicMQTT = "sensors/" + NodeName + "/humidity";
    //Creamos el mensaje. Sera del estilo: "NodeName humidity=";
    payload = ""; //Limpiamos la variable.
    payload += NodeName;
    payload += " Humidity=";
    payload += valHumidity;
    //Enviamos la trama via MQTT.
    client.publish((char*) TopicMQTT.c_str(), (char*) payload.c_str());
    delay(3000);

    //Bloque para el envio del valor Bateria.
    char valBattery[5];
    dtostrf(battery, 3, 1, valBattery);
    //Creamos la trama. Sera del estilo: "sensors/NodeName/bat"
    TopicMQTT = "sensors/" + NodeName + "/bat";
    //Creamos el mensaje. Sera del estilo: "NodeName Battery=";
    payload = ""; //Limpiamos la variable.
    payload += NodeName;
    payload += " Battery=";
    payload += valBattery;
    //Enviamos la trama via MQTT.
    client.publish((char*) TopicMQTT.c_str(), (char*) payload.c_str());
    delay(3000);

    //Mensaje para indicar que la trama se ha enviado.
    Serial.println("-- Tramas enviadas! --");
    //En la version ESP12 y ESP12E existe un bug. Hay que desconectar el Wifi
    //para que despues de despertar, no se quede bloqueado el nodo.
    WiFi.disconnect();
  }
  delay(1000);
  // Tiempo de deepSleep especificado en 'sleeptime'.
  ESP.deepSleep(sleeptime, WAKE_RF_DEFAULT);
}
