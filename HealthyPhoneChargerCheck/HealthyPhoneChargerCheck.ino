#include<SoftwareSerial.h>
int buzzerPin = 1;
const int voltagePin = A2;
double measure = 0;

SoftwareSerial softwareSerial(99, 3);

void setup()
{
	softwareSerial.begin(9600);
	pinMode(1, OUTPUT);
	analogReference(INTERNAL2V56);
}

void loop()
{
	measure = (2.56 / 1024)* analogRead(voltagePin);
	softwareSerial.println(measure);
	if (measure < (4.35 - 2.56))
	{
		alarmFunction();
	}
}

void alarmFunction()
{
	softwareSerial.println("Allarme");
	TinyTone(239, 5, 500);
	delay(1000);
}

void TinyTone(unsigned char divisor, unsigned char octave, unsigned long duration)
{
	//TCCR1 = 0x90 | (8 - octave); // for 1MHz clock
	TCCR1 = 0x90 | (11 - octave); // for 8MHz clock
	OCR1C = divisor - 1;         // set the OCR
	delay(duration);
	TCCR1 = 0x90;              // stop the counter
}


