#include <MIDI.h>


MIDI_CREATE_DEFAULT_INSTANCE();

int intensity = 0;
int last = 0;
int reading;
int sensorIni;
const int analogInPin = A0;

void setup()
{
    MIDI.begin();

    //Read of the initial sensor value (not blowing) for calibration
    delay(200);
    sensorIni = analogRead(analogInPin);
}

void loop()
{
        reading = constrain(analogRead(analogInPin)-sensorIni, 0, 1014-sensorIni);
        intensity = map(reading, 0, 1014-sensorIni, 0, 127);

        //Only sending if value has changed from last time and is different from 0 to prevent saturation
        if(intensity > 0 && intensity != last){
          MIDI.sendControlChange(11, intensity, 1);
          last = intensity;
        }

        //If intensity drops to 0 from another value the 0 isn't sent and the last value is maintained, so we send a 0
        else{
          if(intensity == 0 && last > 0){
            MIDI.sendControlChange(11, 0, 1);
            last = 0;
          }
        }
                        
}
