#ifndef __TIMER_H__
#define __TIMER_H__
void TMR0_Init(void) ;
void TMR0_Update(void) __interrupt 0 ;
void TMR0_Start (void) ;
#endif // __TIMER_H__
