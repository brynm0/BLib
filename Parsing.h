#ifndef PARSING_H
#define PARSING_H

enum TokenType
{
    TOKEN_UNKNOWN,
    TOKEN_COMMA,
    //TODO distinguish between assignment and equivalence
    TOKEN_EQUALS,
    TOKEN_ASSIGNMENT,
    TOKEN_IDENTIFIER,
    TOKEN_PAREN_OPEN,
    TOKEN_PAREN_CLOSE,
    TOKEN_BRACKET_OPEN,
    TOKEN_BRACKET_CLOSE,
    TOKEN_BRACE_OPEN,
    TOKEN_BRACE_CLOSE,
    TOKEN_NUMBER,
    TOKEN_COLON,
    TOKEN_SEMICOLON,
    TOKEN_STRING,
    TOKEN_ASTERISK,
    TOKEN_POUND,
    TOKEN_LSHIFT,
    TOKEN_RSHIFT,
    TOKEN_LESSER_THAN,
    TOKEN_GREATER_THAN,
    TOKEN_POINTER_ACCESS,
    TOKEN_OR,
    TOKEN_OR_ASSIGNMENT,
    TOKEN_OR_BITWISE,
    TOKEN_END
};

struct Token
{
    TokenType type;
    u32 length;
    char* text;
};

struct Tokenizer
{
    char* at;
};

flocal inline b32
isEOL(char c)
{
    return (c == '\n') || (c == '\r');
}


flocal inline b32
isWhitespace(char c)
{
    return ((c == ' ')  || (c == '\t') || isEOL(c));
}

flocal void
eatAllWhitespace(Tokenizer* tok)
{
    while(true)
    {
        if (isWhitespace(tok->at[0]))
        {
            tok->at++;
        }
        else if (tok->at[0] == '/' && tok->at[1] == '/')
        {
            while(tok->at[0] && !isEOL(tok->at[0]))
            {
                tok->at++;
            }
        }
        else if (tok->at[0] == '/' && tok->at[1] == '*')
        {
            tok->at += 2;
            while (tok->at[0] && (tok->at[0] != '*' && tok->at[1] != '/'))
            {
                tok->at++;
            }
            tok->at+=2;
        }
        else
        {
            break;
        }
    }
     
}

flocal inline b32
isAlpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

flocal inline b32
isNumeric(char c)
{
    return c >= '0' && c <= '9';   
}

flocal u32
lenStringToInt(char* c, u32 len)
{
    char* buf = (char*)malloc(len + 1);
    for (int i = 0; i < len; i++)
    {
        buf[i] = c[i];
    }
    buf[len] = 0;
    u32 out = strtol(buf, nullptr, 0);
    free(buf);
    return out;
}

