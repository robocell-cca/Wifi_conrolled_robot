/* © Robocell,CCA */
/* This code is given during Autonomous robotics workshop organised  by Robocell,CCA on 14 & 15th September,2019. */
/* Follow us on https://www.facebook.com/ccanitd.in/ 
/* For queries/help mail us at robocell@ccanitd.in 
 * Visit us at-www.ccanitd.in*/

/* FUNCTIONING:
 *This is the code for smart bot controlled wirelessly using wifi  */

/*SETUP:
 * 1.Go to playstore and install Wifi RC Car ESP8266.
 * 2.connect your mobile to the network hosted by Nodemcu.
 * 3.Go to settings of the application and enter the ip address.
 * 4.set the commands in the application.
 * HAVE FUN.............
 */
 
#include <ESP8266WiFi.h>                     /*Importing the libraries which enable WiFi communication.*/
#include <ESP8266WebServer.h>

// SSID parameters
const char *ssid = "NodeMCU Hotspot";                      /*Set as your hotspot name.*/
const char *password = "12345678*";                  /*set password.*/

IPAddress ip(192, 168, 4, 1);               /* IP Address-Enter the same ip in the app.*/
IPAddress netmask(255, 255, 255, 0);        /*Its like the address your device will search for , when it emits the signal.*/
const int port = 80; // Port
ESP8266WebServer server (port);


/* define L298N or L293D motor control pins */
int leftMotorBackward = D1;                 /* (D1) -> IN1  */
int leftMotorForward = D2;                  /* (D2) ->IN2   */
int rightMotorForward = D3;                 /* (D3) -> IN3   */
int rightMotorBackward = D4;                /* (D4) -> IN4  */




void setup() {
  
  Serial.begin(115200);                     
 
  pinMode(D5, OUTPUT);                      /* LED pin*/

   // Setup AP
  WiFi.mode(WIFI_AP); 
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(ip, ip, netmask);

  // Declaration of motors
  pinMode(leftMotorForward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT); 
  pinMode(leftMotorBackward, OUTPUT);  
  pinMode(rightMotorBackward, OUTPUT);


  // Start Server
  server.on("/", HTTP_GET, onConnect);
  server.on("/move", HTTP_GET, handleRequest);          /*Here / is the root page of the server.*/
  server.begin();
  
}


void loop() {

  server.handleClient();                     /*Function which constantly checks whether there is any data sent from the server.*/

}

void onConnect(){
  Serial.println("Connected!");
  server.send(200, "text / plain", "Successful");  
}

void handleRequest() {
  Serial.println("Connected!");
  
  if (server.hasArg("dir")) {             /*Checking whether the data sent by the device contains the argument "State".*/
    
    String value = server.arg("dir");     /*Value is a String which stores the argument sent by the device connected to network.*/
    Serial.println("Value = " + value);
    server.send(200, "text / plain", "Request received");   /*Send a confirmation to the device that their data has been recieved.*/

    /*Applying basic if-else statements to Drive the robot according to the argument sent by device
     For example , value  contains F , then forward() is called , If it contains B , it goes backward
     */
    
    if (value.equals("F")) {                                
      forward();
    }
    else  if (value.equals("B")) {
      backward();
    }
    else  if (value.equals("L")) {
      left();
    }
    else  if (value.equals("R")) {
     right();
    }
    else  if (value.equals("S")) {
      stop_bot();
    }
     else  if (value.equals("ON")) {
      ON();
    }
     else  if (value.equals("OFF")) {
      OFF();
    }
  }
}



/*************** FORWARD *******************/
void forward(void)   
{
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorBackward,LOW);
}

/*************** BACKWARD *******************/
void backward()   
{
  digitalWrite(leftMotorBackward,HIGH);
  digitalWrite(rightMotorBackward,HIGH);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,LOW);
}

/*************** TURN LEFT *******************/
void left()   
{
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorBackward,LOW);
  digitalWrite(leftMotorForward,LOW);
}



/*************** TURN RIGHT *******************/
void right()   
{
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,LOW);
}


/*************** STOPS THE BOT *******************/
void stop_bot()   
{
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,LOW);
}
/*************** ON *******************/
void ON()   
{
  digitalWrite(D5,HIGH);
}
/*************** OFF *******************/
void OFF()   
{
  digitalWrite(D5,LOW);
}
