#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auth.h"
#include "utils.h"

void initUserList(UserList *list) {
    list->count = 0;
    list->capacity = 10;
    list->data = (User *)malloc(list->capacity * sizeof(User));
}

void loadUsers(UserList *list, const char *filename) {
    FILE *fp = fopen(filename, "r");
    User u;
    if (!fp) return;

    while (fscanf(fp, "%63[^;];%63[^\n]\n", u.username, u.password) == 2) {
        if (list->count >= list->capacity) {
            list->capacity *= 2;
            list->data = (User *)realloc(list->data, list->capacity * sizeof(User));
        }
        list->data[list->count++] = u;
    }
    fclose(fp);
}

void saveUsers(const UserList *list, const char *filename) {
    FILE *fp = fopen(filename, "w");
    int i;
    if (!fp) {
        printf("[!] Gagal membuka file %s (pastikan folder data/ tersedia).\n", filename);
        return;
    }
    for (i = 0; i < list->count; i++) {
        fprintf(fp, "%s;%s\n", list->data[i].username, list->data[i].password);
    }
    fclose(fp);
}

int registerUser(UserList *list, const char *filename) {
    User u;
    int i;
    printf("\n=== REGISTER AKUN BARU ===\n");
    inputString("Username: ", u.username, MAX_STR);

    for (i = 0; i < list->count; i++) {
        if (strcmp(list->data[i].username, u.username) == 0) {
            printf("[!] Username sudah digunakan!\n");
            return 0;
        }
    }

    inputString("Password: ", u.password, MAX_STR);
    if (list->count >= list->capacity) {
        list->capacity *= 2;
        list->data = (User *)realloc(list->data, list->capacity * sizeof(User));
    }
    list->data[list->count++] = u;
    saveUsers(list, filename);
    printf("[+] Registrasi berhasil!\n");
    return 1;
}

int loginUser(const UserList *list, char *loggedInUser) {
    char uname[MAX_STR], pass[MAX_STR];
    int i;
    printf("\n=== LOGIN ===\n");
    inputString("Username: ", uname, MAX_STR);
    inputString("Password: ", pass, MAX_STR);

    for (i = 0; i < list->count; i++) {
        if (strcmp(list->data[i].username, uname) == 0 &&
            strcmp(list->data[i].password, pass) == 0) {
            strcpy(loggedInUser, uname);
            printf("[+] Login berhasil! Selamat datang, %s.\n", uname);
            return 1;
        }
    }
    printf("[!] Login gagal. Username atau password salah!\n");
    return 0;
}

void freeUserList(UserList *list) {
    free(list->data);
    list->data = NULL;
    list->count = 0;
    list->capacity = 0;
}
