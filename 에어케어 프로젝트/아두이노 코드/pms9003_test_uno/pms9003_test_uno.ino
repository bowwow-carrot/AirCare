/*
 Name:    PMS_Monitor.ino
 Created: 2019-03-05 오후 3:40:07
 Author:  kwonkyo
  PMS7003 센서를 사용해서 미세입자농도를 측정하고, 측정된 Data를 시리얼모니터로 확인하는 코드입니다. 
  아두이노가 시리얼모니터와 연결된 상태에서 전원이 들어가면, 시리얼 모니터에서 사용자 입력을 기다립니다. 사용자가 정수값을 입력하면 센서가 켜지고 센서 부팅에 필요한 시간만큼 기다렸다가 준비가 되면 입력된 횟수 만큼 측정을 연속적으로 하고 대기상태로 들어갑니다. (PMS라이브러리 예제 참조)
*/

#include <PMS.h>
#include <SoftwareSerial.h>

// 소프트웨어시리얼 포트를 설정하고 PMS7003센서 통신용으로 연결
#define SoftRX 7
#define SoftTX 6
SoftwareSerial mySerial(SoftRX, SoftTX);
PMS pms(mySerial);

// 디버깅용 시리얼은 하드웨어시리얼 포트를 사용합니다.
#define DEBUG_OUT Serial

// 측정 간격 설정
// :::|------|------|------|::::::::::|------|------|------|:::::::::::
//    ↑     ↑     ↑           ↑              ↑
//   요청   측정   측정   다음요청시까지_대기   측정간격(차수내)
static const uint32_t PMS_READ_DELAY = 30000;   // 센서 부팅후 대기시간 (30 sec)
static const uint32_t PMS_READ_GAP = 3000;      // 측정간격 (1 sec)

// 전역변수 선언
uint8_t cycles = 0;   // 반복측정 횟수
bool PMS_POWER = false; // PMS7003센서의 동작상태

// the setup function runs once when you press reset or power the board
void setup() {
  // 시리얼 포트 열기
  DEBUG_OUT.begin(115200);    // 디버깅용
  mySerial.begin(PMS::BAUD_RATE); // 소프트 시리얼용

  // 패시브모드로 변경 후 센서 대기상태로 설정
  pms.passiveMode();
  pms.sleep();
  DEBUG_OUT.println("반복측정 횟수를 입력하세요.");
}

// the loop function runs over and over again until power down or reset
void loop() {
  // 센서동작여부를 판단에 사용할 타이머 변수
  static uint32_t timerLast = 0;    // 센터부팅시작시간 (값이 유지되도록 정적변수 사용
  static uint32_t timerBefore = 0;  // 직전측정시간
  
  // 시리얼모니터로 값을 입력받아 입력받은 값을 cycles 변수에 할당
  if (DEBUG_OUT.available()) {
    cycles = DEBUG_OUT.parseInt();  //한번에 몇번을 측정할지 입력받기
    DEBUG_OUT.print(cycles);
  }

  // 측정요청이 있으면 센서를 깨우고 깨운 시간을 기억
  if (!PMS_POWER && cycles > 0) {
    DEBUG_OUT.println("Waking up.");
    pms.wakeUp();
    timerLast = millis();
    PMS_POWER = true;
  }

  // 입력받은 cycles 수만큼 측정 
  //   센서가 깨어나고나서 최소대기상태를 지났을 때만 측정간격을 두고 측정 실시
  while (cycles > 0) {
    uint32_t timerNow = millis();
    if (timerNow - timerLast >= PMS_READ_DELAY) {
      if (timerNow - timerBefore >= PMS_READ_GAP) {
        timerBefore = timerNow;
        readData();
        cycles--;
      }
    }
  }

  // 측정이 끝나면 cycles 변수는 0이되었기 때문에 센서를 대기모드로 바꾸고 다음 측정요청을 대기
  if (PMS_POWER && cycles == 0) {
    DEBUG_OUT.println("Going to sleep.");
    DEBUG_OUT.println("반복측정 횟수를 입력하세요.");
    pms.sleep();
    PMS_POWER = false;
  }
}

// PMS7003센서에 측정요청을 하고 데이터를 읽어와서 시리얼 화면에 표시하는 함수
void readData()
{
  PMS::DATA data;

  // Clear buffer (removes potentially old data) before read. Some data could have been also sent before switching to passive mode.
  while (Serial.available()) { Serial.read(); }

  DEBUG_OUT.println("Send read request...");
  pms.requestRead();

  DEBUG_OUT.println("Reading data...");
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
    DEBUG_OUT.println("No data.");
  }
}

//test this file
