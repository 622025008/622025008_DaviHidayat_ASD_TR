#ifndef TYPES_H
#define TYPES_H

#define MAX_STR 64
#define HASH_SIZE 31
#define MAX_KOTA 10

typedef struct {
    char username[MAX_STR];
    char password[MAX_STR];
} User;

typedef struct {
    int id;                 /* Kunci unik untuk BST & Binary Search */
    char resi[MAX_STR];     /* Kunci unik untuk Hash Table */
    char pengirim[MAX_STR];
    char tujuan[MAX_STR];
    float berat;
    char status[MAX_STR];   /* "Menunggu", "Dikirim" */
} Paket;

#endif
