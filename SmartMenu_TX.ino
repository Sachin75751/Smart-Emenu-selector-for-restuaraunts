#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

const byte ROWS = 4; // Number of rows in the keypad
const byte COLS = 4; // Number of columns in the keypad

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {2, 3, 11, 5};      // Connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9};      // Connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16x2 display

int enteredNumber = 0;  // Stores the entered number
bool isEnteringNumber = false; // Flag to indicate if the user is entering a number
bool deleteNumber = false; // Flag to indicate if the user wants to delete a number
int numbers[50]; // Array to store entered numbers
int count = 0; // Counter for entered numbers

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);
  lcd.print("Welcome!");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') {
      if (isEnteringNumber) {
        if (deleteNumber) {
          deleteNumberFromArray(enteredNumber);
          deleteNumber = false;
          displayNumbersOnLCD(); // Display updated list after deletion
        } else if (enteredNumber >= 0 && enteredNumber <= 50) {
          storeNumber(enteredNumber);
        } else {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Invalid Number");
          delay(1000);
        }
        enteredNumber = 0;
        isEnteringNumber = false;
      }
    } else if (key == '*') {
      displayAllNumbersOnLCD(); // Display all entered numbers
    } else if (key == 'D') {
      deleteNumber = true;
    } else if (key >= '0' && key <= '9') {
      if (!isEnteringNumber) {
        enteredNumber = 0;
        isEnteringNumber = true;
      }
      enteredNumber = enteredNumber * 10 + (key - '0');
    } else if (key == 'A') {
      scrollLeftOnLCD(); // Scroll the numbers to the left
    } else if (key == 'B') {
      scrollRightOnLCD(); // Scroll the numbers to the right
    } else if (key == 'C') {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Bye");
      delay(1000);
    }
  }
}

void storeNumber(int number) {
  if (count < 50) {
    numbers[count] = number;
    count++;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Entered Number:");
    lcd.setCursor(0, 1);
    lcd.print(number);
    delay(1000);
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Maximum limit reached.");
    delay(1000);
  }
}

void deleteNumberFromArray(int number) {
  for (int i = 0; i < count; i++) {
    if (numbers[i] == number) {
      for (int j = i; j < count - 1; j++) {
        numbers[j] = numbers[j + 1];
      }
      count--;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Number Deleted:");
      lcd.setCursor(0, 1);
      lcd.print(number);
      delay(1000);
      return;
    }
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Number not found.");
  delay(1000);
}

void displayNumbersOnLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Selected Numbers:");
  for (int i = 0; i < count; i++) {
    lcd.setCursor(0, i + 1);
    lcd.print(numbers[i]);
  }
  delay(1000);
}

void displayAllNumbersOnLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("All Numbers:");
  for (int i = 0; i < count; i++) {
    lcd.print(numbers[i]);
    if (i < count - 1) {
      lcd.print(", ");
    }
  }
  delay(1000);
}

void scrollLeftOnLCD() {
  lcd.scrollDisplayLeft();
}

void scrollRightOnLCD() {
  lcd.scrollDisplayRight();
}