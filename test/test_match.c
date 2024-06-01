#include "test.h"

START_TEST(Packet_match) {
  fw_rule_t *head = fw_rule_from_file("test/test.fwall");

  fw_packet_t packets[] = {{16843009, 16843010, 1111, 2222, TCP},
                           {16843009, 435245224, 2532, 2, UDP},
                           {33686017, 14133686, 21, 22, TCP},
                           {33686526, 33686523, 80, 443, UDP},
                           {3789677025, 84214785, 888, 2824, TCP},
                           {3789677025, 84215294, 22, 2, UDP},
                           {1, 2, 23, 1024, TCP},
                           {1, 2, 23, 1024, UDP},
                           {1, 2, 3245, 10, TCP},
                           {21, 22, 3245, 10, UDP},
                           {23, 24, 9999, 8888, TCP},
                           {44, 93, 9999, 8888, UDP},
                           {101056513, 1, 4444, 5555, UDP},
                           {101072894, 1, 4444, 5555, UDP},
                           {101056513, 2147483646, 4444, 5555, UDP},
                           {101072894, 2147483646, 4444, 5555, UDP},
                           {101056513, 1, 4444, 5555, TCP},
                           {101072894, 1, 4444, 5555, TCP},
                           {101056513, 2147483646, 4444, 5555, TCP},
                           {101072894, 2147483646, 4444, 5555, TCP},
                           {101056513, 1, 444, 5555, UDP},
                           {101072894, 1, 4444, 5556, UDP},
                           {101056513, 2147483647, 4444, 5555, UDP},
                           {101072894, 2147483647, 4444, 5555, UDP}};

  enum fw_action expect[] = {ACCEPT, ACCEPT, DROP,   DROP,   DROP,   DROP,
                             ACCEPT, ACCEPT, DROP,   DROP,   DROP,   ACCEPT,
                             ACCEPT, ACCEPT, ACCEPT, ACCEPT, DROP,   DROP,
                             DROP,   DROP,   ACCEPT, ACCEPT, ACCEPT, ACCEPT};

  for (int i = 0; i < 24; i++) {
    ck_assert_int_eq(expect[i], fw_rule_process_packet(head, packets + i));
  }

  fw_rule_free(head);
}

Suite *suite_match() {
  Suite *s;
  TCase *tc;

  s = suite_create("Packet match test");
  tc = tcase_create("Packet match test");

  suite_add_tcase(s, tc);

  tcase_add_test(tc, Packet_match);

  return s;
}
