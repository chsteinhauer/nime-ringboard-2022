
#include "Seeed_MPR121_driver.h"
#include "utils.h"
#include "synth.h"

Mpr121 mpr121;
Processor processor;
Synth synth;

u16 touch_status_flag[CHANNEL_NUM] = {0};

void setup() {
    s32 ret = 0;
    Serial.begin(115200);
    if (mpr121.begin() < 0) {
        Serial.println("Can't detect device!!!!");
    } else {
        Serial.println("mpr121 init OK!");
    }

    /*  set 0x00~0xFF to sensitivity,the value
        The higher the value, the higher the sensitivity of 4/5/6/7 channel
        When the sensor is connected to items such as crocodile clip,
        the value needs to be adjusted
    */
    mpr121.set_sensitivity(0x60);
    delay(100);
}

void loop() {
    u16 result = 0;
    u16 filtered_data_buf[CHANNEL_NUM] = {0};
    u8 baseline_buf[CHANNEL_NUM] = {0};

    result = mpr121.check_status_register();

    mpr121.get_filtered_reg_data(&result, filtered_data_buf);

    for (int i = 0; i < CHANNEL_NUM; i++) {
        updateTouchFlags(result,i);

        if (1 == touch_status_flag[i]) {
            const value = processor.smoothen(i, filtered_data_buf[i]);

            synth.play(i, value);
        } else {
            const value = processor.smoothen(i, 0);

            synth.stop(i, value);
        }
    }
}



void updateTouchFlags(u16 result, int i) {
    if (result & (1 << i)) {                      /*key i is pressed!!*/
        if (0 == touch_status_flag[i]) {
            touch_status_flag[i] = 1;
        }
    } else {
        if (1 == touch_status_flag[i]) {
            touch_status_flag[i] = 0;
        }
    }
}
