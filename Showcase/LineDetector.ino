// IR Sensor
int IR = 2;

// Motor Pins
int IN1 = 8;
int IN2 = 9;
int IN3 = 10;
int IN4 = 11;

// State control
int state = 0; 
// 0 = follow
// 1 = left search
// 2 = back search
// 3 = right search
// 4 = stop

unsigned long startTime = 0;

void setup() {
  pinMode(IR, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
}

// 🚗 Movement (SOFT CONTROL)

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void left() {
  // Soft LEFT (45° type)
  digitalWrite(IN1, LOW);   // left motor stop
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);  // right motor forward
  digitalWrite(IN4, LOW);
}

void right() {
  // Soft RIGHT (45° type)
  digitalWrite(IN1, HIGH);  // left motor forward
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);   // right motor stop
  digitalWrite(IN4, LOW);
}

void back() {
  // Soft BACK (controlled)
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopCar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {
  int sensor = digitalRead(IR);
  unsigned long currentTime = millis();

  // ✅ BLACK detected → follow
  if (sensor == HIGH) {
    forward();
    state = 0;
    return;
  }

  // ❌ WHITE detected → start search
  if (sensor == LOW && state == 0) {
    state = 1;
    startTime = currentTime;
  }

  // 🔍 LEFT search (short)
  if (state == 1) {
    left();
    if (sensor == HIGH) {
      state = 0;
    }
    else if (currentTime - startTime > 300) { // reduced time
      state = 2;
      startTime = currentTime;
    }
  }

  // 🔙 BACK search (short)
  else if (state == 2) {
    back();
    if (sensor == HIGH) {
      state = 0;
    }
    else if (currentTime - startTime > 400) {
      state = 3;
      startTime = currentTime;
    }
  }

  // 🔍 RIGHT search (short)
  else if (state == 3) {
    right();
    if (sensor == HIGH) {
      state = 0;
    }
    else if (currentTime - startTime > 400) {
      state = 4;
    }
  }

  // ⛔ STOP (no line found)
  else if (state == 4) {
    stopCar();
  }
}
