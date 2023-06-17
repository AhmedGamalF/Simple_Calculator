/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD Challange
 *******************************************************************************/

# include "lcd.h"
# include "keypad.h"
#include <util/delay.h> /* For the delay functions */

uint16 Calculator( uint16 num1 , uint16 num2 , uint16 operation );

int main ()
{
	uint16 key = 0 ;
	uint16 temp = 0 ;
	static uint16 operand = 0 ;
	static uint8 oprator = 0 ;


	LCD_init(); /* LCD Intialization*/
	LCD_displayStringRowColumn(0, 1, "My Calculator");
	_delay_ms(1500);
	LCD_clearScreen(); /* clear the LCD*/

	while(1)
	{
		key = KEYPAD_getPressedKey(); /* Get the key pressed*/
		/* read the operands */
		if((key >= 0 ) && (key <= 9))
		{
			LCD_intgerToString(key); /* Display the pressed number  on the LCD*/
			temp =(temp * 10) + key ; /* Get the digits*/
		}

		else if (key == 13)
		{
			LCD_clearScreen(); /* Clear the LCD*/
			/* In case the user entered a number and then chooses to clear LCD */
			temp = 0 ;
		}
		else if(key == '=')

		{
			LCD_displayCharacter(key); /* Display the second operand */
			LCD_moveCursor(1, 11);
			LCD_intgerToString(Calculator(operand,temp,oprator)); /* Display the final result  */
			operand = 0;
		}
		else
		{
			LCD_displayCharacter(key); /* Display the operator on the LCD*/
			oprator = key ; /* save the operator selected*/
			operand = temp ; /* save the frist operand*/
			temp = 0 ; /* clear temp to get the second operand*/
		}

		_delay_ms(500);
	}

}

uint16 Calculator( uint16 num1 , uint16 num2 , uint16 operation )
{
	uint32 result = 0 ;
	switch(operation)
	{
	case '+':
		result = num1 + num2 ;
		break ;
	case '-':
		result = num1 - num2 ;
		break ;
	case '*':
		result = num1 * num2 ;
		break ;
	case '%':
		result = num1 / num2 ;
		break ;
	}
	return result ;
}
