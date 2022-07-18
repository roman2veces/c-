#include <wiringPi.h>
#include <iostream>
using namespace std;

int main(void) {
    int ledPin = 0;
    if (wiringPiSetup() == -1) {
        cout << "Setup wiringPi failed !";
        return 0;
    }

    pinMode(ledPin, OUTPUT);
    while (true)
    {
        digitalWrite(ledPin, LOW);
        cout << "LED ON\n";
        delay(500);

        digitalWrite(ledPin, HIGH);
        cout << "LED OFF\n";
        delay(500);
    }
    
    return 0;
}