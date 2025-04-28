#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "wifi.h"
#include "time_sync.h"
#include "lcd.h"      // <-- Add LCD header
#include <time.h>     // For printing time

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
    vTaskDelay(pdMS_TO_TICKS(20000));  // (optional, safer)

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

    vTaskDelay(pdMS_TO_TICKS(2000)); // show startup message for 2 seconds
    lcd_clear();

    while (1) {
        time_t now;
        struct tm timeinfo;
        time(&now);
        localtime_r(&now, &timeinfo);
    
        // Print time to Serial Monitor
        printf("%02d:%02d:%02d\n", 
            timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);

        // Display time on LCD
        char time_str[16];
        snprintf(time_str, sizeof(time_str), "%02d:%02d:%02d", 
            timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);

        lcd_set_cursor(0, 0);  // Line 1
        lcd_write_string("Time:");
        lcd_set_cursor(0, 1);  // Line 2
        lcd_write_string(time_str);

        vTaskDelay(pdMS_TO_TICKS(1000));  // Update every second
    }
}
