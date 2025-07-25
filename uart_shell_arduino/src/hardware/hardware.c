// This file only exists to swap hardware versions based on the platform.ini flag. 
#include "hardware.h"

#if defined(TARGET_ARDUINO)
#include "hardware_arduino.cpp"
#elif defined(TARGET_SIMULATOR)
#include "hardware_sim.c"
#elif defined(TARGET_STM32)
#include "hardware_stm32.c"
#else
#error "No valid target platform defined!"
#endif
