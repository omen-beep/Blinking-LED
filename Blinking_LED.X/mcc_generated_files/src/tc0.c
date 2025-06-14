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

#include "../include/tc0.h"

volatile uint32_t millis = 0;

void Timer_DefaultCMPAIsrCallback(void);
void (*Timer_CMPA_isr_cb)(void) = &Timer_DefaultCMPAIsrCallback;
void Timer_DefaultCMPBIsrCallback(void);
void (*Timer_CMPB_isr_cb)(void) = &Timer_DefaultCMPBIsrCallback;
void Timer_DefaultOVFIsrCallback(void);
void (*Timer_OVF_isr_cb)(void) = &Timer_DefaultOVFIsrCallback;

void Timer_DefaultCMPAIsrCallback(void)
{
    //Add your ISR code here
}

void Timer_DefaultCMPBIsrCallback(void)
{
    //Add your ISR code here
}

void Timer_DefaultOVFIsrCallback(void)
{
    millis++;
}

void Timer_SetOVFIsrCallback(Timer_cb_t cb)
{
    Timer_OVF_isr_cb = cb;
}

void Timer_SetCMPAIsrCallback(Timer_cb_t cb)
{
    Timer_CMPA_isr_cb = cb;
}

void Timer_SetCMPBIsrCallback(Timer_cb_t cb)
{
    Timer_CMPB_isr_cb = cb;
}

ISR(TIMER0_COMPA_vect)
{
    if (Timer_CMPA_isr_cb != NULL)
        (*Timer_CMPA_isr_cb)();
    
    TIFR0 = OCF0A;
}

ISR(TIMER0_COMPB_vect)
{
    if (Timer_CMPB_isr_cb != NULL)
        (*Timer_CMPB_isr_cb)();
    
    TIFR0 = OCF0B;
}

ISR(TIMER0_OVF_vect)
{
    if (Timer_OVF_isr_cb != NULL)
        (*Timer_OVF_isr_cb)();
    
    TIFR0 = TOV0;
}


/**
 * \brief Initialize TC0 interface
 */
int8_t Timer_Initialize()
{
    //Compare A
    OCR0A = 0x00;

    //Compare B
    OCR0B = 0x00;

    //Count
    TCNT0 = 0x83;


    //TSM disabled; PSRSYNC disabled; 
    GTCCR = 0x00;

    //COMA 0; COMB 0; WGM 0; 
    TCCR0A = 0x00;

    //FOCA disabled; FOCB disabled; WGM disabled; CS VAL_0x03; 
    TCCR0B = 0x03;

    //OCIEB disabled; OCIEA disabled; TOIE enabled; 
    TIMSK0 = 0x01;

    return 0;
}

void Timer_WriteTimer(uint8_t timerVal)
{
    TCNT0=timerVal;
}

uint8_t Timer_ReadTimer(void)
{
    uint8_t readVal;

    readVal = TCNT0;

    return readVal;
}

void Timer_EnableInterrupt(void)
{
    TIMSK0 = 1 << OCIE0A /* Compare A Interrupt: enabled */
                  | 1 << OCIE0B /* Compare B Interrupt: enabled */
                  | 1 << TOIE0; /* Overflow Interrupt: enabled */
}
void Timer_DisableInterrupt(void)
{
    TIMSK0 = 0 << OCIE0A /* Compare 0 Interrupt: disabled */
                  | 0 << OCIE0B /* Compare 1 Interrupt: disabled */
                  | 0 << TOIE0; /* Overflow Interrupt: disabled */
}
void Timer_ClearOverflowInterruptFlag(void)
{
    TIFR0 &= ~TOV0; /* Overflow Interrupt: disabled */
}
bool Timer_IsOverflowInterruptEnabled(void)
{
    return ((TIMSK0 & TOIE0) > 0);
}
