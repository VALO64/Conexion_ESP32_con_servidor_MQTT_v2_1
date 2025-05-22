## Conexion_ESP32_con_servidor_MQTT_v2_1

[![ESP32](https://img.shields.io/badge/ESP-32-000000.svg?longCache=true&style=flat&colorA=CC101F)](https://www.espressif.com/en/products/socs/esp32)

[![Wokwi](https://img.shields.io/badge/Wokwi-Simulador-blue)](https://wokwi.com/projects/423788809188749313)


**Matierial**
  - ESP32
  - Node-Red
  - 2 led
  - Calbes
  - 2 resistencia 220 ohms
  - 1 resistencia 1k ohms
  - Docker compose
  - Portainer
  - RabbitMQ
    
## **Diagrama**
-------------------------------------------------------------------------------------------
![image](https://github.com/user-attachments/assets/7a2fea84-d13b-461e-be00-d6bc56f2a0b8)

## **Circuito fisico**
-------------------------------------------------------------------------------------------
![image](https://github.com/user-attachments/assets/23d85e68-7ae0-4ed4-a42b-7ccb562aa576)
![image](https://github.com/user-attachments/assets/c0b6a82f-25c6-48b6-8550-6b40e379ae2f)

## **Librerias necesarias para node red**
-------------------------------------------------------------------------------------------
![image](https://github.com/user-attachments/assets/2d05d1f4-8b2c-478b-9725-b19d6f878e7d)
![image](https://github.com/user-attachments/assets/2fde5b1b-3e84-4cd2-ae03-4c905be2b34d)

## **UI con Node-Red**
-------------------------------------------------------------------------------------------
### **Panel de control general**
![image](https://github.com/user-attachments/assets/3e5afd35-1218-4cb6-a5fe-ad12fc6c3da5)
### **Control manual puerto serial**
![image](https://github.com/user-attachments/assets/d25209b1-0949-47b0-b4c8-c120d55b015e)
### **Subscripciones**
#### **Subscripcion general**
![image](https://github.com/user-attachments/assets/44bb67e9-7384-47ed-96f2-393a507477ec)
#### **Subscripciones especificas**
##### **Area 1**
![image](https://github.com/user-attachments/assets/27c7ff1d-4c62-4e35-80ef-7ed7ae638dec)
##### **Area 2**
![image](https://github.com/user-attachments/assets/d9896ead-b119-4b52-82cd-8b31bd47ee75)

## **Bloques utilizados en Node-Red**
-------------------------------------------------------------------------------------------
### **Envio de datos**
![image](https://github.com/user-attachments/assets/a539bbd8-4da2-41a0-a472-bdc4688f9de3)
![image](https://github.com/user-attachments/assets/7ea12988-07b6-4815-8274-773423aedc88)
![image](https://github.com/user-attachments/assets/4dcaa22d-b19a-4fe1-b9a2-8a78a863e660)
![image](https://github.com/user-attachments/assets/e79d904b-fa35-4583-87f2-472c44661e13)
### **Subscripciones a temas (topics)**
![image](https://github.com/user-attachments/assets/cce9fa20-2e63-46fe-bcd7-6efdf0b40c55)
![image](https://github.com/user-attachments/assets/c128f343-e7c6-4752-86de-9c08fbe454d2)
### **Conexion serial**
![image](https://github.com/user-attachments/assets/aac1b763-afe1-4e23-a363-97f0d69f7a90)

## **Portainer**
-------------------------------------------------------------------------------------------
````
File: docker-compose.yml
───────┼────────────────────────────────────────────────────────────────────────
   1   │ version: "3.8"
   2   │ services:
   3   │   portainer:
   4   │     image: portainer/portainer-ce:latest
   5   │     container_name: my_portainer
   6   │     restart: always
   7   │     ports:
   8   │       - "8000:8000"
   9   │       - "9000:9000"
  10   │     volumes:
  11   │       - /var/run/docker.sock:/var/run/docker.sock
  12   │       #- ./my_data/:data
  13   │ 
  14   │ volumes:
  15   │   my_data:
````

![image](https://github.com/user-attachments/assets/783d9e51-c940-44c0-99ef-3ef26815e7e1)

![image](https://github.com/user-attachments/assets/74154958-9c0d-4409-99df-41402327743f)

![image](https://github.com/user-attachments/assets/1a300454-78cd-4813-a7ce-020d5e320c2c)

## **Rabbitmq**
-------------------------------------------------------------------------------------------
````
       │ File: docker-compose.yml
───────┼────────────────────────────────────────────────────────────────────────
   1   │ version: "3.8"
   2   │ services:
   3   │     rabbitmq:
   4   │         image: rabbitmq:3.8-management-alpine
   5   │         container_name: my_rabbitmq
   6   │         environment:
   7   │             - RABBITMQ_DEFAULT_USER=guest
   8   │             - RABBITMQ_DEFAULT_PASS=guest
   9   │         ports:
  10   │             # AMQP protocol port
  11   │             - '3672:5672'
  12   │             # MQTT manprotocol port
  13   │             - '3883:1883'
  14   │             # MQTT plugin
  15   │             - '35675:15675'
  16   │             # MQTT Web Example
  17   │             - '35670:15670'
  18   │             # HTTP management UI
  19   │             - '15672:15672'
````
![image](https://github.com/user-attachments/assets/e0c9341d-2012-4e29-bbe1-9f7779c613e6)

![image](https://github.com/user-attachments/assets/c314bf89-1c8f-403d-a86d-c5bc6f13769f)

![image](https://github.com/user-attachments/assets/7d520de7-7117-4049-84e5-abd4f8c0c641)

![image](https://github.com/user-attachments/assets/8ea5bec0-4f14-450e-8854-5c8408882034)




