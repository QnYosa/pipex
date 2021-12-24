/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriyoula <dimitriyoula@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:47:28 by dyoula            #+#    #+#             */
/*   Updated: 2021/12/23 18:47:02 by dimitriyoul      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"
#include "includes/libft.h"

// // env permet de recuperer path poour executer la commande
// //int			path_okay();
int	check_files(t_struct *c)
{
	c->fd_in = open(c->av[1], O_RDONLY);
	if (c->fd_in == -1)
	{
		free_end(c);
		return (c->fd_in);
	}
	c->fd_out = open(c->av[c->ac - 1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR); // 0644
	if (c->fd_out == -1)
	{
		free_end(c);
		return (c->fd_out);
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_struct	*c;
	int			i;

	if (!env || argc < 5)
		return (0);
	i = 1;
	c = init_struct();
	if (!c)
		return (0);
	set_struct(c, argc, argv, env);
	if (check_files(c) == -1)
		return (-1);
	while (++i < argc - 1)
	{
		if (!get_f_path(c, argv[i]))
		{
			free_end(c);
			perror("JE vous emmerde et je rentre a ma maison\n");
			return (0);
		}
	}
	split_cmd(c); // to secure 
	add_index(c->l_pathes);
	//good_path(c, argv);
// j'ai recupere mes commandes et mes options tester si les optioms marchent.
//	display_list(c->l_pathes);
	return (pipex(c));
}

	// int fd = access("decouvertes", F_OK);
	// if (fd == -1)
	// {
	// 	printf("fodase\n");
	// }
	// else
	// {
	// 	printf("fd = %d\n", fd);
	// }
// strncmp"PATH:"
// strdup(env[i] + 5)
// split path :
// /ls = chemin absolu 

// void	child_process(t_struct *c)
// {
// 	close(c->pfd[1]);  close write side 
// 	dup2(c->pfd[0], 0); connect the read side with stdin 
// 	//  read some data and print the result on screen 
// 	close(c->pfd[0]); close the read side  
// 	execlp(c->av[1], c->av[1], (char *) 0);
// 	printf("batard #1\n");
// 	// => execve
// 	//printf("child reads %s", buffer);
// }

// void	parent_process(t_struct *c)
// {
// 	 parent 
// 	//wait(NULL);
// 	close(c->pfd[0]);
// 	dup2(c->pfd[1], 1);
// 	//execlp(c->av[2], c->av[2], (char *) 0);
// 	close(c->pfd[1]);  close read side 
// 	//printf("batard #2\n");
// 	//=>execve
// }

// int main( int argc, char ** argv, char **env)
// {
// 	int 		pid;
// 	t_c
// 	if (argc > 0) // == 5
// 	{
// 		// c = init_struct(argc, argv, env);
// 		//printf("%s", c->av[1]);
// 		// create the pipe 
// 		if (pipe(c->pfd) == -1)
// 		{
// 			perror("pipe");
// 			return (1);
// 		}
// 		 create the child *
// 		if ((pid = fork()) < 0)
// 		{
// 			perror("pid");
// 			return (2);
// 		}
// 		if (pid == 0)
// 		{
// 			child_process(&c);
// 		}
// 		else
// 			parent_process(&c);	
// 	}
// 	return 0;
// }