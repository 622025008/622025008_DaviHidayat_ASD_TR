#ifndef AUTH_H
#define AUTH_H

#include "types.h"

typedef struct {
    User *data;
    int count;
    int capacity;
} UserList;

void initUserList(UserList *list);
void loadUsers(UserList *list, const char *filename);
void saveUsers(const UserList *list, const char *filename);
int registerUser(UserList *list, const char *filename);
int loginUser(const UserList *list, char *loggedInUser);
void freeUserList(UserList *list);

#endif
