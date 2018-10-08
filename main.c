//#define num_of_str 50
#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "stdio.h"
#include <stdlib.h>
#include <string.h>


char** StrFilt(char** str, int num_lines, int* num_of_correct_strs){
    char **out_of_str = (char **)malloc(num_lines*sizeof(char*));
    *num_of_correct_strs = 0;
    int counter_simb = 0;
    for (int y = 0; y < num_lines; y++) {
        int count = 0;
        if (strcmp(str[y], "\n")) {
            int i = 0;
            for (; i < strlen(*(str + y)); i++) {
                
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
            counter_simb += i;
            if (count == 0) {
                memcpy(&out_of_str[(*num_of_correct_strs)], &(str[y]), sizeof(str[y]));
                //strcpy(&(str[y]), &out_of_str[*num_of_correct_strs]);
                (*num_of_correct_strs)++;
            }
        }
    }
    out_of_str = (char**) realloc(out_of_str, *num_of_correct_strs*counter_simb*sizeof(char));
    return out_of_str;
}
int main(int argc, const char * argv[]) {
    int len_of_str = 2;
    int num_of_strs = 1;
    int log_num_of_strs = 0;
    char** strs =  (char**) malloc(num_of_strs*sizeof(char*));

    char *str = (char*)malloc(len_of_str*sizeof(char));
    str[0]='\0';
    char simbl;
    int counter_strs = 0;
    int number_of_symbol = 0; //Счетчик символов в строке
    // while (strncmp(str, "\n", strlen(str))) {
    while ((simbl = getchar()) != EOF) {
        if (simbl == '\n') {
            if (number_of_symbol == 0) {
                if (number_of_symbol+1 >= len_of_str) {
                    str = (char*)realloc(str, (len_of_str+=2) * sizeof(char));
                }
                str[number_of_symbol++] = simbl;
                str[number_of_symbol] = '\0';
                continue;
            }
            if (log_num_of_strs >= num_of_strs) {
                strs = (char**)realloc(strs, ++num_of_strs * sizeof(char*));
            }
            strs[log_num_of_strs++] = str;
            str = (char*)malloc(len_of_str*sizeof(char));
            str[0] = '\0';
            ++counter_strs;
            number_of_symbol = 0;
            continue;
        }
        if (number_of_symbol+1 >= len_of_str) {
            str = (char*)realloc(str, (len_of_str+=2) * sizeof(char));
        }
        str[number_of_symbol++] = simbl;
        str[number_of_symbol] = '\0';
    }
    if (number_of_symbol != 0) {
        if (log_num_of_strs >= num_of_strs) {
            strs = (char**)realloc(strs, ++num_of_strs * sizeof(char*));
        }
        strs[log_num_of_strs] = str;
        str = (char*)malloc(len_of_str*sizeof(char));
        ++counter_strs;
    }
    free(str);
    /*for (int i = 0; i < num_of_strs; i++) {
        printf("%s  //  %d\n", strs[i], strlen(strs[i]));
    }*/
    int num_of_correct_strs = 0;
    char** out = StrFilt(strs, num_of_strs, &num_of_correct_strs);
    for (int i = 0; i < num_of_correct_strs; i++) {
        printf("%s\n", out[i]);
    }
    for (int i = 0; i < num_of_strs; i++) {
        free(strs[i]);
    }
    free(strs);
    free(out);
}

