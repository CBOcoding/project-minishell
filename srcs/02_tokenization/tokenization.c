#include "minishell.h"

int ft_isspace(char c)
{
   return((c >= 9 && c <= 13) || c == ' ');
}

void tokenize_arrows(char *input, int *i, t_token **tokens) {
    t_token *new_token;
    if (input[*i] == '>') {
        if (input[*i + 1] == '>') {
            new_token = create_token(">>", APPEND);
            (*i) += 2;
        } else {
            new_token = create_token(">", REDIR_OUT);
            (*i)++;
        }
    } else if (input[*i] == '<') {
        if (input[*i + 1] == '<') {
            new_token = create_token("<<", HEREDOC);
            (*i) += 2;
        } else {
            new_token = create_token("<", REDIR_IN);
            (*i)++;
        }
    }
    add_token(tokens, new_token);
}


void tokenize_pipe(int *i, t_token **tokens) {
    t_token *new_token = create_token("|", PIPE);
    add_token(tokens, new_token);
    (*i)++;
}

// Handle environment variables (simplified)
void tokenize_var(char *input, int *i, t_token **tokens) {
    int start;
    char *var_name;
    t_token *new_token;

    start = *i;
    (*i)++; // Skip '$'
    while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
        (*i)++;
    var_name = ft_substr(input, start, *i - start);
    new_token = create_token(var_name, ENV_VAR);
    add_token(tokens, new_token);
    free(var_name);
}



// Unified word tokenization (handles quotes and variables)
void tokenize_word(char *input, int *i, t_token **tokens, t_status *status) {
    int start = *i;
    char *word = NULL;
    t_token *new_token;

    if (*status == SQUOTE) {
        // Inside single quotes
        start++; // Skip the opening quote
        while (input[*i] && input[*i] != '\'')
            (*i)++;

        word = ft_substr(input, start, *i - start);
        if (input[*i] == '\'')
            (*i)++; // Skip the closing quote

    } else if (*status == DQUOTE) {
        // Inside double quotes
        start++; // Skip the opening quote
        while (input[*i] && input[*i] != '"') {
            if (input[*i] == '$') {
                // Found a variable, so tokenize up to here
                if (*i > start) {
                    char *partial_word = ft_substr(input, start, *i - start);
                    if (partial_word && *partial_word) {
                        new_token = create_token(partial_word, WORD);
                        add_token(tokens, new_token);
                        free(partial_word);
                    }
                }
                tokenize_var(input, i, tokens); // Handle the variable
                start = *i; // New start after the variable
                continue; // Continue processing
            }
            (*i)++;
        }
        // Handle the remaining part after any variables
        if (*i > start) {
            word = ft_substr(input, start, *i - start);
        }
        if (input[*i] == '"')
            (*i)++; // Skip the closing quote

    } else {
        // Not inside quotes
        while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '>' && input[*i] != '<' && input[*i] != '|')
            (*i)++;
        word = ft_substr(input, start, *i - start);
    }

    if (word && *word) {
        new_token = create_token(word, WORD);
        add_token(tokens, new_token);
        free(word);
    }
}



t_token *tokenize_input(char *input) {
    t_token *tokens = NULL;
    t_status status = DEFAULT;
    int i = 0;

    while (input[i]) {
        if (ft_isspace(input[i]) && status == DEFAULT) {
            i++;
            continue;
        }
        if (status == DEFAULT) {
            if (input[i] == '>' || input[i] == '<') {
                tokenize_arrows(input, &i, &tokens);
                continue;
            } else if (input[i] == '|') {
                tokenize_pipe(&i, &tokens);
                continue;
            }
        }
        tokenize_word(input, &i, &tokens, &status);
    }
    return tokens;
}



