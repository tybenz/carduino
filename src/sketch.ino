int datapin = 2;
int clockpin = 3;
int latchpin = 4;

byte data = 0;

int STBY = 3; // standby

// Motor A
int PWMA = 0; // Speed control
int AIN1 = 2; // Direction
int AIN2 = 1; // Direction

// Motor B
int PWMB = 6; // Speed control
// Temporary swap - need to rewire
int BIN1 = 5; // Direction
int BIN2 = 4; // Direction

void setup() {
  pinMode(datapin, OUTPUT);
  pinMode(clockpin, OUTPUT);
  pinMode(latchpin, OUTPUT);
}

void loop() {
  move(1, HIGH, 1); // motor 1, full speed, left
  move(2, HIGH, 1); // motor 2, full speed, left

  delay(1000); // go for 1 second
  stop(); // stop
  delay(250); // hold for 250ms until move again

  move(1, HIGH, 0); // motor 1, half speed, right
  move(2, HIGH, 0); // motor 2, half speed, right

  delay(1000);
  stop();
  delay(250);
}


// Move specific motor at speed and direction
// motor: 0 for B 1 for A
// speed: 0 is off, and 255 is full speed
// direction: 0 clockwise, 1 counter-clockwise
void move(int motor, int speed, int direction) {
  shiftWrite(STBY, HIGH); // disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if (direction == 1) {
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if (motor == 1) {
    shiftWrite(AIN1, inPin1);
    shiftWrite(AIN2, inPin2);
    shiftWrite(PWMA, speed);
  } else {
    shiftWrite(BIN1, inPin1);
    shiftWrite(BIN2, inPin2);
    shiftWrite(PWMB, speed);
  }
}

void stop() {
  // enable standby
  digitalWrite(STBY, LOW);
}

// This function lets you make the shift register outputs
// HIGH or LOW in exactly the same way that you use digitalWrite().

// Like digitalWrite(), this function takes two parameters:

//    "desiredPin" is the shift register output pin
//    you want to affect (0-7)

//    "desiredState" is whether you want that output
//    to be HIGH or LOW

// Inside the Arduino, numbers are stored as arrays of "bits",
// each of which is a single 1 or 0 value. Because a "byte" type
// is also eight bits, we'll use a byte (which we named "data"
// at the top of this sketch) to send data to the shift register.
// If a bit in the byte is "1", the output will be HIGH. If the bit
// is "0", the output will be LOW.

// To turn the individual bits in "data" on and off, we'll use
// a new Arduino commands called bitWrite(), which can make
// individual bits in a number 1 or 0.
void shiftWrite(int desiredPin, boolean desiredState) {
  // First we'll alter the global variable "data", changing the
  // desired bit to 1 or 0:

  bitWrite(data,desiredPin,desiredState);

  // Now we'll actually send that data to the shift register.
  // The shiftOut() function does all the hard work of
  // manipulating the data and clock pins to move the data
  // into the shift register:

  shiftOut(datapin, clockpin, MSBFIRST, data);

  // Once the data is in the shift register, we still need to
  // make it appear at the outputs. We'll toggle the state of
  // the latchPin, which will signal the shift register to "latch"
  // the data to the outputs. (Latch activates on the high-to
  // -low transition).

  digitalWrite(latchpin, HIGH);
  digitalWrite(latchpin, LOW);
}
