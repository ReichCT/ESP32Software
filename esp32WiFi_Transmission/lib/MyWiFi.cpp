#include <WiFi.h>
void StartWiFi(){
  // const char *ssid = "CU_2MXh"; //网络名称
  // const char *password = "wtsk53ty"; //网络密码
  const char *ssid = "BY"; //网络名称
  const char *password = "71000915"; //网络密码
  // const char *ssid = "ESP32_wifi"; //网络名称
  // const char *password = "12345678"; //网络密码

  WiFi.begin(ssid, password); //连接网络
  while (WiFi.status() != WL_CONNECTED) //等待网络连接成功
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected, IP address: ");
  Serial.println(WiFi.localIP()); //打印模块IP
}

void StartAPWiFi(){
  const char *AP_ssid = "ESP32_wifi";
  const char *password = "12345678";
  IPAddress local_IP(192,168,4,1);
  IPAddress gateway(192,168,4,9);
  IPAddress subnet(255,255,255,0);

  WiFi.mode(WIFI_AP);//设置为接入点模式
  WiFi.softAPConfig(local_IP, gateway, subnet);//配置接入点的IP，网关IP，子网掩码
  Serial.println("Configuring AP WiFi... ");
  WiFi.softAP(AP_ssid, password,3,1);//启动校验式网络（需要输入账号密码的网络）,通道为3，wifi隐藏，最大连接数=4
  int flag = WiFi.softAP(AP_ssid, password);//监控状态变量result 
  if(flag){
    Serial.println("AP set successful");
    //打印IP地址
    Serial.print("WiFi IP address: ");
    Serial.println(WiFi.softAPIP());  //串口输出热点的IP地址
  }
  else{
    Serial.println("AP set failed");
  }
}