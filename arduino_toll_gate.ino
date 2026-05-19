#include <Servo.h>
#include "Arduino_LED_Matrix.h"   // Include the LED_Matrix library
#include "frames.h"               // Include a header file containing some custom icons

// Define the left ultrasound sensor
#define TRIG_PIN_LEFT 13
#define ECHO_PIN_LEFT 12

// Define the right ultrasound sensor
#define TRIG_PIN_RIGHT 4
#define ECHO_PIN_RIGHT 5

Servo toll_gate;  // Create Servo object to control a servo
ArduinoLEDMatrix matrix;   // Create the íonboard LED matrix

// RGB LED - Common Anode LED
int greenPin= 11;
int bluePin = 10;
int redPin = 9;

int GATE_CLOSE_POSITION = 4;
int GATE_OPEN_POSITION = 77;

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 bps
  toll_gate.attach(3);  // Attaches the sg90 servo on pin 3 to the Servo object
                        // Red wire -> +5V
                        // Brown wire -> GND
                        // Orange wire -> PWM

  matrix.begin();  // Initialize the LED matrix

  // Set the pinmodes of the left US sensor
  pinMode(TRIG_PIN_LEFT, OUTPUT);
  pinMode(ECHO_PIN_LEFT, INPUT);

  // Set the pinmodes of the right US sensor
  pinMode(TRIG_PIN_RIGHT, OUTPUT);
  pinMode(ECHO_PIN_RIGHT, INPUT);

  //Defining the RGB pins as OUTPUT
  pinMode(redPin,  OUTPUT);              
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // At the start the gate is closed
  toll_gate.write(GATE_CLOSE_POSITION);     // tell servo to go to position in variable
  setColor(230, 255, 255);
  matrix.loadFrame(stop);

  delay(250);
}

void handle_us_sensors(long &distance_left, long &distance_right){
  long duration_left;
  long duration_right;

  // ====[ LEFT US SENSOR ]============================================================
  // Send TRIG signal – 10µs HIGH
  digitalWrite(TRIG_PIN_LEFT, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_LEFT, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_LEFT, LOW);

  // Read ECHO signal – travel time of the reflected pulse
  duration_left = pulseIn(ECHO_PIN_LEFT, HIGH);

  // Calculate distance (cm) – based on the speed of sound (343 m/s)
  distance_left = duration_left * 0.0343 / 2;

  // ===[ RIGHT US SENSOR ]============================================================
  // Send TRIG signal – 10µs HIGH
  digitalWrite(TRIG_PIN_RIGHT, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_RIGHT, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_RIGHT, LOW);

  // Read ECHO signal – travel time of the reflected pulse
  duration_right = pulseIn(ECHO_PIN_RIGHT, HIGH);

  // Calculate distance (cm) – based on the speed of sound (343 m/s)
  distance_right = duration_right * 0.0343 / 2;
}

void print_us_values(long distance_left, long distance_right){
  Serial.print("Distance left: ");
  Serial.print(distance_left);
  Serial.print(" cm | ");
  Serial.print("distance right: ");
  Serial.print(distance_right);
  Serial.println(" cm.");
}

void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void loop() {
  setColor(230, 255, 255); 

  long distance_threshold = 7.0; // Set the minimum distance for activation
  long distance_left = 255;
  long distance_right = 255;

  handle_us_sensors(distance_left, distance_right);
  print_us_values(distance_left, distance_right);


  if(distance_left < distance_threshold or distance_right < distance_threshold){
      // Handle incoming car
      matrix.loadFrame(car);
      delay(250);

      for(int i=0; i<6; i++){
        setColor(180, 180, 255); 
        delay(250);
        setColor(100, 100, 255); 
        delay(250);
      }

      
      matrix.loadFrame(titi);
      setColor(255, 230, 255); 
      delay(1000);

      toll_gate.write(GATE_OPEN_POSITION);   // tell servo to go to position in variable
      if(distance_right < distance_threshold){
        matrix.loadFrame(arrow_right);
      }
      else{
        matrix.loadFrame(arrow_left);
      }

      delay(5000); 
  }
  else{
    // Closing the gate
    setColor(230, 255, 255); 
    toll_gate.write(GATE_CLOSE_POSITION);     // tell servo to go to position in variable
    matrix.loadFrame(stop);
    delay(500);
  }

}
