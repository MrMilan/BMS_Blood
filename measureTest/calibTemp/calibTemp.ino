#define TEMP1 8
#define TEMP2 12
float temperature1(int pin);
float temp1L;
float temp2L;

void setup() {
  // put your setup code here, to run once:
  pinMode(TEMP1, INPUT);
  pinMode(TEMP2, INPUT);
  Serial.begin(9600);
  temp1L = 0;
  temp2L = 0;

}

void loop() {
  // put your main code here, to run repeatedly:

    float temp1;
    float temp2;
    temp1 = temperature1(TEMP1);
    delay(1000);
    temp2 = temperature1(TEMP2);
    Serial.println("--------------");
    Serial.print("Teplota 1: ");
    Serial.println(temp1);
    Serial.print("Teplota stara 1: ");
    Serial.println(temp1L);
    Serial.print("Teplota 2: ");
    Serial.println(temp2);
    Serial.print("Teplota stara 2: ");
    Serial.println(temp2L);

  }

  float temperature1(int pin)
  {
    float dc = 0;
    float thiOld = 0;
    float thi = 0;
    float tloOld = 0;
    float tlo = 0;
    float temp1 = 0;
    for (int i = 0; i < 2000; i++)
    {
      thi = pulseIn(pin, HIGH, 1000);
      tlo = pulseIn(pin, LOW, 1000);
      thiOld = (thiOld + thi) / (i + 1);
      tloOld = (tloOld + tlo) / (i + 1);

    }
    /*  Serial.print(thi);
      Serial.print(tlo);
      Serial.print(thiOld);
      Serial.print(tloOld);*/
    dc = thi / (tlo + thi);
    temp1 = (dc - 0.32) / 0.0047;
    return temp1;
  }

