#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN D5
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();  
}

void loop() {
  float humi, temp;
  temp = dht.readTemperature(); // 현재 온도 감지
  humi = dht.readHumidity(); // 현재 습도 감지

  if(isnan(humi) || isnan(temp)){ // 온도와 습도를 감지하지 못하면?
      Serial.println("Failed to read from DHT"); // 에러 메시지 출력
      delay(1000);
      return;
    }

   // 온도 출력
   Serial.print("온도 : ");
   Serial.print(temp); 
   Serial.println("℃");

   // 습도 출력
   Serial.print("습도 : ");
   Serial.print(humi);
   Serial.println("%");
   
   delay(1000);
}
