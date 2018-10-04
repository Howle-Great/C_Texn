#define num_of_str 50
#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "stdio.h"
#include <stdlib.h>
#include <string.h>


char** StrFilt(char** str, int num_lines, int* num_of_correct_strs){
    char **out_of_str = (char **)malloc(num_lines*sizeof(char*));
    *num_of_correct_strs = 0;
    for (int y = 0; y < num_lines; y++) {
        int count = 0;
        for (int i = 0; i < strlen(*(str + y)); i++) {
            if (str[y][i] == '(') {
                count++;
            }
            if (str[y][i] == ')') {
                count--;
            }
            if (count < 0) {
                break;
            }
        }
        if (count == 0) {
            memcpy(&out_of_str[(*num_of_correct_strs)], &(*(str + y)), sizeof(*(str + y))+1);
            (*num_of_correct_strs)++;
        }
    }
    return out_of_str;
}
int main(int argc, const char * argv[]) {
    char** tmp_str =  (char**) malloc(num_of_str*sizeof(char*));
    for (int y = 0; y < num_of_str; y++) {
        tmp_str[y] = (char*) malloc(20*sizeof(char));
        //tmp_str[y] = "\o";
    }
    size_t len_str = 2;
    int num_strings_log = 0;
    for (; ;num_strings_log++) {
        if (getline(&tmp_str[num_strings_log], &len_str, stdin) == 1 && ferror(stdin)) {
            printf("[error]");
            return 0;
        }
        if (tmp_str[num_strings_log][0] == '\n') {
            break;
        }
    }
    char** out_str;
    int num_of_correct_strs = 0;
    out_str = StrFilt(tmp_str ,num_strings_log ,&num_of_correct_strs );
    for (int j = 0; j < num_of_correct_strs; j++) {
        printf("%s", out_str[j]);
    }
    for (int i = 0; i < num_of_str; i++) {
        free(*(tmp_str + i));
    }
    free(tmp_str);
}

