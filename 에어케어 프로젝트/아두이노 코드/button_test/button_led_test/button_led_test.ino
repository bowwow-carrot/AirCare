// 사용할 핀 번호들을 사전에 정의해놓음
#define LED 7
#define BUTTON 4

void setup()
{
  Serial.begin(9600);

  pinMode(BUTTON, INPUT_PULLUP); // 5번 핀의 모드를 INPUT_PULLUP으로 설정
  pinMode(LED, OUTPUT); // 7번 핀의 모드를 OUTPUT으로 설정
}

void loop()
{
  if((digitalRead(BUTTON))==LOW){ //버튼이 눌렸으면?
    digitalWrite(LED, HIGH); // LED가 켜짐.
  }
  else{ //안눌렸다면?
    digitalWrite(LED, LOW); // LED가 꺼짐.
  }

  delay(100); // 100ms 단위로 반복
}