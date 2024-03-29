#include <stdio.h>
#include "nvs_flash.h"
#include "esp_log.h"
#include "wifi.h"
#include "httpServer.h"
#include "httpClient.h"
#include "misc.h"
#include "ds18b20_lowlevel.h"
#include "my_settings.h" // make your own my_settings.h

void nvs_init() {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);    
}

void app_main(void)
{
    nvs_init();
    wifi_init();
    wifi_connect(WIFI_SSID, WIFI_PASSWD);
    httpServer_init();

    misc_init();
    ds18b20_init(1);
    
    //misc_http_get("https://www.google.com");
    //misc_http_get("https://api.open-meteo.com/v1/forecast?latitude=36.9741&longitude=-122.0308&hourly=temperature_2m&forecast_days=1");
    misc_whatsapp("Hello EMBD.X403");
    misc_wifi_scan();

    //mise_location_services();

    while (true) {
        misc_read_extTemp();

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
