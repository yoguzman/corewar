#include "op.h"
#include "asm.h"

int	main(void)
{
  t_if info;
  
  printf("ret = %d\n_______\n", pars_instr("live    %42 # entree", &info));
  printf("ret = %d\n_______\n", pars_instr("live    %42 #entree", &info));
  printf("ret = %d\n_______\n", pars_instr("live    %42# entree", &info));
  printf("ret = %d\n_______\n", pars_instr("live    %42#entree", &info));
  return (0);
}
