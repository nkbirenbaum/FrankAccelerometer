// frankAccelerometer.ino flashes LEDs when the accelerometer is moved significantly
// By Nathan Birenbaum 
// Last updated 2/6/2023

// Accelerometer pin connections
const int PIN_X = A3;
const int PIN_Y = A2;
const int PIN_Z = A1;

// LED pin connections (greem ,blue, & violet)
const int PIN_G = 4;
const int PIN_B = 3;
const int PIN_V = 2;

// Values for +/- 1 G
// Change these based on values shown when tilting
// along each axis in each direction
const int X_MIN = 280;
const int Y_MIN = 280;
const int Z_MIN = 280;
const int X_MAX = 420;
const int Y_MAX = 420;
const int Z_MAX = 420;

void setup() {

  pinMode(PIN_G, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_V, OUTPUT);
  Serial.begin(9600);
  flashLEDs();

}

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

void updateLEDs(float &xG, float &yG, float &zG) {

  if (xG >= 0.1 || xG <= -0.1) {
    digitalWrite(PIN_G, HIGH);
  } else {
    digitalWrite(PIN_G, LOW);
  }

  if (yG >= 0.1 || yG <= -0.1) {
    digitalWrite(PIN_B, HIGH);
  } else {
    digitalWrite(PIN_B, LOW);
  }

  if (zG >= 1.1 || zG <= 0.9) {
    digitalWrite(PIN_V, HIGH);
  } else {
    digitalWrite(PIN_V, LOW);
  }

}

void printValues(int &xAcc, int &yAcc, int &zAcc) {

  Serial.print(xAcc);
  Serial.print("\t");
  Serial.print(yAcc);
  Serial.print("\t");
  Serial.print(zAcc);
  Serial.println();
  
}

void printValuesG(int &xG, int &yG, int &zG) {

  Serial.print(xG);
  Serial.print("\t");
  Serial.print(yG);
  Serial.print("\t");
  Serial.print(zG);
  Serial.println();
  
}

void flashLEDs() {

  for (int ii = 0; ii < 10; ii++) {
    digitalWrite(PIN_G, HIGH);
    digitalWrite(PIN_B, HIGH);
    digitalWrite(PIN_V, HIGH);
    delay(100);
    digitalWrite(PIN_G, LOW);
    digitalWrite(PIN_B, LOW);
    digitalWrite(PIN_V, LOW);
    delay(100);
  }
  
}
