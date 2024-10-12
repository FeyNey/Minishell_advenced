/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:38:59 by aglampor          #+#    #+#             */
/*   Updated: 2024/10/12 21:11:55 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdarg.h>
# include <errno.h>

# define OPTION 1
# define DIRECTORY 2
# define FD 3
# define RIN 4
# define ROUT 5
# define RRIN 44
# define RROUT 55
# define BUILTIN 6
# define CMD 7
# define PIPE 8

//token
typedef struct s_token
{
	char			**value;
	int				type;
	int				fdin;
	int				fdout;
	struct s_token	*next;
}	t_token;

//lvar
typedef struct s_local_var
{
	char				*key;
	int					*value;
	struct s_local_var	*next;
}	t_lvar;

//env
typedef struct s_environement
{
	char					*key;
	char					*value;
	int						index;
	struct s_environement	*next;
}	t_env;

//bagage
typedef struct s_bag
{
	struct s_environement	*env;
	struct s_token			*tokens;
	struct s_local_var		*local_v;
}	t_bag;

//build_ft
void	ft_lstadd_back(t_env **alst, t_env *new);
t_env	*ft_lstnew(char *key, char *value);
t_env	*ft_lstlast(t_env *lst);
void	ft_delnode_idx(t_env **lst, int idx);
void	ft_indexion(t_env *list);

//env
char	**constructor(char *s);
void	free_env(t_env	*p);
void	init_env(t_env **env, char **ev);

//export
int		export_no_arg(t_env *e);
int		export_args(t_token *ts, t_env **myev, int i);
int		is_in_ev(char *arg, t_env *myev);

//clean_pipe
int		pipok(t_bag **bag);
void	cleanpip(t_token **t);
int		is_ok(t_bag **bag);

//clean_quote
int		have_quote(char *cmd);
int		mal_no_quote(char *cmd);
void	remove_quote(t_token **t);
void	dup_no_quote(char *cmd, char *new);

//clean_redir
void	refresh_tok(t_token **t, char *fic, int type_redir);
void	remove_redir(t_token **ts);
char	*owr(char *cmd);
int		open_file(char *fic_name, int redir);
int		redir_type(char *cmd);
int		ft_heardoc(char *end);

//redir_realoc
char	**redir_realloc(t_token **token);

//f_builtin
int		ft_export(t_token *t, t_env **myEnv);
int		ft_env(t_token *t, t_env *menv);
int		ft_unset(char **cmds, t_env **menv);

//split_CMD
int		nb_token(t_token *t);
char	**ft_split(char *s, char c);
char	**split_input(char *s);
void	ft_free_split(char **split);
int		ft_strlen(char *s);

//token
void	clean_tok(t_bag **bag);
void	printtok(t_token **t);
void	build_tokens(char *line, t_bag **bag);

//tok_utils
int		len_redir(char *str);
int		end_tok(char *s);
void	ft_addb_tok(t_token **p, t_token *new);
int		type_tok(char *s, t_env *env);
int		end_cmd(char *s);
void	free_tokens(t_token *p);

//triple_join
char	*ft_strjoin_t(char *strt, char *mid, char *end);
void	ft_strcpy(char *str, char *dest);

//exe
int		tokens_exe(t_token *t, t_env **env, t_bag *bag);
int		exe_builtin(t_token *ts, t_env **e);
int		exe_shell(t_token *t, t_env *menv);
void	redir(t_token *t, t_env **env);
int		cmd_exe(t_token *t, t_env **menv);

//split_ws
char	**splt_white(char *s);
int		is_white(char c);
char	*word_dup(char *str, int start, int finish);

//utils
int		is_c(char *str, char c);
int		find_c(char *str, char c);
int		ft_cmp(char *o, char *t);
char	*ft_strdup(char *str);
int		is_empty_line(char *line);
int		is_quote(char c);

//exe_utils
char	*test_path(char **l_path, char *cmd);
char	*tru_path(char *ex_cmd, t_env *mev);
char	**get_ex_env(t_env *ev);

//pipe_utils
void	daddy_rout(int **pfd, int nb_fork, pid_t last_pid);
int		**build_pipe(int nb_t);
void	handle_pip(int **pipefd, int i);
void	free_pipes(int **pipefd);

//verif
int		is_builtin(char *s);
int		is_cmd(char *s, t_env *env);
int		ft_verif_line(char *line);
int		is_redir(char *s);

//signals
void	sigquit_handler(int signal);
void	sigint_handler(int signal);
void	redirect_signals(void);
void	print_err(char *t);

//pwd
void	ft_putstr(char *str);
void	set_pwd(t_env *env);
void	set_old_pwd(t_env *env, char *path);
int		ft_pwd(char **value);

//exit
int		ft_exit(char **command, t_env **env, t_token **tok, t_bag *bag);
void	ft_free_all(t_env **env, t_token **tok);
int		check_exit_args(char **command);

//cd
char	*search_in_ev(char *value, t_env *env);
int		check_arg_cd(char **value, t_env **env);
int		ft_cd(char **value, t_env **env);
int		check_exception_cd(char *value, t_env *env);
int		cd_tiret(char *value, t_env *env, char *oldpwd);
int		cd_all(char *value, t_env *env, char *oldpwd);
int		swap_pwd_oldpwd(char *pwd, t_env *env);

//printf
int		longlong_putnbr_base(unsigned long long nb, char *base, int j);
int		unsigned_putnbr_base(unsigned int nb, char *base);
int		ft_carrefour(char str, va_list list);
int		putnbr_base(long nb, char *base);
int		ft_printf(const char *str, ...);
int		ft_putchar(char c);

//clear_quote2
void	replace_venv1(t_token *tok, t_env **env, char **str);
char	*replace_venv2(char *str, t_env **env);
int		is_between_quote_and_has_venv(char *word);
char	*replace_venv3(char *str, t_env **env, int i, int j);
void	supp_quote(t_token **tok, char **str);
char	*supp_quote2(t_token **tok, char *str);
int		is_env_char(char c);
char	*replace_venv4(char *str, int i, int j, char *value);
char	*found_in_env(t_env **env, int index);
char	*skip_venv(char *str, int i, int j);
char	*skip_venv2(char *str, int i, int j);
int		not_between_quote(char *str, char c, int j);
int		is_in_ev_tok(char *arg, t_env *myev, int flag);
char	*minishell_venv(char *str, int i, int j);
char	*number_venv(char *str, int i);
char	*ft_itoa(int n);
int		is_env_char2(char c);
int		ft_strncmp(char *s1, char *s2, int n);
int		is_valable_venv(char *word);
char	*replace_venv2(char *str, t_env **env);
char	*replace_venv4(char *str, int i, int j, char *value);
char	*ft_malloc(int len);

void	exit_exe(t_bag *bag, char **command);
int		global_variable(int i, int sw);
void	pipe_exe(int **pipefd, int i, t_bag *bag);
int		home_not_set(t_env *env, char *oldpwd);

int		ft_echo_option(char *value);
int		ft_echo(char **value);
void	pipe_end(t_bag *bag);
void	error_execve(char **value);
int		child_exec(t_bag *bag, int **pipefd, int i, int nb_tok);

#endif
