#pragma once

/**
 * HELPER FUNCTIONS (Being Tested For Now)
 */
char* get_requested_resource_path(const char* get_request); // WORKS
char* get_file_ext(char* file_path);
char* get_mime_type(char* file_exit);
char* get_file_data(char* file_path);
char* build_header(char* mime_type, long file_size);

long get_file_size(char* file_path);


/**
 *  Actual Important Functions 
 */
void run_server();
