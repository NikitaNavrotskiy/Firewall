#include "convert.h"

uint32_t fw_convert_ip_str_to_int(char *ip) {
  uint32_t res = 0;
  char *token;
  uint32_t octet;

  token = strtok(ip, ".");

  while (token != NULL) {
    octet = atoi(token);
    res = (res << 8) + octet;
    token = strtok(NULL, ".");
  }

  return res;
}

void fw_convert_ip_int_to_str(uint32_t int_ip, char *str_ip) {
  uint32_t mask = 0xFF;
  sprintf(str_ip, "%d.%d.%d.%d", (int_ip >> 24) & mask, (int_ip >> 16) & mask,
          (int_ip >> 8) & mask, int_ip & mask);
}
