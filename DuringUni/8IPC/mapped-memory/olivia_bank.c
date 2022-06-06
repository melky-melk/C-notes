// code by olivia on discord

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

struct bank {
    int num_accounts;
    struct account *accounts;
};

struct account {
    int balance;
    char name[50];
    char pin[5];

};

void open_account(struct bank **bank, char *details) {
    int acc_num = (*bank)->num_accounts;

    char name[50];
    char pin[5];
    int bal;

    strcpy(name, strtok_r(details, " ", &details));
    strcpy(pin, strtok_r(details, " ", &details));
    bal = atoi(strtok_r(details, " ", &details));

    //So when you use mmap and make a larger mapping for your processes to play with
    //it wipes all the data that was mappen and sets it all to zero.
    //far as I know there is no realloc equivalent
    //so if you are using a dynamic array you need to malloc and memcpy from the mappen
    //data to this new heap.
    struct account *temp = (struct account*)malloc(
                                sizeof(struct account)*(*bank)->num_accounts);

    memcpy(temp, (*bank)->accounts, sizeof(struct account)*(*bank)->num_accounts);

    //dunno if it matters but i unmapped the memory here too.
    munmap((*bank)->accounts, sizeof(struct account)*(*bank)->num_accounts);
    (*bank)->num_accounts++;
    (*bank)->accounts = mmap(NULL, sizeof(struct account) * (*bank)->num_accounts,
                            PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, -1, 0);

    strcpy((*bank)->accounts[acc_num].name, name);
    strcpy((*bank)->accounts[acc_num].pin, pin);
    (*bank)->accounts[acc_num].balance = bal;

    //then once you have mapped the new data you can memcpy it back onto the mapped
    if ((*bank)->num_accounts > 1) {
        memcpy((*bank)->accounts, temp, sizeof(struct account)*((*bank)->num_accounts - 1));
    }
    free(temp);
}

int get_balance(struct bank *bank, int account_num, int tries) {
    if (tries == 0) {
        return -1;
    }
    printf("Please enter PIN\n");
    char command[10];
    fgets(command, 10, stdin);
    for (int i = 0 ; i < 10 ; i++) {
        if (command[i] == '\n') {
            command[i] = '\0';
        }
    }
    if (strcmp(bank->accounts[account_num].pin, command) == 0) {
        printf("Balance: %d\n", bank->accounts[account_num].balance);
        return 0;
    } else {
        printf("Wrong PIN %d tries left.\n", --tries);
        get_balance(bank, account_num, tries);
    }
    return 1;
}

int main() {
    //This is making a pointer for a struct that points to a piece of shared memory.
    //Since the program currently uses a process tree the children will have access to
    //the pointer.

    struct bank *OliBank = mmap(NULL, sizeof(struct bank),
                            PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, -1, 0);

    struct account *shared_accounts = mmap(NULL, sizeof(struct account),
                            PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, -1, 0);

    OliBank->accounts = shared_accounts;

    printf("Welcome to OliBank.\n");

    char command[100];

    while (1) {

        fgets(command, 100, stdin);

        if (strcmp(command, "CLOSE\n") == 0) {
            printf("This bank is closed!\n");
            break;
        }

        if (strcmp(command, "OPEN\n") == 0) {
            printf("Please enter your new account NAME, PIN and initial BALANCE\n");
            fgets(command, 100, stdin);
            open_account(&OliBank, command);
        }

        if (strcmp(command, "BALANCE\n") == 0) {
            printf("Which account would you like to view the balance of?\n");
            fgets(command, 50, stdin);
            for (int i = 0 ; i < 50 ; i++) {
                if (command[i] == '\n') {
                    command[i] = '\0';
                }
            }
            for (int i = 0 ; i < OliBank->num_accounts ; i++) {
                if (strcmp(command, OliBank->accounts[i].name) == 0) {
                    if (get_balance(OliBank, i, 3) == -1);
                    break;
                }
            }
        }

        if (strcmp(command, "ALL\n") == 0) {
            printf("Please enter admin password.\n");
            fgets(command, 50, stdin);
            if (strcmp(command, "ADMIN\n") == 0) {
                if (fork() == 0) {
                    printf("My PID: %d, Bank PID: %d\n", getpid(), getppid());
                    //you can literally write to and read from the shared memory
                    //directly

                    //this will show you read.
                    printf("Displaying all %d accounts.\n", OliBank->num_accounts);
                    for (int i = 0 ; i < OliBank->num_accounts ; i++) {
                        printf("Name: %s, Acc. Num: %d Balance: %d PIN: %s\n",
                                OliBank->accounts[i].name, i,
                                OliBank->accounts[i].balance,
                                OliBank->accounts[i].pin);
                    }
                    munmap(OliBank->accounts, sizeof(struct account)*OliBank->num_accounts);
                    munmap(OliBank, sizeof(struct bank));
                    return 0;
                } else {
                    sleep(1);
                }
            }
        }
        if (strcmp(command, "1337 H4X\n") == 0) {
            //use this to test modifying data, put in your account num (index) and
            //use to add to an account.
            printf("Please enter admin password.\n");
            fgets(command, 50, stdin);
            if (strcmp(command, "ADMIN\n") == 0) {
                if (fork() == 0) {
                    printf("Hello h4x0r would you like to add to your account?\n");
                    fgets(command, 50, stdin);
                    char *leftover;
                    int acc = atoi(strtok_r(command, " ", &leftover));
                    int amnt = atoi(strtok_r(NULL, "\n", &leftover));

                    OliBank->accounts[acc].balance += amnt;
                    munmap(OliBank->accounts, sizeof(struct account)*OliBank->num_accounts);
                    munmap(OliBank, sizeof(struct bank));
                    return 0;
                } else {
                    sleep(1);
                }
            }
        }
    }

    //do this to unmap the data you put up to share.
    //however fsanitize doesnt seem to see any problems like with malloc if you dont.
    munmap(OliBank->accounts, sizeof(struct account)*OliBank->num_accounts);
    munmap(OliBank, sizeof(struct bank));

    return 0;
}