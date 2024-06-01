#include "arg.h"
#include "firewall_db.h"
#include "process.h"

int
main (int argc, char **argv)
{
  int status = 0;
  fw_opt_t options = { 0 };

  status = fw_opt_get (argc, argv, &options);

  if (status)
    return status;

  fw_rule_t *head = fw_rule_from_file (options.arg_f);
  fw_process_input (&options, head);

  fw_rule_free (head);

  return 0;
}
