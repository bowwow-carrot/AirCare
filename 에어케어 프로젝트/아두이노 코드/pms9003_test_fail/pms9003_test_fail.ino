#include <SoftwareSerial.h>
#include <PMS.h>        // PMS센서용 라이브러리
#include <string.h>       // stoi 함수용

// PMS7003센서 통신용 소프트웨어시리얼
#define PMS_TX 1                // Tx: Tx
#define PMS_RX 3                // Rx: Rx

SoftwareSerial SerialForPMS(PMS_RX, PMS_TX);
PMS pms(SerialForPMS);
PMS::DATA data;

void setup()
{
  pms.passiveMode();  //수동모드
  pms.wakeUp();
  SerialForPMS.begin(PMS::BAUD_RATE);
  Serial.begin(115200);
}

void loop()
{
  long started = 0;  // 타이머용 변수 선언 및 초기화  Serial.begin(115200);   // 디버깅용

  if (millis() - started >= 2000) // 2초간격으로 측정
  {
    Serial.println("Go into Microbe mode");
    UpdatePMS();        // 미세먼지관련 함수 호출
    started = millis();     // 타이머기준 리셋
  }

}



/**********************************************************/
void UpdatePMS() {
  Serial.println("update PMS");
  // 변수 선언
  uint16_t number[3] = { 0 };
  char temp[10] = { 0 };
dsdaads
  SerialForPMS.listen();              // PMS센서가 연결된 시리얼포트 활성화
  while (SerialForPMS.available()) { SerialForPMS.read(); } // 버퍼에 남아있을 어떤 데이터를 미리 삭제
  pms.requestRead();      // PMS센서에 측정요청신호 보내기

  if (pms.readUntil(data)){
    Serial.println("reding PMS start");
    number[0] = data.PM_AE_UG_1_0;    // PM 1.0 (ug/m3)값 읽어서 변수에 저장
    utoa(number[0], temp, 10);      // 정수를 텍스트로 변환
    Serial.println(temp);
    
    number[1] = data.PM_AE_UG_2_5;    // PM 2.5 (ug/m3)값 읽어서 변수에 저장
    utoa(number[1], temp, 10);
    Serial.println(temp);
    
    number[2] = data.PM_AE_UG_10_0;   // PM 10.0 (ug/m3)값 읽어서 변수에 저장
    utoa(number[2], temp, 10);
    Serial.println(temp);
    
    Serial.println("reding PMS finish");
  }else{
    Serial.println("none");
  }
  
}
