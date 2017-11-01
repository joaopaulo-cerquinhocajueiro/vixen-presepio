/* AC POWER CONTROL WITH PWM AND ZERO CROSS DETECTION */
 /* AUTHOR: Dimitris El. Vassis - 2013 */

 #include <ACPWM.h>
 #define ZERO_PIN 2 //Input pin from zero cross detector
 #define PWM_PIN 9 //Output pin to TRIAC / SSR
 int SET_PIN = A0; //Analog pin for setting the dutyCycle value with a pontentiometer

 void setup()
 {
    pinMode(ZERO_PIN, INPUT);
    pinMode(PWM_PIN, OUTPUT);
    //Initialize PWM operation.
    //Mains frequency: 50Hz.
    //Zero crossing point reached whenever pulse to PIN2 changes
    //Duty cycle = 0..255. 0:always off. 255: always on. 150: 59% on.
    ACpwm.initialize(50,ZERO_PIN,CHANGE,PWM_PIN,255);
    //Latching on HIGH zero state: 3 microseconds.
    //Latching on LOW zero cross state: 5 microseconds.
    ACpwm.setLatch(3,5);
 }

 void loop() {
    //Adjust the power with the potentiometer
    //Set the duty cycle equal to the value of the potentiometer.
    ACpwm.setDutyCycle(analogRead(SET_PIN));
 }
