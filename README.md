
![Banner](https://i.imgur.com/tx8JCZWl.jpg)

![Banner](https://i.imgur.com/MqIeJcal.jpg)

# SpainLabsIoT2018
Hardware&Firmware creado para el mini curso IoT basado en ESP8266

En este repositorio se pretende subir todos los archivos correspondientes al hardware y firmware creados para el 
curso de IoT SpainLabsIoT2018. Podemos acceder a los contenidos desde el enlace: https://www.spainlabs.com/foros/tema-SpainLabs-con-el-IoT-para-tod-s

El hardware lo podemos ver mas en detalle en: https://www.spainlabs.com/foros/tema-SpainLabsIoT2018-Caso-real-Nodos-ESP8266

El hardware esta basado en la integración del módulo de comunicaciones wifi ESP8266 en sus especificaciones 07/12/12E.

El proyecto del firmware que se ofrece esta escrito usando el IDE de Atom+ Proyecto PlatformIO: https://platformio.org/

Este proyecto forma parte de la comunidad maker spainlabs.com y mas concretamente al usuario Grafisoft.

Podeis hacer uso de todo el contenido sin restricciones siempre y cuando se indique que pertenece a Grafisoft de spainlabs.com

Características:

- Placa desarrollada para ESP8266-07/12/12E.
-Dimensiones: 78mm x 41mm.
- Módulo ESP extraible o posibilidad de soldar directamente sobre la PCB.
- Etapa de carga para las baterías Lipo. Ya sea mediante panel solar (6V-1W) o mediante una conexión de 5V externa.
- Todos los pines del ESP son accesibles. También lo son los de alimentación (tanto Vbat como Vext).
- Programación del ESP desde la propia placa mediante un conversión USB-Serie (este conversor debe ser un modelo que tenga ciertos pines accesibles).
- Bajo consumo en DeepSleep: <50uA.
- Conexión de una batería mediante conector JST o compatible con un holder para baterías de 1 o 2 celdas tipo 18650.
- Botón de reset.
- Nivel de batería: Podremos consultar el nivel de nuestras baterías para conocer su estado.
- Modular: Esto es, no es necesario tener soldadas todas las etapas para su funcionamiento. De cara a desplegar una red, no tenemos porque soldar todos los componentes para tener un nodo operativo. Por lo que tenemos un cierto ahorro en el momento de desplegar nodos.
- Se dispone de zócalos para poder pinchar una placa encima de forma que en ella podamos integrar la electrónica necesaria para añadir mas sensores.
- Se ha dejado huella para zócalo 2x2 y disponer unicamente acceso a I2C y alimentación 3v3.
- Su coste en componentes ronda los 6€ sin incluir el módulo ESP ni batería(s). Es un coste bastante razonable.

Desarrollo de una shield para conectar sensores: https://github.com/grafisoft/Smart-Sensors-Shield

-------------------------------------------------

ESp8266 IoT Board for SpainLabsIoT2018 course is based on ESP8266 NodeMCU. Some changes are do and new version is created. We can use the board as if we were using NodeMCU or any ESP8266 module.

Features:

- Board developed for ESP8266-07/12/12E version modules.
- Dimensions: 78mm x 41mm.
- Designed to use non-fixed modules or you can soldier it.
- Include battery Lipo charger. We can use a solar panel (6V-1W) or external power-dc 5v.
- All ESP8266 module pins are accessible. Power pins accessible too (Vbat and Vext).
- ESP8266 can be programmed using external USB-Serial: https://www.ebay.es/itm/USB-2-0-to-TTL-UART-6PIN-CP2102-Module-Serial-Converter-T1/252583963023?rmvSB=true 
- Low power DeepSleep current: 50uA. *Note: We need extract resistor betwen leds components.
- Battery connector is JST type or we can use a battery holder (1 or 2 cells). Battery type is 18650.
- Reset button.
- Battery level: ADC of ESP module is used to measure battery level.
- It is not necessary to weld all the components. Board can work with parcial smd components. We can get low cost when we need to deploy some nodes and weld necessary components only. 
- Board provide some connectors to add personal shields and increase board features or integrate new sensors.
- Board include footprint for I2C connector. Shape is 2x2.
- Board costs are over 6€. Not included ESP module or battery.

I am developing a shield for sensors: https://github.com/grafisoft/Smart-Sensors-Shield
