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

int		valid_arg(char *str, int index_op, int nb_arg)
{
	if (str[0] == '%')
	{
		if (str[1])
			if (str[1] == ':')
			{
				if (arg_is_labelchar(str + 2) == -1)
					return (-1);
			}
			else
				if (arg_is_correct(str + 1) == -1)
					return (-1);
		if ((op_tab[index_op].arg[nb_arg] & T_DIR) == 0)
			return (-1);
	}
	else if (str[0] == 'r')
	{
		if (arg_is_correct(str + 1) == -1)
			return (-1);
		if ((op_tab[index_op].arg[nb_arg] & T_REG) == 0)
			return (-1);
	}
}
int     pars_turfu(char *instr)
{
	char **t_str;
	int i_op;
	int i;
	int arg;

	i = 0;
	arg = 0;
	if (!(instr))
		return (puterr(ERR_INSTR_VIDE));
	if (!(t_str = ft_strsplit(instr, "\t ,")))
		return (puterr(ERR_SPLIT));
	if ((i_op = check_name(t_str[i++], op_tab)) == -1)
		return (puterr(ERR_NAME));
	if (check_nb_arg(t_str, i_op, op_tab) == -1)
		return (puterr(ERR_ARG));
	while (t_str[i])
	{
		if (valid_arg(t_str[i], i_op, arg) == -1)
			return (puterr(ERR_ARG_TYPE));
		arg++;
		i++;
	}
	ft_putendl("[T_STR]");
	ft_putendl("_______");
	ft_print_words_tables(t_str);
	ft_putendl("_______");
	printf("kk = %d | %s\n",i_op, op_tab[i_op].name);
	return (0);
}

int     main()
{
	if (pars_turfu(
			"\t\t\t    ld        \t\t \t \t \t\t\t\t\t  %0,r5\t\t")
		== 0)
		ft_putendl(".s correct");
	else
		ft_putendl(".s incorrect");
}
