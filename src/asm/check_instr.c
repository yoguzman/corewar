#include "asm.h"
#include "libft.h"
#include "op.h"

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

int		ft_tablen(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
int		valid_arg(char *str, int index_op, int nb_arg)
{
	int ret;

	if ((ret = arg_is_direct(str, index_op, nb_arg, op_tab)) < 0)
		return (ret);
	if ((ret = arg_is_reg(str, index_op, nb_arg, op_tab)) < 0)
		return (ret);
	return (0);
}

int		check_arg(char **t_str, int i_op, int i)
{
	int ret;
	int arg;

	arg = 0;
	while (t_str[i])
	{
		if ((ret = valid_arg(t_str[i], i_op, arg)) == -1)
			return (-1);
		else if (ret == -2)
			return (-1);
		arg++;
		i++;
	}
	return (0);
}

void	check_comment(char **t_str)
{
  int i;

  i = 0;
  while (t_str[i])
    {
      if (t_str[i][0] == '#')
	{
	  if (t_str[i][1])
	    t_str[i] = 0;
	  else if (t_str[i + 1])
	    {
	      t_str[i] = 0;
	      t_str[i + 1] = 0;
	    }
	}
      i++;
    }
}

void	check_comment2(char **t_str)
{
  int i;
  int j;

  i = 0;
  while (t_str[i])
    {
      j = 0;
      while (t_str[i][j])
	{
	  if (t_str[i][j] == '#')
	    {
	      t_str[i][j] = 0;
	      if (t_str[i + 1])
		t_str[i + 1] = 0;
	    }
	  j++;
	}
      i++;
    }
}

int     pars_instr(char *instr, t_if *info)
{
	char **t_str;
	int i_op;
	int i;

	i = 0;
	if (!(instr))
		return (puterr(ERR_INSTR_VIDE));
	if (!(t_str = ft_strsplit(instr, "\t ,")))
		return (puterr(ERR_SPLIT));
	if (ft_tablen(t_str) == 1)
	  return (puterr("Syntax error at token ENDLINE"));
	check_comment(t_str);
	check_comment2(t_str);
	ft_print_words_tables(t_str);
	if ((i_op = check_name(t_str[i++], op_tab)) == -1)
	{
		puterr_noend("Invalid instruction at token instruction ");
		puterr(t_str[i - 1]);
		return (-1);
	}
	if (check_nb_arg(t_str, i_op, op_tab) == -1)
		return (puterr(ERR_ARG));
	if (check_arg(t_str, i_op, i) == -1)
		return (-1);
	info->name_instr = t_str[0];
	info->arg = t_str + 1;
	return (0);
}
