#include<LiquidCrystal.h>
#include<Keypad.h>
#include <Time.h>
#include <TimeLib.h>
#include <Servo.h>

#define RELAY_ON 0
#define RELAY_OFF 1


const int PIN_RELAY = A4;
const int PIN_RELAY2 = 13;
const int buzzer = A3;
int led = A2;
const int songspeed = 1.5;

const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {3, 2, 1, 0};
byte colPins[COLS] = {6, 5, 4};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

Servo servo;

int x = 0;
int z = 0;
int y = 0;
int w = 0;
int count = 0;
int countLampu = 0;
int countMenu = 0;
int countServo = 0;
int countKipas = 0;
int menuLevel = 1;
int jamLevel = 1;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A4, OUTPUT);
  servo.attach(A5);
  servo.write(A5);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Smart Fungsional");
  lcd.setCursor(0, 1);
  lcd.print("Keypad");
  delay(1000);
  setTime(5, 59, 50, 27, 06, 19); //(Jam,Menit,Detik,Tanggal,Bulan,Tahun)
}

void loop() {
  char key = keypad.getKey();
  idle();
  if (key) {
    switch (key) {
      case '0':
        delay(100);
        menuAwal();
        break;
    }
  }
}

void menuAwal() {
  while (w < 1)
  {
    switch (countMenu)
    {
      case 0:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("1 = Lampu Depan");
        lcd.setCursor(0, 1);
        lcd.print("2 = Suhu Diluar");
        countMenu = countMenu + 1;
        delay (1000);
      case 1:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("2 = Suhu Diluar");
        lcd.setCursor(0, 1);
        lcd.print("3 = Jam");
        countMenu = countMenu + 1;
        delay (1000);
      case 2:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("3 = Jam");
        lcd.setCursor(0, 1);
        lcd.print("4 = Kunci Pintu");
        countMenu = countMenu + 1;
        delay (1000);
      case 3:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("4 = Kunci Pintu");
        lcd.setCursor(0, 1);
        lcd.print("5 = Kipas Angin ");
        countMenu = countMenu + 1;
        delay (1000);
      case 4:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("5 = Kipas Angin");
        lcd.setCursor(0, 1);
        lcd.print("0 = Ulangi Menu");
        countMenu = countMenu + 1;
        delay (1000);
      case 5:
        keyMenuAwal();
        break;
    }
  }
}

void keyMenuAwal() {
  char key = keypad.getKey();
  if (key)
  {
    switch (key)
    {
      case '1':
        countMenu = 0;
        menuLampu();
        break;
      case '2':
        countMenu = 0;
        suhuDiluar();
        break;
      case '3':
        countMenu = 0;
        lcd.clear();
        Jam();
        break;
      case '4':
        countMenu = 0;
        menuServo();
        break;
      case '5':
        countMenu =0;
        menuKipas();
        break;
      case '0':
        countMenu = 0;
        menuAwal();
        break;
    }
  }
}

void menuLampu() {
  while (menuLevel = 1)
  {
    switch (countLampu)
    {
      case 0 :
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("1= Lampu Menyala");
        lcd.setCursor(0, 1);
        lcd.print("2= Lampu Mati");
        countLampu = countLampu + 1;
        delay (1000);
      case 1 :
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("2= Lampu Mati");
        lcd.setCursor(0, 1);
        lcd.print("*= Menu Awal");
        countLampu = countLampu + 1;
        delay (1000);
      case 2 :
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("*= Menu Awal");
        lcd.setCursor(0, 1);
        lcd.print("0= Ulangi Menu");
        countLampu = countLampu + 1;
        delay (1000);
      case 3 :
        keyLampu();
        break;
    }
  }
}

void keyLampu() {
  char key = keypad.getKey();
  if (key)
  {
    switch (key)
    {
      case '1':
        digitalWrite(PIN_RELAY, RELAY_ON);
        break;
      case '2':
        digitalWrite(PIN_RELAY, RELAY_OFF);
        break;
      case '*':
        countLampu = 0;
        menuAwal();
        break;
      case '0':
        countLampu = 0;
        menuLampu();
        break;
    }
  }
}


void suhuDiluar() {
  while (y < 1)
  {
    char key = keypad.getKey();
    int suhu = analogRead(A0) * 0.4888;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Suhu : ");
    lcd.print(suhu);
    lcd.print("C");
    delay(1);

    if (suhu < 34)
    {
      lcd.setCursor(0, 1);
      lcd.print("Pakai Baju Tebal");
      delay (50);
    }
    if (suhu > 33 && suhu < 38)
    {
      lcd.setCursor(0, 1);
      lcd.print("Pakai Baju Biasa");
      delay (50);
    }
    if (suhu > 37)
    {
      lcd.setCursor(0, 1);
      lcd.print("Pakai Baju Tipis");
      delay(50);
    }
    if (key == '0')
    {
      menuAwal();
    }
  }
}

void idle() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tekan 0 untuk");
  lcd.setCursor(0, 1);
  lcd.print("masuk ke menu");
}

