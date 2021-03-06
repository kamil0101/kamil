#include <SPI.h>
#include <Ethernet.h>
#include <dht11.h>

int fotoPin = A0;    
int fotoDane=0;

dht11 DHT11;
  
#define DHT11PIN 2

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x04
};
IPAddress ip(192,168,0,5);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

const char page_start[] = "<!DOCTYPE html><html lang=\"en\"><head><title>NAZWA STRONY</title><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css\">  <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script><script src=\"https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js\"></script><script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js\"></script></head><body><div class=\"container\"><h2>OPIS PROJEKTU</h2><p>COKOLWIEK</p><div class=\"card-deck\">";
const char page_end[] = "</div></div></body></html>";

String temp_buildCard;
String temp_buildPage;

const String par_names[3][3] = {
  {"temp_PL","temp_EN","temp_DE"},
  {"hum_PL","hum_EN","hum_DE"},
  {"prox_PL","prox_EN","prox_DE"}};

String par_values[6] = {"13*C","13%","13","4","5","6"};


void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Ethernet WebServer Example");

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);

  // Check for Ethernet hardware present

  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

int czas=0  ;

void czytajSensory()
{
  DHT11.read(DHT11PIN);
  float temp = (float)DHT11.temperature;
  Serial.print("AAAAAAAAAAAAAAAAAAAAA");
  Serial.print(temp);
  par_values[0] = (((String)temp));
  par_values[2] = (String)analogRead(fotoPin);  
}



void loop() {
    if(czas<millis())
  {
    czytajSensory();
    Serial.println( par_values[1]);
    Serial.println( par_values[2]);
    czas+=3000;
  }
  // listen for incoming clients
  EthernetClient client = server.available();

  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println(page_start);
          client.println("Compilation date: ");
          client.println(__DATE__);
          client.println("Compilation time: ");
          client.println(__TIME__);
 for(int i = 0; i<3;i++)
 {   
  client.println("<div class=\"card bg-primary\"><div class=\"card-body text-center\"><p class=\"card-text\">");
  client.println(par_names[i][1]);
  Serial.println(i);
  Serial.println(par_names[i][1]);
  client.println("</p><p class=\"card-text\">");
  Serial.println(par_values[i]);
  client.println(par_values[i]);
  client.println("</p> </div></div>");
}         

          client.println(page_end);
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}
