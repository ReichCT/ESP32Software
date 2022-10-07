#include <Arduino.h>
#include <BluetoothSerial.h>

// 用于计时
unsigned long long t_now;

BluetoothSerial SerialBT;

void setup()
{
    Serial.begin(115200);
    SerialBT.begin("esp32-bluetooth"); // 如果没有参数传入则默认是蓝牙名称是: "ESP32"
    SerialBT.setPin("1234");   // 蓝牙连接的配对码
    Serial.printf("BT initial ok and ready to pair. \r\n");
}

void receive_data_and_process();
void get_data_and_send();

void loop()
{
    receive_data_and_process();
    get_data_and_send();
    delay(100);
}

void receive_data_and_process(){
    if (SerialBT.available()){
        Serial.write(SerialBT.read());
    }
}

void get_data_and_send(){
    char Time[256],Data[256];
    double data = touchRead(T0);
    // Serial.println(data);
    t_now = millis();
    sprintf(Time, "Time=%d,",t_now);
    sprintf(Data, "data=%f;",data);
    SerialBT.print(strcat(Time,Data));
}