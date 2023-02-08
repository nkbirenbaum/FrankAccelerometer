// frankAccelerometer.ino flashes LEDs when the accelerometer is moved significantly
// By Nathan Birenbaum 
// Last updated 2/8/2023

// Accelerometer pin connections
const int PIN_X = A3;
const int PIN_Y = A2;
const int PIN_Z = A1;

// LED pin connections (green, blue, & violet)
const int PIN_LED_G = 4;
const int PIN_LED_B = 3;
const int PIN_LED_V = 2;

// Values for +/- 1 G
// Change these based on values shown when tilting
// along each axis in each direction
const int X_MIN = 270;
const int Y_MIN = 266;
const int Z_MIN = 273;
const int X_MAX = 405;
const int Y_MAX = 405;
const int Z_MAX = 404;

// Detection threshold in G for lighting LEDs
const float X_THRESHOLD = 0.3;
const float Y_THRESHOLD = 0.3;
const float Z_THRESHOLD = 0.3;

// Runs once on power up
void setup() {

  pinMode(PIN_LED_G, OUTPUT);
  pinMode(PIN_LED_B, OUTPUT);
  pinMode(PIN_LED_V, OUTPUT);
  Serial.begin(9600);
  flashLEDs();

}

// Runs indefinitely until powered down
void loop() {

  int xAcc = analogRead(PIN_X);
  int yAcc = analogRead(PIN_Y);
  int zAcc = analogRead(PIN_Z);
  
  int xScaled = map(xAcc, X_MIN, X_MAX, -1000, 1000);
  int yScaled = map(yAcc, Y_MIN, Y_MAX, -1000, 1000);
  int zScaled = map(zAcc, Z_MIN, Z_MAX, -1000, 1000);
  
  float xG = xScaled / 1000.0;
  float yG = yScaled / 1000.0;
  float zG = zScaled / 1000.0;

  updateLEDs(xG, yG, zG);
  printValues(xAcc, yAcc, zAcc);
  delay(100);

}

// Toggles LEDs on if outside threshold or off if within threshold
void updateLEDs(float &xG, float &yG, float &zG) {

  if (xG >= X_THRESHOLD || xG <= -X_THRESHOLD) {
    digitalWrite(PIN_LED_G, HIGH);
  } else {
    digitalWrite(PIN_LED_G, LOW);
  }

  if (yG >= Y_THRESHOLD || yG <= -Y_THRESHOLD) {
    digitalWrite(PIN_LED_B, HIGH);
  } else {
    digitalWrite(PIN_LED_B, LOW);
  }

  if (zG >= 1 + Z_THRESHOLD || zG <= 1 - Z_THRESHOLD) {
    digitalWrite(PIN_LED_V, HIGH);
  } else {
    digitalWrite(PIN_LED_V, LOW);
  }

}
// Prints acceleration integer values for debugging
void printValues(int &xAcc, int &yAcc, int &zAcc) {

  Serial.print(xAcc);
  Serial.print("\t");
  Serial.print(yAcc);
  Serial.print("\t");
  Serial.print(zAcc);
  Serial.println();
  
}

// Print acceleration G values for debugging (currently unused)
void printValuesG(int &xG, int &yG, int &zG) {

  Serial.print(xG);
  Serial.print("\t");
  Serial.print(yG);
  Serial.print("\t");
  Serial.print(zG);
  Serial.println();
  
}

// Blink LEDs at startup
void flashLEDs() {

  for (int ii = 0; ii < 10; ii++) {
    digitalWrite(PIN_LED_G, HIGH);
    digitalWrite(PIN_LED_B, HIGH);
    digitalWrite(PIN_LED_V, HIGH);
    delay(200);
    digitalWrite(PIN_LED_G, LOW);
    digitalWrite(PIN_LED_B, LOW);
    digitalWrite(PIN_LED_V, LOW);
    delay(200);
  }
  
}
