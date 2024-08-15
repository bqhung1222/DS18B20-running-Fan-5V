#include <OneWire.h>
#include <DallasTemperature.h>


#define ONE_WIRE_BUS 27

#define FAN_PIN 26
int maxtemp;
int mintemp;
float temperatureC;
// Thiết lập OneWire với DS18B20
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  sensors.begin();
  analogWriteResolution(12);

  Serial.println("Nhập nhiệt độ min và nhấn Enter: ");
  while (Serial.available() == 0) {}  
  String minTempStr = Serial.readStringUntil('\n');  // Đọc chuỗi đến khi gặp ký tự Enter
  mintemp = minTempStr.toInt();  // Chuyển chuỗi thành số nguyên
  Serial.print("Nhiệt độ mix đã nhập: ");
  Serial.println(mintemp);  
  
  // Nhập giá trị nhiệt độ max
  Serial.println("Nhập nhiệt độ max và nhấn Enter: ");
  while (Serial.available() == 0) {}  
  String maxTempStr = Serial.readStringUntil('\n');  // Đọc chuỗi đến khi gặp ký tự Enter
  maxtemp = maxTempStr.toInt();  
  Serial.print("Nhiệt độ max đã nhập: ");
  Serial.println(maxtemp);  
}
void loop() {
  sensors.requestTemperatures();
  temperatureC = sensors.getTempCByIndex(0);
   

   
  if (temperatureC != DEVICE_DISCONNECTED_C) {
    Serial.print("Temperature: ");
    Serial.print(temperatureC);
    Serial.println(" °C");
    
    int speed =  2800 + (temperatureC - mintemp) * (4095-2800) / (maxtemp - mintemp);
    
    if(speed>=4095){
      Serial.println("Fan Max");
      analogWrite(FAN_PIN, 4095);
    }else{
    analogWrite(FAN_PIN, speed);
    Serial.println(speed);
    }
  } else {
    Serial.println("Could not read temperature data");
  }

  delay(1000);
}
