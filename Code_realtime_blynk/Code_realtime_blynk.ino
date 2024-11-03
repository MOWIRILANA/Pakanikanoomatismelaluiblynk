//Deklarasi Servo
#include <ESP32Servo.h>
static const int servoPin = 26;
Servo myservo;

//Deklarasi Led
#define led 2

//Deklarasi Blynk
#define BLYNK_TEMPLATE_ID "TMPL631L-yVKA"
#define BLYNK_TEMPLATE_NAME "IoTFishFeeder"
#define BLYNK_AUTH_TOKEN "M98Ct_eQp95rqcQuCVm07P_lYfXeW0d5"
#include <BlynkSimpleESP32.h>

//Deklarasi WiFi
char ssid[]="SSID";
char pass[]="mowirilana";

int start;

void setup(){
  //Serial Monitor
  Serial.begin(115200);
  //Setting Servo
  myservo.attach(servoPin);
  myservo.write(0);
  //Setting led
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  // Setting WiFi
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("WiFi Connected");

  // Setting Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.println("Blynk Connected");
  delay(500);
}

void makan(){
  Serial.println("Makan Yok");
  for(int pos = 0; pos<=180;pos++)
  {
    myservo.write(pos);
    delay(10);
  }

  for (int pos = 180;pos>=0;pos--)
  {
    myservo.write(pos);
    delay(10);
  }
}

void loop(){
  digitalWrite(led, LOW);
  //Menjalankan sistem blynk
  Blynk.run();
  if(start == 1)
  {
    makan();
    digitalWrite(led, HIGH);
    delay(1000);
    while(true);
  }
}

BLYNK_WRITE(V1)
{
  start = param.asInt();
}

