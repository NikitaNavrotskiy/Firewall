#ifndef _FIREWALL_TEST_TEST_H
#define _FIREWALL_TEST_TEST_H

#include <check.h>

#include "../src/convert.h"
#include "../src/firewall_db.h"
#include "../src/rule.h"

Suite *suite_convert();
Suite *suite_rules_load();

#endif
