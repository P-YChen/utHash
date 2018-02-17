#include <stdio.h>   /* gets */
#include <stdlib.h>  /* atoi, malloc */
#include <string.h>  /* strcpy */
#include "uthash.h"

struct my_struct {
    int id;                    /* key */
    char name[10];
    UT_hash_handle hh;         /* makes this structure hashable */
};

struct my_struct *users = NULL;

void add_user(int user_id, char *name)
{
    struct my_struct *s = NULL;

    HASH_FIND_INT(users, &user_id, s);  /* id already in the hash? */
    if (s==NULL) {
        s = (struct my_struct*)malloc(sizeof(struct my_struct));
        if (s == NULL) {
            printf("add_user malloc fail!\n");
            return -1;
        }
        s->id = user_id;
        HASH_ADD_INT( users, id, s );  /* id: name of key field */
    }
    strcpy(s->name, name);
}

void add_user_by_name(int user_id, char *name)
{
    struct my_struct *s = NULL;

    HASH_FIND_STR(users, name, s);
    if (s == NULL) {
        s = (struct my_struct *)uthash_malloc(sizeof(struct my_struct));
        if (s == NULL) {
            printf("add_user_by_name malloc fail!\n");
            return -1;
        }
        s->id = user_id;
        strcpy(s->name, name);
        HASH_ADD_STR(users, name, s);
    }
}

struct my_struct *find_user(int user_id)
{
    struct my_struct *s;

    HASH_FIND_INT( users, &user_id, s );  /* s: output pointer */
    return s;
}

struct my_struct *find_user_by_name(char *name)
{
    struct my_struct *s = NULL;

    HASH_FIND_STR(users,name,s);
    return s;
}

void delete_user(struct my_struct *user)
{
    HASH_DEL( users, user);  /* user: pointer to deletee */
    free(user);
}

void delete_all()
{
    struct my_struct *current_user, *tmp;

    HASH_ITER(hh, users, current_user, tmp) {
        HASH_DEL(users,current_user);  /* delete it (users advances to next) */
        free(current_user);            /* free it */
    }
}

void print_users()
{
    struct my_struct *s = NULL;

    for(s=users; s != NULL; s=(struct my_struct*)(s->hh.next)) {
        printf("user id %d: name %s\n", s->id, s->name);
    }
}

int name_sort(struct my_struct *a, struct my_struct *b)
{
    return strcmp(a->name,b->name);
}

int id_sort(struct my_struct *a, struct my_struct *b)
{
    return (a->id - b->id);
}

void sort_by_name()
{
    HASH_SORT(users, name_sort);
}

void sort_by_id()
{
    HASH_SORT(users, id_sort);
}

int main(int argc, char *argv[])
{
    char in[10] = {0};
    char in_buf[10] = {0};
    int id=1, running=1;
    struct my_struct *s;
    unsigned num_users;

    while (running) {
        printf(" 1. add user\n");
        printf(" 2. add/rename user by id\n");
        printf(" 3. find user\n");
        printf(" 4. delete user\n");
        printf(" 5. delete all users\n");
        printf(" 6. sort items by name\n");
        printf(" 7. sort items by id\n");
        printf(" 8. print users\n");
        printf(" 9. count users\n");
        printf("10. quit\n");
        printf("11. add users by name\n");
        printf("12. find users by name\n");
        memset(in_buf, 0, sizeof(in_buf));
        memset(in, 0, sizeof(in));
        gets(in);
        
        switch(atoi(in)) {
            case 1:
                printf("name?\n");
                gets(in_buf);
                add_user(id++, in_buf);
                break;
            case 2:
                printf("id?\n");
                gets(in_buf);
                id = atoi(in_buf);
                printf("name?\n");
                gets(in_buf);
                add_user(id, in_buf);
                break;
            case 3:
                printf("id?\n");
                gets(in_buf);
                s = find_user(atoi(in_buf));
                printf("user: %s\n", s ? s->name : "unknown");
                break;
            case 4:
                printf("id?\n");
                gets(in_buf);
                s = find_user(atoi(in_buf));
                if (s) {
                    delete_user(s);
                } else {
                    printf("id unknown\n");
                }
                break;
            case 5:
                delete_all();
                break;
            case 6:
                sort_by_name();
                break;
            case 7:
                sort_by_id();
                break;
            case 8:
                print_users();
                break;
            case 9:
                num_users=HASH_COUNT(users);
                printf("there are %u users\n", num_users);
                break;
            case 10:
                running=0;
                break;
            case 11:
                printf("name?\n");
                gets(in_buf);
                add_user_by_name(id++, in_buf);
                break;
            case 12:
                printf("name?\n");
                gets(in_buf);
                s = find_user(in_buf);
                printf("user: %s\n", s ? s->name : "unknown");
                break;
        }
    }

    delete_all();  /* free any structures */
    return 0;
}
