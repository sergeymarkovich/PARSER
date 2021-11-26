#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <head.h>
#include <utils.h>
#include <general.h>
void store_from(char *str, char* memory, data_t* data) {
    char *trade = (char *)malloc((strlen(str)-1)*sizeof(char));
            strncpy(trade, str, strlen(str) - 2);
            trade[strlen(str)-2] = '\0';
    char *c = scan_dop(trade, memory);
    c = delete_space(5, c);
    char *rez = (char *)malloc((strlen(c)-4)*sizeof(char));
            strncpy(rez, c+5, strlen(c)-5);
            rez[strlen(c)-5]='\0';
    data->from = clear(rez);
    free(c);
    free(trade);
    free(rez);
}
void store_to(char *str, char* memory, data_t* data) {
    char *trade = (char *)malloc((strlen(str)-1)*sizeof(char));
    strncpy(trade, str, strlen(str) - 2);
    trade[strlen(str)-2] = '\0';
    char *c = scan_dop(trade, memory);
    c = delete_space(3, c);
    char *rez = (char *)malloc((strlen(c)-2)*sizeof(char));
    strncpy(rez, c+3, strlen(c)-3);
    rez[strlen(c)-3]='\0';
    data->to = clear(rez);
    free(c);
    free(trade);
    free(rez);
}
void store_boundary(char* str, char *memory, data_t* data) {
    char *t = (char *)malloc((strlen(str)-1)*sizeof(char));
    strncpy(t, str, strlen(str) - 2);
    t[strlen(str)-2] = '\0';
    char *c = scan_dop(t, memory);
    char *ch1 = strcasestr(c, " boundary");
    if (ch1 == NULL) {
        ch1 = strcasestr(c, "\tboundary");
        if (ch1 == NULL) {
            ch1 = strcasestr(c, ";boundary");
        }
    }
    if (ch1 != NULL) {
        char * ch2 = strdup(ch1);
        char *a = clear(ch2);
        free(ch2);
        ch2 = a;
        if (ch2[0] == ' ') {
            char *trade =(char*)malloc((strlen(ch2))*sizeof(char));
            strncpy(trade, ch2+1, strlen(ch2));
            free(ch2);
            ch2 = trade;
        }
        char *rez = (char*)malloc((strlen(ch2)-8)*sizeof(char));
        strncpy(rez, ch2 + 9, strlen(ch2) - 8);
        if (rez[0] == '=') {
            char *trade =(char*)malloc((strlen(rez))*sizeof(char));
            strncpy(trade, rez+1, strlen(rez));
            free(rez);
            rez = trade;
        }
        if (rez[0] == ' ') {
            char *trade =(char*)malloc((strlen(rez))*sizeof(char));
            strncpy(trade, rez+1, strlen(rez));
            free(rez);
            rez = trade;
        }
        if (rez[0] == '\"') {
            char *trade =(char*)malloc((strlen(rez))*sizeof(char));
            strncpy(trade, rez+1, strlen(rez));
            free(rez);
            rez = (char*)malloc((strlen(trade) - strlen(strstr(trade, "\""))+1)*sizeof(char));
            strncpy(rez, trade, strlen(trade) - strlen(strstr(trade, "\"")) );
            rez[strlen(trade) - strlen(strstr(trade, "\""))]= '\0';
            free(trade);
        }
        char *temp = adj("--", rez);
        free(rez);
        data->boundary = clear(temp);
        free(temp);
        free(ch2);
    }
    free(t);
    free(c);
}
void store_date(char* str, char*memory, data_t* data) {
    char *trade = (char *)malloc((strlen(str)-1)*sizeof(char));
    strncpy(trade, str, strlen(str) - 2);
    trade[strlen(str)-2] = '\0';
    char *c = scan_dop(trade, memory);
    c = delete_space(5, c);
    char *rez = (char *)malloc((strlen(c)-4)*sizeof(char));
    strncpy(rez, c+5, strlen(c)-5);
    rez[strlen(c)-5]='\0';
    data->date = clear(rez);
    free(c);
    free(trade);
    free(rez);
}
void head(char* memory, data_t *data, char *len_sp) {
    char *str;
    if ((str = scans("\nfrom:", memory)) != NULL) {
        int ch_len = strlen(len_sp) - strlen(strstr(memory, str));
        if (ch_len <= 0) {
            store_from(str, memory, data);
        }
        free(str);
    }
    if ((str = scans("\nto:", memory)) != NULL) {
        int ch_len = strlen(len_sp) - strlen(strstr(memory, str));
        if (ch_len <= 0) {
            store_to(str, memory, data);
        }
        free(str);
    }
    if ((str = scans("\ndate:", memory)) != NULL) {
        int ch_len = strlen(len_sp) - strlen(strstr(memory, str));
        if (ch_len <= 0) {
            store_date(str, memory, data);
        }
        free(str);
    }
    if ((str = scans("\ncontent-type: multipart", memory)) != NULL) {
        int ch_len = strlen(len_sp) - strlen(strstr(memory, str));
        if (ch_len <= 0) {
            store_boundary(str, memory, data);
        }
        free(str);
    }
}
