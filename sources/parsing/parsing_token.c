/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 04:34:41 by aclement          #+#    #+#             */
/*   Updated: 2023/04/18 01:09:31 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list  **create_token(t_list **token, char *input)//creation des tokens
{
    int i;
    int size;
    int len;
    int start;
    int end;
    char    *stock;

    i = 0;
    len = ft_strlen(input);
    len--;
    while (input[len] && (input[len] == ' ' || (input[len] > 8 && input[len] < 14)))
        len--;
    while (i < len)
    {
        while (input[i] && (input[i] == ' ' || (input[i] > 8 && input[i] < 14)))
            i++;
        start = i;
        size = 0;
        if (input[i] == 39)
        {
            size++;
            i++;
            while (input[i] != 39)
            {
                size++;
                i++;
            }
            if (input[i] == 39)
            {
                size++;
                i++;
            }
        }
        else if (input[i] == 34)
        {
            i++;
            size++;
            while (input[i] != 34)
            {
                size++;
                i++;
            }
            if (input[i] == 34)
            {
                size++;
                i++;
            }
        }
        else if (input[i] == '|')
        {
            i++;
            size++;
        }
        else if (input[i] == '<' || input[i] == '>')
        {
            i++;
            size++;
            if ((input[i - 1] == '<' && input[i] == '<') || (input[i - 1] == '>' && input[i] == '>'))
            {
                i++;
                size++;
            }
        }
        else
        {
            while (input[i] && input[i] != '<' && input[i] != '>' && input[i] != ' ' && input[i] != '|' && input[i] != 34 && input[i] != 39)
            {
                i++;
                size++;
            }
        }

        end = i - 1;
        stock = block_malloc(input, start, end, size);
        add_list(token, stock);
    }
    return (token);
}

void    init_list(t_list **token, char *input, t_env **var_env)//envoie des tokens pour la creation + substituion + epur
{
    (void)var_env;
    token = create_token(token, input);
    epur_token(token);
    //if (*token)
    //    dollar_substitution(token, var_env);
}

char    *delete_doublequotes(char *str)// sup les ""
{
    char    *new;
    int       i;
    int         j;

    i = 0;
    j = 1;
    new = malloc(sizeof(char) * (ft_strlen(str) - 2));
    while (str && str[j] != 34)
        new[i++] = str[j++];
    new[i] = '\0';
    return (new);
}

void    epur_token(t_list   **token)//enlever les $ en trop
{
    t_list  *tmp;
    int     i;
    int     j;
    char    *new;

    tmp = (*token);
    while ((*token) != NULL)
    {
        i = 0;
        j = 0;
        if ((*token)->block[i] == 39)
            break ;
        new = malloc(sizeof(char) * (ft_strlen((*token)->block)));
        if (!new)
            return ;
        while ((*token)->block[i])
        {
            if ((*token)->block[i] == '$' && (*token)->block[i + 1] == '$')
                i++;
            else
                new[j++] = (*token)->block[i++];
        }
        new[j] = '\0';
        j = 0;
        while (j <= i)
        {
            (*token)->block[j] = new[j];
            j++;
        }
        free(new);
        *(token) = (*token)->next;
    }
    *token = tmp;
}

void    dollar_substitution(t_list **token, t_env **var_env)//remplacer les token par rien ou var_env
{
    t_list  *tmp;
    t_env   *tmp_env;
    int        i;
    int         j;
    int         nb_ofdoll;
    char        *k;
    int         end;
    char        *new;
    int         flag;
    char        *spaces_keeper;
    int         s_quote;

    i = 0;
    tmp = (*token);
    //printf("la\n");
    while ((*token) != NULL)
    {
        nb_ofdoll = numb_doll((*token)->block);
        k = NULL;
        flag = 0;
        spaces_keeper = NULL;
        s_quote = 0;
        if ((*token)->block[0] == 34) // si y a des "" je les supp et remets le token du debut
        {
            new = delete_doublequotes((*token)->block);
            flag = 1;
            free((*token)->block);
            (*token)->block = new;
            //printf("lalalalala : %s\n", (*token)->block);
        }
        j = 0;
        if ((*token)->block[0] != 39 && flag == 0)// sans ceux qui commenecent par '' ou ceux qui avaient des ""
        {
            tmp_env = (*var_env);
            //printf("2la\n");
            while (nb_ofdoll != 0)
            {
                i = find_dollar((*token)->block);
                end = ft_strlen((*token)->block);
                if (nb_ofdoll == 1) //il y a un doll dans le token a i position
                {
                    i++;
                    //printf("3la\n");
                    k = find_word_in_env((*token)->block + i, var_env); // k renvoie strlen de var_env.value ou null si pas de mot a changer
                    if (k != NULL)
                    {
                        //printf("k != NULL la\n");
                        new = final_word(k, (*token)->block);
                        free((*token)->block);
                        (*token)->block = malloc(sizeof(char) * (ft_strlen(new) + 1));
                        (*token)->block = str_copy((*token)->block, new);
                        //printf("%s\n", new);
                        free(new);
                    }
                    else if (k == NULL && (*token)->block[end - 1] != '$')
                        (*token)->block = word_without_env((*token)->block);
                }
                else if (nb_ofdoll > 1)
                {
                    j = ++i;
                    while ((*token)->block[j] != '$')
                        j++;
                    k = find_word_in_env_more((*token)->block + i, j, var_env);
                    if (k != NULL)
                    {
                        new = tmp_word(k, (*token)->block);
                        free((*token)->block);
                        (*token)->block = malloc(sizeof(char) * (ft_strlen(new) + 1));
                        (*token)->block = str_copy((*token)->block, new);
                        free(new);
                    }
                    else if (k == NULL)
                        (*token)->block = word_without_env_more((*token)->block);
                }
                printf("k = [%s] for [%s]\n", k, (*token)->block);
                nb_ofdoll--;
                *var_env = tmp_env;
            }
        }
        else if (flag == 1)// ceux qui avaient "" meme avec ''
        {
            tmp_env = (*var_env);
            while (nb_ofdoll != 0)
            {
                //printf("%s\n", (*token)->block + i);
                i = find_dollar((*token)->block + i) + i;
                printf("hahahah [%s]\n", (*token)->block + i);
                printf("%d\n", i);
                //s_quote = find_simple_quote_between_start_to_doll((*token)->block, (*token)->block + i);
                //while (j < i)
                //{
                //    if ((*token)->block[j] == 39)
                //    {
                //        s_quote++;
                //        printf("s_quote = %d\n", s_quote);
                //    }
                //    j++;
                //}
                //printf("%d\n", s_quote);
                if (nb_ofdoll == 1)
                {
                    i++;
                    printf("dernier $\n");
                }
                else if (nb_ofdoll > 1)
                {
                    //j = ++i;
                    i++;
                    //printf("find prend la phrase dici :%s\n", (*token)->block + i);
                    k = find_word_in_env_quotes_more_squote((*token)->block + i, var_env);
                    if (k == NULL)
                    {
                        i++;
                        (*token)->block = word_without_env_more_quotes((*token)->block);
                    }
                    else if (k != NULL)
                    {
                        new = tmp_word_quotes(k, (*token)->block);
                        free((*token)->block);
                        (*token)->block = malloc(sizeof(char) * (ft_strlen(new) + 1));
                        (*token)->block = str_copy((*token)->block, new);
                        free(new);
                    }

                }
                printf("k = [%s] for [%s]\n", k, (*token)->block);

                nb_ofdoll--;
                *var_env = tmp_env;
            }
        }
        (*token) = (*token)->next;  
    }
    *token = tmp;
}

/*
int     find_simple_quote_between_start_to_doll(char *str, char *stri)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(str) - ft_strlen(stri);
    printf("len : %d\n", len);
    while (i <= len)
    {
        printf("%c", str[i]);
        if (str[i] == 39)
            return (1);
        i++;
    }
    return (0);
}

//char    *find_word_in_env_quotes(char *str, char *stri, t_env **var_env)
//{
//
//}
*/
char    *str_copy(char *dst, char *src)//copie de src a dst
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(src);
    while (i < len)
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return (dst);
}

