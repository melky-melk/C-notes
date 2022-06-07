#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#include "q5_common.h"

#define BUF_LEN 256

struct account* find_account_by_cardno(struct bank* bank, unsigned long cardno) {
    for (int i = 0; i < bank->num_acc; i++) {
        if (bank->accounts[i].cardno == cardno) {
            return &(bank->accounts[i]);
        }
    }
    return NULL;
}

void parse_command(char* command, char** buf) {
    char* tok = command;
    int i = 0;
    while (i < 4 && tok != NULL) {
        buf[i] = strsep(&tok, " \n");
        i++;
    }
}

int main() {
    // creates or opens new data
    int fd = shm_open("bank_data_TOP_SECRET", O_RDWR, 0777);
    if (fd < 0) {
        perror("shm_open");
    }

	// creates the shared memory data (similar to malloc) or if the memory exists it gives a pointer to that memory
    struct bank* bank_data = mmap(NULL, sizeof(struct bank), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (bank_data == MAP_FAILED) {
        perror("mmap failed");
        return 0;
    }

    char command_buf[BUF_LEN];
    char* args_buf[4];
    while (fgets(command_buf, BUF_LEN, stdin) != 0) {
        parse_command(command_buf, args_buf);
        if (strncasecmp(args_buf[0], "BALANCE", 7) == 0) {
            unsigned long cardno = strtol(args_buf[1], NULL, 10);
            unsigned short pin = strtol(args_buf[2], NULL, 10);
            struct account* account = find_account_by_cardno(bank_data, cardno);
            if (account == NULL) {
                puts("Couldn't find account.");
                continue;
            }
            if (pin == account->pin) {
                printf("Your balance is %lu.\n", account->balance);
            } else {
                puts("Bad pin.");
            }
        }
    }

    munmap(bank_data, sizeof(struct bank));
    close(fd);
    return 0;
}