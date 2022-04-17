#include <ESP8266WiFi.h>

const char* ssid = ""; //put your SSID here
const char* passwd = ""; //put your password here

WiFiServer server(80);

int ENA = 4;
int INA1 = 0;
int INA2 = 2;

int ENB = 14;
int INB1 = 12;
int INB2 = 13;

void setup() {
  // put your setup code here, to run once:

  pinMode(ENA, OUTPUT);
  pinMode(INA1, OUTPUT);
  pinMode(INA2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(INB1, OUTPUT);
  pinMode(INB2, OUTPUT);

  Serial.begin(115200);
  delay(10);
  WiFi.begin(ssid, passwd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" ");
  Serial.println("WiFi Connected!");

  server.begin();
  Serial.println("Server Started!");
  Serial.println(WiFi.localIP());
}


void loop() {
  // put your main code here, to run repeatedly:

  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  while (!client.available()) {
    delay(1);
  }

  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();


  if (request.indexOf("/forward") != -1) {
    forward();
  }
  if (request.indexOf("/back") != -1) {
    back();
  }

  if (request.indexOf("/left") != -1) {
    left();
  }

  if (request.indexOf("/right") != -1) {
    right();
  }

  if (request.indexOf("/brake") != -1) {
    brake();
  }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<title> Internet Controlled Car </title>");
  client.println("</head>");
  client.println("<body>");
  client.println("<h1>Internet Controlled Car</h1>");
  client.println("<p> Drive the f****ing car! </p>");
  client.println("<h2> Control Options </h2>");
  client.println("<li/> <a href='/forward'> Accelerate Forward </a>");
  client.println("<li/> <a href='/back'> Accelerate Backward </a>");
  client.println("<li/> <a href='/left'> Turn Left </a>");
  client.println("<li/> <a href='/right'> Turn Right </a>");
  client.println("<li/> <a href='/brake'> STOP! </a>");
  client.println("</body>");
  client.println("</html>");

}

void forward() {
  analogWrite(ENB, 900);
  digitalWrite(INB1, LOW);
  digitalWrite(INB2, HIGH);

  analogWrite(ENA, 900);
  digitalWrite(INA1, LOW);
  digitalWrite(INA2, HIGH);

  delay(250);
  brake();
}

void right() {
  analogWrite(ENB, 1023);
  digitalWrite(INB1, LOW);
  digitalWrite(INB2, HIGH);

  delay(500);
  brake();
}

void left() {
  analogWrite(ENA, 1023);
  digitalWrite(INA1, LOW);
  digitalWrite(INA2, HIGH);
  delay(500);
  brake();
}

void back() {
  analogWrite(ENB, 900);
  digitalWrite(INB1, HIGH);
  digitalWrite(INB2, LOW);

  analogWrite(ENA, 900);
  digitalWrite(INA1, HIGH);
  digitalWrite(INA2, LOW);

  delay(250);
  brake();
}

void brake() {
  digitalWrite(ENB, LOW);
  digitalWrite(ENA, LOW);
}