char    *final_word(char *af_doll, char *bef_doll)
{
    char    *new;
    int     i;
    int     j;

    i = 0;
    j = 0;
    while (bef_doll[i] != '$')
        i++;
    new = malloc(sizeof(char) * (ft_strlen(af_doll) + i));
    if (!new)
        return (NULL);
    i = 0;
    while (bef_doll && bef_doll[i] != '$')
    {
        new[i] = bef_doll[i];
        i++;
    }
    while (af_doll && af_doll[j] != '\0')
        new[i++] = af_doll[j++];
    new[i] = '\0';
    return (new);
}

char    *tmp_word(char *af_doll, char *bef_doll)
{
    char    *new;
    int     i;
    int     j;
    int     k;

    i = 0;
    j = 0;
    k = 0;
    new = malloc(sizeof(char) * (ft_strlen(af_doll) + ft_strlen(bef_doll)));
    if (!new)
        return (NULL);
    while (bef_doll[i] != '$')
    {
        new[i] = bef_doll[i];
        k = i++;
    }
    while (af_doll && af_doll[j] != '\0')
        new[i++] = af_doll[j++];
    k++;
    if (bef_doll[k] == '$')
        k++;
    while (bef_doll[k] && bef_doll[k] != '$')
        k++;
    while (bef_doll[k] != '\0')
        new[i++] = bef_doll[k++];
    new[i] = '\0';
    return (new);
}

