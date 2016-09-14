#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>
#include <GSM.h>

// PIN Number
#define PINNUMBER ""

// APN data
#define GPRS_APN       "GPRS_APN" // replace your GPRS APN
#define GPRS_LOGIN     "login"    // replace with your GPRS login
#define GPRS_PASSWORD  "password" // replace with your GPRS password

File myFile;
int output_data;
int incomingByte = 0;   // for incoming serial data

// initialize the library instance
GPRS gprs;
GSM gsmAccess;     // include a 'true' parameter for debug enabled
GSMServer server(80); // port 80 (http default)

SoftwareSerial PortOne(10, 11);
SoftwareSerial PortTwo(8, 9);

void setup() {
  PortOne.begin(9600);
  PortTwo.begin(9600); 
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

// connection state
  boolean notConnected = true;

  // Start GSM shield
  // If your SIM has PIN, pass it as a parameter of begin() in quotes
  while(notConnected)
  {
    if((gsmAccess.begin(PINNUMBER)==GSM_READY) &
        (gprs.attachGPRS(GPRS_APN, GPRS_LOGIN, GPRS_PASSWORD)==GPRS_READY))
      	notConnected = false;
    else
    {
      Serial.println("Not connected");
      delay(1000);
    }
  }

  Serial.println("Connected to GPRS network");

  // start server
  server.begin();

  //Get IP.
  IPAddress LocalIP = gprs.getIPAddress();
  Serial.println("Server IP address=");
  Serial.println(LocalIP);
}

void loop() {

while(1){
        // send data only when you receive data:
	PortOne.listen();
        if (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.read();
		// open the file. note that only one file can be open at a time,
  		// so you have to close this one before opening another.
	  	myFile = SD.open("test.txt", FILE_WRITE);

	 	 // if the file opened okay, write to it:
	  	if (myFile) {
		    	Serial.print("Writing to test.txt...");
    			myFile.println((char) incomingByte);
    			// close the file:
    			myFile.close();
    			Serial.println("done.");
  		} else {
    			// if the file didn't open, print an error:
    			Serial.println("error opening test.txt");
  			}
		delay(30000);
		// re-open the file for reading:
  		myFile = SD.open("test.txt");
  		if (myFile) {
    		Serial.println("test.txt:");
    		// read from the file until there's nothing else in it:
    		while (myFile.available()) {
      			output_data = myFile.read();
    		}
    		// close the file:
    		myFile.close();
  		} else {
    			// if the file didn't open, print an error:
    			Serial.println("error opening test.txt");
  		}				

		PortTwo.listen();
		// if you've gotten to the end of the line (received a newline
     		// character)
		// listen for incoming clients
  		GSM3MobileClientService client = server.available();

		if (client)
		{  
			return 0;
		}
		if (client.available())
		{
			Serial.println("Receiving request!");
			bool sendResponse = false;
			while(char c=client.read()) {
			if (c == '\n') 
				sendResponse = true;
		}
       		if (sendResponse)
       		{
	        	// if you've gotten to the end of the line (received a newline
     			// character)
       			// send a standard http response header
          		client.println("HTTP/1.1 200 OK");
          		client.println("Content-Type: text/html");
          		client.println();
          		client.println("<html>");
          		// output the value of each analog input pin
            		client.print("Temperature value");
            		client.print(output_data );
            		client.println("<br />");      
          		client.println("</html>");
          		// necessary delay
          		delay(1000);
			// client.stop();
		}
}
	
}
