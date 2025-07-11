// Main file for Node 2 - the distance detection system used to determine if someone
// has left the apartment. 

#include "hcsr04.h" // include header file for sensor used
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "hcsr04.h"

#define ECHO_PIN 18 
#define TRIG_PIN 5
#define DETECTION_DISTANCE 20
#define EXIT_DEBOUNCE_MS 10000

unsigned long last_exit_time = 0; 

void app_main(){ 
    hcsr04_init(TRIG_PIN, ECHO_PIN); 
    printf("Sensor intialised\n"); 

    while (true) { 
        float distance = hcsr04_get_distance(); 
        printf("Distance to object is %f cm\n", distance);
        int64_t current_time = esp_timer_get_time() / 1000; 
        if (distance <= DETECTION_DISTANCE && current_time - last_exit_time >= EXIT_DEBOUNCE_MS) { 
            printf("Exit detected!\n");
            last_exit_time = current_time;  
        } 
        vTaskDelay(pdMS_TO_TICKS(1000)); // wait 1s until next reading 
    }
}

