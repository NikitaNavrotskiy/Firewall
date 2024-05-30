#include "arg.h"
#include "firewall_db.h"

#include <stdio.h>

int main(int argc, char **argv) {
  int status = 0;
  fw_opt_t options = {0};

  status = fw_opt_get(argc, argv, &options);

  if (status)
    return status;

  fw_rule_t *head = fw_rule_from_file(options.arg_f);

  for (fw_rule_t *cur = head; cur != NULL; cur = cur->next) {
    printf("src: %15s:% 5d dst: %15s:% 5d proto: %d action: %d\n", cur->saddr,
           cur->sport, cur->daddr, cur->dport, cur->proto, cur->action);
  }

  fw_rule_free(head);

  return 0;
}
