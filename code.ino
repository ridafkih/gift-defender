// HERE ARE THE VARIABLES YOU CAN CHANGE TO ALTER
// THE BEHAVIOUR OF THE SCRIPT

// The smaller the next variable, the more sensitive the sensor will be.
float TOLERANCE = 120;

// Include Wire library for interaction with Gyroscope module.
#include <Wire.h>

// Get average values ready for assignment during calibration.
float averageX, averageY, averageZ;

// Assign the I2C address and buzzer pin constant variables.
const int MPU6050_addr = 0x68;
const int BUZZER_PIN = 12;

// Create acceleration variables on the X, Y, and Z axis.
int16_t AccX, AccY, AccZ;

void setup() {
  // Set the pin mode for the BUZZER_PIN to OUTPUT
  // in order to control the buzzer.
  pinMode(BUZZER_PIN, OUTPUT);

  // Begin intercommunication between the gyroscope
  // MPU-6050 module and the Arduino Nano.
  Wire.begin();
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  // Begin the Serial with a BaudRate of 9600.
  Serial.begin(9600);
}

// Create the variable used to track iterations for calibration.
int iteration = 0;
// Create x, y, and z float arrays to save variables to so we
// can average their values for calibration.
float x[25], y[25], z[25];

// Create calibrating varaible so that we know if the calibration
// has been completed.
bool calibrating = true;

void loop() {
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_addr, 14, true);

  // Read gyroscopic data from the MPU-6050 module
  // for the acceleration on each axis.
  AccX = Wire.read() << 8 | Wire.read();
  AccY = Wire.read() << 8 | Wire.read();
  AccZ = Wire.read() << 8 | Wire.read();

  // If the iteration is falsey, assume calibration has not yet
  // completed, play a single beep through the buzzer to indicate
  // that calibration is completed if serial monitoring is not avail.
  if (!iteration) {
    Serial.println("--== Calibration Sequence Beginning ==--");
    tone(BUZZER_PIN, 2400, 100);
  }

  // Collect 25 measurements in 100ms increments (2.5 seconds) of
  // gyroscoping data to their respective arrays.

  // If the iteration exceeds 25, assume calibration is complete,
  // average the values collected, and use that as a POR for
  // potential future acceleration.
  if (iteration < 25) {
    x[iteration] = AccX;
    y[iteration] = AccY;
    z[iteration] = AccZ;
    iteration++;
  }  else if (calibrating) {
    Serial.println("--== Calibration Complete ==--");

    // Play a simple two-tone noise through the buzzer to
    // indicate that the calibration has been completed.
    tone(BUZZER_PIN, 2400, 100);
    delay(200);
    tone(BUZZER_PIN, 3600, 100);

    // Use the calculateAverage function to average out
    // the values saved to the x, y, and z float arrays.
    averageX = calculateAverage(x);
    averageY = calculateAverage(y);
    averageZ = calculateAverage(z);

    // Print averages to the serial monitor for debugging.
    Serial.print(" - X: ");
    Serial.println(averageX);
    Serial.print(" - Y: ");
    Serial.println(averageY);
    Serial.print(" - Z: ");
    Serial.println(averageZ);

    Serial.println("");
    Serial.println("These will be the values the Arduino uses as its normal values.");
    Serial.println("If these values deviate too much, the buzzer will activate.");

    // Assume calibration complete.
    calibrating = false;
  } else {
    // Get the percent differential between the average values
    // and the current measured value from the MPU-6050 module.
    float diffX = abs((AccX - averageX) / averageX);
    float diffY = abs((AccY - averageY) / averageY);
    float diffZ = abs((AccZ - averageZ) / averageZ);

    // If the value exceeds the TOLERANCE variable defined
    // in the first few lines, sound the alarm.

    // Otherwise, print values to the serial monitor for debugging
    // purposes. If the readings are incomplete or impossible, ignore.
    if (
      (diffY >= TOLERANCE / 100 && AccY != -1) ||
      (diffZ >= TOLERANCE / 100 && AccZ != -1)
    ) {
      soundAlarm();
    } else {
      Serial.print(" - X: ");
      Serial.println(diffX * 100);
      Serial.print(" - Y: ");
      Serial.println(diffY * 100);
      Serial.print(" - Z: ");
      Serial.println(diffZ * 100);
    }
  }

  // Hangup 100ms
  delay(100);
}

// Sound the buzzer, own function for debugging purposes.
void soundAlarm() {
  tone(BUZZER_PIN, 800, 1000);
}

// Simple averaging function that takes an array of floats.
float calculateAverage(float numbers[]) {
  float sum = 0;
  for (int i = 0; i < 25; i++)
    sum += numbers[i];
  return sum / 25;
}
