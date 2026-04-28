int irSensor = A1;

// Motor pins
int IN1 = 8;
int IN2 = 9;
int IN3 = 10;
int IN4 = 11;

void setup() {
  pinMode(irSensor, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(irSensor);

  if (sensorValue > 500) {
    // ✅ No obstacle → forward
    forward();
  }
  else {
    // ❌ Obstacle detected

    stopMotors();
    delay(500);

    backward();
    delay(1000);

    stopMotors();
    delay(500);

    // 🔀 Turn (left ya right)
    turnRight();   // tum yaha turnLeft() bhi use kar sakti ho
    delay(1000);
  }
}

// 🔹 Functions
void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
