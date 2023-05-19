/**************************************************************************************************************************************
  This code is TOP SECRET and only members of Fyryyx should be able to access this
 ***************************************************************************************************************************************/
#define USE_WIFI_NINA         false
#define USE_WIFI101           true
#include <WiFiWebServer.h>
#include <WiFiUdp.h>

const char ssid[] = "EEERover";
const char pass[] = "exhibition";
const int groupNumber = 7; // Set your group number to make the IP address constant - only do this on the EEERover network

//Webpage to return when root is requested
const char webpage[] = \
"<html><head><style>\
.btn {background-color: inherit;padding: 14px 28px;font-size: 16px;}\
.btn:hover {background: #eee;}\
</style></head>\
<body>\
<button class=\"btn\" onclick=\"ledOn()\">LED On</button>\
<button class=\"btn\" onclick=\"ledOff()\">LED Off</button>\
<br>LED STATE: <span id=\"state\">OFF</span>\
</body>\
<script>\
var xhttp = new XMLHttpRequest();\
xhttp.onreadystatechange = function() {if (this.readyState == 4 && this.status == 200) {document.getElementById(\"state\").innerHTML = this.responseText;}};\
function ledOn() {xhttp.open(\"GET\", \"/on\"); xhttp.send();}\
function ledOff() {xhttp.open(\"GET\", \"/off\"); xhttp.send();}\
</script></html>";

WiFiWebServer server(80);
WiFiUDP udp;

//Return the web page
void handleRoot()
{
  server.send(200, F("text/html"), webpage);
}

//Switch LED on and acknowledge
void ledON()
{
  digitalWrite(LED_BUILTIN,1);
  server.send(200, F("text/plain"), F("ON"));
}

//Switch LED on and acknowledge
void ledOFF()
{
  digitalWrite(LED_BUILTIN,0);
  server.send(200, F("text/plain"), F("OFF"));
}

//Generate a 404 response with details of the failed request
void handleNotFound()
{
  String message = F("File Not Found\n\n"); 
  message += F("URI: ");
  message += server.uri();
  message += F("\nMethod: ");
  message += (server.method() == HTTP_GET) ? F("GET") : F("POST");
  message += F("\nArguments: ");
  message += server.args();
  message += F("\n");
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, F("text/plain"), message);
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);

  Serial.begin(9600);

  //Wait 10s for the serial connection before proceeding
  //This ensures you can see messages from startup() on the monitor
  //Remove this for faster startup when the USB host isn't attached
  while (!Serial && millis() < 10000);  

  Serial.println(F("\nStarting Web Server"));

  //Check WiFi shield is present
  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println(F("WiFi shield not present"));
    while (true);
  }

  //Configure the static IP address if group number is set
  if (groupNumber)
    WiFi.config(IPAddress(192,168,0,groupNumber+1));

  // attempt to connect to WiFi network
  Serial.print(F("Connecting to WPA SSID: "));
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED)
  {
    delay(500);
    Serial.print('.');
  }

  //Register the callbacks to respond to HTTP requests
  server.on(F("/"), handleRoot);
  server.on(F("/on"), ledON);
  server.on(F("/off"), ledOFF);

  server.onNotFound(handleNotFound);
  
  server.begin();
  
  Serial.print(F("HTTP server started @ "));
  Serial.println(static_cast<IPAddress>(WiFi.localIP()));

  // Establish UDP connection
  udp.begin(1234);
}

//Call the server polling function in the main loop
void loop()
{
  server.handleClient();

  // Recieve and process UDP packets
  int packetSize = udp.parsePacket();
  if (packetSize) {
    char buffer[255];
    int len = udp.read(buffer, sizeof(buffer));
    if (len > 0) {
      buffer[len] = '\0'; // Add null-terminator to create a valid C-string

      // Process the received data as neededs
    }
  }
}