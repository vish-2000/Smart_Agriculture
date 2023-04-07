#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

#define buzz 8 //attach pin D8 Arduino to +ve pin of Buzzer

#define pump 9 //attach pin D9 Arduino to live of pump

const int min_dist=5;
const int max_dist=6;//Distance between sensor and water level in cm

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

void setup()
{
  pinMode(buzz, OUTPUT); //Sets the buzz pin as an OUTPUT
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(pump, OUTPUT); // Sets the pump pin as an OUTPUT
  
  Serial.begin(9600); // Serial Communication is starting with 9600 of baudrate speed
}

void loop()
{
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
 
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

  // Displays the distance on the Serial Monitor and sending to bolt
  Serial.print(distance);
  Serial.print("\n");
  
  if(distance>min_dist)//Comparing with max distance
   {
      digitalWrite(buzz, HIGH);//Buzzer ON
      if(distance>max_dist)
      {
        digitalWrite(pump,LOW);//Pump OFF
      }
   }
  else
  {
    digitalWrite(buzz, LOW); //Buzzer OFF
    digitalWrite(pump, HIGH); //Pump ON
  }
  delay(5000);
}
