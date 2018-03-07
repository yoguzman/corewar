#include "op.h"

static const t_op		g_op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, {0}},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, {1, 0}},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, {0, 1}},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, {0, 0, 0}},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, {0, 0, 0}},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, {1, 1, 0}},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, {1, 1, 0}},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, {1, 1, 0}},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, {0}},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1, {2, 0, 0}},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1, {0, 2, 0}},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, {0}},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0, {1, 0}},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, {1, 1, 0}},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, {0}},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, {0}},
	{0, 0, {0}, 0, 0, 0, 0, 0, {0, 0, 0}}
};

int			replace_cod_oct(unsigned char octet, unsigned char op_code)
{
	int		i;
	int		mask;
	int		decal;
	int		replace[6];

	i = 0;
	mask = 3;
	decal = 6;
	replace[0] = 192;
	replace[1] = 48;
	replace[2] = 12;
	replace[3] = 64;
	replace[4] = 16;
	replace[5] = 4;
	while (i < 3)
	{
		if (((op_code <= 15) &&
					(((octet >> decal) & mask) == 2 ||
					 ((octet >> decal) & mask) == 3)) &&
				(i < g_op_tab[op_code].parameter_count) &&
				((g_op_tab[op_code].rep[i] == 1) ||
				 (g_op_tab[op_code].rep[i] == 2 && ((octet >> decal) & mask) == 3)))
		{
			if (((octet >> decal) & mask) == 2)
				octet = octet | replace[i];
			else if (((octet >> decal) & mask) == 3)
				octet = octet ^ replace[i + 3];
		}
		++i;
		decal -= 2;
	}
	return (octet);
}

/*
 **				reg | dir | ind
 ** ---------------------------
 ** encoding	 01 |  10 | 11
 ** TYPE		 1  |  2  | 4
 ** INC_VAL		 1  |  4  | 2
 */

int			check_encoding_byte(unsigned char byte, unsigned char op_code)
{
	int		i;
	int		inc_pc;
	int		shift;
	int		inc_val[3];
	int		is_valid;

	i = 0;
	inc_pc = 0;
	shift = 6;
	inc_val[0] = T_REG;
	inc_val[1] = T_DIR;
	inc_val[2] = T_IND;
	is_valid = 0;
	while (i < g_op_tab[op_code].parameter_count)
	{
		inc_pc += ((byte >> shift) & 3)
		++i;
	}
	return (inc_pc);
}
