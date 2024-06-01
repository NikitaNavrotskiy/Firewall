#ifndef _FIREWALL_SRC_UTIL_PACKET_GEN_ARG_H
#define _FIREWALL_SRC_UTIL_PACKET_GEN_ARG_H

#include <getopt.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "generator.h"

typedef struct
{
  uint64_t timeout;
  uint64_t count;
  char *arg_o;
} gen_opt_t;

int gen_opt_get (int argc, char **argv, gen_opt_t *options);

#endif //_FIREWALL_SRC_ARG_H
