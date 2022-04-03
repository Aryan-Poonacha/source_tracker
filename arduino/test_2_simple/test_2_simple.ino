const int rightSensorPin = 2;
const int leftSensorPin = 3;
const int enablePin = 5 ;
boolean rightVal = 0;
boolean leftVal = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(leftSensorPin, INPUT); //Make pin 8 an input pin.
  pinMode(rightSensorPin, INPUT); //Make pin 7 an input pin.

  digitalWrite(enablePin, LOW); //Enable is active low
  Serial.begin (9600); // initialize the serial port:

}

void loop() {
  // put your main code here, to run repeatedly:
  rightVal = analogRead(rightSensorPin);
  leftVal = analogRead(leftSensorPin);

  // when the sensor detects a signal above the threshold value set on sensor, turn finder to the direction of sound
  if (leftVal == LOW && rightVal == HIGH)
  {
    Serial.println("Turning Right");
  }
  else if (leftVal == HIGH && rightVal == LOW)
  {
    Serial.println("Turning Left");
  }
  else {
    {
      //Do nothing
      rightVal = 0;
      leftVal = 0;
    }
  }
}
