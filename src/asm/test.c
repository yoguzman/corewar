#include "op.h"
#include "asm.h"

int	main(void)
{
  t_if info;
  int i = 0;
  
  printf("ret = %d\n_______\n", pars_instr("live    r42 # entree", &info, i));
  printf("ret = %d\n_______\n", pars_instr("tamer    %42 #entree", &info, i));
  printf("ret = %d\n_______\n", pars_instr("live    %42 %46# entree", &info, i));
  printf("ret = %d\n_______\n", pars_instr("live    %42#entree", &info, i));
  printf("ret = %d\n_______\n", pars_instr(" # entree", &info, i));
  printf("ret = %d\n_______\n", pars_instr("#entree", &info, i));
  return (0);
}
