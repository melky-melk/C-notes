#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#include "q5_common.h"

#define BUF_LEN 256

const struct account init_accounts[] = {
    {
        .name = {'h', 'a', 'r', 'r', 'y', 0},
        .cardno = 12345678,
        .pin = 1234,
        .balance = 12000,
    },
    {
        .name = {'j', 'a', 'm', 'i', 'e', 0},
        .cardno = 12345679,
        .pin = 2341,
        .balance = 17000,
    },
    {
        .name = {'c', 'l', 'a', 'r', 'a', 0},
        .cardno = 12345688,
        .pin = 3412,
        .balance = 9000,
    },
    {
        .name = {'a', 'l', 'i', 'c', 'e', 0},
        .cardno = 12345689,
        .pin = 4123,
        .balance = 8000,
    }};

int main() {
    struct bank init_bank = {.num_acc = 4};

    memcpy(init_bank.accounts, init_accounts, sizeof(init_accounts));

    int fd = shm_open("bank_data_TOP_SECRET", O_RDWR | O_CREAT, 0777);
    if (fd < 0) {
        perror("shm_open");
    }

    ftruncate(fd, sizeof(init_bank));

    void* bank_data = mmap(NULL, sizeof(init_bank), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (bank_data == MAP_FAILED) {
        perror("mmap failed");
        return 0;
    }

    memcpy(bank_data, &init_bank, sizeof(init_bank));

    // block
    getchar();

    munmap(bank_data, sizeof(init_bank));
    close(fd);
    shm_unlink("bank_data_TOP_SECRET");
    return 0;
}