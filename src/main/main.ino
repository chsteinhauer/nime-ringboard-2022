
#include "Seeed_MPR121_driver.h"
#include "utils.h"
//#include "synth.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

AudioOutputI2S           i2s2; 
AudioControlSGTL5000     sgtl5000_1;
AudioSynthWaveform       waveform1;

Mpr121 mpr121;
AudioProcessor processor;
//ProSynth synth;

AudioConnection          patchCord1(waveform1, 0, i2s2, 0);
AudioConnection          patchCord2(waveform1, 0, i2s2, 1);

u16 touch_status_flag[CHANNEL_NUM] = {0};

void setup() {
    s32 ret = 0;
    Serial.begin(115200);
    if (mpr121.begin() < 0) {
        Serial.println("Can't detect device!!!!");
    } else {
        Serial.println("mpr121 init OK!");  
    }
    
    AudioMemory(1500);
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.5);

      
    /*  set 0x00~0xFF to sensitivity,the value
        The higher the value, the higher the sensitivity of 4/5/6/7 channel
        When the sensor is connected to items such as crocodile clip,
        the value needs to be adjusted
    */
    mpr121.set_sensitivity(0x60);
    delay(100);

    prepare(500);
}

void loop() {
    u16 result = 0;
    u16 filtered_data_buf[CHANNEL_NUM] = {0};
    u8 baseline_buf[CHANNEL_NUM] = {0};

    result = mpr121.check_status_register();

    mpr121.get_filtered_reg_data(&result, filtered_data_buf);

    for (int i = 0; i < CHANNEL_NUM; i++) {
        updateTouchFlags(result,i);

        if (1 == touch_status_flag[i] && i == 1) {
            auto value = processor.smoothen(i, filtered_data_buf[i]); //mov averaged
            Serial.print("Value ");
            Serial.print(i);
            Serial.print(": ");
            //Serial.println(filtered_data_buf[i]); //raw data
            //Serial.print(" - ");
            //Serial.println(value);
            //synth.play(i, value);
            auto gain1 = (2-value);
            play(gain1);
            Serial.println(gain1);
        } else if(i == 1) {
            auto value = processor.smoothen(i, filtered_data_buf[i]);

            //synth.stop(i, value);
            stop(value);
        }
        
    }
delay(5);
}



void updateTouchFlags(u16 result, int i) {
    if (result & (1 << i)) {                      /*key i is pressed!!*/
        if (0 == touch_status_flag[i]) {
            touch_status_flag[i] = 1;

            //Serial.println();
        }
    } else {
        if (1 == touch_status_flag[i]) {
            touch_status_flag[i] = 0;
        }
    }
}




void prepare(double frequency) {
    waveform1.begin(0.8, frequency, WAVEFORM_SINE);
}

void play(float value) {
    waveform1.amplitude(value);
}

void stop(float value) {
    waveform1.amplitude(0);
}
