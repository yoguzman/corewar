#include "asm.h"
#include "libft.h"
#include "op.h"

typedef	union u_neg
{
  unsigned short neg;
  unsigned char bneg[2];
}	     t_neg;
  
int	neg(unsigned short neg)
{
  int first_octet;
  int second_octet;
  t_neg lol;
  
  lol.neg = neg;
  first_octet = lol.bneg[0];
  second_octet = lol.bneg[1];
  lol.bneg[0] = second_octet + 1;
  lol.bneg[1] = first_octet;
  return (lol.neg);
}

int	main(void)
{
  int tamer;

  tamer = 510;
  printf("> %d\n", neg(tamer));
}
