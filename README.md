# Blinking LED with Button (Debounced)

This project demonstrates how to toggle an LED using a button press on the ATmega328P microcontroller. The button input is **debounced in software** using a timer-based `millis` counter generated via **Timer0** and **MPLAB Code Configurator (MCC)**.

##  Features

- LED toggles only on **clean, stable button presses**
- Implements **software debounce** using `millis`
- Avoids blocking delays (`_delay_ms`) using Timer0
- Built using **MPLAB X**, **XC8**, and **MCC**

---

##  Requirements

- **Microcontroller**: ATmega328P
- **MPLAB X IDE** (v6.0+)
- **MPLAB Code Configurator (MCC)**
- **XC8 Compiler**
- Breadboard, pushbutton, LED, 220Ω resistor

---

##  Project Setup

###  Hardware Connections

| Component | Pin               |
|----------:|------------------|
| LED       | PORTB5 (digital output) |
| Button    | PORTB0 (digital input, active HIGH) |
| Resistor  | 220Ω in series with LED |

> Button should connect from **PORTB0** to **VCC**, with an external or internal pull-down resistor.

---

###  MCC Configuration

1. **GPIO**:
   - Set `RB5` as **Output** (LED)
   - Set `RB0` as **Input** (Button)

2. **Timer0**:
   - Mode: 8-bit Timer
   - Enable **Overflow Interrupt**
   - Use **Prescaler** suitable for 1ms resolution (e.g. 1:64 with 8MHz)

3. **Generate Code**

---

##  Code Overview

### `main.c`

```c
#include "mcc_generated_files/mcc.h"

uint8_t buttonLastState = 0;
uint8_t buttonStableState = 0;
uint32_t lastDebounceTime = 0;
const uint8_t debounceDelay = 20; // in milliseconds

extern volatile uint32_t millis;

int main(void) {
    SYSTEM_Initialize();

    while (1) {
        uint8_t currentState = BUTTON_GetValue();

        if (currentState != buttonLastState) {
            lastDebounceTime = millis; // Reset timer on state change
        }

        if ((millis - lastDebounceTime) > debounceDelay) {
            if (currentState != buttonStableState) {
                buttonStableState = currentState;

                if (buttonStableState != 0) {
                    LED_Toggle();
                }
            }
        }

        buttonLastState = currentState;
    }
}
