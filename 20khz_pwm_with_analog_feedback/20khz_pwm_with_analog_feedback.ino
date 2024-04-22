const int pwmPin = 3;       // PWM output pin
const int feedbackPin = A0; // Analog pin for feedback voltage

float desiredVoltage = 5.0; // Desired output voltage
float feedbackVoltage = 0.0; // Current feedback voltage
float error = 0.0;           // Voltage error
float dutyCycle = 0.0;       // PWM duty cycle
const float pwmPeriod = 50;  // PWM period in microseconds (1 / 20kHz = 50us)
//int k =0;

void setup() {
  pinMode(pwmPin, OUTPUT); // Set PWM pin as output
  analogReference(DEFAULT); // Use default analog reference voltage (usually 5V)
  Serial.begin(9600);
}

void loop() {
  // Read feedback voltage
  feedbackVoltage = analogRead(feedbackPin) * (5.0 / 1023.0); // Convert ADC reading to voltage
  //k+=1;
  
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
  // if(k=1000000000000000){
  //   Serial.println(feedbackVoltage);
  //   Serial.println(dutyCycle);
  //   Serial.println(pwmPeriod);
  //   delay(1000);
  //   k=0;
  // }
  
  // Calculate ON time based on duty cycle
  float onTime = dutyCycle * pwmPeriod;
  
  // Generate PWM signal
  digitalWrite(pwmPin, HIGH); // Turn on PWM signal
  delayMicroseconds(onTime);  // Wait for ON time
  digitalWrite(pwmPin, LOW);  // Turn off PWM signal
  delayMicroseconds(pwmPeriod - onTime); // Wait for remaining OFF time
}
