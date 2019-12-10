#include <SPI.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetUdp.h>
#include <EthernetServer.h>

// network configuration.  gateway and subnet are optional.

 // the media access control (ethernet hardware) address for the shield:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };  
//the IP address for the shield:
byte ip[] = { 192, 168, 10, 49 };    
// the router's gateway address:
byte gateway[] = { 192, 168, 10, 1 };
// the subnet:
byte subnet[] = { 255, 255, 0, 0 };

// telnet defaults to port 23
//EthernetServer debug = EthernetServer(24);
EthernetServer server = EthernetServer(23);

String inputString = "";         // a String to hold incoming data
String etherString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
bool ethStringComplete = false;
bool ESC = false;
bool alreadyConnected=false;
char last_c=0;
char slast_c=0;

void setup() {
  // initialize serial:
  Serial.begin(19200);
  // reserve 200 bytes for the inputString:
  inputString.reserve(2000);
  etherString.reserve(2000);
  
  // initialize the ethernet device
  Ethernet.begin(mac, ip, gateway, subnet);
  // start listening for clients
  server.begin();
}

void loop() {
  EthernetClient client = server.available();
  char c;
  if(client) 
  {
    if (!alreadyConnected) {
      // clean out the input buffer:
      client.flush();
      alreadyConnected = true;
    }
    
    while(client.available() > 0){
      c = client.read();

      // exit 
      if ( ESC ) {
        ESC=false;
        if (c == '.' ){
          client.print("\n\nTCHAU!\n\n");
          client.stop();
          alreadyConnected = false;
          return;
        }
      }
  
      // ESC char
      if (c == '~' ) {
        ESC=true;
        return;
      }
      Serial.write(c);
      last_c = c;
    }
  }
    

  // transfer all bytes to the cmdServer
  // (all connected clients will recieve it)
  char sc=0;
  while(Serial.available() > 0){
    sc = Serial.read();
    if( sc==c ){
      // do nothing
    }else{
      server.write(sc);
    }

//    char buf[12]; // "-2147483648\0"
//    debug.println(itoa(sc, buf, 10));

    slast_c = sc;
  }
}

