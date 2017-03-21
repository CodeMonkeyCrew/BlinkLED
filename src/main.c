/*
 * Blink LED
 */
#include <inttypes.h>
//This register controls the PER domain power state transition.
#define PM_PWSTCTRL_PER (volatile uint32_t*)0x483070E0
//Controls the modules functional clock activity.
#define CM_ICLKEN_PER (volatile uint32_t*)0x48005010

#define GPIO5_SETDATAOUT (volatile uint32_t*) 0x49056094
#define GPIO5_CLEARDATAOUT (volatile uint32_t*) 0x49056090
#define GPIO5_OE (volatile uint32_t*)0x49056034

// register to set mux mode (bit 16-18)
#define LED_GREEN_MUXMODE (volatile uint32_t*) 0x4800217C

#define LED_GREEN (1<<21)

int main(void)
{
    volatile long i = 0;
    /*
     * System
     */
    *PM_PWSTCTRL_PER |= ((1 << 0) | (1 << 1)); //Set power state on 0x03 Power On
    *CM_ICLKEN_PER |= (1 << 16);

    // set mux mode to 4 (GPIO)
    *LED_GREEN_MUXMODE &= ~(1 << 16);
    *LED_GREEN_MUXMODE &= ~(1 << 17);
    *LED_GREEN_MUXMODE |= (1 << 18);
    /*
     * GPIO
     */

    *GPIO5_OE &= ~LED_GREEN; //set GPIO5_OE pin 16 on 0 -> OutputPin

    while (1)
    {
        for (i = 0; i < 100000L; i++)
        {
        }
        // led on
        *GPIO5_SETDATAOUT |= LED_GREEN;
        for (i = 0; i < 100000L; i++)
        {
        }
        *GPIO5_CLEARDATAOUT |= LED_GREEN;
    }
    return 0;
}
