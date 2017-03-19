/*
 * Blink LED
 */

//This register controls the PER domain power state transition.
#define PM_PWSTCTRL_PER (long*)0x483070E0
//Controls the modules functional clock activity.
#define CM_FCLKEN_PER (long*)0x48005000

#define GPIO5_DATAOUT (long*)0x4905603C
#define GPIO5_OE (long*)0x49056034
#define GPIO5_CTRL (long*)0x49056030

#define LED1 (1<<21)

int main(void)
{
    volatile long i = 0;
    /*
     * System
     */
    *PM_PWSTCTRL_PER |= (1 << 0); //Set power state on
    *PM_PWSTCTRL_PER |= (1 << 1); //0x03 Power On
    *CM_FCLKEN_PER |= (1 << 16);    //enable functional clock for gpio5
    /*
     * GPIO
     */
    *GPIO5_OE |= ~LED1; //set GPIO5_OE pin 16 on 0 -> OutputPin
    *GPIO5_DATAOUT &= ~LED1;    //turn off led

    while (1)
    {
        for (i = 0; i < 2000000L; i++)
        {

        }
        *GPIO5_DATAOUT ^= ~LED1;
    }
    return 0;
}
