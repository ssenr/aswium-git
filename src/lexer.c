#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

static void skip_whitespace(const char *input, int *pos) {
    while (isspace(input[*pos])) (*pos)++;
}