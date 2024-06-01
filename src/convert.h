/**
 * @file convert.h
 */

#ifndef _FIREWALL_SRC_CONVERT_H
#define _FIREWALL_SRC_CONVERT_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Funtion to convert c-string ip to uint32_t representation.
 *
 * @param ip C-string ip address.
 * @return uint32_t Representation of ip.
 */
uint32_t fw_convert_ip_str_to_int(char *ip);

/**
 * @brief Funtion to convert uint32_t ip to c-string representation.
 *
 * @param int_ip uint32_t representation of ip.
 * @param str_ip char array to store string ip. Should has at least 16 cells.
 * @return uint32_t Representation of ip.
 */
void fw_convert_ip_int_to_str(uint32_t int_ip, char *str_ip);

#endif
