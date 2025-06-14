#include "mcc_generated_files/mcc.h"
#include <util/delay.h>

uint8_t buttonLastState = 0;
uint8_t buttonStableState = 0;

const uint8_t debounceDelay = 20;
uint32_t lastDebounceTime = 0;

extern volatile uint32_t millis;

int main(void) {
    SYSTEM_Initialize();

    while (1) {
        uint8_t currentState = BUTTON_GetValue();

        // Button signal changed
        if (currentState != buttonLastState) {
            lastDebounceTime = millis;  // reset debounce timer
        }

        // Only consider it a stable press after debounceDelay
        if ((millis - lastDebounceTime) > debounceDelay) {
            if (currentState != buttonStableState) {
                buttonStableState = currentState;

                if (buttonStableState != 0) {
                    LED_Toggle();  // toggle only on new stable press
                }
            }
        }

        buttonLastState = currentState;
    }
}
