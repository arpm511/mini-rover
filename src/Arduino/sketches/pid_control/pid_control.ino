/*
 * JGA25-370 Motor PID Control
 * 
 * This sketch implements PID control for the JGA25-370 DC geared motor
 * with integrated magnetic hall encoder for precise speed control.
 * 
 * Hardware:
 * - JGA25-370 DC Motor with encoder (6V variant recommended)
 * - L298N or TB6612FNG motor driver
 * - Arduino Nano/Uno/Mega
 * 
 * Connections:
 * - Motor Driver PWM -> Arduino PWM Pin (e.g., Pin 9)
 * - Motor Driver DIR1 -> Arduino Digital Pin (e.g., Pin 8)
 * - Motor Driver DIR2 -> Arduino Digital Pin (e.g., Pin 7)
 * - Encoder Channel A -> Arduino Interrupt Pin (e.g., Pin 2)
 * - Encoder Channel B -> Arduino Interrupt Pin (e.g., Pin 3)
 * 
 * Author: Artemis
 * License: MIT
 * Date: February 2026
 */

// Pin Definitions
const int MOTOR_PWM = 9;      // PWM pin for motor speed
const int MOTOR_DIR1 = 8;     // Direction pin 1
const int MOTOR_DIR2 = 7;     // Direction pin 2
const int ENCODER_A = 2;      // Encoder channel A (interrupt pin)
const int ENCODER_B = 3;      // Encoder channel B (interrupt pin)

// Motor Parameters
const int ENCODER_PPR = 12;   // Pulses per revolution (before gearing)
const float GEAR_RATIO = 46.8; // Gear ratio (check your motor specs)
const int ENCODER_CPR = ENCODER_PPR * GEAR_RATIO * 2; // Counts per revolution (quadrature)

// PID Parameters (tuned for JGA25-370, adjust as needed)
// Based on research: Kp ~ 2, Ki ~ 5, Kd ~ 1 for stable performance
float Kp = 2.0;               // Proportional gain
float Ki = 5.0;               // Integral gain
float Kd = 1.0;               // Derivative gain

// PID Variables
float setpoint = 0;           // Target speed in RPM
float input = 0;              // Current speed in RPM
float output = 0;             // PID output (PWM value)
float error = 0;              // Current error
float lastError = 0;          // Previous error
float integral = 0;           // Integral sum
float derivative = 0;         // Derivative term

// Speed Measurement Variables
volatile long encoderCount = 0;
long lastEncoderCount = 0;
unsigned long lastTime = 0;
const int SAMPLE_TIME = 100;  // Sample time in milliseconds

// Output limits
const int PWM_MIN = 0;
const int PWM_MAX = 255;
const float INTEGRAL_MAX = 1000; // Anti-windup limit

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  Serial.println("JGA25-370 PID Control Initialized");
  Serial.println("Commands: S<rpm> - Set speed, P<val> K<val> D<val> - Tune PID");
  
  // Configure motor driver pins
  pinMode(MOTOR_PWM, OUTPUT);
  pinMode(MOTOR_DIR1, OUTPUT);
  pinMode(MOTOR_DIR2, OUTPUT);
  
  // Configure encoder pins with pullup resistors
  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);
  
  // Attach interrupts for encoder
  attachInterrupt(digitalPinToInterrupt(ENCODER_A), encoderISR_A, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_B), encoderISR_B, CHANGE);
  
  // Initialize motor (stopped)
  setMotor(0, 1);
  
  lastTime = millis();
}

void loop() {
  // Check for serial commands
  handleSerialCommands();
  
  // Calculate speed at regular intervals
  unsigned long currentTime = millis();
  if (currentTime - lastTime >= SAMPLE_TIME) {
    // Calculate speed in RPM
    long encoderDelta = encoderCount - lastEncoderCount;
    float timeInterval = (currentTime - lastTime) / 1000.0; // Convert to seconds
    input = (encoderDelta / (float)ENCODER_CPR) * (60.0 / timeInterval); // RPM
    
    // Compute PID
    computePID();
    
    // Apply output to motor
    setMotor(output, (setpoint >= 0) ? 1 : -1);
    
    // Print status
    printStatus();
    
    // Update variables
    lastEncoderCount = encoderCount;
    lastTime = currentTime;
  }
}

