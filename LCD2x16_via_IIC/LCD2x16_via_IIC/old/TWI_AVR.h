#ifndef __TWI_AVR__
#define __TWI_AVR__

#include <avr/io.h>
/* ---------------------------
 SETUP OF TWI INTERFACE
 --------------------------- */
#define TWI_PRESCALER_1 ((0<<TWPS1)|(0<<TWPS0))
#define TWI_PRESCALER_4 ((0<<TWPS1)|(1<<TWPS0))
#define TWI_PRESCALER_16 ((1<<TWPS1)|(0<<TWPS0))
#define TWI_PRESCALER_64 ((1<<TWPS1)|(1<<TWPS0))

/* available values are <1;255> */
#define BITRATE_REGISTER_VALUE 72
/* available values are _1, _4, _16, _64 */
#define TWI_PRESCALER TWI_PRESCALER_1
// for calculation of SCL freq. see page 222 in ATmega328P Data Sheet

// SCL frequency = 40kHz

#define ACK 1
#define NOACK 0

// TWI setup functuons - some settings like 
void TWIsetup(void);
// TWI start signal
void TWIstart(void);
// TWI stop signal
void TWIstop(void);
// TWI transmit one byte of data
void TWIwrite(char data);
// TWI read one byte of data
char TWIread(char ack);



#endif