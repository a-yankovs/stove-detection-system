
#include "hcsr04.h" // pulls func delcarations from .h file 
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include "driver/gpio.h"

// defines the gpio pin numbers 
static gpio_num_t trig; // static = only exist in this file 
static gpio_num_t echo; 

void hcsr04_init(gpio_num_t trig_pin, gpio_num_t echo_pin){ 
    trig = trig_pin; 
    echo = echo_pin; 
    
    gpio_set_direction(trig, GPIO_MODE_OUTPUT); // func from driver file
    gpio_set_direction(echo, GPIO_MODE_INPUT); 

}

// gets distance in cm using sensor readings 
float hcsr04_get_distance(void) { 
    gpio_set_level(trig, 0); // ensure that trig is LOW 
    vTaskDelay(pdMS_TO_TICKS(3)); // debounce 

    // the pattern to start measuring is turning the sensor to HIGH for 
    // 10 microsec - afterwards sensor emits ultrasonic pulse 
    gpio_set_level(trig, 1); 
    esp_rom_delay_us(10); // esp read only memory - low-level delay. Used it instead of 
      // vTaskDelay bc it only has granularity of 1ms, whereas i needed microsecs. 
    gpio_set_level(trig, 0); 
    int64_t start = esp_timer_get_time(); 
    while(gpio_get_level(echo) == 0) { 
        start = esp_timer_get_time(); 
    }

    int64_t end = start; 
    while(gpio_get_level(echo) == 1) { 
        end = esp_timer_get_time(); 
    }

    int64_t duration = end - start; 
    // 0.0343 cm/microsecond = 343 m/s --> speed of sound
    // /2 because the sound has to get there and back  
    return (duration * 0.0343) / 2.0f; 
}