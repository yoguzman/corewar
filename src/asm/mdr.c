int			modif_label(t_if *here, char *str_tmp, int i[3], t_list *tmp)
{
	char	*save;
	t_if	*inf;

	inf = (t_if *)tmp->content;
	if (inf->label != NULL && (ft_strcmp(inf->label,
								here->arg[i[1]] + 1 + i[0]) == 0))
	{
		if ((here->arg[i[1]] =
				ft_itoa(inf->bytes_line - here->bytes_line)) == NULL)
			return (-1);
		if (str_tmp[0] == '%')
		{
			str_tmp[1] = 0;
			if ((save = ft_strjoin(str_tmp, here->arg[i[1]])) == NULL)
				return (-1);
			here->arg[i[1]] = save;
		}
		return (1);
	}
	return (0);
}

t_list		*go_first(t_list *list)
{
	while (list->prev)
		list = list->prev;
	return (list);
}

int			is_label(t_if *here, t_list *list)
{
	char	*str_tmp;
	t_list	*tmp;
	int		i[3];

	ft_bzero(i, 12);
	while (here->arg[i[1]])
	{
		str_tmp = here->arg[i[1]];
		if (here->arg[i[1]][0] == '%')
			i[0] += 1;
		if (here->arg[i[1]][i[0]] == ':')
		{
			tmp = go_first(list);
			while (tmp)
			{
				if ((i[2] = modif_label(here, str_tmp, i, tmp)) == -1)
					return (-1);
				else if (i[2] == 1)
					break ;
				tmp = tmp->next;
			}
		}
		++i[1];
	}
	return (0);
}
