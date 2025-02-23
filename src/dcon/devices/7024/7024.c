#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <common.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include <dcon/dcon_dev.h>
#include "dcon/dcon_dev_common.h"
#include "7024.h"
#include "7024_hw.h"

#define MODULE_7024_ADDR 0x04
#define MODULE_7024_TYPE 0x60

#define MODULE_7024_NAME "7024"

/* Forward declarations */
static void set_7024_config(const char *, char *);
static void set_7024_analog_output(const char *, char *);
static void get_7024_name(const char *, char *);
static void get_7024_config(const char *, char *);
//static void set_7024_chan_analog_output(const char *, char *);
static void get_7024_analog_output(const char *, char *);

static const struct cmd_t cmds[] = {
    {"%AANN40CCFF", "056", get_7024_config},
    {"$AAM", "03", get_7024_name},
    {"$AA2", "03", get_7024_config},
    {"#AANV.VVV", "05", set_7024_analog_output},
    {"$AA6N", "03", get_7024_analog_output},
};

static struct dcon_dev dev_7024 = {
    .addr = MODULE_7024_ADDR,
    .type = MODULE_7024_TYPE,
};

static char current_value[6];

static inline void set_7024_config(const char *request, char *response) {
    char char_addr[3];

    strncpy(char_addr, request + 5, ARRAY_SIZE(char_addr) - 1);
    char_addr[2] = '\0';

    dev_7024.addr = hex_to_int(char_addr);

    snprintf(response, DCON_MAX_RESPONSE_SIZE, "!\r");
}

static inline long parse_out_voltage(const char *request) {
    const char *char_val = request + 4;
    long value;

    if ((request[3] - '0') > 3 || !isdigit((int) char_val[0]) ||
        !isdigit((int) char_val[2]) || !isdigit((int) char_val[3]) ||
        !isdigit((int) char_val[4])) {
        return -1;
    }

    value = (char_val[0] - '0') * PWM_PERIOD / 5;
    value += (char_val[2] - '0') * PWM_PERIOD / 100;
    value += (char_val[3] - '0') * PWM_PERIOD / 1000;
    value += (char_val[4] - '0') * PWM_PERIOD / 10000;

    return ((value > PWM_PERIOD) ? -1 : (value));
}

static inline void set_7024_analog_output(const char *request, char *response) {
    int value = parse_out_voltage(request);

    if (value != -1) {
        set_analog_output(value);
        memcpy(current_value, request + 4,
               sizeof(current_value) - 1);
        current_value[5] = '\0';
        snprintf(response, DCON_MAX_RESPONSE_SIZE, ">\r");
    } else {
        snprintf(response, DCON_MAX_RESPONSE_SIZE, "?\r");
    }

    return;
}

static void get_7024_analog_output(const char *request, char *response) {
    UNUSED(request);
    snprintf(response, DCON_MAX_RESPONSE_SIZE, "!%02x%s\r", dev_7024.addr,
             current_value);
}

static inline void get_7024_name(const char *request, char *response) {
    UNUSED(request);
    snprintf(response, DCON_MAX_RESPONSE_SIZE, "!%02x%s\r", dev_7024.addr,
             MODULE_7024_NAME);
}

static inline void get_7024_config(const char *request, char *response) {
    UNUSED(request);
    snprintf(response, DCON_MAX_RESPONSE_SIZE, "!%02x%02d0000\r", dev_7024.addr,
             dev_7024.type);
}

static void Task7024Function(void *unused) {
    UNUSED(unused);
    dcon_run_device(&dev_7024, cmds, ARRAY_SIZE(cmds));
}

void dcon_dev_7024_run(void) {
    init_7024();
    dcon_dev_register(&dev_7024);
    xTaskCreate(Task7024Function, "7024",
                DEFAULT_MODULE_STACK_SIZE, NULL, 1, NULL);
}
