// Header file for HCSR04 sensor 

#ifndef HCSR04_H // if HCSR04_H is not defined, run all of the code below: 

#define HCSR04_H
#include "driver/gpio.h"

void hcsr04_init(gpio_num_t trig_pin, gpio_num_t echo_pin); 
float hcsr04_get_distance(void); 

#endif