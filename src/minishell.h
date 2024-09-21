/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:38:59 by aglampor          #+#    #+#             */
/*   Updated: 2024/09/21 18:03:38 by acoste           ###   ########.fr       */
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

# define RED     "\x1b[31m" // test printf
# define GREEN   "\x1b[32m"
# define CYAN    "\x1b[36m"
# define MAGENTA "\x1b[35m"
# define YELLOW  "\x1b[33m"
# define RESET   "\x1b[0m"

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

//exit
void	m_exit(int code, char *val);

//export
int		export_no_arg(t_env *e);
int		export_args(t_token *ts, t_env **myev, int i);
int		is_in_ev(char *arg, t_env *myev);

//cleaning
void	refresh_tok(t_token **t, char *fic, int type_redir);
void	remove_redir(t_token **ts);
void	remove_quote(t_token **t);
char	*dup_no_quote(char *cmd);
int		mal_no_quote(char *cmd);
int		open_file(char *fic_name, int redir);
int		redir_type(char *cmd);
char	**redir_realloc(t_token **token);
char	*owr(char *cmd);

//f_builtin
int		ft_export(t_token *t, t_env **myEnv);
int		ft_env(t_token *t, t_env *menv);
int		ft_unset(char **cmds, t_env **menv);

//split_CMD
char	**ft_split(char *s, char c);
char	**split_input(char *s);
void	ft_free_split(char **split);
int		ft_strlen(char *s);

//token
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

//minishell
int		s_exe(t_token *t, t_env **menv);

//exe
int		ex_cmd(t_token *ts, t_env **e);

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

//verif
int		is_builtin(char *s);
int		is_cmd(char *s, t_env *env);
int		ft_verif_line(char *line);
int		is_redir(char *s);

//signals
void	sigquit_handler(int signal);
void	sigint_handler(int signal);
void	redirect_signals(void);

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
int		not_between_quote(char *str, char c, int j);
int		is_in_ev_tok(char *arg, t_env *myev);
char *minishell_venv(char *str, int i, int j);
char *number_venv(char *str, int i);
#endif
