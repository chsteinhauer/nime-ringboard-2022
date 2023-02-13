#include "Seeed_MPR121_driver.h"
#include "utils.h"

#define CHANNEL_NUM   12

/* Setup and audio connections */

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


// Create 16 waveforms, one for each MIDI channel
AudioSynthWaveform sine0, sine1, sine2, sine3;
AudioSynthWaveform sine4, sine5, sine6, sine7;
AudioSynthWaveform sine8, sine9, sine10, sine11;
AudioSynthWaveform sine12, sine13, sine14, sine15;
const AudioSynthWaveform *waves[16] = {
  &sine0, &sine1, &sine2, &sine3,
  &sine4, &sine5, &sine6, &sine7,
  &sine8, &sine9, &sine10, &sine11,
  &sine12, &sine13, &sine14, &sine15
};


// Each waveform will be shaped by an envelope
AudioEffectEnvelope env0, env1, env2, env3;
AudioEffectEnvelope env4, env5, env6, env7;
AudioEffectEnvelope env8, env9, env10, env11;
AudioEffectEnvelope env12, env13, env14, env15;
const AudioEffectEnvelope *envs[16] = {
  &env0, &env1, &env2, &env3,
  &env4, &env5, &env6, &env7,
  &env8, &env9, &env10, &env11,
  &env12, &env13, &env14, &env15
};

// Route each waveform through its own envelope effect
AudioConnection patchCord01(sine0, env0);
AudioConnection patchCord02(sine1, env1);
AudioConnection patchCord03(sine2, env2);
AudioConnection patchCord04(sine3, env3);
AudioConnection patchCord05(sine4, env4);
AudioConnection patchCord06(sine5, env5);
AudioConnection patchCord07(sine6, env6);
AudioConnection patchCord08(sine7, env7);
AudioConnection patchCord09(sine8, env8);
AudioConnection patchCord10(sine9, env9);
AudioConnection patchCord11(sine10, env10);
AudioConnection patchCord12(sine11, env11);
AudioConnection patchCord13(sine12, env12);
AudioConnection patchCord14(sine13, env13);
AudioConnection patchCord15(sine14, env14);
AudioConnection patchCord16(sine15, env15);

// Four mixers are needed to handle 16 channels of music
AudioMixer4     mixer1;
AudioMixer4     mixer2;
AudioMixer4     mixer3;
AudioMixer4     mixer4;

// Mix the 16 channels down to 4 audio streams
AudioConnection patchCord17(env0, 0, mixer1, 0);
AudioConnection patchCord18(env1, 0, mixer1, 1);
AudioConnection patchCord19(env2, 0, mixer1, 2);
AudioConnection patchCord20(env3, 0, mixer1, 3);
AudioConnection patchCord21(env4, 0, mixer2, 0);
AudioConnection patchCord22(env5, 0, mixer2, 1);
AudioConnection patchCord23(env6, 0, mixer2, 2);
AudioConnection patchCord24(env7, 0, mixer2, 3);
AudioConnection patchCord25(env8, 0, mixer3, 0);
AudioConnection patchCord26(env9, 0, mixer3, 1);
AudioConnection patchCord27(env10, 0, mixer3, 2);
AudioConnection patchCord28(env11, 0, mixer3, 3);
AudioConnection patchCord29(env12, 0, mixer4, 0);
AudioConnection patchCord30(env13, 0, mixer4, 1);
AudioConnection patchCord31(env14, 0, mixer4, 2);
AudioConnection patchCord32(env15, 0, mixer4, 3);

AudioMixer4     mixer;
AudioMixer4     mixerOut;
AudioOutputI2S  audioOut;

AudioConnection patchCord33(mixer1, 0, mixer, 0);
AudioConnection patchCord34(mixer2, 0, mixer, 1);
AudioConnection patchCord35(mixer3, 0, mixer, 2);
AudioConnection patchCord36(mixer4, 0, mixer, 3);

AudioEffectFreeverb      freeverb;

AudioConnection patchCord40(mixer, 0, freeverb, 0);
AudioConnection patchCord39(freeverb, 0, mixerOut, 0);

AudioConnection patchCord41(mixerOut, 0, audioOut, 0);
AudioConnection patchCord42(mixerOut, 0, audioOut, 1);

AudioControlSGTL5000     sgtl5000_1;

/* Setup and audio connections end */

Mpr121 mpr121;
AudioProcessor processor;

struct Synth {
  
  void prepare(int i, float value) {
      waves[i]->begin(1 - (value/100.f), Frequency[scale[i]], WAVEFORM_SINE);
  }

  void play(int i, float value) {
      waves[i]->amplitude(1 - (value/100.f));
  }

  void stop(int i, float value) {
      waves[i]->amplitude(0);
  }
};

Synth synth;

u16 touch_status_flag[CHANNEL_NUM] = {0};

void setup() {
    
    Serial.begin(115200);
    if (mpr121.begin() < 0) {
        Serial.println("Can't detect device!!!!");
    } else {
        Serial.println("mpr121 init OK!");  
    }
    
    AudioMemory(1500);
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.6);

    
    /*  set 0x00~0xFF to sensitivity,the value
        The higher the value, the higher the sensitivity of 4/5/6/7 channel
        When the sensor is connected to items such as crocodile clip,
        the value needs to be adjusted
    */
    mpr121.set_sensitivity(0x50);

    setupEffects();

    delay(100);

}

void loop() {
    u16 result = 0;
    u16 filtered_data_buf[CHANNEL_NUM] = {0};
    u8 baseline_buf[CHANNEL_NUM] = {0};

    result = mpr121.check_status_register();

    mpr121.get_filtered_reg_data(&result, filtered_data_buf);

    for (int i = 0; i < CHANNEL_NUM; i++) {
        updateTouchFlags(result,filtered_data_buf[i],i);

        if (1 == touch_status_flag[i]) {
          auto value = processor.smoothen(i, filtered_data_buf[i]); //mov averaged

          AudioNoInterrupts();
          synth.play(i,value);
          AudioInterrupts();
          
        }
    }
}



void updateTouchFlags(u16 result, u16 data, int i) {
    if (result & (1 << i)) {                      /*key i is pressed!!*/
        if (0 == touch_status_flag[i]) {
            touch_status_flag[i] = 1;

            //Serial.println();
            auto value = processor.smoothen(i, data); //mov averaged

            AudioNoInterrupts();
            synth.play(i,value);
            envs[i]->noteOn();
            AudioInterrupts();
        }
    } else {
        if (1 == touch_status_flag[i]) {
            touch_status_flag[i] = 0;

            envs[i]->noteOff();
            synth.stop(i,0);
        }
    }
}


void setupEffects() {
    mixer.gain(1, 0.36);
    mixer.gain(3, 0.36);
    mixer.gain(0, 0.36);
    mixer.gain(2, 0.36);

    freeverb.roomsize(0.3);
    freeverb.damping(0.3);

    for (int i = 0; i < CHANNEL_NUM; i++) {
        synth.prepare(i,0);

        envs[i]->attack(9.2);
        envs[i]->hold(2.1);
        envs[i]->decay(31.4);
        envs[i]->sustain(0.6);
        envs[i]->release(84.5);
    }
}
