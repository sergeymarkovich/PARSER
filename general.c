#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <general.h>
#include <utils.h>

char* clear(char* str) {
    if (strlen(str) < 1) {
        return str;
    }
    int len = strlen(str);
    int i;
    int j = 0;
    int ch = 0;
    char* t = (char*) malloc((strlen(str) + 1)*sizeof(char));
    char *rez;
    for (i = 0; i < len; i++) {
        if (str[i] != '\n' && str[i] != '\r' && str[i] != '\0') {
            if (ch == 1) {
                ch = 0;
                while (str[i] == ' ') {
                    i++;
                }
                t[j++] = ' ';
            }
            t[j++] = str[i];
        } else {
            ch = 1;
        }
    }
    t[j] = '\0';
    if (t[0] == ' ') {
        int k = 1;
        while (t[k] == ' ') {
            k++;
        }
        char *trade = strdup(t);
        free(t);
        t = (char*)malloc((strlen(trade) - k + 2) * sizeof(char));
        strncpy(t, trade + k - 1, strlen(trade) - k + 2);
        free(trade);
    }
    j = strlen(t);
    if (t[j-1] == ' ') {
        if (!(rez = (char*)malloc((strlen(t)) * sizeof(char)))) {
            printf("Memory");
            return NULL;
        }
        snprintf(rez, strlen(t), "%s", t);
    } else {
        rez = strdup(t);
    }
    free(t);
    return rez;
}
char* adj(char *str1, char *str2) {
    if (str1 == NULL || str2 == NULL) {
        char * out;
        out = strdup(str1);
        return out;
    }
    char *rez = (char*)malloc((strlen(str2) + strlen(str1) + 1) * sizeof(char));
    snprintf(rez, strlen(str1) + strlen(str2) + 2, "%s%s", str1, str2);
    rez[strlen(rez)] = '\0';
    return rez;
}
char* scans(char*w, char* memory) {
    char *ch = strdup(w);
    int obr = 0;
    if (strlen(w) > 1) {
        char *p;
        p = strchr(w+1, w[1]);
        free(ch);
        ch =(char*)malloc((strlen(p) + 1)*sizeof(char));
        strncpy(ch, p, strlen(p) + 1);
    }
    if (strcasestr(memory, ch) == NULL) {
        free(ch);
        return NULL;
    }
    if (strncmp(strcasestr(memory, ch), memory, strlen(ch))) {
        free(ch);
        ch = strdup(w);
        obr = 1;
    }
    char *a;
    if ((a = strcasestr(memory, ch)) != NULL) {
        char * c;
        char *d;
        d = strchr(a, a[obr]);
        c = (char*)malloc((strlen(d) + 1)*sizeof(char));
        strncpy(c, d, strlen(d)+1);
        char *b;
        if ((b = strchr(c, '\n')) != NULL) {
            int len = strlen(c) - strlen(b) + 1;
            char *rez = (char*)malloc((len + 1)*sizeof(char));
            strncpy(rez, c, len);
            rez[len] = '\0';
            free(c);
            free(ch);
            return rez;
        }
        free(c);
    }
    free(ch);
    return NULL;
}
char * scan_end(char *memory) {
    char * b;
    if ((b = strstr(memory, "\n")) != NULL) {
        int len = strlen(memory) - strlen(b) + 1;
        char *rez = (char*)malloc((len + 1) * sizeof(char));
         strncpy(rez, memory, len);
         rez[len] = '\0';
        return rez;
    }
    return NULL;
}
char * scan_dop(char* c, char *memory) {
    char *out;
    char *rez = (char *)malloc((strlen(strstr(memory, c)) - strlen(c) + 2)*sizeof(char));
    strncpy(rez, strstr(memory, c) + strlen(c) + 2, strlen(strstr(memory, c)) - strlen(c) + 2);
    char *save = (char*)malloc ((strlen(strstr(memory, c))+1)*sizeof(char));
    strncpy(save, strstr(memory, c), strlen(strstr(memory, c)) + 1);
    while (rez[0] == ' '|| rez[0] == '\t') {
        char *trade;
        char *t;
        t = scan_end(rez);
        trade =(char*) malloc((strlen(rez) + 1)*sizeof(char));
        strncpy(trade, rez+strlen(t), strlen(rez)+1);
        free(rez);
        rez = trade;
        free(t);
    }
    out = (char*)malloc((strlen(save)-strlen(rez)+1)*sizeof(char));
    strncpy(out, save, strlen(save) - strlen(rez));
    out[strlen(save)-strlen(rez)] = '\0';
    free(save);
    free(rez);
    return out;
}
char * delete_space(int n, char *str) {
    if (str[n] == ' ') {
        char *t1 = (char*)malloc((strlen(str)-n)*sizeof(char));
        strncpy(t1, str+n+1, strlen(str)-n);
        char *t2 = (char*)malloc((n+1)*sizeof(char));
                strncpy(t2, str, n);
                t2[n] = '\0';
        free(str);
        str = adj(t2, t1);
        free(t1);
        free(t2);
    }
    return str;
}
