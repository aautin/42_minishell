/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:00:16 by aautin            #+#    #+#             */
/*   Updated: 2024/05/20 16:21:34 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

#include "builtin_cd.h"
#include "getenv.h"
#include "getenv_utils.h"

#define ENV_OVERWRITING_ERR	"change_pwds():modify_env()/add_env()\n"

void	go_previous_dir(char **components, int twodot_index)
{
	components[twodot_index--][0] = '\0';
	while (twodot_index > 0 && components[twodot_index][0] == '\0')
		twodot_index--;
	if (twodot_index >= 0)
		components[twodot_index][0] = '\0';
}

int	change_directory(t_list **envp, char absolute_path[])
{
	if (chdir(absolute_path) == -1)
	{
		perror(absolute_path);
		return (free(absolute_path), 1);
	}
	if (change_pwds(envp, absolute_path, find_env(*envp, "PWD"),
			find_env(*envp, "OLDPWD")))
	{
		free(absolute_path);
		return (1);
	}
	free(absolute_path);
	return (0);
}

int	change_pwds(t_list **envp, char absolute_path[],
		t_list *pwd, t_list *oldpwd)
{
	int		status;
	char	*lastpwd_str;

	status = 0;
	lastpwd_str = NULL;
	if (pwd != NULL)
		lastpwd_str = ft_strchr(pwd->content, '=');
	if (lastpwd_str != NULL)
		lastpwd_str++;
	if (oldpwd != NULL)
		status = status | modify_env(oldpwd, "OLDPWD", lastpwd_str);
	else
		status = status | add_env(envp, "OLDPWD", lastpwd_str);
	if (pwd != NULL)
		status = status | modify_env(pwd, "PWD", absolute_path);
	else
		status = status | add_env(envp, "PWD", absolute_path);
	if (status == 1)
		write(STDERR_FILENO, ENV_OVERWRITING_ERR,
			ft_strlen(ENV_OVERWRITING_ERR));
	return (status);
}
