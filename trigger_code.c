// define the LED on pin D0
int led = D0;

// define the trigger for the Arduino on pin D7
int trigger = D7;

void soundAlarm(const char *event, const char *data)
{
    // when the motion event has been triggered
    // turn on the LED
    digitalWrite(led, HIGH);
    
    // turn on the trigger
    digitalWrite(trigger, HIGH);
    
    // wait two seconds
    delay(2000);
    
    // turn off the trigger
    digitalWrite(trigger, LOW);

    // turn off the LED
    digitalWrite(led, LOW);
}

void setup()
{
    // subscribe to motion events from my devices only
    // define soundAlarm as the event handler
    Particle.subscribe("motion", soundAlarm, MY_DEVICES);
    
    // set the LED pin as output
    pinMode(led, OUTPUT);

    // set the trigger pin as output
    pinMode(trigger, OUTPUT);
}

void loop()
{

}