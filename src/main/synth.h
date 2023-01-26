

#ifndef SYNTH_H_
#define SYNTH_H_

#include "utils.h"
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


class ProSynth {
public:

    AudioOutputI2S i2s2; 
    AudioSynthWaveform waveform1;
    
    void prepare() {
        for (int i = 0; i < CHANNEL_NUM; i++) {
            double freq = Utils::getFrequency(scale[i]);

            test[i].prepare(freq, i2s2);
            glass[i].prepare(freq);
        }
    }
    
    void play(int index, float value) {
        switch (state)
        {
        case I::State::TEST:
            test[index].play(value);
            break;
        case I::State::GLASS:
            glass[index].play(value);
            break;
        default:
            break;
        }
    }


    void stop(int index, float value) {
        switch (state)
        {
        case I::State::TEST:
            test[index].stop(value);
            break;
        case I::State::GLASS:
            glass[index].stop(value);
            break;
        
        default:
            break;
        }
    }
    
private:
    struct Test {
        
//        AudioConnection          patchCord1(waveform1, 0, i2s2, 0);
  //      AudioConnection          patchCord2(waveform1, 0, i2s2, 1);

        void prepare(double frequency, AudioOutputI2S i2s2) {
            waveform1.begin(0, frequency, WAVEFORM_SINE);
        }

        void play(float value) {
            waveform1.amplitude(value);
        }

        void stop(float value) {
            waveform1.amplitude(0);
        }
    };

    struct Glass {

        void prepare(double frequency) {
            // to do
        }

        void play(float value) {
            // to do
        }

        void stop(float value) {
            // to do
        }
    };

    Test test[CHANNEL_NUM];
    Glass glass[CHANNEL_NUM];

    I::State state;

    I::Note scale[CHANNEL_NUM] = {
        I::C3,I::D3,I::E3,I::F3,I::G3,I::A_3,I::B_3,I::C4,I::D4,I::E4,I::F4,I::G4
    };
};

#endif
