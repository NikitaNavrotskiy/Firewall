#include "test.h"
#include <limits.h>

START_TEST(Convert_ip_int_to_str) {
  uint64_t int_ip = 1;
  char str_ip[16] = {0};
  while (int_ip < UINT_MAX) {
    fw_convert_ip_int_to_str(int_ip, str_ip);
    uint32_t res_int_ip = fw_convert_ip_str_to_int(str_ip);
    ck_assert_uint_eq(int_ip, res_int_ip);
    int_ip += 9317;
  }
}

Suite *suite_convert() {
  Suite *s;
  TCase *tc;

  s = suite_create("Convert test");
  tc = tcase_create("Convert test");

  suite_add_tcase(s, tc);

  tcase_add_test(tc, Convert_ip_int_to_str);

  return s;
}
