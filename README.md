# Temperature-Monitoring
Project is all about automatically uploading sensed temperature data values to server for Temperature monitoring

Components used for this project are :  Arduino + Zigbee as receiver + RTC + SD Card for storage
This receives temperature data from Zigbee connected LM35 sensors
Function:
Node sends data to Receiver
Receiver Arduino time stamps data coming in, stores it on Sd Card and transmits via SIM 900A module to server

