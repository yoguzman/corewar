#include "asm.h"
#include "libft.h"
#include "op.h"

int     main()
{
	if (pars_turfu("\t\t\t    ld        \t\t \t \t \t\t\t\t\t  %0,r5\t\t")
		== 0)
		ft_putendl(".s correct");
	else
		ft_putendl(".s incorrect");
	ft_putendl("_________");
	if (pars_turfu("fork    %:tirop")
		== 0)
		ft_putendl(".s correct");
	else
		ft_putendl(".s incorrect");
	ft_putendl("_________");
	if (pars_turfu(" sub r3,r5,r3")
		== 0)
		ft_putendl(".s correct");
	else
		ft_putendl(".s incorrect");
	ft_putendl("_________");
	if (pars_turfu("sti r1,%:tirb,%1")
		== 0)
		ft_putendl(".s correct");
	else
		ft_putendl(".s incorrect");
	ft_putendl("_________");

	if (pars_turfu("\t\t\t    ld        \t\t \t \t \t\t\t\t\t  %-0,r5\t\t")
		== 0)
		ft_putendl(".s correct");
	else
		ft_putendl(".s incorrect");
	ft_putendl("_________");
	if (pars_turfu("\t\t\t    ld        \t\t \t \t \t\t\t\t\t  %-0,rMABITE\t\t")
		== 0)
		ft_putendl(".s correct");
	else
		ft_putendl(".s incorrect");
	ft_putendl("_________");
	if (pars_turfu("\t\t\t    ld        \t\t \t \t \t\t\t\t\t  %-0,r100\t\t")
		== 0)
		ft_putendl(".s correct");
	else
		ft_putendl(".s incorrect");
	ft_putendl("_________");
	if (pars_turfu("\t\t\t   prout        \t\t \t \t \t\t\t\t\t  %-0MABITE,r5\t\t")
		== 0)
		ft_putendl(".s correct");
	else
		ft_putendl(".s incorrect");
	ft_putendl("_________");

}
