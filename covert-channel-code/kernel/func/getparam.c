#include <stddef.h>
#include <stdint.h>
#include "uart.c"

//pow(int number,int power)
int pow(int a, int b) {
//  uart_puts("pow func in getparam.c\n");
    int result = 1;
    if (b == 0)
        result = 1;
    else {
        for (int i = 1; i <= b; i++)
            result *= a;
    }
    return result;

}

int div(int a, int b) {
//    uart_puts("div func in getparam.c\n");
    int result = 0;
    for (result = 0;; result++) {
        if (a < b)
            break;
        else
            a -= b;
    }
    return result;
}

//get 8-digit puf_address
unsigned int getaddress() {
//    uart_puts("getaddress func in getparam.c\n");
    unsigned int address = 0;
    short flag = 0;
    unsigned char temp;
    while ((int) (temp = uart_getc()) != 13) {
        int add = (int) temp;
        if (48 <= add && add <= 57) {
            uart_putc(temp);
            add = add - 48;
        } else if (65 <= add && add <= 70) {
            uart_putc(temp);
            add = add - 55;
        } else if (97 <= add && add <= 102) {
            uart_putc(temp);
            add = add - 87;
        }
        address = address * 16 + add;
        flag++;
    }
    if (flag == 0 || flag > 8) {
        return 0xC3000000;
    } else if (flag < 8) {
        address *= pow(16, 8 - flag);
    }
    return address;
}

// get puf_init_value
uint32_t getinitvalue() {
//    uart_puts("getinitvalue func in getparam.c\n");
    uint32_t result = 0;
    while (1) {
        unsigned char temp = uart_getc();
        if (temp >= '0' && temp <= '9') {
            uart_putc(temp);
            result = (result << 4) | (temp - '0');
        } else if (temp >= 'a' && temp <= 'f') {
            uart_putc(temp);
            result = (result << 4) | (temp - 'a' + 10);
        } else if (temp >= 'A' && temp <= 'F') {
            uart_putc(temp);
            result = (result << 4) | (temp - 'A' + 10);
        } else if (temp == 13) {
            uart_putc(temp);
            return result;
        }
    }
}

// get address_mode
uint32_t getaddmode() {
//    uart_puts("getaddmode func in getparam.c\n");
    uint32_t result = 0;
    while (1) {
        unsigned char temp = uart_getc();
        if (temp == 48) {
            uart_putc(temp);
            result = 0;
        } else if (temp == 49) {
            uart_putc(temp);
            result = 1;
        } else if (temp == 13) {
            uart_putc(temp);
            return result;
        }
    }
}

// get decay_time
int getdecaytime() {
//    uart_puts("getdecaytime func in getparam.c\n");
    int time = 0;
    short flag = 0;
    unsigned char temp;
    while ((int) (temp = uart_getc()) != 13) {
        if (48 <= temp && temp <= 57) {
            uart_putc(temp);
            int add = (int) temp - 48;
            time = time * 10 + add;
            flag = 1;
        }
    }
    uart_putc(temp);
    if (flag == 0) {
        return 60;
    }
    return time;
}

int getfuncfreq() {
//    uart_puts("getfuncfreq func in getparam.c\n");
    int freq = 0;
    short flag = 0;
    unsigned char temp;
    while ((int) (temp = uart_getc()) != 13) {
        if (48 <= temp && temp <= 57) {
            uart_putc(temp);
            int add = (int) temp - 48;
            freq = freq * 10 + add;
            flag = 1;
        }
    }
    uart_putc(temp);
    if (flag == 0) {
        return 1;
    }
    return freq;
}

// choose mode
int get_mode() {
//    uart_puts("getmode func in getparam.c\n");
    int mode = 0;
    while (1) {
        unsigned char temp = uart_getc();
        if (temp == 13) {
            uart_putc(temp);
            return mode;
        } else if (48 <= temp && temp <= 57) {
            uart_putc(temp);
            mode = temp - 48;
        }
    }
}
