// =========================================================
/// TO DO: Header -  Arduino Program of a Dual functional Gadget
// =========================================================

#include "devboard.h"

// Enumerated type definition to define the three
// possible operating modes.

typedef enum {
  MODE_TITLE_PAGE,
  MODE_SPIRIT_LEVEL,
  MODE_TIMER
} mode_t;

mode_t mode;  // Declaring a variable 'mode' of type 'mode_t'

// =========================================================
//                    FUNCTION PROTOTYPES
// =========================================================

// TO DO: add your function prototypes here
int average(int *array, int nLen);
void printTitlePage();
void runTimer();
void runSpiritLevel();
// =========================================================
/// \fn     average()
///
/// \brief  Calculates the average value of an array of ints
///
/// \param  *array Pointer to integer array
/// \param  nLen Length of the array
///
/// \return The average value (as an integer)
///
/// The use of an internal variable of type long will be
/// beneficial in reducing 16-bit integer overflow. Plenty
/// of oportunity for casting.
// =========================================================

// TO DO: Add your 'average' function here. Note from the
// description above it takes two arguments/parameters, and
// returns a value.
int average(int *array, int nLen) {
  long sum = 0;
  for (int i = 0; i < nLen; i++) {
    sum += array[i];
  }
  int avg = sum / nLen;
  return avg;
}

// =========================================================
/// \fn     runTimer()
///
/// \brief  Runs the timer mode
///
/// This function firstly requires the user to enter a time
/// between 0 and 999 seconds.
///
/// Following this the countdown will take place.
/// - the remaining seconds will be displayed on the LCD
/// - the remaining units will be displayed on the 7-seg
/// - the remaining 10s of seconds will be displayed on the
///   LED bank.
/// S1 can abort the countdown.
///
/// On completion, a 3-beep patten will be played.
/// When the counting is complete or aborted, the function
/// is terminated by a press and release of S2.
///
/// During the execution of this function, the green LED
/// should be on, the red and yellow LEDs should be off.
// =========================================================

// TO DO: Add your 'runTimer()' function here
void runTimer() {
  //Set the Green LED on to indicate the state
  DEVBOARD_setLedRed(0);
  DEVBOARD_setLedYellow(0);
  DEVBOARD_setLedGreen(1);

  //Display the state
  DEVBOARD_lcdClear();
  DEVBOARD_lcdPrintString("Timer State");
  delay(2000);
  //Request the user to enter the time
  DEVBOARD_lcdClear();
  DEVBOARD_lcdSetCursor(0, 0);
  DEVBOARD_lcdPrintString("Enter time 0-999 seconds:");

  //Assigning the time Remaining read to timeremaining
  int timeRemaining = DEVBOARD_keypadReadInt(0);
  DEVBOARD_soundBuzzer();
  // Time remaining state
  if (timeRemaining == 0) {
    DEVBOARD_lcdClear();
    DEVBOARD_lcdPrintString("DONE");
    delay(1000);
    return;
  }
  while (timeRemaining > 0) {
    // Check S1 status to abort
    if (DEVBOARD_buttonS1Status() == BUTTON_PRESSED) {
      DEVBOARD_lcdClear();
      DEVBOARD_lcdPrintString("ABORTED");
      DEVBOARD_soundBuzzer();
      DEVBOARD_waitForS2Press();
      return;
    }
    //Print the time left
    DEVBOARD_lcdClear();
    DEVBOARD_lcdPrintString("Time left:");
    DEVBOARD_lcdSetCursor(0, 1);
    DEVBOARD_lcdPrintInt(timeRemaining);
    // LED Bankdisplay Binary Equivalent of time
    int ledValue = timeRemaining / 10;
    DEVBOARD_writeLedBank(ledValue);
    // 7-Segment display unit digit
    int unit = timeRemaining % 10;
    DEVBOARD_sevenSegment(sCharSet[unit]);

    delay(1000);
    timeRemaining--;
  }
  DEVBOARD_lcdClear();
  DEVBOARD_lcdPrintString("DONE");

  // Turn off all LEDs and 7-seg
  DEVBOARD_writeLedBank(B00000000);
  DEVBOARD_sevenSegment(B00000000);
  // 3 Beeps
  for (int i = 0; i < 3; i++) {
    DEVBOARD_soundBuzzer();
    delay(500);
  }
  // Wait for S2 before exiting
  DEVBOARD_waitForS2Press();
}
// =========================================================
/// \fn     runSpiritLevel()
///
/// \brief  Runs the Spirit Level mode
///
/// This function runs an infinite loop. The X-component of
/// acceleration is obtained every 50ms. Four samples are
/// obtained and averaged. The value of the averaged Z-
/// component are used to illuminate two of eight LEDs:
///    00011000: indicates flat
///    00110000: indicates slight left-tilt
///    01100000: indicates medium left-tilt
///    11000000: indicates extreme left-tilt
///    00001100: indicates slight right-tilt
///    00000110: indicates medium right-tilt
///    00000011: indicates extreme right-tilt
/// During the execution of this function, the yellow LED
/// should be on, the red and green LEDs should be off.
// =========================================================

