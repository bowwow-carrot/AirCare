#include <SoftwareSerial.h>
#include "PMS.h"

// PMS7003센서 통신용 소프트웨어시리얼
#define PMS_TX 1                // Tx: Tx
#define PMS_RX 3                // Rx: Rx
SoftwareSerial SerialForPMS(PMS_RX, PMS_TX);

//void readData();

#define DEBUG_OUT Serial
PMS pms(SerialForPMS);

void setup()
{
  pms.passiveMode();  //수동모드
  pms.wakeUp();
  SerialForPMS.begin(PMS::BAUD_RATE);
  DEBUG_OUT.begin(115200);

  DEBUG_OUT.println("테스트 텍스트 : setup");
}

void loop()
{
  DEBUG_OUT.println("테스트 텍스트 : loop");
  readData();
  delay(3000);
}

/***********************************************************/

void readData(){
  PMS::DATA data;
  while (Serial.available()) { Serial.read(); }

  DEBUG_OUT.println("#1 : 응답신호 보내는중...");
  pms.requestRead();
  DEBUG_OUT.println("#2 : 데이터 읽는중...");
  

  
  if (pms.readUntil(data))
  {
    DEBUG_OUT.println();

    DEBUG_OUT.print("PM 1.0 (ug/m3): ");
    DEBUG_OUT.println(data.PM_AE_UG_1_0);

    DEBUG_OUT.print("PM 2.5 (ug/m3): ");
    DEBUG_OUT.println(data.PM_AE_UG_2_5);

    DEBUG_OUT.print("PM 10.0 (ug/m3): ");
    DEBUG_OUT.println(data.PM_AE_UG_10_0);

    DEBUG_OUT.println();
  }
  else
  {
    DEBUG_OUT.println("####noData####");
  }
}
