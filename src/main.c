#include "./arg.h"

#include <stdio.h>

int main(int argc, char **argv) {
  int status = 0;
  fw_opt_t options = {0};

  status = fw_opt_get(argc, argv, &options);

  if (status)
    return status;
}
