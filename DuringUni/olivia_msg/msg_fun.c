#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

struct server {
    int num_usr;
    int num_msg;
    struct user *usr;
    struct message *msg;
    int fd_srv;
    int fd_usr;
    int fd_msg;
    int new_msg;
};

struct user {
    int num_messages;
    char name[30];
    char pwrd[30];
    int id;
};

struct message {
    int len_msg;
    char msg[100];
    int id;
};

int add_usr(struct server **srv, struct user **usr, char *usrn, char *pwrd) {
	/*
	this method creates a copy of the memory using malloc with n + 1 and assigns it the new user values
	then once the malloc has all the old memory and the new memory addition
	you then create a new mmap for the server
	and transfer all the information from the temp malloc to the new mmap
	*/

    // creates a copy of the users inside the server
	struct user *cpy = (struct user*)malloc(
                    sizeof(struct user) * ((*srv)->num_usr + 1));
    memcpy(cpy, *usr, sizeof(struct user) * ((*srv)->num_usr));

	//deep copies all of the information given in the parameters to create the new user
    strcpy(cpy[(*srv)->num_usr].name, usrn);
    strcpy(cpy[(*srv)->num_usr].pwrd, pwrd);
    cpy->id = (*srv)->num_usr;
	(*srv)->num_usr++;

	// truncates the users to now fit the new user size (not the copyy)
    ftruncate((*srv)->fd_usr, sizeof(struct user) * (*srv)->num_usr);
	
	//creates the new user for real 
    struct user *usr_new = mmap(NULL, sizeof(struct user) * (*srv)->num_usr,
                            PROT_READ|PROT_WRITE, MAP_SHARED, (*srv)->fd_usr, 0);

    if (usr_new == MAP_FAILED) {
        printf("Failed to map users\n");
    }

	// 
    *usr = usr_new;
    (*srv)->usr = usr_new;
    memcpy(usr_new, cpy, sizeof(struct user)*((*srv)->num_usr));
    free(cpy);

    return (*srv)->num_usr - 1;
}

void add_msg(struct server **srv, int usr, char *msg) {


    struct message *cpy = (struct message*)malloc(
                    sizeof(struct message) * ((*srv)->num_msg + 1));
    memcpy(cpy, (*srv)->msg, sizeof(struct message) * ((*srv)->num_msg));
    cpy[(*srv)->num_msg].len_msg = sizeof(msg);
    cpy[(*srv)->num_msg].id = usr;
    strcpy(cpy[(*srv)->num_msg].msg, msg);
    (*srv)->num_msg++;
    (*srv)->new_msg = (*srv)->num_msg;
    ftruncate((*srv)->fd_msg, sizeof(struct message) * (*srv)->num_msg);
    struct message *msg_new = mmap(NULL, sizeof(struct message) * (*srv)->num_usr,
                            PROT_READ|PROT_WRITE, MAP_SHARED, (*srv)->fd_msg, 0);

    if (msg_new == MAP_FAILED) {
        printf("Failed to map messages\n");
    }
    (*srv)->msg = msg_new;
    memcpy(msg_new, cpy, sizeof(struct message)*((*srv)->num_msg));
    free(cpy);
}

void print_all(struct server *srv) {
    for (int i = 0; i < srv->num_msg ; i++) {
        printf("%s: %s\n", srv->usr[srv->msg[i].id].name ,srv->msg[i].msg);
    }
}

int print_new_message(struct server *srv, int old, int id) {
    if (srv->num_msg - old > 0) {
        for (int i = old; i < srv->num_msg ; i++) {
            if (srv->msg[i].id != id) {
                printf("%s: %s", srv->usr[srv->msg[i].id].name ,srv->msg[i].msg);
                //printf("%s\n", srv->msg[i].msg);
            }
        }
    }
    return srv->num_msg;
}