Token getToken(Tokenizer* tokenizer)
{
    eatAllWhitespace(tokenizer);
    Token t = {};
    t.length = 1;
    t.text = tokenizer->at;
    switch(tokenizer->at[0])
    {

        case ',' :
        {
            t.type = TOKEN_COMMA;
            tokenizer->at++;
        } break;
        case '=' :
        {
            if (tokenizer->at[1] == '=')
            {
                t.type = TOKEN_EQUALS;
                t.length = 2;
                t.text = "==";
                tokenizer->at+=2;   
            }
            else
            {
                t.type = TOKEN_ASSIGNMENT;
                t.length = 1;
                t.text = "=";
                tokenizer->at++;   
            }
        } break;
        case '(' :
        {
            t.type = TOKEN_PAREN_OPEN;
            tokenizer->at++;
        } break;
        case ')' :
        {
            t.type = TOKEN_PAREN_CLOSE; 
            tokenizer->at++;
        } break;
        case '#' :
        {
            t.type = TOKEN_POUND;
            tokenizer->at++;
        } break;
        case '[' :
        {
            t.type = TOKEN_BRACKET_OPEN; 
            tokenizer->at++;
        } break;
        case ']' :
        {
            t.type = TOKEN_BRACKET_CLOSE;
            tokenizer->at++;
        } break;
        case '{' :
        {
            t.type = TOKEN_BRACE_OPEN;
            tokenizer->at++;
        } break;
        case '}' :
        {
            t.type = TOKEN_BRACE_CLOSE; 
            tokenizer->at++;
        } break;
        case ':' :
        {
            t.type = TOKEN_COLON;
            tokenizer->at++;
        } break;
        case ';':
        {
            t.type = TOKEN_SEMICOLON; 
            tokenizer->at++;
        } break;
        case '*':
        {
            t.type = TOKEN_ASTERISK; 
            tokenizer->at++;
        } break;
        case '"' :
        {
            tokenizer->at++;
            while(tokenizer->at[0] && tokenizer->at[0] != '"')
            {
                if (tokenizer->at[0] == '\\' && tokenizer->at[1])
                {
                    tokenizer->at++;
                }
                tokenizer->at++;
            }
            if (tokenizer->at[0] == '"')
            {
                tokenizer->at++;
            }
            t.type = TOKEN_STRING;
            t.length = tokenizer->at - t.text;
        } break;
        case '<' : 
        {
            if (tokenizer->at[1] == '<')
            {
                t.type = TOKEN_LSHIFT;
                t.text = "<<";
                t.length = 2;
                tokenizer->at++;
                tokenizer->at++;
            }
            else
            {
                t.type = TOKEN_LESSER_THAN;
                t.text = "<";
                t.length = 1;
                tokenizer->at++;
            }
        } break;
        case '>' :
        {

            if (tokenizer->at[1] == '>')
            {
                t.type = TOKEN_RSHIFT;
                t.text = ">>";
                t.length = 2;
                tokenizer->at++;
                tokenizer->at++;
            }
            else
            {
                t.type = TOKEN_GREATER_THAN;
                t.text = ">";
                t.length = 1;
                tokenizer->at++;
            }
        } break;
        case '-' :
        {
            if (tokenizer->at[1] == '>')
            {
                t.type = TOKEN_POINTER_ACCESS;
                t.text = "->";
                t.length = 2;
                tokenizer->at+=2;
            }
            else
            {
                tokenizer->at++;
                t.type = TOKEN_UNKNOWN;
                t.length = 0;
                t.text = nullptr;
            }
            
        } break;
        case '|' :
        {
            if (tokenizer->at[1] == '|')
            {
                t.type = TOKEN_OR;
                t.text = "||";
                t.length = 2;
                tokenizer->at+=2;
            }
            else if (tokenizer->at[1] == '=')
            {
                t.type = TOKEN_OR_ASSIGNMENT;
                t.text = "|=";
                t.length = 2;
                tokenizer->at+=2;
            }
            else
            {
                t.type = TOKEN_OR_BITWISE;
                t.text = "|";
                t.length = 1;
                tokenizer->at++;
            }
        }break;
        case 0 :
        {
            t.type = TOKEN_END;
            t.text = '\0';
            t.length = 0;
        } break;
        default :
        {
            if (isAlpha(tokenizer->at[0]))
            {
                while(isAlpha(tokenizer->at[0]) ||
                      isNumeric(tokenizer->at[0]) ||
                      tokenizer->at[0] == '_')
                {
                    tokenizer->at++;
                }
                t.type = TOKEN_IDENTIFIER;
                t.length = tokenizer->at - t.text;
            }
            else if (isNumeric(tokenizer->at[0]))
            {
#if 1        
                while(isNumeric(tokenizer->at[0])) //!isWhitespace(tokenizer->at[0]) && tokenizer->at[0] != ')' && tokenizer->at[0] != ',')
                {
                    tokenizer->at++;
                }
                t.type = TOKEN_NUMBER;
                t.length = tokenizer->at - t.text;
#else
                parse_number_token(tokenizer);
#endif
            }
            else
            {
                tokenizer->at++;
                t.type = TOKEN_UNKNOWN;
                t.length = 0;
                t.text = nullptr;
            }
        } break;
        
    }
    return t;
}

Token peek_tok(Tokenizer tokenizer)
{
    return getToken(&tokenizer);
}

#if 0     
flocal b32 strEq(char* a, char* b)
{
    char* c = a;
    char* d = b;
    while (c[0] && d[0])
    {
        if(*c++ != *d++)
        {
            return false;
        }
        
    }
    return true;
}
#endif

