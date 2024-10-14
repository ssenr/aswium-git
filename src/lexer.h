#ifndef lexer_h
#define lexer_h

typedef enum {
  TOKEN_HEADING,
  TOKEN_BOLD,
  TOKEN_ITALIC,
  TOKEN_BLOCKQUOTE,
  TOKEN_ORDEREDLIST,
  TOKEN_UNORDEREDLIST,
  TOKEN_CODE,
  TOKEN_HORIZONTALRULE,
  TOKEN_LINK,
  TOKEN_IMAGE,
  TOKEN_FENCECODEBLOCK,
  TOKEN_FOOTNOTE,
  TOKEN_SUBSCRIPT,
  TOKEN_SUPERSCRIPT,
} TokenType;

typedef struct {
    TokenType type;
    char *value; //this is a pointer heh just learned this
} Token;

#endif
