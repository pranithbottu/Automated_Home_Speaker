// include SPI, Music Maker and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

// Define the pins used for the music maker shield
#define SHIELD_RESET  -1     // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)
#define CARDCS        4      // Card chip select pin
#define DREQ          3      // VS1053 Data request, ideally an Interrupt pin

// define the music player
Adafruit_VS1053_FilePlayer musicPlayer = 
  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);
  
// define the GPIO pin on which the photon connects
int photonPin = 7;
int const ledPin = 9;

void setup()
{
  // initialise the music player
  musicPlayer.begin();
  
  // initialise the SD card
  SD.begin(CARDCS);
  
  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(1,1);

  // If DREQ is on an interrupt pin (on uno, #2 or #3)
  // we can do background audio playing but it is not
  // being used in this initial phase of the project
  // initialize the DREQ interrupt
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);

  // initialize the GPIO pin to which the photon is connected as an input
  musicPlayer.GPIO_pinMode(photonPin, INPUT);
  
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  if (musicPlayer.GPIO_digitalRead(photonPin) == HIGH)
  {
    // Play the file, don't return until complete
    digitalWrite(ledPin, HIGH);
    musicPlayer.playFullFile("song.mp3"); 
  }
  delay(500);
}
