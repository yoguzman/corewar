#include "libft.h"
#include "asm.h"

int			get_info_file_loop2(t_list **tmp_list, t_list **inf_line,
								t_if *info_line, t_if **tmp)
{
	if (list_push_back_alloc_content(inf_line, info_line, sizeof(t_if)) == -1)
		return (-1);
	*tmp_list = *inf_line;
	while ((*tmp_list)->next)
		*tmp_list = (*tmp_list)->next;
	*tmp = (t_if *)(*tmp_list)->content;
	return (0);
}

int			del_comment(char *file)
{
	int		i;

	i = 0;
	while (file[i])
	{
		if (file[i] == '#')
		{
			file[i] = 0;
			return (0);
		}
		i++;
	}
	return (0);
}

int			get_info_file_loop(char **file, int *i, t_if *info_line)
{
	if (!(*i > 1 && file[*i - 1] == NULL && info_line->label))
		ft_bzero(info_line, sizeof(*info_line));
	if ((file[*i] = check_label(file[*i], info_line, *i)) == NULL)
		return (-1);
	if (del_comment(file[*i]) == 1 || file[*i][0] == 0 ||
			check_blank_line(file[*i]) == 0)
	{
		free(file[*i]);
		file[*i] = NULL;
		++*i;
		return (1);
	}
	if (pars_instr(file[*i], info_line, *i + 1) == -1)
		return (-1);
	return (0);
}
