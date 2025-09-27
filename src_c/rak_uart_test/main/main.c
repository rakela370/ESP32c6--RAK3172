#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "esp_log.h"

#define UART_PORT       UART_NUM_1
#define UART_TX_PIN     4      // povezati na RX RAK modula
#define UART_RX_PIN     5      // povezati na TX RAK modula
#define UART_BAUD       115200

static const char *TAG = "RAK_TEST";

void app_main(void)
{
    // Konfigurisanje UARTa
    uart_config_t uart_config = {
        .baud_rate = UART_BAUD,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(UART_PORT, &uart_config);
    uart_set_pin(UART_PORT, UART_TX_PIN, UART_RX_PIN,
                 UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_PORT, 1024, 0, 0, NULL, 0);

    ESP_LOGI(TAG, "UART test start (TX=%d, RX=%d, %d baud)", UART_TX_PIN, UART_RX_PIN, UART_BAUD);

    // Saljemo neki inicijalni string ka RAK-u
    const char *init_msg = "AT\r\n";
    uart_write_bytes(UART_PORT, init_msg, strlen(init_msg));
    ESP_LOGI(TAG, "Sent: %s", "AT");

    uint8_t data[128];
    while (1) {
        int len = uart_read_bytes(UART_PORT, data, sizeof(data)-1, pdMS_TO_TICKS(100));
        if (len > 0) {
            data[len] = 0;
            ESP_LOGI(TAG, "RX: %s", (char *)data);
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
