/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 18:44:10 by jcoutare          #+#    #+#             */
/*   Updated: 2018/02/28 20:04:49 by jcoutare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"
#include "libft.h"

static const t_op    op_tab[17] =
{
        {"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
        {"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
        {"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
        {"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
        {"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
        {"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
                "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
        {"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
                "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
        {"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
                "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
        {"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
        {"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
                "load index", 1, 1},
        {"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
                "store index", 1, 1},
        {"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
        {"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
        {"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
                "long load index", 1, 1},
        {"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
        {"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
        {0, 0, {0}, 0, 0, 0, 0, 0}
};

void	avance_pc(t_corewar *vm, t_proc *lol, t_instr *instr)
{

}

void	zjmp(t_corewar *vm, t_proc *lol, t_instr *instr)
{
  
}

int	check_params(unsigned char *parameter_type, unsigned char parameter_count, char *val_arg)
{
  int i;
  int j;

  j = 2;
  i = 0;
  
  while (i < parameter_count)
    {
      if (parameter_type[i] & val_arg[i] == 0)
	  return (-1);
      i++;
    }
  return (0);
}

int 	*get_octet(char octet, char *val_arg, int opcode)
{
  char mask;
  int ret;
  int i;

  i = 2;
  mask = 3;
  while (i >= 0)
    {
      octet = octet >> 2;
      ret = octet & mask;
      if (ret == 3)
	ret = ret + 1;
      val_arg[i] = ret;
      i--;
    }
  if (check_params(op_tab[opcode].parameter_types, op_tab[opcode].parameter_count, val_arg) == -1)
    {
      printf("FAIL IN CHECK_PARAMS\n");
    }
  return (val_arg);
}


void	ld(t_corewar *vm, t_proc *lol, t_instr *instr)
{
  int arg[2];
  int i = 0;

  get_octet(vm->arena[lol->pc], instr->val_arg, 2);
  lol->pc++;
  arg[0] = vm->arena[lol->pc];
  if (instr->val_arg[0] == T_DIR)
    {
      while (++i < DIR_SIZE)
	{
	  ++lol->pc;
	  arg[0] += vm->arena[lol->pc];
	}
      lol->pc += 1;
      ft_putstr("\nfirst_parametre = ");
      ft_putnbr(arg[0]);
       
    }
  else if (instr->val_arg[0] == T_REG)
    {
      instr->tab_instr[0](vm, lol, instr);
      return ;
    }
  else if (instr->val_arg[0] == T_IND)
    lol->pc += IND_SIZE; 
  ft_putstr("\nregistre = ");
  arg[1] = vm->arena[lol->pc];
  ft_putnbr(arg[1]);
  if (arg[1] > 15)
    {
      instr->tab_instr[0](vm, lol, instr);
      return ;
    }  
  lol->reg[arg[1]] += arg[0];
  lol->carry = 1;
  lol->pc += 1;
}

void	init_tab_instr(void (*tab_instr[16])(t_corewar *vm, t_proc *lol, t_instr *instr))
{
	tab_instr[0] = &avance_pc;
	tab_instr[2] = &ld;
	tab_instr[9] = &zjmp;
}

void	mabite(t_corewar *vm)
{
  t_proc		lol;
  t_instr		instr;
  int			opcode;
	
  lol.pc = 0;
  init_tab_instr(instr.tab_instr);
  while (42)
    {
      opcode= vm->arena[lol.pc];
      lol.pc++;
      ft_putstr("\n opcode = ");
      ft_putnbr(opcode);
      instr.tab_instr[opcode](vm, &lol, &instr);
    }
}
