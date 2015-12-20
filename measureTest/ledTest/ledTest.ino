#define LED1 9
#define LED2 11
void setup() {
  // put your setup code here, to run once:
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  Serial.begin(9600);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int i = 0;
  delay(1000);
  while (i < 250)
  {
    analogWrite(LED1, i);
    analogWrite(LED2, i);
    i+=10;
    delay(200);
  }
}
