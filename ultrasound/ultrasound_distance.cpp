#include <wiringPi.h>
#include <sys/time.h>
#include <iostream>

using namespace std;

// ------ CALCULUS OF DISTANCE BY ULTRASOUND PRINCIPLE ------
// d: distance between ultrasound component and an object
// wavelength: this ultrasound component wavelength (m/cycle) 
// frequence: this ultrasound component frequence (Hz)
// t2: time when the ultrasound receiver gets a ultrasound wave
// t1: time when the ultrasound emitter starts sending a ultrasound wave

// d = ((wavelength * frequence) / 2) * (t2 - t1) 
// ----------------------------------------------------------


int main() {
    if (wiringPiSetup() == -1) {
        cout << "Setup wiringPi failed";
    }

    int trig = 4; // on raspberry pi GPIO23 = wiringPi 4
    int echo = 5; // on raspberry pi GPIO24 = wiringPi 5
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    
    digitalWrite(trig, LOW);
    delayMicroseconds(2);

    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    
    // TODO: find a easier way to do this 
    struct timeval timeval_1;
    struct timeval timeval_2;
    gettimeofday(&timeval_1, NULL);
    float t1 = (timeval_1.tv_sec * 1000000) + timeval_1.tv_usec;
    float t2; 
    
    bool waveCatched = false;
    while (!waveCatched)
    {
        // cout << "je suis la" + to_string(digitalRead(echo));
        if (digitalRead(echo) == 1) {
            gettimeofday(&timeval_2, NULL);
            t2 = (timeval_2.tv_sec * 1000000) + timeval_2.tv_usec;    
            waveCatched = true;
        }
    }

    float wavelength = 0.0085;
    float frequence = 40000;     
    float d = ((wavelength * frequence) / 2) * ((t2 - t1) / 1000000);
    cout << "ici: " + to_string(((wavelength * frequence) / 2)) + "\n";
    cout << "t2: " + to_string(t2) + " t1: " + to_string(t1) + "\n";
    cout << "temps: " + to_string((t2 - t1) / 1000000);
    cout << "Distance: " + to_string(d) + "\n";
    return 0;
}