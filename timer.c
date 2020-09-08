#include "timer.h"
#include <pic16f877a.h>
#include "pushbutton.h"
#include "counter.h"
#include "ssd.h"

#define TMR0_TICK_MS                           (5)

#define TMR0_SET_PRE_SCALER(y)                   PSA = 0              ;\
                                                 PS0 = (y &0x1 )       ;\
								                 PS1 = ((y &0x2 )>> 1)  ;\
								                 PS2 = ((y &0x4 )>> 2) ;
#define TMR0_CHECK_INTERRUPT_FLAG()              (TMR0IF)
#define TMR0_CLEAR_FLAG()                       (TMR0IF = 0)
#define TMR0_SELECT_CLOCK_SOURCE(x)	             (T0CS = x )
#define TMR0_EXTERNAL_SOURCE_EDGE_SELECTION(x)	 (TOSE = x )
#define TMR0_SET_TIME_MS(t)                      (TMR0 = 256 - 8*t )
#define TMR0_READ_COUNT()                        (TMR0 )
#define TMR0_SET_INT_STATE(x)                    (TMR0IE = x )

void TMR0_Init(void)
{
    TMR0_SET_PRE_SCALER(7);
    TMR0_SELECT_CLOCK_SOURCE(0);
    GIE = 1 ;
    TMR0_SET_INT_STATE(1) ;
}
void TMR0_Start (void)
{
    TMR0_CLEAR_FLAG() ;
    TMR0_SET_TIME_MS(TMR0_TICK_MS);
    TMR0_SELECT_CLOCK_SOURCE(0);
}
void TMR0_Update(void) __interrupt 0 // @ 5 ms
{
    // tasks
     static unsigned char counter = 0 ;
     counter += TMR0_TICK_MS ;
     if(counter == 20 )
     {
       PB_Update () ; // @20 ms to avoid bouncing time
       CNT_Update() ; // @20 ms as it update due to changes occurred in push buttons
       counter = 0 ;
     }
       SSD_Update () ; // @ 5 ms as i can not realize the ssd multiplexing

       TMR0_CLEAR_FLAG() ;
       TMR0_SET_TIME_MS(TMR0_TICK_MS);
}
