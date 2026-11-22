#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#define RS PB0
#define EN PB1

// LCD command function
void lcd_command(unsigned char cmd)
{
    PORTB = (PORTB & 0x0F) | (cmd & 0xF0);

    PORTB &= ~(1 << RS);

    PORTB |= (1 << EN);
    _delay_ms(1);
    PORTB &= ~(1 << EN);

    PORTB = (PORTB & 0x0F) | (cmd << 4);

    PORTB |= (1 << EN);
    _delay_ms(1);
    PORTB &= ~(1 << EN);
}

// LCD data function
void lcd_data(unsigned char data)
{
    PORTB = (PORTB & 0x0F) | (data & 0xF0);

    PORTB |= (1 << RS);

    PORTB |= (1 << EN);
    _delay_ms(1);
    PORTB &= ~(1 << EN);

    PORTB = (PORTB & 0x0F) | (data << 4);

    PORTB |= (1 << EN);
    _delay_ms(1);
    PORTB &= ~(1 << EN);
}

// LCD initialization
void lcd_init()
{
    DDRB = 0xFF;

    lcd_command(0x02);
    lcd_command(0x28);
    lcd_command(0x0C);
    lcd_command(0x06);
    lcd_command(0x01);
}

// Display string function
void lcd_string(char *str)
{
    while (*str)
    {
        lcd_data(*str++);
    }
}

int main(void)
{
    lcd_init();

    // Display name on first line
    lcd_command(0x80);
    lcd_string("Vishal Bhodde");

    // Display USN on second line
    lcd_command(0xC0);
    lcd_string("1IC24AM010");

    while (1)
    {
    }
}