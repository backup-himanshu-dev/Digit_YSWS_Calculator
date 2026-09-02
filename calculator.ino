#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte rows = 4;
const byte cols = 4;

char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[rows] = {9, 8, 7, 6};
byte colPins[cols] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

float num1 = 0;
float num2 = 0;
char op;
String input = "";

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.print("Calculator");
  delay(1000);
  lcd.clear();
}

void loop() {
  char key = keypad.getKey();

  if (!key) return;

  if (key >= '0' && key <= '9') {
    input += key;
    lcd.clear();
    lcd.print(input);
  }

  if (key == 'A' || key == 'B' || key == 'C' || key == 'D') {
    num1 = input.toFloat();
    input = "";

    if (key == 'A') op = '+';
    if (key == 'B') op = '-';
    if (key == 'C') op = '*';
    if (key == 'D') op = '/';

    lcd.clear();
    lcd.print(num1);
    lcd.print(op);
  }

  if (key == '#') {
    num2 = input.toFloat();

    if (op == '+') num1 += num2;
    if (op == '-') num1 -= num2;
    if (op == '*') num1 *= num2;

    if (op == '/') {
      if (num2 == 0) {
        lcd.clear();
        lcd.print("Error");
        delay(1000);
        input = "";
        lcd.clear();
        return;
      }
      num1 /= num2;
    }

    lcd.clear();
    lcd.print("Answer:");
    lcd.setCursor(0, 1);
    lcd.print(num1);

    input = "";
  }

  if (key == '*') {
    num1 = 0;
    num2 = 0;
    input = "";
    op = 0;
    lcd.clear();
  }
}
