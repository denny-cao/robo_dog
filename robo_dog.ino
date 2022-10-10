#include <NewPing.h>
#include <pcmConfig.h>
#include <pcmRF.h>
#include <TMRpcm.h>
#include <SPI.h>
#include <SD.h>
#include <math.h>

// MOTORS L298N

// Motor A
#define A_SPEED_CTRL_PIN 9 // PWM
#define A_FORWARDS_PIN 8
#define A_BACKWARDS_PIN 7

// Motor B
#define B_SPEED_CTRL_PIN 3 // PWM
#define B_FORWARDS_PIN 2
#define B_BACKWARDS_PIN 4

// ULTRASONIC SENSOR HC-SR04 
#define MAX_DIST 200 // Max dist to ping (in cm) (Max is 400-500 cm)

#define TRIGGER_PIN 12
#define ECHO_PIN 11

NewPing sonar(TRIGGER, ECHO, MAX_DIST);

// SD CARD MODULE 
#define SD_CHIPSELECTPIN 1

TMRpcm tmrpcm;

// Speaker
#define SPEAKER_PIN 10

tmmmrpcm.speakerPin = 10;

// GPS Coordinates
#define SENSITIVITY = .01;
float cur_longitude;
float cur_latitude;

float goal_longitude;
float goal_latitude;

float cur_bearing;
float goal_bearing;

void setup() {
  Serial.begin(115200); 

  // Motors
  pinMode(A_SPEED_CTRL_PIN, OUTPUT);
  pinMode(A_FORWARDS_PIN, OUTPUT);
  pinMode(A_BACKWARDS_PIN, OUTPUT);
  
  pinMode(B_SPEED_CTRL_PIN, OUTPUT);
  pinMode(A_FORWARDS_PIN, OUTPUT);
  pinMode(A_BACKWARDS_PIN, OUTPUT);

  // Set initial state
  digitalWrite(A_FORWARDS_PIN, LOW);
  digitalWrite(A_BACKWARDS_PIN, LOW);
  analogWrite(A_SPEED_CTRL_PIN, 0);

  digitalWrite(B_FORWARDS_PIN, LOW);
  digitalWrite(B_BACKWARDS_PIN, LOW);  
  analogWrite(B_SPEED_CTRL_PIN, 0);
}

void forward() {
  // Runs motors forwards

  // Turn on Motor A
  digitalWrite(A_FORWARDS_PIN, HIGH);
  digitalWrite(A_BACKWARDS_PIN, LOW);

  // Turn on Motor B
  digitalWrite(B_FORWARDS_PIN, HIGH);
  digitalWrite(B_BACKWARDS_PIN, LOW);

  // Set speed to max
  analogWrite(A_SPEED_CTRL_PIN, 255);
  analogWrite(B_SPEED_CTRL_PIN, 255;
}

void backward() {
  // Runs motors backward

  // Turn on Motor A
  digitalWrite(A_FORWARDS_PIN, LOW);
  digitalWrite(A_BACKWARDS_PIN, HIGH);

  // Turn on Motor B
  digitalWrite(B_FORWARDS_PIN, LOW);
  digitalWrite(B_BACKWARDS_PIN, HIGH);

  // Set speed to max
  analogWrite(A_SPEED_CTRL_PIN, 255);
  analogWrite(B_SPEED_CTRL_PIN, 255;
}

void stop() {
  // Stops motors

  digitalWrite(A_FORWARDS_PIN, LOW);
  digitalWrite(A_BACKWARDS_PIN, LOW);

  digitalWrite(B_FORWARDS_PIN, LOW);
  digitalWrite(B_BACKWARDS_PIN, LOW);  

  // Set speed to 0
  analogWrite(A_SPEED_CTRL_PIN, 0);
  analogWrite(B_SPEED_CTRL_PIN, 0);
}

void right() {
  // Turn right

  // Turn off Motor A
  digitalWrite(A_FORWARDS_PIN, LOW);
  digitalWrite(A_BACKWARDS_PIN, LOW);

  // Turn on Motor B
  digitalWrite(B_FORWARDS_PIN, HIGH);
  digitalWrite(B_BACKWARDS_PIN, LOW);

  // Set speed (0, 255)
  analogWrite(A_SPEED_CTRL_PIN, 0);
  analogWrite(B_SPEED_CTRL_PIN, 100);

}

void left() {
  // Turn left
  
  // Turn on Motor A
  digitalWrite(A_FORWARDS_PIN, HIGH);
  digitalWrite(A_BACKWARDS_PIN, LOW);

  // Turn off Motor B
  digitalWrite(B_FORWARDS_PIN, LOW);
  digitalWrite(B_BACKWARDS_PIN, LOW);  

  // Set speed (0, 255)
  analogWrite(A_SPEED_CTRL_PIN, 100);
  analogWrite(B_SPEED_CTRL_PIN, 0);
}

void updateCurrentCoords() {
  // From Android phone coordinates, update current coordinate variables
  ;
}

void updateGoalCoords() {
  /* 
    From Android phone, get new destination to reach
    Idea: Google Maps or different map API to get "corners", or
          positions where a change in direction is required
    Simple Approach: Set goal coord once, and straight path.
                     Follow path until obstacle, then avoid and
                     try to stay on line
    https://developer.android.com/reference/android/location/Location: getBearing()
  */
  ;
  // Detect 
}

void bearingAdjust() {
  /*
    Keep turning until bearing is within bound of goal bearing
  */
  while (goal_bearing + SENSITIVITY < cur_bearing || goal_bearing - SENSITIVITY > cur_bearing) {
    float abs_bearing = cur_bearing;

    if (cur_bearing >= 180) {
      abs_bearing = 360 - cur_bearing;
    }

    if (abs_bearing >= goal_bearing) {
      right();
    }
    else {
      left();
    }
  }
}

void path() {
  // Only need to check latitude and not longitude because, by traveling in goal bearing, if latitudes match, longitudes match
  while (cur_latitude > goal_latitude + SENSITIVITY || cur_latitude < goal_latitude - SENSITIVITY) {
    straight();
  }
  stop();
}

void avoid() {
  // Ping ultrasonic sensor to get distance from object and move if something in front. 
  
  delay(50); // Delay 50 ms before pinging = 20 pings/sec. Min delay is 29ms.
  int dist = sonar.ping_cm()

  Serial.print("Ping: %d cm \n", dist);
  
  if(dist <= 40) {
    // Stop motors
    backward();
    delay(200);
    right();
  }
}

void loop() {
  forward();
  avoid();
  play();
}


void play() {
  // Play sound
  tmrpcm.setVolume(5);
  tmrpcm.stopPlayback();
  tmmmmmmr.play("bark.wav");
  delay(20000);
  return;
}