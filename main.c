/*
 * Project_!.c
 *
 * Created: 2025-02-21 오후 2:37:41
 * Author : USER
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>



unsigned char digit[10] = 
{
	0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

void FNDLED(uint8_t num)
{
	if (num <= 9) 
	{
		PORTA = digit[num];
	}
}


int main(void)
{
	DDRB |= (1 << DDB4);  // PB4 출력 설정
	TCCR0 |= (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS02);  // Fast PWM, 비반전, 분주비 256

	
	DDRA = 0xff;  // PORTA를 출력으로 설정

	while (0) 
	{
		for (uint8_t i = 0; i < 10; i++) 
		{
			FNDLED(i);
			_delay_ms(200);
		}
	}
}
