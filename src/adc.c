#include "adc.h"

/* ================================ C codes ================================ */
ADC_HANDLE adch[21];

/* ============================= mruby/c codes ============================= */

void c_adc_read(mrb_vm *vm, mrb_value *v, int argc){
    ADC_HANDLE *handle = *(ADC_HANDLE **)v->instance->data;
    int pin = handle->pin_num;
    SET_FLOAT_RETURN(analogRead(pin));
}

void c_adc_read_v(mrb_vm *vm, mrb_value *v, int argc){
    ADC_HANDLE *handle = *(ADC_HANDLE **)v->instance->data;
    int pin = handle->pin_num;
    float adc_p = 5 * analogRead(pin) / 1023;
    SET_FLOAT_RETURN(adc_p);
}

void c_adc_new(mrb_vm *vm, mrb_value *v, int argc){
    *v = mrbc_instance_new(vm, v->cls, sizeof(ADC_HANDLE *));
    *((ADC_HANDLE **)v->instance->data) = &adch[GET_INT_ARG(1)];
    ADC_HANDLE *handle = *(ADC_HANDLE **)v->instance->data;
    handle->pin_num = GET_INT_ARG(1);
}

void mrbc_init_class_adc(struct VM *vm){
    mrb_class *adc;
    adc = mrbc_define_class(0, "ADC",  mrbc_class_object);
    mrbc_define_method(0, adc, "new", c_adc_new);
    mrbc_define_method(0, adc, "read", c_adc_read);
    mrbc_define_method(0, adc, "read_v", c_adc_read_v);
}