int     numb_doll(char *str)
{
    int     i;
    int     nb;

    i = 0;
    nb = 0;
    while (str && str[i])
    {
        if (str[i] == '$')
            nb++;
        i++;
    }
    return (nb);
}

char    *find_word_in_env(char *str, t_env **var_env)
{
    t_env *tmp;
    int     i;
    int     end;

    end = ft_strlen(str);
    tmp = (*var_env);
    while (*var_env)
    {
        i = 0;
        while (i < end && (str[i] == (*var_env)->name[i]))
        {
            i++;
            if (i == end && (*var_env)->name[i] == '\0')// && str[i] != '$')
                return ((*var_env)->value);
        }
        (*var_env) = (*var_env)->next;
    }
    (*var_env) = tmp;
    return (NULL);
}

char    *find_word_in_env_more(char *str, int j, t_env **var_env)
{
    t_env *tmp;
    int     i;
    int     len;
    (void)j;

    len = 0;
    printf("findwordinenvmore\n");
    while (str[len] != '$')
        len++;
    tmp = (*var_env);
    while (*var_env)
    {
        i = 0;
        while (i <= len && str[i] == (*var_env)->name[i])// && (*var_env)->value[i] == '\0' && str[i] != '$')
        {
            i++;
            if (i == len && (*var_env)->name[i] == '\0')
                return ((*var_env)->value);
        }
        (*var_env) = (*var_env)->next;
    }
    (*var_env) = tmp;
    return (NULL);
}

/*char    *find_word_in_env_quotes_more(char *str, t_env **var_env)
{
    t_env   *tmp;
    int     i;
    int     len;

    len = 0;
    while (str[len] != '$' && str[len] != ' ')
        len++;
    tmp = (*var_env);
    while (*var_env)
    {
        i = 0;
        while (i <= len && str[i] == (*var_env)->name[i])
        {
            i++;
            if (i == len && (*var_env)->name[i] == '\0')
                return ((*var_env)->value);
        }
        (*var_env) = (*var_env)->next;
    }
    (*var_env) = tmp;
    return (NULL);

}*/

char    *find_word_in_env_quotes_more_squote(char *str, t_env **var_env)
{
    t_env   *tmp;
    int     i;
    int     len;
    int     to_del;

    len = 0;
    to_del = 0;
    while (str[to_del] && (str[to_del] == ' ' || str[to_del] == 39 || str[to_del] == '$'))
        to_del++;
    printf("findwordinenvquotesmoresquotes\n");
    while (str[len + to_del] && str[len + to_del] != '$' && str[len + to_del] != 39 && str[len + to_del] != ' ')
        len++;
    //printf("%c\n", str[len]);
    tmp = (*var_env);
    len = len - to_del;
    while (*var_env)
    {
        i = 0;
        while (i <= len && str[i] == (*var_env)->name[i])
        {
            i++;
            if (i == len && (*var_env)->name[i] == '\0')
                return ((*var_env)->value);
        }
        (*var_env) = (*var_env)->next;
    }
    (*var_env) = tmp;
    return (NULL);
}

char    *word_without_env_more_quotes(char *str)
{
    int i;
    int j;

    j = 0;
    i = 0;
    printf("wordwithoutenvmorequotes\n");
    while (str && str[i] != '$')
        i++;
    j = i++;
    if (str[i] == ' ' || str[i] == 39)
        return (str);
    //printf("%c\n", str[i]);
    while (str[i] && str[i] != '$' && str[i] != 39 && str[i] != ' ')
        i++;
    while (str[i])
        str[j++] = str[i++];
    str[j] = '\0';
    //printf("str : %s\n", str);
    return (str);
}

char    *tmp_word_quotes(char *af_doll, char *bef_doll)
{
    char    *new;
    int     i;
    int     j;
    int     k;

    i = 0;
    j = 0;
    k = 0;
    printf("tmpwordquotes\n");
    new = malloc(sizeof(char) * (ft_strlen(af_doll) + ft_strlen(bef_doll)));
    if (!new)
        return (NULL);
    while (bef_doll[i] != '$')
    {
        new[i] = bef_doll[i];
        k = i++;
    }
    while (af_doll && af_doll[j] != '\0')
        new[i++] = af_doll[j++];
    k++;
    if (bef_doll[k] == '$')
        k++;
    while (bef_doll[k] && bef_doll[k] != '$' && bef_doll[k] != 39 && bef_doll[k] != ' ')
        k++;
    while (bef_doll[k] != '\0')
        new[i++] = bef_doll[k++];
    new[i] = '\0';
    return (new);
}
