/*
 * FND.c
 *
 * Created: 2025-02-22 오후 4:12:43
 *  Author: USER
 */ 


void FNDLED(uint8_t num)
{
	if (num < 10)
	{
		PORTA = digit[num];
	}
}