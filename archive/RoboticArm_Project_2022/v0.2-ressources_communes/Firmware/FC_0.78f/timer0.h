#ifndef TIMER0_H
#define TIMER0_H

#define TIMER_TEILER        CK8
#define TIMER_RELOAD_VALUE  250
#define HEF4017R_ON     PORTC |=  (1<<PORTC6)
#define HEF4017R_OFF    PORTC &= ~(1<<PORTC6)

void Timer_Init(void);
void TIMER2_Init(void);
void Delay_ms(unsigned int);
void Delay_ms_Mess(unsigned int);
unsigned int SetDelay (unsigned int t);
char CheckDelay (unsigned int t);

extern volatile unsigned int CountMilliseconds;
extern volatile unsigned char UpdateMotor;
extern volatile unsigned int beeptime;
extern volatile unsigned int cntKompass;
extern unsigned int BeepMuster;
extern volatile unsigned char SendSPI, ServoActive;
//extern volatile int16_t	ServoNickValue;
//extern volatile int16_t	ServoRollValue;

extern struct LongAngles angleIntegral;
#endif
