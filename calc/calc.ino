#include <LiquidCrystal.h>

/**********************************************************/
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// init the buttons pins
int buttonPin1 = 9;
int buttonPin2 = 8;
byte buttonState1 = 0; // for reading the button input
bool buttonPressed1 = false;
byte buttonState2 = 0; // for reading the button input
bool buttonPressed2 = false;

int buttonPin3 = 10;
int buttonPin4 = 11;
byte buttonState3 = 0; // for reading the enter input
bool buttonPressed3 = false;
byte buttonState4 = 0; // for reading the back/clear input
bool buttonPressed4 = false;

bool getButtons[4] = {false, false, false, false};


int count = 0;
int value1 = 0;
int value2 = 0;
float result = 0;
char operations[4] = {'+', '-', '.', '/'};

int calcState = 0;
// 0 = waiting for value 1
// 1 = waiting for value 2
// 2 = waiting for operation
// 3 = displaying result - press any button to reset

String toDisplay;

/*********************************************************/
void setup()
{
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  // Serial.begin(9600); // open the serial port at 9600 bps:
  toDisplay = String();
}
/*********************************************************/
void loop() 
{
  lcd.home();
  lcd.clear();
  lcd.print(toDisplay);
  

  getInputs();
  if (calcState == 0) {
    // getting value 1
    if (getButtons[0]) { // count up
      count++;
      getButtons[0] = false;
    } else if (getButtons[1]) { // count down
      count--;
      getButtons[1] = false;
    } else if (getButtons[2]) { // confirm
      value1 = count;
      calcState = 1;
      getButtons[2] = false;
    }

    toDisplay = count;
  } else if (calcState == 1) {
    // getting value 2
    if (getButtons[0]) { // count up
      count++;
      getButtons[0] = false;
    } else if (getButtons[1]) { // count down
      count--;
      getButtons[1] = false;
    } else if (getButtons[2]) { // confirm
      value2 = count;
      count = 0;
      calcState = 2;
      getButtons[2] = false;
    } else if (getButtons[3]) { // cancel
      value2 = 0;
      count = value1;
      calcState = 0;
      getButtons[3] = false;
    }

    toDisplay = String(value1) + "   " + String(count);
  } else if (calcState == 2) {
    // getting operations
    if (getButtons[0]) { // count up
      count++;
      if (count > 3) count = 0;
      getButtons[0] = false;
    } else if (getButtons[1]) { // count down
      count--;
      if (count < 0) count = 3;
      getButtons[1] = false;
    } else if (getButtons[2]) { // confirm
      if (count == 0) 
        result = value1 + value2;
      else if (count == 1)
        result = value1 - value2;
      else if (count == 2)
        result = value1 * value2;
      else
        result = ((float) value1) / (value2);
        Serial.println(result);
      calcState = 3;
      getButtons[2] = false;
    } else if (getButtons[3]) { // cancel
      count = value2;
      calcState = 1;
      getButtons[3] = false;
    }

    toDisplay = String(value1) + ' ' + String(operations[count]) + ' ' + String(value2);
  } else if (calcState == 3) {
    if (getButtons[0] || getButtons[1] || getButtons[2] || getButtons[3]) {
      value1 = 0;
      value2 = 0;
      result = 0;
      count = 0;
      calcState = 0;
      for (int i = 0; i < 4; i++) {
        getButtons[i] = false;
      }
    }
    toDisplay = String(value1) + ' ' + String(operations[count]) + ' ' + String(value2) + " = " + String(result);
  }
}
/************************************************************/

void getInputs() {
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);

  if (buttonState1 == HIGH && !buttonPressed1) {
    getButtons[0] = true;
    buttonPressed1 = true;
  } else if (buttonState1 == LOW) {
    getButtons[0] = false;
    buttonPressed1 = false;
  }
  if (buttonState2 == HIGH && !buttonPressed2) {
    getButtons[1] = true;
    buttonPressed2 = true;
  } else if (buttonState2 == LOW) {
    getButtons[1] = false;
    buttonPressed2 = false;
  }
  if (buttonState3 == HIGH && !buttonPressed3) {
    getButtons[2] = true;
    buttonPressed3 = true;
  } else if (buttonState3 == LOW) {
    getButtons[2] = false;
    buttonPressed3 = false;
  }
  if (buttonState4 == HIGH && !buttonPressed4) {
    getButtons[3] = true;
    buttonPressed4 = true;
  } else if (buttonState4 == LOW) {
    getButtons[3] = false;
    buttonPressed4 = false;
  }
}