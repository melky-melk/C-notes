#include "msg_fun.c"

int main() {

	// creates mapped memory 
    int fd_srv = shm_open("/shm_srv", O_RDWR, 0777);
    int fd_usr = shm_open("/shm_usr", O_RDWR, 0777);
    int fd_msg = shm_open("/shm_msg", O_RDWR, 0777);

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

	//sets the size of the mapped reigon that other things write to
    ftruncate(fd_srv, sizeof(struct server));
    ftruncate(fd_usr, sizeof(struct user));
    ftruncate(fd_msg, sizeof(struct message));

    // struct server *srv = (struct server*)malloc(sizeof(struct server));
    // struct user *usr = (struct user*)malloc(sizeof(struct user));
    // struct message *msg = (struct message*)malloc(sizeof(struct message));

	/////////////////////////////////ALLOCATES MAPPED MEMORY////////////////////////////////
	
	//maps memory for a server to the mapped memory shm opened earlier 
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

	///////////////////////////START TAKING INPUT FROM OTHER SOURCES///////////////////////

    printf("Please enter username and password.\n");
    char command[100];
    fgets(command, 100, stdin);
    char username[50];
    char password[50];

    int usr_id = -1;
    int lst_msg = 0;

    strcpy(username, strtok(command, " "));
    strcpy(password, strtok(NULL, "\n"));

    printf("%s %s\n", username, password);
    for (int i = 0 ; i < srv->num_usr ; i++) {
        if (strcmp(username, usr[i].name) == 0) {
            if (strcmp(password, usr[i].pwrd) == 0) {
                printf("Welcome back %s\n", username);
            } else {
                printf("Wrong password.\n");
                usr_id = -2;
                break;
            }
        }
    }
    if (usr_id == -1) {
        usr_id = add_usr(&srv, &usr, username, password);
    }
    printf("Enter ':quit' to close.\n");
    if (usr_id != -2) {
        while (strcmp(command, ":quit\n") != 0) {
            fgets(command, 100, stdin);
            srv->msg = msg;
            srv->usr = usr;
            add_msg(&srv, usr_id, command);
            lst_msg = print_new_message(srv, lst_msg, usr_id);
        }
    }

	////////////////////////////////////////CLOSING EVERYTHING///////////////////////////////

    munmap(srv->usr, sizeof(struct user) * (srv->num_usr));
    munmap(srv->msg, sizeof(struct message) * (srv->num_msg));
    munmap(srv, sizeof(struct server));
    shm_unlink("/shm_srv");
    shm_unlink("/shm_usr");
    shm_unlink("/shm_msg");

    return 0;
}