void Jam() {
  for (count = 0; count <= 2; count++) {
    if (day() >= 28 && month() == 2 && year() == 19) {
      setTime(0, 0, 0, 1, 3, 19);
    }
    else if (day() >= 30 && month() == 4 && year() == 19) {
      setTime(0, 0, 0, 1, 5, 19);
    }
    else if (day() >= 30 && month() == 6 && year() == 19) {
      setTime(0, 0, 0, 1, 7, 19);
    }
    else if (day() >= 30 && month() == 9 && year() == 19) {
      setTime(0, 0, 0, 1, 10, 19);
    }
    else if (day() >= 30 && month() == 11 && year() == 19) {
      setTime(0, 0, 0, 1, 12, 19);
    }

    //Kelender Tahun 2020
    else if (day() >= 29 && month() == 2 && year() == 20) {
      setTime(0, 0, 0, 1, 3, 20);
    }
    else if (day() >= 30 && month() == 4 && year() == 20) {
      setTime(0, 0, 0, 1, 5, 20);
    }
    else if (day() >= 30 && month() == 6 && year() == 20) {
      setTime(0, 0, 0, 1, 7, 20);
    }
    else if (day() >= 30 && month() == 9 && year() == 20) {
      setTime(0, 0, 0, 1, 10, 20);
    }
    else if (day() >= 30 && month() == 11 && year() == 20) {
      setTime(0, 0, 0, 1, 12, 20);
    }

    else if (hour() == 0 && minute() == 0 && second() == 0) {
      lcd.clear();
      lcd.setCursor (0, 0);
      lcd.print ("Date: ");
      printkurangdarinol(day());
      lcd.print(":");
      printkurangdarinol(month());
      lcd.print(":");
      printkurangdarinol(year());

      lcd.setCursor(0, 1);
      lcd.print("Time:  ");
      printkurangdarinol(hour());
      lcd.print(":");
      printkurangdarinol(minute());
      lcd.print(":");
      printkurangdarinol(second());
    }
    lcd.clear();
    lcd.print ("Date: ");
    printkurangdarinol(day());
    lcd.print(":");
    printkurangdarinol(month());
    lcd.print(":");
    printkurangdarinol(year());

    lcd.setCursor(0, 1);
    lcd.print("Time:  ");
    printkurangdarinol(hour());
    lcd.print(":");
    printkurangdarinol(minute());
    delay (1000);
  }
  for (count = 4; count >= 0; count -- ) {
    count = 0;
    menuAwal();
    break;
  }
}

void printkurangdarinol(int data) {
  if (data >= 0 && data < 10) {
    lcd.write('0');
  }
  lcd.print(data);
}

void menuServo () {
  while (menuLevel = 1)
  {
    switch (countServo)
    {
      case 0 :
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("1= Pintu Lock");
        lcd.setCursor(0, 1);
        lcd.print("2= Pintu UnLock");
        countServo = countServo + 1;
        delay (1000);
      case 1 :
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("2= Pintu UnLock");
        lcd.setCursor(0, 1);
        lcd.print("3= Buka Lalu");
        countServo = countServo + 1;
        delay (1000);
      case 2 :
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("3= Buka Lalu");
        lcd.setCursor(0, 1);
        lcd.print("   Kunci Pintu");
        countLampu = countServo + 1;
        delay (1000);
      case 3 :
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("   Kunci Pintu");
        lcd.setCursor(0, 1);
        lcd.print("*= Menu Awal");
        countServo = countServo + 1;
        delay (1000);
      case 4 :
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("*= Menu Awal");
        lcd.setCursor(0, 1);
        lcd.print("0= Ulangi Menu");
        countServo = countServo + 1;
        delay (1000);
      case 5 :
        keyServo();
        break;
    }
  }
}

void keyServo() {
  char key = keypad.getKey();
  if (key)
  {
    switch (key)
    {
      case '1':
        servo.write(0);
        digitalWrite(led, HIGH);
        delay(1000);
        break;
      case '2':
        servo.write(90);
        digitalWrite(led, LOW);
        delay(1000);
        break; 
      case '3':
        servo.write(90);
        digitalWrite(led, LOW);
        music();
        noTone(buzzer);
        servo.write(0);
        digitalWrite(led, HIGH);
      case '*':
        countServo = 0;
        menuAwal();
        break;
      case '0':
        countServo = 0;
        menuServo();
        break;
    }
  }
}

void menuKipas() {
  while (menuLevel = 1)
  {
    switch (countKipas)
    {
      case 0 :
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("1= Kipas Menyala");
        lcd.setCursor(0, 1);
        lcd.print("2= Kipas Mati");
        countKipas = countKipas + 1;
        delay (1000);
      case 1 :
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("2= Kipas Mati");
        lcd.setCursor(0, 1);
        lcd.print("*= Menu Awal");
        countKipas = countKipas + 1;
        delay (1000);
      case 2 :
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("*= Menu Awal");
        lcd.setCursor(0, 1);
        lcd.print("0= Ulangi Menu");
        countKipas = countKipas + 1;
        delay (1000);
      case 3 :
        keyKipas();
        break;
    }
  }
}

void keyKipas() {
  char key = keypad.getKey();
  if (key)
  {
    switch (key)
    {
      case '1':
        digitalWrite(PIN_RELAY2, RELAY_ON);
        break;
      case '2':
        digitalWrite(PIN_RELAY2, RELAY_OFF);
        break;
      case '*':
        countKipas = 0;
        menuAwal();
        break;
      case '0':
        countKipas = 0;
        menuKipas();
        break;
    }
  }
}

void music(){
#define NOTE_C4  262 
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784
#define NOTE_A5  880
#define NOTE_B5 988
  int notes[] = {       //Note of the song, 0 is a rest/pulse
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0, 
   NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
   NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
   
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_D5, NOTE_E5, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
   NOTE_C5, NOTE_A4, NOTE_B4, 0  
  };
  int duration[] = {         //duration of each note (in ms) Quarter Note is set to 250 ms
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125, 
  250, 125, 250, 125, 
  125, 125, 250, 125, 125,
  125, 125, 375, 125
  };
  for (int i=0;i<76;i++)
  {              //203 is the total number of music notes in the song
  int wait = duration[i] * songspeed;
  tone(buzzer,notes[i],wait);          //tone(pin,frequency,duration)
  delay(wait);
  }       
}
