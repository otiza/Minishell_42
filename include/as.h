/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaiza <amaaiza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:22:37 by zsidki            #+#    #+#             */
/*   Updated: 2022/02/15 01:16:04 by amaaiza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AS_H
# define AS_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

typedef struct s_redirect
{
	char	*file;
	enum
	{
		INPUT,
		OUTPUT,
		APPEND,
		HEREDOC
	} e_type;
}	t_redirect;

typedef struct s_command
{
	char			**args;
	size_t			args_size;
	t_redirect		**redi;
	size_t			redi_size;
	int				in;
	int				out;
}					t_command;

typedef struct s_env
{
	char			*name;
	char			*str;
	struct s_env	*next;
}				t_env;

typedef struct s_as
{
	t_command		**cmds;
	size_t			cmds_size;
	char			**envp;
	t_env			*env;
	int				sigint;
	int				exitstat;
}					t_as;

t_as		*init_as(void);
t_command	*init_command(void);
void		ft_check(t_as	*as, t_command	*cmd);
void		do_help(void);
void		do_echo(t_as *as, t_command *cmd);
void		do_pwd(t_as *as, t_command *cmd);
void		do_export(t_as *as, t_command *cmd);
void		do_env(t_as *as, t_command *cmd);
void		do_unset(t_as *as, t_command *cmd);
void		ft_exit(t_as *as, t_command *cmd);
void		do_cd(t_as *as, t_command *cmd);
void		change_oldpwd(t_as *as);
void		change_pwd(t_as *as);
void		ft_docdret(t_as *as);
void		ft_docdsing(t_as *as);
int			ft_myatoi(char *str);
void		ft_error(char *s, int i);
void		pipes(t_as *as);
void		mydup(t_as *as, int *fds, size_t cmd, int fd);
void		ft_exitstatu(int *fd, int *fds, pid_t pid);
void		other(char **cmd1, t_as *as, t_command *cmd);
t_env		*ft_addevnlist(t_env **l, char **evn, char ***env, t_as **as);
void		ft_addenv_back(t_env **alst, t_env *new);
char		**ft_free_split(char **d);
t_env		*ft_lastenv(t_env *lst);
t_env		*ft_lstnewenv(char *name, char *str);
int			ft_cmp(char *s1, char *s2);
t_env		*ft_getbiglst(t_env	*env, t_env *big);
t_env		*ft_smllst(t_env *env);
void		ft_printsortlst(t_as	*as);
void		ft_lstupdate(t_as *as, char **str);
void		addnewenv(char	**p, t_as *as);
char		**mycatstr(char *str, int i);
char		*ft_strcpy(char *dest, char *src);
int			ft_findc(char *str, char c);
void		export_join(t_as *as, char **p);
t_env		*ft_lstfind(t_env *lst, char *name);
void		ft_deletlst(char *name, t_as *as);
void		ft_asclear(t_env **env, void (*del)(t_env *));
void		free_env(t_env *env);
int			ft_myatoi(char *str);
char		**env_tochar(t_env *env);
int			listln(t_env *env);
void		freechar(char **env);
char		*get_absolute_path(char **pa, char *cmd);
char		*get_cmd_path(char *str, t_env *env);
void		freepath(char **table);
void		clear(void);
void		get_redi(t_as *as);
void		get_outredi(int *out, int *in, t_command *cmd);
void		ft_out(int *i, t_redirect *redi);
void		ft_in(int *i, t_redirect *redi);
void		ft_lstupdatehelp(t_as *as, char **p, char str);
void		handlesigquit(void);
void		sighandle(int sig);
void		cmdstart(t_as *as);
void		siginit(void);
void		envpcast(char ***envp, t_env *env);
void		ft_paarse(char *str, char **envp, t_env *env, t_as *as);
int			my_readline(char **str);
int			thisisfornorme(char **str);
void		argeror(int argc, char **argv);

#endif