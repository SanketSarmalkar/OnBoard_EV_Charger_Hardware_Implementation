const int feedbackPin = A0;
float feedbackVoltage = 0;

void setup() {
  // put your setup code here, to run once:
 analogReference(DEFAULT);
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  feedbackVoltage = analogRead(feedbackPin) * (5.0 / 1023.0);
  Serial.println(feedbackVoltage);
  delay(1000);
}
