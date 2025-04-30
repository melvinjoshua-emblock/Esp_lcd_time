#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "wifi.h"
#include "time_sync.h"
#include "lcd.h"
#include <time.h>
#include "buttons.h"
#include "driver/gpio.h"
#include <sys/time.h>

bool edit_mode = false;
int edit_hour = 0, edit_minute = 0;

void app_main(void)
{
    // Initialize NVS Flash
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Start Wi-Fi
    wifi_init_sta();

    // Wait for Wi-Fi to connect
    vTaskDelay(pdMS_TO_TICKS(20000));

    // Obtain time via NTP
    obtain_time();
    vTaskDelay(pdMS_TO_TICKS(10000));

    // Set Timezone to IST
    setenv("TZ", "IST-5:30", 1);
    tzset();

    // Initialize LCD
    lcd_init();
    lcd_clear();
    lcd_write_string("Clock Started");
    vTaskDelay(pdMS_TO_TICKS(2000));
    lcd_clear();

    // Initialize Buttons
    buttons_init();

    // Track last button state
    bool last_btn_confirm = false;
    bool last_btn_hour = false;
    bool last_btn_min = false;

    while (1) {
        time_t now;
        struct tm timeinfo;
        time(&now);
        localtime_r(&now, &timeinfo);

        // Read button states
        bool curr_btn_confirm = is_button_pressed(GPIO_NUM_25);
        bool curr_btn_hour = is_button_pressed(GPIO_NUM_32);
        bool curr_btn_min = is_button_pressed(GPIO_NUM_33);

        // Toggle edit mode on button press edge
        if (curr_btn_confirm && !last_btn_confirm) {
            edit_mode = !edit_mode;

            if (edit_mode) {
                edit_hour = timeinfo.tm_hour;
                edit_minute = timeinfo.tm_min;
            } else {
                // Apply edited time
                struct tm new_time = {
                    .tm_year = timeinfo.tm_year,
                    .tm_mon = timeinfo.tm_mon,
                    .tm_mday = timeinfo.tm_mday,
                    .tm_hour = edit_hour,
                    .tm_min = edit_minute,
                    .tm_sec = 0
                };
                time_t new_timestamp = mktime(&new_time);
                struct timeval now_val = { .tv_sec = new_timestamp };
                settimeofday(&now_val, NULL);
            }
        }

        // Increment time only once per press
        if (edit_mode) {
            if (curr_btn_hour && !last_btn_hour) {
                edit_hour = (edit_hour + 1) % 24;
            }
            if (curr_btn_min && !last_btn_min) {
                edit_minute = (edit_minute + 1) % 60;
            }
        }

        // Update last button states
        last_btn_confirm = curr_btn_confirm;
        last_btn_hour = curr_btn_hour;
        last_btn_min = curr_btn_min;

        // Display time
        char time_str[16];
        if (edit_mode) {
            snprintf(time_str, sizeof(time_str), "SET %02d:%02d", edit_hour, edit_minute);
        } else {
            snprintf(time_str, sizeof(time_str), "%02d:%02d:%02d",
                     timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
        }

        lcd_clear();
        lcd_set_cursor(0, 0);
        lcd_write_string(edit_mode ? "Edit Mode" : "Time:");
        lcd_set_cursor(0, 1);
        lcd_write_string(time_str);

        vTaskDelay(pdMS_TO_TICKS(200));  
    }
}
