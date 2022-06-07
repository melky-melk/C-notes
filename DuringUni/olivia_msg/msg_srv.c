#include "msg_fun.c"


int main() {
    int fd_srv = shm_open("/shm_srv", O_RDWR|O_CREAT, 0777);
    int fd_usr = shm_open("/shm_usr", O_RDWR|O_CREAT, 0777);
    int fd_msg = shm_open("/shm_msg", O_RDWR|O_CREAT, 0777);

    if (fd_srv == -1) {
        printf("Error creating server fd\n");
        return -1;
    }
    if (fd_usr == -1) {
        printf("Error creating user fd\n");
        return -1;
    }
    if (fd_msg == -1) {
        printf("Error creating message fd\n");
        return -1;
    }

    ftruncate(fd_srv, sizeof(struct server));
    ftruncate(fd_usr, sizeof(struct user));
    ftruncate(fd_msg, sizeof(struct message));

    // struct server *srv = (struct server*)malloc(sizeof(struct server));
    // struct user *usr = (struct user*)malloc(sizeof(struct user));
    // struct message *msg = (struct message*)malloc(sizeof(struct message));

    struct server *srv = mmap(NULL, sizeof(struct server),
                                PROT_READ|PROT_WRITE, MAP_SHARED, fd_srv, 0);
    if (srv == MAP_FAILED) {
        printf("Failed to map server\n");
        return -1;
    }
    struct user *usr = mmap(NULL, sizeof(struct user),
                                PROT_READ|PROT_WRITE, MAP_SHARED, fd_usr, 0);
    if (usr == MAP_FAILED) {
        printf("Failed to map users\n");
        return -1;
    }
    struct message *msg = mmap(NULL, sizeof(struct message),
                                PROT_READ|PROT_WRITE, MAP_SHARED, fd_msg, 0);
    if (msg == MAP_FAILED) {
        printf("Failed to map messages\n");
        return -1;
    }

    srv->num_usr = 0;
    srv->num_msg = 0;
    srv->usr = usr;
    srv->msg = msg;
    srv->fd_srv = fd_srv;
    srv->fd_usr = fd_usr;
    srv->fd_msg = fd_msg;
    srv->new_msg = 0;

    srv->usr = usr;
    srv->msg = msg;


    int lst_msg = 0;

    while (1) {
        sleep(5);
        printf("Num users: %d, Num messages: %d\n",
                                    srv->num_usr, srv->num_msg);
        srv->msg = msg;
        srv->usr = usr;
        lst_msg = print_new_message(srv, lst_msg, -10);
        //print_all(srv);
    }

    munmap(srv->usr, sizeof(struct user) * (srv->num_usr));
    munmap(srv->msg, sizeof(struct message) * (srv->num_msg));
    munmap(srv, sizeof(struct server));
    shm_unlink("/shm_srv");
    shm_unlink("/shm_usr");
    shm_unlink("/shm_msg");

    return 0;
}
