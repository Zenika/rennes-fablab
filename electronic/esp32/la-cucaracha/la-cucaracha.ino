/**
 *
 * Playing part of Cucaracha song 
 * A buzzer must be plug in to VCC and GPIO22
 * This code use pwm to make buzzer work, alternate PWM at 0 and 150
 *
**/

int pos = 0;
int val = 0;
int note[] = { 150, 50, 100, 50, 100, 50, 400, 100, 150, 700, 150, 50, 100, 50, 100, 50, 400, 100, 150, 700, 100, 50, 100, 50, 100, 50, 100, 50, 100, 50, 100, 50, 400 };
int sizeOfArray = sizeof(note) / sizeof(note[0]);

void setup() {
  Serial.begin(115200);
  pinMode(22, OUTPUT);
}

void loop() {
  if (pos >= sizeOfArray) {
    analogWrite(22, 0);
    delay(800);
    pos = 0;
    val = 0;
  }
  if (val == 0) {
    val = 150;
  } else {
    val = 0;
  }
  analogWrite(22, val);
  delay(note[pos]);
  pos++;
}
