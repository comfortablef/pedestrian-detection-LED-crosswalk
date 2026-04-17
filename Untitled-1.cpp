// 보행자 감지 스마트 LED 횡단보도
// 초음파 센서 거리값을 이용해 보행자 접근 시 LED를 점등하는 프로토타입

// ------------------------------
// 핀 설정
// ------------------------------
const int TRIG_PIN = 9;
const int ECHO_PIN = 10;
const int LED_PIN  = 7;

// ------------------------------
// 설정값
// ------------------------------
const float DETECTION_DISTANCE_CM = 100.0;   // 감지 기준 거리(cm)
const int SAMPLE_DELAY_MS = 100;             // 측정 주기(ms)

// ------------------------------
// 초기 설정
// ------------------------------
void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(TRIG_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  Serial.println("Smart LED Crosswalk System Start");
}

// ------------------------------
// 초음파 센서 거리 측정 함수
// ------------------------------
float getDistanceCm() {
  // 초음파 송신
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // 초음파 수신 시간 측정
  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // timeout 30ms

  // timeout 시 유효하지 않은 값 반환
  if (duration == 0) {
    return -1.0;
  }

  // 거리 계산 (음속 기준)
  float distance = duration * 0.0343 / 2.0;
  return distance;
}

// ------------------------------
// 메인 루프
// ------------------------------
void loop() {
  float distance = getDistanceCm();

  if (distance > 0) {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // 보행자 접근 판단
    if (distance <= DETECTION_DISTANCE_CM) {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("Pedestrian detected -> LED ON");
    } else {
      digitalWrite(LED_PIN, LOW);
      Serial.println("No pedestrian -> LED OFF");
    }
  } else {
    // 측정 실패 시 LED OFF
    digitalWrite(LED_PIN, LOW);
    Serial.println("Sensor timeout -> LED OFF");
  }

  delay(SAMPLE_DELAY_MS);
}