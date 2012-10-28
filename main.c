#include <stdio.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "i2c.h"
#include "nunchuck.h"
#include "uart.h"
 
int main(void)
{
    struct nunchuck n;

    i2c_init(I2C_FREQ(400000));
    uart_init(BAUD(38400));

    if (nunchuck_init()){
        printf("nunchuck failed to init\n");
    } else {
        printf("nunchuck: ok\n");
    }

    for (;;) {
        uint8_t res = nunchuck_read(&n);
        if (res){
            printf("error reading\n");
            _delay_ms(100);
            nunchuck_init();
            continue;
        }

        printf("%u\t%u\t", n.joy_x, n.joy_y);
        printf("%u\t%u\t%u\t", n.accel_x, n.accel_y, n.accel_z);
        printf("%c\t%c\n", n.z_button ? 'Z' : ' ', n.c_button ? 'C' : ' ');

        _delay_ms(5);
    }
 
    return 0;
 
}
