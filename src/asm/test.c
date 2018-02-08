#include "op.h"
#include "asm.h"

int	main(void)
{
  t_if info;
  
  printf("ret = %d\n", pars_turfu("live    %42 #entree", &info));
  return (0);
}
