/*******************************************************************/
/**************** Name    : Mohamed Ahmed Hafiz ********************/
/**************** Date    : 25/9/2020           ********************/
/**************** SWC     :     TMR             ********************/
/**************** Version :     1.0             ********************/
/*******************************************************************/
#ifndef TMR_CONFIG_H
#define TMR_CONFIG_H


/***************** TIMER0 ****************/
/* Select Mode of Timer */
#define NORMAL_MODE              0
#define CTC_MODE                 1
#define FAST_PWM                 2
#define PHASE_CORRECT_PWM        3
#define TIMER0_MODE            FAST_PWM


/* Enable Timer0 OVF or CTC PIE  */
#define ENABLE_TIMER0_PIE             0
#define DISABLE_TIMER0_PIE            1
#define TIMER_PIE             ENABLE_TIMER0_PIE


/* Set Preload Value */
#define PRELOAD_VALUE                192




/* Select Action on OC0 Pin */
#define OC0_DISCONNECTED                         0
#define TOGGLE_OC0_ON_COMPARE                    1
#define CLEAR_OC0_ON_COMPARE                     2
#define NON_INVERTING_PWM                        2
#define SET_OC0_ON_COMPARE                       3
#define INVERTING_PWM                            3
#define TMR0_COMPARE_OUTPUT_MODE            NON_INVERTING_PWM


/* Set Timer0 Prescaler Value */
#define TIMER_OFF                          0
#define NO_PRESCALING                      1
#define CLOCK_8                            2
#define CLOCK_64                           3
#define CLOCK_256                          4
#define CLOCK_1024                         5
#define CLOCK_FALLING_EDGE                 6
#define CLOCK_RISING_EDGE                  7
#define TMR0_PRESCALER_VALUE             CLOCK_8



/***************** TIMER1 ****************/
/* Select Mode of Timer1 */
#define NORMAL_MODE                             0
#define PHASE_CORRECT_PWM_8BIT                  1
#define PHASE_CORRECT_PWM_9BIT                  2
#define PHASE_CORRECT_PWM_10BIT                 3
#define CTC_OCR1A                               4
#define FAST_PWM_8BIT                           5
#define FAST_PWM_9BIT                           6
#define FAST_PWM_10BIT                          7
#define PWM_PHASE_FREQUENCY_CORRECT_ICR1        8
#define PWM_PHASE_FREQUENCY_CORRECT_OCR1A       9
#define PWM_PHASE_CORRECT_ICR1                  10
#define PWM_PHASE_CORRECT_OCR1A                 11
#define CTC_ICR1                                12
#define FAST_PWM_ICR1                           13
#define FAST_PWM_OCR1A                          14
#define TIMER1_MODE                          CTC_OCR1A


 /* Enable Timer1 OVF or CTC PIE  */
#define ENABLE_TIMER1_PIE             0
#define DISABLE_TIMER1_PIE            1
#define TIMER1_PIE             ENABLE_TIMER1_PIE


	/* Set Max ICR1 Value */
#define ICR1_MAX_VALUE                          19999


///* Timer1 ISR CTC Counter */
//#define TMR1_ISR_CTC_COUNTER                   100


/* Select Action on OC1 Pin */
#define OC1_DISCONNECTED                                  0
#define TOGGLE_OC1_ON_COMPARE                             1
#define CLEAR_OC1_ON_COMPARE                              2
#define NON_INVERTING_PWM                                 2
#define SET_OC1_ON_COMPARE                                3
#define INVERTING_PWM                                     3
#define TMR1_CHANNELA_COMPARE_OUTPUT_MODE           OC1_DISCONNECTED
#define TMR1_CHANNELB_COMPARE_OUTPUT_MODE           OC1_DISCONNECTED


/* Set Timer1 Prescaler Value */
#define TIMER_OFF                           0
#define NO_PRESCALING                       1
#define CLOCK_8                             2
#define CLOCK_64                            3
#define CLOCK_256                           4
#define CLOCK_1024                          5
#define CLOCK_FALLING_EDGE                  6
#define CLOCK_RISING_EDGE                   7
#define TMR1_PRESCALER_VALUE              CLOCK_8






#endif