flocal inline b32
tokenEquals(const Token& a, const Token& b)
{
    return (a.type == b.type && a.length == b.length && streq(a.text, b.text, b.length));
}

b32 operator==(const Token& a, const Token& b)
{
    return tokenEquals(a,b);
}

flocal inline
Token token(TokenType type, u32 len, char* text)
{
    return {type, len, text};
}


flocal inline b32 is_cpp_or_h_file(char* file)
{
    const char* h = ".h";
    const char* cpp = ".cpp";
    char* c = file;
    while (*c != '.')
    {
        c++;
    }
    if (c)
    {
        if (strcmp(c,h))
        {
            return true;
        }
        if (strcmp(c,cpp))
        {
            return true;
        }
    }
    return false;
}

flocal b32 find_next_enum_in_file(char** file)
{
    Tokenizer tok = {};
    tok.at = *file;
    b32 should_break = false;
    b32 ret_val = false;
    while (!should_break)
    {
        Token t = getToken(&tok);
        if (tokenEquals(token(TOKEN_IDENTIFIER, 4, "enum"), t))
        {
            should_break = true;
            ret_val = true;
        }
        if (tokenEquals(token(TOKEN_END, 0, "\0"), t))
        {
            
            should_break = true;
            ret_val = false;
        }
    }
    
    *file = tok.at;
    return ret_val;
}

flocal b32 find_next_token_in_file(char** file, Token query)
{
    Tokenizer tok = {};
    tok.at = *file;
    b32 should_break = false;
    b32 ret_val = false;
    while (!should_break)
    {
        Token t = getToken(&tok);
        if (query == t)
        {
            should_break = true;
            ret_val = true;
        }
        if (token(TOKEN_END, 0, "\0") == t)
        {
            
            should_break = true;
            ret_val = false;
        }
    }
    
    *file = tok.at;
    return ret_val;
}

flocal b32 find_next_tokens_in_file(char** file, Token* query, u32 count)
{
    Tokenizer tok = {};
    tok.at = *file;
    b32 should_break = false;
    b32 ret_val = false;
    while (!should_break)
    {
        Token t = getToken(&tok);
        LOOP(i, count)
        {
            if (query[i] == t)
            {
                should_break = true;
                ret_val = true;
            }
        }
        if (token(TOKEN_END, 0, "\0") == t)
        {
            
            should_break = true;
            ret_val = false;
        }
    }
    
    *file = tok.at;
    return ret_val;
}

flocal b32 find_next_id_in_file(char** file, char* text, u32 len)
{
    Tokenizer tok = {};
    tok.at = *file;
    b32 should_break = false;
    b32 ret_val = false;
    while (!should_break)
    {
        Token t = getToken(&tok);
        if (tokenEquals(token(TOKEN_IDENTIFIER, len, text), t))
        {
            should_break = true;
            ret_val = true;
        }
        if (tokenEquals(token(TOKEN_END, 0, "\0"), t))
        {
            
            should_break = true;
            ret_val = false;
        }
    }
    
    *file = tok.at;
    return ret_val;
}

flocal b32 find_next_token(Tokenizer* tok, Token query)
{
    b32 should_break = false;
    b32 ret_val = false;
    while (!should_break)
    {
        Token t = getToken(tok);
        if (query == t)
        {
            should_break = true;
            ret_val = true;
        }
        if (tokenEquals(token(TOKEN_END, 0, "\0"), t))
        {
            
            should_break = true;
            ret_val = false;
        }
    }
    return ret_val;
}

flocal i32 update_brace_counter(Token t)
{
    if (t == token(TOKEN_BRACE_CLOSE, 1, "}"))
    {
        return 1;
    }
    if (t == token(TOKEN_BRACE_OPEN, 1, "{"))
    {
        return -1;
    }
    return 0;\
}

flocal b32 eat_to_next_whitespace(Tokenizer* tok)
{
    while(*tok->at && !isWhitespace(*tok->at))
    {
        tok->at++;
    }
    if (*tok->at)
    {
        return false;
    }
    return true;
}

#endif
