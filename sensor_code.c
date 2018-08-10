// define the LED on pin D0
int led = D0;

// define the PIR sensor input on pin D6
int pir = D6;

// track whether or not the publish was successful
bool published;

void setup()
{
    // set the LED pin as output
    pinMode(led, OUTPUT);
    
    // set the PIR sensor input pin as input
    pinMode(pir, INPUT);
    
    // ensure the LED is off
    digitalWrite(led, LOW);
}

void loop()
{
    if (digitalRead(pir) == HIGH)
    // if motion is detected
    {
        // turn on the LED as an indicator that I was detected
        digitalWrite(led, HIGH);
        published = Particle.publish("motion-detected", NULL, 60, PRIVATE);
        if (!published)
        // if the publish was unsuccessful
        {
            // flash the LED 10 times as an indicator of the publish failure
            for (int i = 0; i < 10; i++)
            {
                digitalWrite(led, LOW);
                delay(500);
                digitalWrite(led, HIGH);
                delay(500);
            }
        }
    }
    else
        // if no motion is detected, turn off the LED
        digitalWrite(led, LOW);
    
    // wait 2 seconds before taking another reading    
    delay(2000);
}