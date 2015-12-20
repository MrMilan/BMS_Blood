#define TEMP1 8
#define TEMP2 12
#define LED1 9
#define LED2 11
#define REG_CAS_KONS 500
#define BORTEP 23
#define MRATEP 18
#define DEDTEP 18
float temperature1(int pin);
long timos;
int cerp;
int pelt;


float temp1L;
float temp2L;

void setup() {
  // put your setup code here, to run once:
  pinMode(TEMP1, INPUT);
  pinMode(TEMP2, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  Serial.begin(9600);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  timos = 0;
  cerp = 0;
  pelt = 0;
  temp1L = BORTEP;
  temp2L = BORTEP;

}

void loop() {
  // put your main code here, to run repeatedly:


  if (millis() - timos > REG_CAS_KONS)
  {
    timos = millis();
    float temp1;
    float temp2;
    temp1 = temperature1(TEMP1);
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
    if (abs(temp1 - temp1L) > 0.5)//proti kmitani regulace
    {
      Serial.print("Diff:");
      Serial.println(temp1 - BORTEP);
      if (temp1 - BORTEP > 0)
      {
        if (pelt < 240)
        {
          pelt += 10;
          Serial.println("Chladime");
        }
      }
      else
      {
        if (pelt > 0)
        {
          pelt -= 10;
          Serial.println("Topime");
        }
      }
      //pokud podchlazuji krev na bod mrazu vypnout peltiera
      if (temp1 < MRATEP)
      {
        pelt = LOW;
      }
    }

//pokud na druhem teplomeru je smrtelná teplota vypneme chlazení ihned
    if (abs(temp2 - temp2L) > 0.5)//proti kmitani regulace
    {
      if (temp2 < DEDTEP)
      {
         Serial.println("Zabijim");
        pelt = LOW;
      } 
    }

    Serial.print("Vykon peltiera (0-255): ");
    Serial.println(pelt);
    temp1L = temp1;
    temp2L = temp2;
  }
  analogWrite(LED1, pelt);
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

