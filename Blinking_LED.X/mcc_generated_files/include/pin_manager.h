/**
  @Company
    Microchip Technology Inc.

  @Description
    This Source file provides APIs.
    Generation Information :
    Driver Version    :   1.0.0
*/
/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PINS_H_INCLUDED
#define PINS_H_INCLUDED

#include <avr/io.h>
#include "port.h"

//get/set LED aliases
#define LED_SetHigh() do { PORTD |= 0x10; } while(0)
#define LED_SetLow() do { PORTD &= ~0x10; } while(0)
#define LED_Toggle() do { PIND |= 0x10; } while(0)
#define LED_GetValue() (PIND & (0x1 << 4))
#define LED_SetDigitalInput() do { DDRD &= ~0x10; } while(0)
#define LED_SetDigitalOutput() do { DDRD |= 0x10; } while(0)
#define LED_SetPullUp() do { PORTD |= 0x10; } while(0)
#define LED_ResetPullUp() do { PORTD &= ~0x10; } while(0)
#define LED_SetInverted() do { PORTD_PIN4CTRL  |= PORT_INVEN_bm; } while(0)
#define LED_ResetInverted() do { PORTD_PIN4CTRL  &= ~PORT_INVEN_bm; } while(0)

//get/set BUTTON aliases
#define BUTTON_SetHigh() do { PORTB |= 0x1; } while(0)
#define BUTTON_SetLow() do { PORTB &= ~0x1; } while(0)
#define BUTTON_Toggle() do { PINB |= 0x1; } while(0)
#define BUTTON_GetValue() (PINB & (0x1 << 0))
#define BUTTON_SetDigitalInput() do { DDRB &= ~0x1; } while(0)
#define BUTTON_SetDigitalOutput() do { DDRB |= 0x1; } while(0)
#define BUTTON_SetPullUp() do { PORTB |= 0x1; } while(0)
#define BUTTON_ResetPullUp() do { PORTB &= ~0x1; } while(0)
#define BUTTON_SetInverted() do { PORTB_PIN0CTRL  |= PORT_INVEN_bm; } while(0)
#define BUTTON_ResetInverted() do { PORTB_PIN0CTRL  &= ~PORT_INVEN_bm; } while(0)

void PIN_MANAGER_Initialize();
#endif /* PINS_H_INCLUDED */