void computePID() {
  // Calculate error
  error = setpoint - input;
  
  // Proportional term
  float P = Kp * error;
  
  // Integral term with anti-windup
  integral += error * (SAMPLE_TIME / 1000.0);
  if (integral > INTEGRAL_MAX) integral = INTEGRAL_MAX;
  if (integral < -INTEGRAL_MAX) integral = -INTEGRAL_MAX;
  float I = Ki * integral;
  
  // Derivative term
  derivative = (error - lastError) / (SAMPLE_TIME / 1000.0);
  float D = Kd * derivative;
  
  // Calculate total output
  output = P + I + D;
  
  // Constrain output
  output = constrain(abs(output), PWM_MIN, PWM_MAX);
  
  // Store error for next iteration
  lastError = error;
}

void setMotor(int pwmValue, int direction) {
  // Constrain PWM value
  pwmValue = constrain(abs(pwmValue), 0, 255);
  
  // Set direction
  if (direction > 0) {
    digitalWrite(MOTOR_DIR1, HIGH);
    digitalWrite(MOTOR_DIR2, LOW);
  } else if (direction < 0) {
    digitalWrite(MOTOR_DIR1, LOW);
    digitalWrite(MOTOR_DIR2, HIGH);
  } else {
    // Brake
    digitalWrite(MOTOR_DIR1, LOW);
    digitalWrite(MOTOR_DIR2, LOW);
  }
  
  // Set speed
  analogWrite(MOTOR_PWM, pwmValue);
}

// Encoder interrupt service routines
void encoderISR_A() {
  bool A = digitalRead(ENCODER_A);
  bool B = digitalRead(ENCODER_B);
  
  if (A == B) {
    encoderCount++;
  } else {
    encoderCount--;
  }
}

void encoderISR_B() {
  bool A = digitalRead(ENCODER_A);
  bool B = digitalRead(ENCODER_B);
  
  if (A != B) {
    encoderCount++;
  } else {
    encoderCount--;
  }
}

void handleSerialCommands() {
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    float value = Serial.parseFloat();
    
    switch (cmd) {
      case 'S':
      case 's':
        setpoint = value;
        integral = 0; // Reset integral when changing setpoint
        Serial.print("Setpoint: ");
        Serial.print(setpoint);
        Serial.println(" RPM");
        break;
        
      case 'P':
      case 'p':
        Kp = value;
        Serial.print("Kp: ");
        Serial.println(Kp);
        break;
        
      case 'I':
      case 'i':
        Ki = value;
        Serial.print("Ki: ");
        Serial.println(Ki);
        integral = 0; // Reset integral when changing Ki
        break;
        
      case 'D':
      case 'd':
        Kd = value;
        Serial.print("Kd: ");
        Serial.println(Kd);
        break;
        
      case 'X':
      case 'x':
        setpoint = 0;
        integral = 0;
        Serial.println("Motor stopped");
        break;
        
      case '?':
        printHelp();
        break;
    }
  }
}

void printStatus() {
  Serial.print("Setpoint: ");
  Serial.print(setpoint);
  Serial.print(" | Speed: ");
  Serial.print(input);
  Serial.print(" | Error: ");
  Serial.print(error);
  Serial.print(" | Output: ");
  Serial.print(output);
  Serial.print(" | Count: ");
  Serial.println(encoderCount);
}

void printHelp() {
  Serial.println("\n=== PID Motor Control Commands ===");
  Serial.println("S<value> - Set target speed in RPM (e.g., S100)");
  Serial.println("P<value> - Set Kp gain (e.g., P2.5)");
  Serial.println("I<value> - Set Ki gain (e.g., I5.0)");
  Serial.println("D<value> - Set Kd gain (e.g., D1.2)");
  Serial.println("X        - Stop motor");
  Serial.println("?        - Show this help");
  Serial.println("==================================\n");
}
