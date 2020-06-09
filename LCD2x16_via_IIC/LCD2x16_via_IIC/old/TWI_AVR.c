#include "TWI_AVR.h"

// TWI setup functuons - some settings like
void TWIsetup(void){
	TWBR = BITRATE_REGISTER_VALUE;	// bit rate register
	TWSR = TWI_PRESCALER;				// prescaler
}

// TWI start signal
void TWIstart(void){
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT))); // wait for the end of start condition
}
// TWI stop signal
void TWIstop(void){
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	while ((TWCR & (1<<TWSTO))); // wait for the end of stop condition
}
// TWI transmit one byte of data
void TWIwrite(char data){
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT))); // wait for the end of transmision
}
// TWI read one byte of data
char TWIread(char ack){
	TWCR = ack
	? ((1 << TWINT) | (1 << TWEN) | (1 << TWEA)) // read with ACK
	: ((1 << TWINT) | (1 << TWEN)) ;			// read with NACK
	while (!(TWCR & (1<<TWINT)));				// wait for the end of transmision
	return TWDR;								// return recived byte
}