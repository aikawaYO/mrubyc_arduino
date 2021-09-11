#ifndef _ADC_H
#define _ADC_H

#include "mrubyc.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
    
/* C codes */

typedef struct ADC_HANDLE {
  int pin_num;
} ADC_HANDLE;

/* mruby/c codes */
void mrbc_init_class_adc(struct VM *vm);

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif
