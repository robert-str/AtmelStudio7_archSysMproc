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
volatile unsigned char ADCValue;

ISR(USART_RX_vect){
	cmd = UDR0;
}

ISR(ADC_vect){
	ADCValue = ADCH;

}
ISR(INT1_vect){
	//if(en)
	//	PORTD ^= (1<<PD6);
}
/*
ISR(TIMER1_OVF_vect){ // normal mode
	PORTD ^= (1<<PD6);
}

ISR(TIMER1_COMPA_vect){ // CTC mode
	PORTD ^= (1<<PD6);
}
*/
ISR(TIMER0_OVF_vect){ // PWM
	OCR0A = ADCValue;
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
	unsigned char sendADC = 0;
	unsigned char lastADCValue=0;
    unsigned char tempVal1;
	
	DDRB |= 0x2F;
	PORTB |= 0x21;
	
	DDRD = 0x40;
	
	EICRA |= (1<<ISC10 | 1<<ISC11);
	EIMSK |= 0x02;
	
	// ADC Init
	ADMUX = (1<<REFS0) | (1<<ADLAR);
	DIDR0 = (1<<ADC0D);
	ADCSRB = 0;
	ADCSRA = (1<<ADEN) | (1<<ADATE) | (1<<ADIE) | 0x07;
	ADCSRA |= (1<<ADSC);
	
	//Timer1 Init - normal mode
	/*TCCR1A = 0;
	TCCR1B = (1<<CS11) | (1<<CS10) ;
	TIMSK1 = (1<<TOIE1);
	*/
	
	//Timer1 Init - CTC mode
	TCCR1A = (1<<COM1A0);
	TCCR1B = (1<<WGM12) | (1<<CS12) | (1<<CS10);
	TIMSK1 = 0;//(1<<OCIE1A);
	OCR1A = 390;
	
	//Timer0 Init - PWM
	TCCR0A = (1<<COM0A0) | (1<<COM0A1) | (1<<WGM01) | (1<<WGM00);
	TCCR0B = (1<<CS01) | (1<<CS00);
	TIMSK0 = (1<<TOIE0);
	OCR0A = 100;
	
	//USART Init
	USART_Init();
	
	sei();
	while(1){};
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
			case 'a':
				sendADC = 1;
				break;
			case 'z':
				sendADC = 0;
				break;
			case '+':
				tempVal1 = TCCR1B & 0x07;
				if(tempVal1 == 0x05)
					tempVal1 = 1;
				else
					tempVal1++;
				TCCR1B = (TCCR1B & 0xF8) | tempVal1;
				//USART0_sendString("OK\r");
				GTCCR = 0x01;
				break;
			case '-':
				tempVal1 = TCCR1B & 0x07;
				if(tempVal1 == 1)
					tempVal1 = 0x05;
				else
					tempVal1--;
					TCCR1B = (TCCR1B & 0xF8) | tempVal1;
				//USART0_sendString("OK\r");
				GTCCR = 0x01;
			case ']':
				if(OCR1A==0x8000)
					OCR1A = 0x0080;
				else
					OCR1A = OCR1A<<1;
				break;
			case 'p':
				USART0_send(TCNT1H);USART0_send(TCNT1L);
			break;
			
			default:
				break;
			}
			cmd=0;
		}
		
		if(sendADC)
			if( (ADCValue-lastADCValue)>=10 || (lastADCValue-ADCValue)>=10 ){
				USART0_send(ADCValue);
			lastADCValue = ADCValue;
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

