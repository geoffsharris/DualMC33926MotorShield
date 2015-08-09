#include "DualMC33926MotorShield.h"

// Constructors ////////////////////////////////////////////////////////////////

DualMC33926MotorShield::DualMC33926MotorShield()
{
  //Pin map
  _EN = D3;
  _M1IN1 = D0;
  _M1IN2 = D1;
  _M2IN1 = D4;
  _M2IN2 = D5;
  _nSF = D2;
  _M1FB = A0; 
  _M2FB = D6;
}

(unsigned char M1IN1, unsigned char M1IN2, unsigned char M1FB,
                           unsigned char M2IN1, unsigned char M2IN2, unsigned char M2FB,
                           unsigned char EN, unsigned char nSF); // User-defined pin selection. 





DualMC33926MotorShield::DualMC33926MotorShield(unsigned char M1IN1, unsigned char M1IN2, unsigned char M1FB,
                           unsigned char M2IN1, unsigned char M2IN2, unsigned char M2FB,
                           unsigned char EN, unsigned char nSF)
{
  //Pin map
  //PWM1 and PWM2 cannot be remapped because the library assumes PWM is on timer1
  _EN = EN;
  _M1IN1 = M1IN1;
  _M1IN2 = M1IN2;
  _M2IN1 = M2IN1;
  _M2IN2 = M2IN2;
  _nSF = nSF;
  _M1FB = M1FB; 
  _M2FB = M2FB;
}

// Public Methods //////////////////////////////////////////////////////////////
void DualMC33926MotorShield::init()
{
// Define pinMode for the pins and set the frequency for timer1.

  pinMode(_M1IN1,OUTPUT);
  pinMode(_M1IN2,OUTPUT);
  pinMode(_M1FB,INPUT);
  pinMode(_M2IN1,OUTPUT);
  pinMode(_M2IN1,OUTPUT);
  pinMode(_M2FB,INPUT);
  pinMode(_EN,OUTPUT);
  digitalWrite(_EN,HIGH); // default to on
  pinMode(_nSF,INPUT);

}
// Set speed for motor 1, speed is a number betwenn -400 and 400
void DualMC33926MotorShield::setM1Speed(int speed)
{
  unsigned char reverse = 0;
  
  if (speed < 0)
  {
    speed = -speed;  // Make speed a positive quantity
    reverse = 1;  // Preserve the direction
  }
  if (speed > 255)  // Max PWM dutycycle
    speed = 255;
    
  if (reverse)
    analoglWrite(_M1IN2,0);
    analoglWrite(_M1IN1,speed);
  else
    analoglWrite(_M1IN1,0);
    analoglWrite(_M1IN2,speed);
}

// Set speed for motor 2, speed is a number betwenn -400 and 400
void DualMC33926MotorShield::setM2Speed(int speed)
{
  unsigned char reverse = 0;
  
  if (speed < 0)
  {
    speed = -speed;  // Make speed a positive quantity
    reverse = 1;  // Preserve the direction
  }
  if (speed > 255)  // Max PWM dutycycle
    speed = 255;
    
  if (reverse)
    analoglWrite(_M2IN2,0);
    analoglWrite(_M2IN1,speed);
  else
    analoglWrite(_M2IN1,0);
    analoglWrite(_M2IN2,speed);
}

// Set speed for motor 1 and 2
void DualMC33926MotorShield::setSpeeds(int m1Speed, int m2Speed)
{
  setM1Speed(m1Speed);
  setM2Speed(m2Speed);
}

// Return motor 1 current value in milliamps.
float DualMC33926MotorShield::getM1CurrentMilliamps()
{
  // 5V / 1024 ADC counts / 525 mV per A = 9 mA per count
  return analogRead(_M1FB) * 1.5244;
}

// Return motor 2 current value in milliamps.
float DualMC33926MotorShield::getM2CurrentMilliamps()
{
  // 5V / 1024 ADC counts / 525 mV per A = 9 mA per count
  return analogRead(_M2FB) * 1.5244;
}

// Return error status
unsigned char DualMC33926MotorShield::getFault()
{
  return !digitalRead(_nSF);
}
