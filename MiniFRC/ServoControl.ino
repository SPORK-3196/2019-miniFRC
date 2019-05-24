#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// SG90 servo specs
#define SG90_MIN  115 // this is the 'minimum' pulse length count (out of 4096)
#define SG90_MAX  585 // this is the 'maximum' pulse length count (out of 4096)

void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 60;   // 60 Hz
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000000;  // convert to us
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}

void initServoControl() {
  pwm.begin();
  pwm.setPWMFreq(60);
  delay(10);
}

void moveServo(int port, int val) {
  pwm.setPWM(0, 0, map(val, 0, 180, SG90_MIN, SG90_MAX));
}
