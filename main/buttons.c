#include "buttons.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define BTN_HOUR    GPIO_NUM_32
#define BTN_MIN     GPIO_NUM_33
#define BTN_CONFIRM GPIO_NUM_25

#define BUTTON_DEBOUNCE_MS 200

static void configure_button(gpio_num_t gpio_num) {
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << gpio_num),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);
}

void buttons_init(void) {
    configure_button(BTN_HOUR);
    configure_button(BTN_MIN);
    configure_button(BTN_CONFIRM);
}

bool is_button_pressed(int gpio_num) {
    if (gpio_get_level(gpio_num) == 0) {  // Active-low button
        vTaskDelay(pdMS_TO_TICKS(BUTTON_DEBOUNCE_MS));
        if (gpio_get_level(gpio_num) == 0) {
            return true;
        }
    }
    return false;
}
