#include <IRremote.hpp>
#include <LiquidCrystal.h>
long randomNumber;
const int rs = 3, en = 2, d4 = 24, d5 = 25, d6 = 22, d7 = 23;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int recv_pin = 13;
IRrecv irrecv(recv_pin);
decode_results results;
uint32_t rock = 0xFF30CF;
uint32_t paper = 0xFF18E7;
uint32_t scissors = 0xFF7A85;
uint32_t hehe = 0xFF52AD;
uint32_t nokia = 0xFF4AB5;

extern int readnevergonnagiveyouup();
extern int readnokia();

int buzzer = 8;

int LED1 = 12;
int LED2 = 11;
int LED3 = 10;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("You: ");
  randomSeed(analogRead(0));
}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.println("hi");
  lcd.setCursor(4, 0);
  if (irrecv.decode(&results)) {
      uint32_t val= results.value;
      Serial.println(val, HEX);
      if (val == rock) {
        digitalWriteFast(LED1, HIGH);
        delay(1000);
        digitalWrite(LED1, LOW);
        lcd.print("Rock    ");
        game(1);
      }
      if (val == paper) {
        digitalWriteFast(LED2, HIGH);
        delay(1000);
        digitalWrite(LED2, LOW);
        lcd.print("Paper   ");
        game(2);
      }
      if (val == scissors) {
        digitalWriteFast(LED3, HIGH);
        delay(1000);
        digitalWrite(LED3, LOW);
        lcd.print("Scissors");
        game(3);
      }
      if (val == hehe) {
        song1();
      }
      if (val == nokia) {
        song2();
      }
      irrecv.resume(); // Receive the next value
  }

  delay(400);

}

void game(int x){
  randomNumber = random(1, 4);
  lcd.setCursor(0, 1);
  lcd.print("Me: ");
  switch (randomNumber) {
    case 1:
      lcd.print("Rock    ");
      break;
    case 2:
      lcd.print("Paper   ");
      break;
    case 3:
      lcd.print("Scissors");
      break;
  }
  lcd.setCursor(12, 1);

  int val = abs(x - randomNumber);
  switch (val) {
    case 0:
      lcd.print("Tie ");
      break;
    case 1:
      if (randomNumber > x) {
        lcd.print("Lose");
      } else if (randomNumber < x) {
        lcd.print("Win ");
      }
      break;
    case 2:
      if (randomNumber > x) {
        lcd.print("Win");
      } else if (randomNumber < x) {
        lcd.print("Lose");
      }
      break;
  }
  return;
}