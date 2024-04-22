const int pwmPin = 3;       // PWM output pin
const int feedbackPin = A0; // Analog pin for feedback voltage

float desiredVoltage = 5.0; // Desired output voltage
float feedbackVoltage = 0.0; // Current feedback voltage
float error = 0.0;           // Voltage error
float dutyCycle = 0.0;       // PWM duty cycle

void setup() {
  pinMode(pwmPin, OUTPUT); // Set PWM pin as output
  analogReference(DEFAULT); // Use default analog reference voltage (usually 5V)

  // Configure Timer 2 for Fast PWM mode with non-inverted output
  TCCR2A = _BV(COM2A1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(WGM22) | _BV(CS20); // No prescaler
}

void loop() {
  // Read feedback voltage
  feedbackVoltage = analogRead(feedbackPin) * (5.0 / 1023.0); // Convert ADC reading to voltage
  
  // Calculate error
  error = desiredVoltage - feedbackVoltage;
  
  // Adjust duty cycle based on error
  if (error > 0) {
    dutyCycle += 0.01; // Increase duty cycle incrementally
    if (dutyCycle > 1.0) dutyCycle = 1.0; // Clamp duty cycle to maximum value
  } else if (error < 0) {
    dutyCycle -= 0.01; // Decrease duty cycle incrementally
    if (dutyCycle < 0.0) dutyCycle = 0.0; // Clamp duty cycle to minimum value
  }
  
  // Apply PWM duty cycle
  int pwmValue = dutyCycle * 255;
  analogWrite(pwmPin, pwmValue); // Output PWM signal
}
