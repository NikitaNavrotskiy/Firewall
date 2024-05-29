#ifndef _FIREWALL_SRC_ARG_H
#define _FIREWALL_SRC_ARG_H

#include <getopt.h>
#include <stddef.h>

typedef struct {
  char *arg_i;
  char *arg_f;
  char *arg_o;
} fw_opt_t;

int fw_opt_get(int argc, char **argv, fw_opt_t *options);

#endif //_FIREWALL_SRC_ARG_H
