#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// FND에 출력할 숫자 패턴
unsigned char digit[10] = 
{
	0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x67
};

// FND에 숫자 출력 함수
void FND_NUM(uint8_t num) 
{
	if (num < 10) 
	{
		PORTA = digit[num];
	}
}

// 모터 세기 조절 함수
void setMotorSpeed(uint8_t speed) 
{
	switch (speed) 
	{
		case 0:  // 정지
		OCR0 = 0;
		
		break;
		
		case 1:  // 1단 (50%)
		OCR0 = 128;
		
		break;
		
		case 2:  // 2단 (100%)
		OCR0 = 255;
		
		break;
		
		default:
		OCR0 = 0;  // 기본값은 정지
		break;
	}
}

int main(void) 
{
	// PB4 출력 설정 (PWM 출력)
	DDRB |= (1 << DDB4);

	// Fast PWM 모드 설정, 분주비 256
	TCCR0 |= (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS02);

	// PORTA를 출력으로 설정 (FND)
	DDRA = 0xff;

	// PG2, PG3, PG4를 입력으로 설정 (버튼)
	DDRG &= ~((1 << PING2) | (1 << PING3) | (1 << PING4));
	PORTG |= (1 << PING2) | (1 << PING3) | (1 << PING4);  // 내부 풀업 저항 활성화

	uint8_t motorSpeed = 0;  // 모터 세기 초기값 (정지)

	while (1) 
	{
		// FND에 0부터 9까지 무한 반복 출력
		for (uint8_t i = 0; i < 10; i++) 
		{
			FND_NUM(i);  // FND에 숫자 출력
			_delay_ms(50);  // 0.2초 딜레이

			// 버튼 입력 확인
			if (!(PING & (1 << PING2))) // PG2 버튼이 눌렸을 때 (정지)
			{  
				motorSpeed = 0;
				
				_delay_ms(50);  // 디바운싱
			}
			else if (!(PING & (1 << PING3))) // PG3 버튼이 눌렸을 때 (1단)
				{  
				motorSpeed = 1;
				
				_delay_ms(50);  // 디바운싱
			} 
			else if (!(PING & (1 << PING4))) // PG4 버튼이 눌렸을 때 (2단)
			{  
				motorSpeed = 2;
				_delay_ms(5);  // 디바운싱
			}

			// 모터 세기 설정
			setMotorSpeed(motorSpeed);
		}
	}
}





