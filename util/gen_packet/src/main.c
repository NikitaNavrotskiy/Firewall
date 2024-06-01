#include <stdio.h>

#include "arg.h"
#include "generator.h"

int
main (int argc, char **argv)
{
  FILE *fd_out = stdout;
  int status = 0;
  gen_opt_t options = { 0 };

  status = gen_opt_get (argc, argv, &options);

  if (options.arg_o)
    {
      fd_out = fopen (options.arg_o, "w");

      if (!fd_out)
        return 1;
    }

  if (status)
    return 2;

  gen_generator_proc (fd_out, options.count, options.timeout);

  if (fd_out)
    fclose (fd_out);

  return 0;
}
