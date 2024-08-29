/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:38:59 by aglampor          #+#    #+#             */
/*   Updated: 2024/08/29 17:17:33 by acoste           ###   ########.fr       */
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


//local_var
typedef struct s_local_var
{
	char	*key;
	int		*value;
	struct	s_local_var	*next;
}	t_lvar;


//token
typedef struct s_token
{
	char			**value;
	int				type;
	struct s_token	*next;
}	t_token;

//env
typedef struct s_environement
{
	char					*key;
	char					*value;
	int						index;
	struct s_environement	*next;
}	t_env;

//bagage
typedef struct  s_bag
{
	struct s_environement *env;
	struct s_token *tokens;
	struct s_local_var local_v;
}	t_bag;


//build_ft
void	ft_lstadd_back(t_env **alst, t_env *new);
t_env	*ft_lstnew(char *key, char *value);
t_env	*ft_lstlast(t_env *lst);
void	ft_delnode_key(t_env **lst, char *key );
void	ft_indexion(t_env *list);

//env
int	get_idx(char *s, char c);
char	**constructor(char *s);
void	free_env(t_env	*p);
void	init_env(t_env **env, char **ev);

//exit
void	m_exit(int code, char *val);

//export
int	build_export(t_env *e);
int     add_myenv(t_token *toks, t_env **myenv);

//f_builtin
int     export(t_token *t, t_env **myEnv);

//split_CMD
char	**ft_split(char *s, char c);
char	**split_input(char *s);
void	ft_free_split(char **split);
int		ft_strlen(char *s);

//ft

//token
void	printtok(t_token **t);
void	build_tokens(char *line, t_bag **bag);

//tok_utils
int	type_redir(char *cmd);
int	len_redir(char *str);
int	end_tok(char *s);
void	ft_addb_tok(t_token **p, t_token *new);
int	type_tok(char *s, t_env *env);
int	end_cmd(char *s);
void	free_tokens(t_token *p);

//triple_join
char	*ft_strjoin_t(char *strt, char *mid, char *end);
void	ft_strcpy(char *str, char *dest);

//minishell
int     s_exe(t_token *ts, t_env **e);

//exe
int     ex_cmd(t_token  *ts, t_env **e);

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
void	ft_putstr(char *str);

//verif
int		is_builtin(char *s);
int		is_cmd(char *s, t_env *env);
int		ft_verif_line(char *line);
int		is_redir(char *s);

//signals
void	sigquit_handler(int signal);
void	sigint_handler(int signal);
void	redirect_signals(void);
#endif
