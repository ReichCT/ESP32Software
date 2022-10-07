#include <Arduino.h>
#include <BluetoothSerial.h>

// 用于计时
unsigned long long t_now;
BluetoothSerial SerialBT;

const int trigPin = 5;
const int echoPin = 18;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

void get_data_and_send();
double Measure_distance();

void setup() {
  Serial.begin(115200); // Starts the serial communication
  SerialBT.begin("esp32-bluetooth2"); // 如果没有参数传入则默认是蓝牙名称是: "ESP32"
  SerialBT.setPin("1234");   // 蓝牙连接的配对码
  Serial.printf("BT initial ok and ready to pair. \r\n");
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void loop() {
  get_data_and_send();
  delay(100);
}

void get_data_and_send(){
    char Time[256],Data[256];
    double data = Measure_distance();
    // Serial.println(data);
    t_now = millis();
    sprintf(Time, "Time=%d,",t_now);
    sprintf(Data, "data=%f;",data);
    SerialBT.print(strcat(Time,Data));
}

double Measure_distance(){
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;

  return distanceCm;
}