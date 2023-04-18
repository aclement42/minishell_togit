/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:26:31 by aclement          #+#    #+#             */
/*   Updated: 2023/04/17 20:29:39 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_list
{
	char			*block;
	int				type;
	struct s_list	*next;
}		t_list;

typedef	struct s_env
{
	char	*name;
	char	*value;
	struct s_env	*next;
}		t_env;


/********************
 * MAIN.C
 * ******************/

void	print_list(t_list **token);
void	print_env(t_env **var_env);
int main(int ac, char **av, char **env);

int pair_quote(char *input);
int find_dollar(char *str);

/**************************
 * PARSING
 * ************************/

/*parsing_env.c*/

t_env    **create_env(t_env **var_env, char **env);
void    init_env(t_env **var_env, char **env);

/*parsing_token.c*/

void    init_list(t_list **token, char *input, t_env **var_env);
t_list  **create_token(t_list **token, char *input);
void    dollar_substitution(t_list **token, t_env **var_env);
char	*find_word_in_env(char *str, t_env **var_env);
//char	*find_word_in_env_quotes(char *str, t_env **var_env);
char    *final_word(char *af_doll, char *bef_doll);
char    *str_copy(char *dst, char *src);
void    epur_token(t_list   **token);
int     numb_doll(char *str);
char    *find_word_in_env_more(char *str, int j, t_env **var_env);
char    *tmp_word(char *af_doll, char *bef_doll);
char    *word_without_env_more(char *str);
int     find_simple_quote_between_start_to_doll(char *str, char *stri);
char	*find_word_in_env_quotes_more_squote(char *str, t_env **var_env);
char    *word_without_env_more_quotes(char *str);
char    *tmp_word_quotes(char *af_doll, char *bef_doll);

//char	*find_word_in_env_quotes_more(char *str, t_env **var_env);


/**************************
 * UTILS
 * *************************/

/*utils_list.c*/

t_list	*ft_lstnew(char *input);
void    add_list(t_list **token, char *stock);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);

/*utils_env.c*/

t_env	*ft_envlast(t_env *lst);
void	ft_envadd_back(t_env **lst, t_env *new);
t_env	*ft_envnew(char *stockname, char *stockvalue);
void	add_env(t_env **var_env, char *stockname, char *stockvalue);

/*utils.c*/

char    *get_input(void);
int ft_strlen(char *str);
char    *block_malloc(char *input, int start, int end, int size);
char    *word_without_env(char *str);
char    *wordquotes_without_env(char *str);


#endif