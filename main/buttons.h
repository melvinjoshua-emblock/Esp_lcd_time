#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdbool.h>

void buttons_init(void);
bool is_button_pressed(int gpio_num);

#endif // BUTTONS_H
