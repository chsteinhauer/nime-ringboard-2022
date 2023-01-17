#include "interfaces.h"



struct Utils {
    static double getFrequency(Note note) {
        return Frequency[note];
    }

    static float calcGain(float value) {
        //float val = powf((100.f - value),2);

        return (200.f - value);
    }
};


struct Processor {
    const static int ringCount = 12;
    const static int bSize = 50;
    float circularBuffer[ringCount][bSize] = {0};
    float rtotal[ringCount] = {0};
    int bindex = 0;

    const float scale = 1.f / bSize;

    float smoothen(int index, float value) {
        if (index == 0) {
            bindex = (bindex + 1) % bSize;
        }

        rtotal[index] -= circularBuffer[index][bindex];
        circularBuffer[index][bindex] = value;
        rtotal[index] += value;

        return 200.f-(rtotal[index] * scale);
    }
};