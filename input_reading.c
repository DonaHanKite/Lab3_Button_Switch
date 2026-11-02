#include "input_reading.h"

static GPIO_TypeDef* BUTTON_PORT[NO_OF_BUTTONS] = {BT0_GPIO_Port, BT1_GPIO_Port, BT2_GPIO_Port};
static uint16_t BUTTON_PIN[NO_OF_BUTTONS] = {BT0_Pin, BT1_Pin, BT2_Pin};

static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer3[NO_OF_BUTTONS];

static GPIO_PinState buttonState[NO_OF_BUTTONS] = {BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};

static uint8_t flagForButtonPressed[NO_OF_BUTTONS] = {0, 0, 0};


void button_reading(void) {
    for (char i = 0; i < NO_OF_BUTTONS; i++) {
        debounceButtonBuffer1[i] = debounceButtonBuffer2[i];
        debounceButtonBuffer2[i] = debounceButtonBuffer3[i];
        debounceButtonBuffer3[i] = HAL_GPIO_ReadPin(BUTTON_PORT[i], BUTTON_PIN[i]);

        if ((debounceButtonBuffer1[i] == debounceButtonBuffer2[i]) &&
            (debounceButtonBuffer2[i] == debounceButtonBuffer3[i])) {

            if (buttonState[i] != debounceButtonBuffer3[i]) {
                buttonState[i] = debounceButtonBuffer3[i];

                if (buttonState[i] == BUTTON_IS_PRESSED) {
                    flagForButtonPressed[i] = 1;
                }
            }
        }
    }
}


int is_button_pressed(uint8_t index) {
    if (index >= NO_OF_BUTTONS) return 0;

    if (flagForButtonPressed[index] == 1) {
        flagForButtonPressed[index] = 0;
        return 1;
    }
    return 0;
}
