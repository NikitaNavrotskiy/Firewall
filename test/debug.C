#include "../src/firewall_db.h"
#include "../src/rule.h"
#include <stdbool.h>

bool __test_is_rules_equal(fw_rule_t *first, fw_rule_t *second) {
  return first->daddr == second->daddr && first->dmask == second->dmask &&
         first->dport == second->dport && first->saddr == second->saddr &&
         first->smask == second->smask && first->sport == second->sport &&
         first->proto == second->proto && first->action == second->action;
}

void __test_is_lists_equal(fw_rule_t *head, fw_rule_t *expect_array) {
  int index = 0;

  for (fw_rule_t *cur = head; cur; cur = cur->next) {
    printf("%d", __test_is_rules_equal(cur, expect_array + index));
    index++;
  }
}

int main() {
  fw_rule_t expect[] = {{16843009, 0, NULL, 0, 0, UDP, ACCEPT, 32, 0}};

  fw_rule_t *head = fw_rule_from_file("test/test.fwall");

  __test_is_lists_equal(head, expect);

  fw_rule_free(head);
}
