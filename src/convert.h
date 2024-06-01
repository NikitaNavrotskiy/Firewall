#ifndef _FIREWALL_SRC_CONVERT_H
#define _FIREWALL_SRC_CONVERT_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32_t fw_convert_ip_str_to_int (char *ip);

void fw_convert_ip_int_to_str (uint32_t int_ip, char *str_ip);

#endif
