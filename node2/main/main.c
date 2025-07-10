// Main file for Node 2 - the distance detection system used to determine if someone
// has left the apartment. 

#include "hcsr04.h" // include header file for sensor used
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hcsr04.h"

#define ECHO_PIN 18 
#define TRIG_PIN 5

void app_main(){ 
    hcsr04_init(TRIG_PIN, ECHO_PIN); 

    while (true) { 
        float distance = hcsr04_get_distance(); 
        printf("Distance to object is %f cm", distance); 
        vTaskDelay(pdMS_TO_TICKS(1000)); // wait 500ms until next reading 
    }
}

