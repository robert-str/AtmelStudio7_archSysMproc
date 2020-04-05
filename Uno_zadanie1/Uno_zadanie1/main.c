/*
 * Uno_zadanie1.c
 *
 * Created: 02.04.2020 11:30:23
 * Author : Robert
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile unsigned char val = 0, en=1, cmd;

ISR(USART_RX_vect){
	cmd = UDR0;
}

ISR(INT1_vect){
	if(en)
		PORTB ^= 0x01;
}

void USART_Init(void){
	/*Set baud rate */
	UBRR0H = (unsigned char)0;
	UBRR0L = (unsigned char)16;
	UCSR0A |= (1<<U2X0);
	/* Enable receiver and transmitter */
	UCSR0B = (1<<TXEN0) | (1<<RXEN0) | (1<<RXCIE0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (0<<USBS0)|(3<<UCSZ00);
}
	
void USART0_send(char data){
	while ( !(UCSR0A & (1<<UDRE0)) );
	UDR0 = data;
}

void USART0_sendString(char* data){
	unsigned char i=0;
	
	while(data[i] != 0){
		while ( !(UCSR0A & (1<<UDRE0)) );
		UDR0 = data[i];
		if(i==255)
			break;
		i++;
	}
}

int main(void)
{
	//unsigned char val=0, en=1;
	unsigned char val2=0, lastvalue = 0;//, cmd=0;
	unsigned int cnt = 0;
	DDRB |= 0x2F;
	PORTB |= 0x21;
	
	DDRD = 0;
    
	sei();
	EICRA |= (1<<ISC10 | 1<<ISC11);
	EIMSK |= 0x02;
	
	USART_Init();
	
	/* Replace with your application code */
    while (1) 
    {
		_delay_ms(1);
		PORTB ^= 0x20;
		_delay_ms(10);
		
	//	if(UCSR0A & (1<<RXC0)){
		//	cmd = UDR0;
		//	PORTB ^= 0x04;
	//	}
		
		if(cmd != 0){
			switch (cmd)
			{
			case 'b':
				PORTB ^= 0x04;
				break;
			default:
				break;
			}
			cmd=0;
		}
		
		if((PIND & 0x10) != 0x10)
		{
			if(val2 == 0){
				USART0_sendString("Green pressed\r");
				en = !en;
				PORTB ^= 0x02;
			}
			val2 = 1;
		}else val2 = 0;
		
		/*if((PIND & 0x08) != 0x08)
		{
			if(val == 0 && en)
				PORTB ^= 0x01;
			val = 1;			
		}else val = 0;*/
    }
}

