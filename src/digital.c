#include "digital.h"

/* ================================ C codes ================================ */

GPIO_HANDLE gpioh[21];

/* ============================= mruby/c codes ============================= */
static void c_gpio_new(mrb_vm *vm, mrb_value *v, int argc) {
    *v = mrbc_instance_new(vm, v->cls, sizeof(GPIO_HANDLE *));
    *((GPIO_HANDLE **)v->instance->data) = &gpioh[GET_INT_ARG(1)];
    GPIO_HANDLE *handle = *(GPIO_HANDLE **)v->instance->data;
    handle->pin_num = GET_INT_ARG(1);
}

static void c_gpio_write(mrb_vm *vm, mrb_value *v, int argc) {
    GPIO_HANDLE *handle = *(GPIO_HANDLE **)v->instance->data;
    int pin = handle->pin_num;
    int mode = GET_INT_ARG(1);
    digitalWrite(pin,mode);
}

static void c_gpio_setmode(mrb_vm *vm, mrb_value *v, int argc) {
    GPIO_HANDLE *handle = *(GPIO_HANDLE **)v->instance->data;
    int pin = handle->pin_num;
    int mode = GET_INT_ARG(1);
    pinMode(pin,mode);
}

static void c_gpio_read(mrb_vm *vm, mrb_value *v, int argc) {
    GPIO_HANDLE *handle = *(GPIO_HANDLE **)v->instance->data;
    int pin = handle->pin_num;
    SET_INT_RETURN(digitalRead(pin));
}

void mrbc_init_class_digital(struct VM *vm){
    mrb_class *gpio;
    gpio = mrbc_define_class(0, "GPIO",  mrbc_class_object);
    mrbc_define_method(0, gpio, "new", c_gpio_new);
    mrbc_define_method(0, gpio, "write", c_gpio_write);
    mrbc_define_method(0, gpio, "setmode", c_gpio_setmode);
    mrbc_define_method(0, gpio, "read", c_gpio_read);
}
