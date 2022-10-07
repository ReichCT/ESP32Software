#include <WiFi.h>
#include "../lib/MyWiFi.cpp"

// 用于计时
unsigned long long t_now;

void setup(){
  Serial.begin(115200);// 启动串口通讯
  StartWiFi();         // 启动并连接WiFi
}

// 创建TCP client
WiFiClient client; //声明一个ESP32客户端对象，用于与服务器进行连接
const IPAddress serverIP(192,168,43,168); //欲访问的服务端IP地址
uint16_t serverPort = 8888;//服务端口号
void get_data_and_send();
void receive_data_and_process();

void loop(){
    Serial.println("Trying to access the server");
    if (client.connect(serverIP, serverPort)){ //尝试访问目标地址
        Serial.println("Successfully Accessed!");
        client.print("Successfully Accessed!");
        
        while (client.connected() || client.available()) //如果已连接或有收到的未读取的数据
        {
            receive_data_and_process();
            get_data_and_send();
            delay(1000);
        }

        Serial.println("Connection loss, will retry after 1 second");
        client.stop(); //关闭客户端
    }
    else{
        Serial.println("Access failed, will retry after 1 second");
        client.stop(); //关闭客户端
    }

    delay(1000);//暂停1s重试
}

void get_data_and_send(){
  char Time[256],Data[256];
  double data = touchRead(T0);
  // Serial.println(data);
  t_now = millis();
  sprintf(Time, "Time=%d,",t_now);
  sprintf(Data, "data=%f;",data);
  client.print(strcat(Time,Data));
}

void receive_data_and_process(){
  if (client.available()){ //如果有数据可读取
      String line = client.readStringUntil('\n'); //读取数据到换行符
      Serial.print("Data Read: ");
      Serial.println(line);
  }
}