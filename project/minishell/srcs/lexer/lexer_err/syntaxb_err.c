/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxb_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 16:17:36 by azeraoul          #+#    #+#             */
/*   Updated: 2021/09/25 16:17:37 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int posix_(char c)
{
    if (ft_isdigit(c) || ft_isalpha(c) || c == 0x5f)
        return (1);
    return (0);
}

static void    read_(char *file, char *delim, int *stream)
{
    int        fd;
    int        res;
    char    *line;

    fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0660);
    while (42)
    {
        res = get_next_line(STDIN_FILENO, &line);
        if (!res || !ft_strcmp(line, delim))
        {
            free(line);
            break ;
        }
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    close(fd);
    fd = open(file, O_CLOEXEC | O_RDONLY);
    unlink(file);
    while (*stream)
        ++stream;
    *stream = fd;
}

void    heredoc(char *delim, int *stream)
{
    static char name[9] = "/tmp/`aa\0";
    static int  here[50] = {0};
    static int  *curr = here;
    int         i;

    if (!stream)
    {
        i = 0;
        while (i < 3)
        {
            if (ft_isalpha(name[i + 5] + 1))
            {
                ++name[i + 5];
                break ;
            }
            ++i;
        }
        read_(name, delim, here);
        return ;
    }
    while (*(curr + 1))
        ++curr;
    stream[0] = *curr;    
}

void    setstdin(t_tokens *token)
{
    t_tokens    *next;

    if (g_err)
        return ;
    while (token)
    {
        next = token->next;
        if (token->type == REDIR && !ft_strcmp(token->word, "<<"))
        {
            token = next;
            if (token->type == BLANK)
                token = token->next;
            heredoc(token->word, NULL);
        }
        token = token->next;
    }
}

void	syntaxb(t_tokens **token, t_var **vars)
{
	t_tokens	*curr;

	curr = (*token);
	if (g_err)
		return ;
	while (curr)
	{
		if (curr->type == WORD && !ft_strcmp(curr->word, "export"))
		{
			curr = curr->next;
			if (curr->type == BLANK)
				curr = curr->next;
			if (curr && curr->type == WORD && *curr->word == '=')
			{
				g_err = SYNTAX;
				printf("export: `%s': not a valid identifier\n", curr->word);
				update_var(vars, "?", "1", LOCAL);
			}
		}
		curr = curr->next;
	}
}
