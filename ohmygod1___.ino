int distance;             /*  초음파센서로 모터제어 하기  */
int trigPin1 = 12;
int echoPin1 = 11;
int trigPin2 = 10;
int echoPin2 = 9;
int trigPin3 = 8;
int echoPin3 = 7;

#define IN1 6  // L298모듈의 제어 신호 입력 핀 번호 지정

#define IN2 5

#define IN3 4

#define IN4 3



int servoPin = 2;     // 서보모터 연결 포트

long duration1, distance1;
long duration2, distance2;
long duration3, distance3;


void forward() {      // L298 제어용 전진 함수

  digitalWrite(IN1, HIGH);

  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);

  digitalWrite(IN4, LOW);
}



void back() {         // 후진

  digitalWrite(IN1, LOW);

  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);

  digitalWrite(IN4, HIGH);
}



void left() {         // 좌회전(왼쪽모터 멈춤:오른쪽모터 전진)

  digitalWrite(IN1, LOW);

  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);

  digitalWrite(IN4, LOW);
}



void right() {      // 우회전(왼쪽모터 전진:오른쪽모터 멈춤)

  digitalWrite(IN1, HIGH);

  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);

  digitalWrite(IN4, LOW);
}



void stop() {       // 정지

  digitalWrite(IN1, LOW);

  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);

  digitalWrite(IN4, LOW);
}



void setup( )  {

  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT); // trigPin을 출력으로
  pinMode(echoPin1, INPUT); // echoPin을 입력이다.
  pinMode(trigPin2, OUTPUT); // trigPin을 출력으로
  pinMode(echoPin2, INPUT); // echoPin을 입력이다.
  pinMode(trigPin3, OUTPUT); // trigPin을 출력으로
  pinMode(echoPin3, INPUT); // echoPin을 입력이다.


  delay(1000);

}



float getDistanceCM1() {      // 초음파 센서 거리 측정 함수(단위:cm)
  digitalWrite(trigPin1, LOW); //초음파 센서를 초기화 하는 과정입니다.
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH); // 트리거 핀에서 나온 펄스를 받아서
  distance1 = duration1 * 0.034 / 2; // 거리를 측정합니다.

  if (distance1 >= 500 || distance1 <= 0) { //500보다 크거나, 0보다 작으면 측정이 불가하다는 것을 프린트합니다.
    Serial.println("Out of range"); //측정 불가 라는 것을 프린트 합니다.
  }
  else {
    Serial.print ( "Sensor1 : "); //센서 1에
    Serial.print ( distance1);// 거리 값
    
    Serial.println("cm"); // cm를 출력합니다.
  }

}
void getStableDistanceCM1() {

  int CmSum1 = 0;

  for (int i = 0; i < 8; i++) {

    CmSum1 += getDistanceCM1();  //예, 'sum = sum + cm' 과 동일
    CmSum1 = CmSum1 / 8;
  }
  if (CmSum1 >= 25 || CmSum1 <= 50) {
    left();

  }

}
float getDistanceCM2() {      // 초음파 센서 거리 측정 함수(단위:cm)
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 * 0.034 / 2;

  if (distance2 >= 500 || distance2 <= 0) {
    Serial.println("Out of range");
  }
  else {
    Serial.print("Sensor2 : ");
    Serial.print (distance2);
    Serial.println("cm");
  }


  return distance2;

}

void getStableDistanceCM2() {

  int CmSum2 = 0;

  for (int i = 0; i < 8; i++) {

    CmSum2 += getDistanceCM2();  //예, 'sum = sum + cm' 과 동일
    CmSum2 = CmSum2 / 8;
  }
  if (CmSum2 >= 25 || CmSum2 <= 50) {
    forward();



  }
}
float getDistanceCM3() {      // 초음파 센서 거리 측정 함수(단위:cm)
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  distance3 = duration3 * 0.034 / 2;

  if (distance3 >= 500 || distance3 <= 0) {
    Serial.println("Out of range");
  }
  else {
    Serial.print("Sensor3 : ");
    Serial.print(distance3);
    Serial.println("cm");
  }



}

void getStableDistanceCM3() {

  int CmSum3 = 0;

  for (int i = 0; i < 8; i++) {

    CmSum3 += getDistanceCM3();  //예, 'sum = sum + cm' 과 동일
    CmSum3 = CmSum3 / 8;
  }
  if (CmSum3 >= 25 || CmSum3 <= 50) {
    right();

  }
}




void loop( ) {
  stop();

  delay(300);
  getStableDistanceCM1();
  delay(500);
  getStableDistanceCM2();
  delay(500);
  getStableDistanceCM3();


}
