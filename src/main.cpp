#include <Arduino.h>
#include <Adafruit_MotorShield.h>


Adafruit_MotorShield motorController;
auto* motor = motorController.getMotor(3);

void setup()
{
    Serial.begin(115200);
    Serial.println("initializing motor shield");
    motorController.begin();
}


#define FADE_STEP   4

void fadeInAndOut(Adafruit_DCMotor* motor,
                  uint8_t direction,
                  unsigned long durationMs,
                  unsigned long holdTime = 0,
                  uint8_t minBrightness = 0,
                  uint8_t maxBrightness = 255)
{
    auto numberOfSteps = ((maxBrightness - minBrightness) + 1) / FADE_STEP;
    auto stepDuration = (durationMs / 2) / numberOfSteps;
    if (stepDuration == 0)
    {
        stepDuration = 1;   // Sorry there is a minimum 128 ms duration
    }

    motor->setSpeed(0);
    motor->run(direction);

    for (int16_t brightness = minBrightness; brightness <= maxBrightness; brightness += FADE_STEP)
    {
        motor->setSpeed(brightness);
        delay(stepDuration);
    }
    if (holdTime > 0)
    {
        delay(holdTime);
    }
    for (int16_t brightness = maxBrightness; brightness > minBrightness; brightness -= FADE_STEP)
    {
        motor->setSpeed(brightness);
        delay(stepDuration);
    }
    motor->setSpeed(0);
}

void loop()
{
    Serial.print(".");
    fadeInAndOut(motor, FORWARD, 6000, 1000);
    delay(1000);

    fadeInAndOut(motor, BACKWARD, 6000, 1000);
    delay(1000);
}