#include <stdio.h>
#include <string.h>
#include "types.h"
#include "utils.h"
#include "auth.h"
#include "paket.h"
#include "stack_queue.h"
#include "hashtable.h"
#include "bst.h"
#include "graph.h"

#define FILE_AKUN  "data/akun.txt"
#define FILE_PAKET "data/paket.txt"
#define FILE_GRAPH "data/graph.txt"

void syncStructures(const PaketList *list, Queue *q, HashTable *ht, BSTNode **root) {
    int i;
    Paket p;
    for (i = 0; i < list->count; i++) {
        p = list->data[i];
        insertHash(ht, p);
        *root = insertBST(*root, p);
        if (strcmp(p.status, "Menunggu") == 0) {
            enqueue(q, p);
        }
    }
}

void updateStatusPaket(PaketList *list, int id, const char *newStatus) {
    int i;
    for (i = 0; i < list->count; i++) {
        if (list->data[i].id == id) {
            strcpy(list->data[i].status, newStatus);
            break;
        }
    }
}

void menuUtama(const char *user, PaketList *pList, Queue *q, Stack *s,
               HashTable *ht, BSTNode **bstRoot, const Graph *g) {
    int pilihan;
    do {
        printf("\n==============================================\n");
        printf("  SISTEM MANAJEMEN LOGISTIK (User: %s)\n", user);
        printf("==============================================\n");
        printf("1. Tambah Paket Baru\n");
        printf("2. Lihat & Urutkan Daftar Paket (Sorting)\n");
        printf("3. Cari Paket (Sequential & Binary Search)\n");
        printf("4. Lacak Resi Instan (Hash Table)\n");
        printf("5. Proses Antrean & Undo Pengiriman (Queue & Stack)\n");
        printf("6. Manajemen Indeks Paket (BST)\n");
        printf("7. Penelusuran Rute Gudang (Graph BFS & DFS)\n");
        printf("8. Logout\n");
        pilihan = inputInt("Pilih menu: ");

        if (pilihan == 1) {
            Paket p;
            p.id = inputInt("ID Paket (angka unik): ");
            if (searchBST(*bstRoot, p.id) != NULL) {
                printf("[!] ID Paket sudah terdaftar!\n");
                continue;
            }
            inputString("No Resi (misal RES001): ", p.resi, MAX_STR);
            if (searchHash(ht, p.resi) != NULL) {
                printf("[!] Nomor Resi sudah terdaftar!\n");
                continue;
            }
            inputString("Nama Pengirim: ", p.pengirim, MAX_STR);
            inputString("Kota Tujuan: ", p.tujuan, MAX_STR);
            p.berat = inputFloat("Berat (kg): ");
            strcpy(p.status, "Menunggu");

            addPaketToList(pList, p);
            insertHash(ht, p);
            *bstRoot = insertBST(*bstRoot, p);
            enqueue(q, p);
            savePaket(pList, FILE_PAKET);
            printf("[+] Paket berhasil ditambahkan dan masuk antrean!\n");

        } else if (pilihan == 2) {
            int alg, asc;
            printf("1. Bubble Sort (Berat) | 2. Selection Sort (ID)\n");
            alg = inputInt("Pilih algoritma: ");
            asc = inputInt("Urutan (1 = Ascending, 0 = Descending): ");
            if (alg == 1) bubbleSortBerat(pList, asc);
            else selectionSortId(pList, asc);
            tampilkanPaket(pList);

        } else if (pilihan == 3) {
            int mode;
            printf("1. Sequential Search (Kota Tujuan) | 2. Binary Search (ID Paket)\n");
            mode = inputInt("Pilih metode: ");
            if (mode == 1) {
                char kota[MAX_STR];
                inputString("Masukkan Kota Tujuan: ", kota, MAX_STR);
                if (!sequentialSearchTujuan(pList, kota))
                    printf("[!] Paket dengan tujuan '%s' tidak ditemukan.\n", kota);
            } else {
                int target, idx;
                selectionSortId(pList, 1);
                target = inputInt("Masukkan ID Paket: ");
                idx = binarySearchId(pList, target);
                if (idx != -1) {
                    Paket p = pList->data[idx];
                    printf("[+] Ditemukan: [%s] %s -> %s (%.2f kg, %s)\n",
                           p.resi, p.pengirim, p.tujuan, p.berat, p.status);
                } else {
                    printf("[!] ID Paket tidak ditemukan.\n");
                }
            }

        } else if (pilihan == 4) {
            char resi[MAX_STR];
            Paket *res;
            inputString("Masukkan No Resi: ", resi, MAX_STR);
            res = searchHash(ht, resi);
            if (res) {
                printf("[+] Ditemukan via Hash Table -> ID: %d | Pengirim: %s | Tujuan: %s | Berat: %.2f kg | Status: %s\n",
                       res->id, res->pengirim, res->tujuan, res->berat, res->status);
            } else {
                printf("[!] Resi '%s' tidak ditemukan.\n", resi);
            }

        } else if (pilihan == 5) {
            int sub;
            printf("1. Lihat Antrean | 2. Kirim Paket Terdepan | 3. Lihat Riwayat | 4. Undo Pengiriman Terakhir\n");
            sub = inputInt("Pilih: ");
            if (sub == 1) displayQueue(q);
            else if (sub == 2) {
                Paket p;
                if (dequeue(q, &p)) {
                    Paket *hp;
                    strcpy(p.status, "Dikirim");
                    push(s, p);
                    updateStatusPaket(pList, p.id, "Dikirim");
                    hp = searchHash(ht, p.resi);
                    if (hp) strcpy(hp->status, "Dikirim");
                    savePaket(pList, FILE_PAKET);
                    printf("[+] Paket [%s] berhasil dikirim!\n", p.resi);
                } else {
                    printf("[!] Antrean kosong.\n");
                }
            } else if (sub == 3) displayStack(s);
            else if (sub == 4) {
                Paket p;
                if (pop(s, &p)) {
                    Paket *hp;
                    strcpy(p.status, "Menunggu");
                    enqueue(q, p);
                    updateStatusPaket(pList, p.id, "Menunggu");
                    hp = searchHash(ht, p.resi);
                    if (hp) strcpy(hp->status, "Menunggu");
                    savePaket(pList, FILE_PAKET);
                    printf("[+] Pengiriman paket [%s] dibatalkan (Undo) & dikembalikan ke antrean.\n", p.resi);
                } else {
                    printf("[!] Tidak ada riwayat untuk di-undo.\n");
                }
            }

        } else if (pilihan == 6) {
            int sub;
            printf("1. Traversal (Pre/In/Post-Order) | 2. Cari ID di BST | 3. Hapus ID dari BST\n");
            sub = inputInt("Pilih: ");
            if (sub == 1) {
                printf("Pre-Order : "); preorderBST(*bstRoot); printf("\n");
                printf("In-Order  : "); inorderBST(*bstRoot); printf("\n");
                printf("Post-Order: "); postorderBST(*bstRoot); printf("\n");
            } else if (sub == 2) {
                int id = inputInt("Masukkan ID: ");
                BSTNode *found = searchBST(*bstRoot, id);
                if (found) printf("[+] Ditemukan di BST: [%s] Tujuan: %s\n", found->data.resi, found->data.tujuan);
                else printf("[!] ID tidak ditemukan di BST.\n");
            } else if (sub == 3) {
                int id = inputInt("Masukkan ID yang dihapus dari BST: ");
                *bstRoot = deleteBST(*bstRoot, id);
                printf("[+] Proses hapus BST selesai.\n");
            }

        } else if (pilihan == 7) {
            int start;
            displayGraph(g);
            start = inputInt("Pilih indeks kota awal (0 - 4): ");
            if (start >= 0 && start < g->numVertices) {
                bfsGraph(g, start);
                dfsGraph(g, start);
            } else {
                printf("[!] Indeks kota tidak valid.\n");
            }

        } else if (pilihan == 8) {
            printf("[+] Logout berhasil.\n");
        } else {
            printf("[!] Pilihan tidak valid.\n");
        }
    } while (pilihan != 8);
}

