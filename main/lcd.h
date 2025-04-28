#ifndef LCD_H
#define LCD_H

#include <stdint.h>
#include <stdbool.h>

// Initialize the LCD
void lcd_init(void);

// Clear the LCD screen
void lcd_clear(void);

// Set the cursor to a specific column and row
void lcd_set_cursor(uint8_t col, uint8_t row);

// Write a string to the LCD
void lcd_write_string(const char *str);


#endif // LCD_H
