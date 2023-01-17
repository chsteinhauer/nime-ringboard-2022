#include "utils.h"
#include <Audio.h>

class Synth {
public:

    void prepare() {
        for (int i = 0; i < CHANNEL_NUM; i++) {
            double freq = Utils::getFrequency(scale[i]);

            test[i].prepare(freq);
            glass[i].prepare(freq);
        }
    }
    
    void play(int index, float value) {
        switch (state)
        {
        case State::TEST:
            test[index].play(value);
            break;
        case State::GLASS:
            glass[index].play(value);
            break;
        default:
            break;
        }
    }


    void stop(int index, float value) {
        switch (state)
        {
        case State::TEST:
            test[index].stop(value);
            break;
        case State::GLASS:
            glass[index].stop(value);
            break;
        
        default:
            break;
        }
    }
    
private:
    struct Test {
        AudioSynthWaveform waveform;

        void prepare(double frequency) {
             waveform.begin(0, frequency, WAVEFORM_SINE);
        }

        void play(float value) {
            waveform.amplitude(value);
        }

        void stop(float value) {
            waveform.amplitude(0);
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

    State state;

    Note scale[CHANNEL_NUM] = {
        C3,D3,E3,F3,G3,A3,B3,C4,D4,E4,F4,G4
    };
};