int main(void) {
    UserList users;
    PaketList pakets;
    Queue antrean;
    Stack riwayat;
    HashTable ht;
    BSTNode *bstRoot = NULL;
    Graph petaGudang;
    int menuAwal;
    char currentUser[MAX_STR];

    setvbuf(stdout, NULL, _IONBF, 0);

    initUserList(&users);
    initPaketList(&pakets);
    initQueue(&antrean);
    initStack(&riwayat);
    initHashTable(&ht);

    loadUsers(&users, FILE_AKUN);
    loadPaket(&pakets, FILE_PAKET);
    syncStructures(&pakets, &antrean, &ht, &bstRoot);
    initGraph(&petaGudang, FILE_GRAPH);

    do {
        printf("\n=== SISTEM LOGISTIK & RUTE PENGIRIMAN ===\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Keluar\n");
        menuAwal = inputInt("Pilih menu: ");

        if (menuAwal == 1) {
            if (loginUser(&users, currentUser)) {
                menuUtama(currentUser, &pakets, &antrean, &riwayat, &ht, &bstRoot, &petaGudang);
            }
        } else if (menuAwal == 2) {
            registerUser(&users, FILE_AKUN);
        } else if (menuAwal == 3) {
            printf("Menyimpan data dan membersihkan memori...\n");
        } else {
            printf("[!] Pilihan tidak valid.\n");
        }
    } while (menuAwal != 3);

    savePaket(&pakets, FILE_PAKET);
    freeUserList(&users);
    freePaketList(&pakets);
    freeQueue(&antrean);
    freeStack(&riwayat);
    freeHashTable(&ht);
    freeBST(bstRoot);

    return 0;
}
