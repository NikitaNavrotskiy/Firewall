/**
 * @file arg.h
 */

#ifndef _FIREWALL_SRC_ARG_H
#define _FIREWALL_SRC_ARG_H

#include <getopt.h>
#include <stddef.h>

/**
 * @struct fw_opt
 * @brief Structure to store program options.
 * @var arg_i Stores file to get input from.
 * @var arg_f Stores file to get firewall rules from.
 * @var arg_o Stores file to writing logs.
 */
typedef struct fw_opt
{
  /**
   * @brief Stores file to get input from.
   */
  char *arg_i;

  /**
   * @brief Stores file to get firewall rules from.
   */
  char *arg_f;

  /**
   * @brief Stores file to writing logs.
   */
  char *arg_o;
} fw_opt_t;

/**
 * @brief Function to write program options to struct fw_opt
 * from argv.
 *
 * @param argc Argc param of main().
 * @param argv Argv param of main().
 * @param options struct fw_opt to write options.
 * @return Status code. 0 on success.
 */
int fw_opt_get (int argc, char **argv, fw_opt_t *options);

#endif //_FIREWALL_SRC_ARG_H
