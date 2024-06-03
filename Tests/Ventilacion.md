## Pruebas

Al inicio del video, se puede observar que el dispositivo está en modo "ahorro" para reducir el consumo. Se ha instalado un sensor de presencia que, después de un tiempo predeterminado, desactiva la pantalla LCD y otros modos de funcionamiento.

Para la ventilación, se ha utilizado un motor DC conectado a un pequeño ventilador (SmallFan). Además, se ha incorporado un servomotor para simular la apertura y cierre de ventanas. Como medidas de control, se han instalado un sensor DHT11 para medir la temperatura interior y un LM35 para medir la temperatura exterior, ambos conectados a una resistencia para evitar interferencias y proteger los sensores.

El ventilador se encenderá cuando la temperatura interior, medida por el DHT11, supere la temperatura de consigna y, al mismo tiempo, sea inferior a la temperatura exterior. Por ejemplo, si la temperatura de consigna es 20°C, la temperatura interior es 30°C y la temperatura exterior es 35°C, el ventilador se encenderá gradualmente a medida que aumenten estas diferencias.

Por otro lado, si la temperatura exterior es inferior a la temperatura interior, el servomotor se activará para enfriar la habitación.

Acceder al Video: <br>
[![Alt text](https://img.youtube.com/vi/NsltNeztmXQ/0.jpg)](https://www.youtube.com/watch?v=NsltNeztmXQ)