// TO DO: Add your 'runSpiritLevel()' function here
void runSpiritLevel() {
  //Set the Green Yellow on to indicate the state
  DEVBOARD_setLedRed(0);
  DEVBOARD_setLedYellow(1);
  DEVBOARD_setLedGreen(0);
  //Display the state
  DEVBOARD_lcdClear();
  DEVBOARD_lcdPrintString("Spirit Level");
  delay(2000);

  // An array of 4x values
  int xval[4];
  int refX, x, y, z;

  // read flat reference
  DEVBOARD_readAccelerometer(&refX, &y, &z);
  while (1) {
    // Collect 4 X-axis readings every 50 ms
    for (int i = 0; i < 4; i++) {
      DEVBOARD_readAccelerometer(&x, &y, &z);
      xval[i] = x;
      delay(50);
    }

    // Calculate average of 4 x values
    int avgX = average(xval, 4);

    // Compare with reference
    int difference = avgX - refX;
    //Display flat pattern
    byte pattern = B00011000;
    // Determine LED pattern based on tilt difference

    if (difference < -6000) {
      pattern = B00000011;
      DEVBOARD_lcdClear();
      DEVBOARD_lcdSetCursor(0, 0);
      DEVBOARD_lcdPrintString("extreme right");
    }  //extreme right

    else if (difference < -4000) {
      pattern = B00000110;
      DEVBOARD_lcdClear();
      DEVBOARD_lcdSetCursor(0, 0);
      DEVBOARD_lcdPrintString("medium right");
    }  // medium right

    else if (difference < -2000) {
      pattern = B00001100;
      DEVBOARD_lcdClear();
      DEVBOARD_lcdSetCursor(0, 0);
      DEVBOARD_lcdPrintString("slightly right");
    }  // slight right

    else if (difference > 6000) {
      pattern = B11000000;
      DEVBOARD_lcdClear();
      DEVBOARD_lcdSetCursor(0, 0);
      DEVBOARD_lcdPrintString("extreme left");
    }  // extreme left

    else if (difference > 4000) {
      pattern = B01100000;
      DEVBOARD_lcdClear();
      DEVBOARD_lcdSetCursor(0, 0);
      DEVBOARD_lcdPrintString("medium left");
    }  // medium left

    else if (difference > 2000) {
      pattern = B00110000;
      DEVBOARD_lcdClear();
      DEVBOARD_lcdSetCursor(0, 0);
      DEVBOARD_lcdPrintString("slight left");
    }  // slight left

    else {
      pattern = B00011000;
      DEVBOARD_lcdClear();
      DEVBOARD_lcdSetCursor(0, 0);
      DEVBOARD_lcdPrintString("flat");
    }  // flat

    //Print difference that represents the tilt
    DEVBOARD_lcdSetCursor(0, 1);
    DEVBOARD_lcdPrintInt(difference);
    // Light corresponding LEDs
    DEVBOARD_writeLedBank(pattern);
    // Exit if S2 is pressed
    if (DEVBOARD_buttonS2Status() == BUTTON_PRESSED) {
      DEVBOARD_waitForS2Press();
      return;
    }
  }
}
// =========================================================
/// \fn     printTitlePage()
///
/// \brief  Runs the title page mode
///
/// This function simply puts a title page on the LCD
/// display. The function waits until S2 is pressed
/// then released.
/// During the execution of this function, the red LED
/// should be on, the yellow and green LEDs should be off.
// =========================================================

// TO DO: Add your 'printTitlePage()' function here

void printTitlePage() {
  //Set the Red LED on to indicate the state
  DEVBOARD_setLedRed(1);
  DEVBOARD_setLedYellow(0);
  DEVBOARD_setLedGreen(0);
  //Display the state
  DEVBOARD_lcdClear();
  DEVBOARD_lcdPrintString("Title Page");
  delay(2000);

  DEVBOARD_lcdClear();
  DEVBOARD_lcdSetCursor(0, 0);
  DEVBOARD_lcdPrintString("Dual Functional");
  DEVBOARD_lcdSetCursor(0, 1);
  DEVBOARD_lcdPrintString("Gadget-P2892870");

  DEVBOARD_waitForS2Press();
}
// =========================================================
/// \fn     void setup()
///
/// \brief  Performs one-off initialization.
///
/// Usual Arduino fayre.
// =========================================================

void setup() {
  // There are at least four TO DO items:-
  // Initialize the mode variable
  //Stat on Title paage
  mode = MODE_TITLE_PAGE;
  // Set-up the development board
  DEVBOARD_init();
  // Read the accelerometer to get reference X-value
  int x, y, z;
  DEVBOARD_readAccelerometer(&x, &y, &z);
  // Sound the beeper once.
  DEVBOARD_soundBuzzer();
}

// =========================================================
/// \fn     void loop()
///
/// \brief  This function is called ad-infinitum.
///
/// Usual Arduino fayre.
// =========================================================

void loop() {
  // TO DO:
  // Call the appropriate function based on the value of
  // mode. Once the function has completed execution, the
  // value of mode should be updated to indicate the next
  // state.
  switch (mode)
  //Run first state (Title page) and move to spirit level
  {
    case MODE_TITLE_PAGE:
      printTitlePage();
      mode = MODE_SPIRIT_LEVEL;
      break;
    //Run spirit level then move to Mode timer
    case MODE_SPIRIT_LEVEL:
      runSpiritLevel();
      mode = MODE_TIMER;
      break;
    // Run mode timer then move to title page
    case MODE_TIMER:
      runTimer();
      mode = MODE_TITLE_PAGE;
      break;

    default:
      mode = MODE_TITLE_PAGE;
      break;
  }
}
