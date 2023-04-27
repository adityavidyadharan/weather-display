#include "AiEsp32RotaryEncoder.h"

#include "Arduino.h"

/*
connecting Rotary encoder

Rotary encoder side    MICROCONTROLLER side  
-------------------    ---------------------------------------------------------------------
CLK (A pin)            any microcontroler intput pin with interrupt -> in this example pin 32
DT (B pin)             any microcontroler intput pin with interrupt -> in this example pin 21
SW (button pin)        any microcontroler intput pin with interrupt -> in this example pin 25
GND - to microcontroler GND
VCC                    microcontroler VCC (then set ROTARY_ENCODER_VCC_PIN -1) 

***OR in case VCC pin is not free you can cheat and connect:***
VCC                    any microcontroler output pin - but set also ROTARY_ENCODER_VCC_PIN 25 
                        in this example pin 25

*/
#define ROTARY_ENCODER_A_PIN 4
#define ROTARY_ENCODER_B_PIN 36
#define ROTARY_ENCODER_BUTTON_PIN 26

#define ROTARY_ENCODER_VCC_PIN -1 
#define ROTARY_ENCODER_STEPS 4
AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);

float brightnessModifier = 1.0;


void rotary_loop()
{
	//dont print anything unless value changed
	if (rotaryEncoder.encoderChanged())
	{
		Serial.println(rotaryEncoder.readEncoder());
    int brightness = map(rotaryEncoder.readEncoder(), 0, 100, 25, 255);
	brightnessModifier = brightness / 255.0;
    ledcWrite(6, brightness);
	}
}

void IRAM_ATTR readEncoderISR()
{
	rotaryEncoder.readEncoder_ISR();
}

void rotarySetup()
{
	Serial.println("Rotary Setup");
	rotaryEncoder.begin();
	rotaryEncoder.setup(readEncoderISR);
	rotaryEncoder.setBoundaries(0, 100, false);
	rotaryEncoder.setAcceleration(200);
	rotaryEncoder.setEncoderValue(255);
	// setup pwm on pin 39
	ledcSetup(6, 10000, 8);
	ledcAttachPin(25, 6);
	ledcWrite(6, 255);
}
