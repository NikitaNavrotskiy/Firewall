#ifndef _FIREWALL_SRC_UTIL_PACKET_GEN_GENERATOR_H
#define _FIREWALL_SRC_UTIL_PACKET_GEN_GENERATOR_H

#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../../../src/convert.h"
#include "../../../src/packet.h"

#define GEN_FORMAT "%-15s %-15s %-5hu %-5hu %-2d\n"

#define GEN_COUNT_DEFAULT 10

uint32_t gen_generate_ip();

uint16_t gen_generate_port();

enum fw_proto gen_generate_proto();

void gen_generator_proc(FILE *fd_out, uint64_t count, uint64_t milsec_timeout);

#endif
