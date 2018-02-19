#include <unistd.h>
#include "libft.h"
#include <fcntl.h>
#include "asm.h"

int	get_info_file_loop2(t_list **tmp_list, t_list **inf_line, t_if *info_line, t_if **tmp)
{
  if (list_push_back_alloc_content(inf_line, info_line, sizeof(t_if)) == -1)
    return (-1);
  *tmp_list = *inf_line;
  while ((*tmp_list)->next)
    *tmp_list = (*tmp_list)->next;
  *tmp = (t_if *)(*tmp_list)->content;
  return (0);
}

int	get_info_file_loop(char **file, int *i, t_if *info_line)
{
  int	ret;

  ft_bzero(info_line, sizeof(*info_line));
  if ((file[*i] = check_label(file[*i], info_line)) == NULL)
    return (-1);
  if (file[*i][0] == 0 || check_blank_line(file[*i]) == 0)
    {
      free(file[*i]);
      ++*i;
      return (1);
    }
  if ((ret = pars_instr(file[*i], info_line, *i + 1)) == -1)
    return (-1);
  else if (ret == 1)
    {
      free(file[*i]);
      ++*i;
      return (1);
    }
  return (0);
}
