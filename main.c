#include "string.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include "libft/includes/libft.h"

#define ALLOC_FAILED	"minishell: allocation error\n"

int		ft_getchar(void)
{
	int		res;

	read(1, &res, 1);
	return (res);
}

void	*ft_realloc(void *ptr, size_t size, size_t new_size)
{
	void	*new;

	new = (char *)malloc(sizeof(char) * new_size);
	bzero(new, sizeof(char) * new_size);
	memcpy(new, ptr, sizeof(char) * size);
	free(ptr);
	return (new);
}

char	*minishell_read_line(void)
{
	char	*line;

	get_next_line(0, &line);
	return (line);
}

int		is_white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\a')
		return (1);
	else
		return (0);
}

char	**minishell_split_line(char *line)
{
	char		**res;
	int			nb_word;
	int			i;
	int			j;

	nb_word = 0;
	i = -1;
	while (line[++i])
		if (!is_white_space(line[i]) && (i == 0 || is_white_space(line[i - 1])))
			nb_word++;
	res = (char **)malloc(sizeof(char *) * (nb_word + 1));
	i = -1;
	j = -1;
	while (line[++i])
		if (!is_white_space(line[i]) && (i == 0 || is_white_space(line[i - 1])))
			res[++j] = &line[i];
	res[++j] = NULL;
	i = -1;
	while (line[++i])
		if (is_white_space(line[i]))
			line[i] = '\0';
	return (res);
}

int		minishell_execute(char **args, char **env)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	if (!args[0])
		return (1);
	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, env) == -1)
		{
			perror("minishell");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
		perror("minishell");
	else
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (1);
}

#define PROMPT	"> "
int		minishell_loop(char **env)
{
	char	*line;
	char	**args;
	int		status;

	status = 1;
	write(1, PROMPT, strlen(PROMPT));
	while (status)
	{
		if ((line = minishell_read_line()))
		{
			args = minishell_split_line(line);
			status = minishell_execute(args, env);
			free(line);
			free(args);
			write(1, PROMPT, strlen(PROMPT));
		}
	}
	return (0);
}

int		main(int argc, char **argv, char **env)
{
	minishell_loop(env);
}
