#pragma once

#define MAX_HTML_LENGTH     2048
#define MAX_HEADER_LENGTH   2048

char* read_html(const char* file_path);
void error(const char* message);

