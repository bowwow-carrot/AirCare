#include <SoftwareSerial.h>
#include "PMS.h"

// PMS7003센서 통신용 소프트웨어시리얼
#define PMS_TX 1                // Tx: Tx
#define PMS_RX 3                // Rx: Rx
#define DEBUG_OUT Serial

SoftwareSerial Serial_PMS(PMS_TX, PMS_RX);

char pms[32];

void readData();

void setup()
{
  DEBUG_OUT.begin(115200);
  Serial_PMS.begin(9600);
  
  DEBUG_OUT.println("테스트 텍스트 : setup");
}

void loop()
{
  readData();
  delay(3000);
}

/***********************************************************/

void readData(){
  
  DEBUG_OUT.println("#1 : 시리얼 초기화 중...");
  if(Serial_PMS.available()>=32){
    for(int j=0; j<32; j++){
      pms[j] = Serial_PMS.read();
    }
    DEBUG_OUT.println("#2 : 데이터 읽는중...");
    DEBUG_OUT.println(pms);
    DEBUG_OUT.println();
  }
  
}
