#include "test.h"

bool __test_is_rules_equal(fw_rule_t *first, fw_rule_t *second) {
  return first->daddr == second->daddr && first->dmask == second->dmask &&
         first->dport == second->dport && first->saddr == second->saddr &&
         first->smask == second->smask && first->sport == second->sport &&
         first->proto == second->proto && first->action == second->action;
}

void __test_is_lists_equal(fw_rule_t *head, fw_rule_t *expect_array) {
  int index = 0;

  for (fw_rule_t *cur = head; cur; cur = cur->next) {
    ck_assert(__test_is_rules_equal(cur, expect_array + index));
    index++;
  }
}

START_TEST(Rules_from_file) {
  fw_rule_t expect[] = {
      {101058054, 117901063, NULL, 4444, 5555, UDP, ACCEPT, 18, 1},
      {16843009, 0, NULL, 0, 0, NONE, ACCEPT, 32, 0},
      {33686018, 0, NULL, 0, 0, NONE, DROP, 23, 0},
      {0, 67372036, NULL, 0, 0, NONE, ACCEPT, 0, 32},
      {0, 84215045, NULL, 0, 0, NONE, DROP, 0, 23},
      {0, 0, NULL, 0, 1024, NONE, ACCEPT, 0, 0},
      {0, 0, NULL, 3245, 0, NONE, DROP, 0, 0},
      {0, 0, NULL, 0, 0, UDP, ACCEPT, 0, 0},
      {0, 0, NULL, 0, 0, TCP, DROP, 0, 0}};

  fw_rule_t *head = fw_rule_from_file("test/test.fwall");

  __test_is_lists_equal(head, expect);

  fw_rule_free(head);
}

Suite *suite_rules_load() {
  Suite *s;
  TCase *tc;

  s = suite_create("Rules load test");
  tc = tcase_create("Rules load test");

  suite_add_tcase(s, tc);

  tcase_add_test(tc, Rules_from_file);

  return s;
}
