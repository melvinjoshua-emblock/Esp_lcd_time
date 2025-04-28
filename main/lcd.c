// lcd.c
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_rom_sys.h"
#include "lcd.h"
#include <string.h>

#define LCD_RS_PIN    GPIO_NUM_4
#define LCD_EN_PIN    GPIO_NUM_5
#define LCD_D4_PIN    GPIO_NUM_18
#define LCD_D5_PIN    GPIO_NUM_19
#define LCD_D6_PIN    GPIO_NUM_21
#define LCD_D7_PIN    GPIO_NUM_22

static void lcd_send_nibble(uint8_t nibble) {
    gpio_set_level(LCD_D4_PIN, (nibble >> 0) & 0x01);
    gpio_set_level(LCD_D5_PIN, (nibble >> 1) & 0x01);
    gpio_set_level(LCD_D6_PIN, (nibble >> 2) & 0x01);
    gpio_set_level(LCD_D7_PIN, (nibble >> 3) & 0x01);
    
    gpio_set_level(LCD_EN_PIN, 1);
    vTaskDelay(pdMS_TO_TICKS(10));
    gpio_set_level(LCD_EN_PIN, 0);
    vTaskDelay(pdMS_TO_TICKS(10));
}

static void lcd_send_byte(uint8_t data, bool is_data) {
    gpio_set_level(LCD_RS_PIN, is_data);

    lcd_send_nibble(data >> 4);   // send higher nibble
    lcd_send_nibble(data & 0x0F); // send lower nibble
}

void lcd_clear(void) {
    lcd_send_byte(0x01, false);
    vTaskDelay(pdMS_TO_TICKS(10));
}

void lcd_set_cursor(uint8_t col, uint8_t row) {
    uint8_t offsets[] = {0x00, 0x40}; // Line 1, Line 2
    lcd_send_byte(0x80 | (offsets[row] + col), false);
}

void lcd_write_string(const char *str) {
    while (*str) {
        lcd_send_byte((uint8_t)(*str), true);
        str++;
    }
}

void lcd_init(void) {
    gpio_set_direction(LCD_RS_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(LCD_EN_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(LCD_D4_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(LCD_D5_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(LCD_D6_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(LCD_D7_PIN, GPIO_MODE_OUTPUT);

    vTaskDelay(pdMS_TO_TICKS(50)); // wait LCD power up

    lcd_send_nibble(0x03);
    vTaskDelay(pdMS_TO_TICKS(10));
    lcd_send_nibble(0x03);
    vTaskDelay(pdMS_TO_TICKS(10));
    lcd_send_nibble(0x03);
    vTaskDelay(pdMS_TO_TICKS(10));
    lcd_send_nibble(0x02); // Set to 4-bit mode

    lcd_send_byte(0x28, false); // 4-bit, 2 lines, 5x8 dots
    lcd_send_byte(0x0C, false); // Display ON, cursor OFF
    lcd_send_byte(0x06, false); // Entry mode
    vTaskDelay(pdMS_TO_TICKS(20));
    lcd_clear();
}
