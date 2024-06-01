#include "test.h"

void run_one_test(Suite *test) {
  SRunner *sr = srunner_create(test);
  srunner_set_fork_status(sr, CK_FORK);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
}

void run_tests() {
  Suite *list[] = {suite_convert(), suite_rules_load(), suite_match(), NULL};

  for (Suite **cur = list; *cur; cur++)
    run_one_test(*cur);
}

int main() { run_tests(); }
