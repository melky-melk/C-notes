#define NAME_LEN 256
#define MAX_ACC 10

struct account {
    unsigned long balance;
    unsigned long cardno;
    char name[NAME_LEN];
    unsigned short pin;
};

struct bank {
    int num_acc;
    struct account accounts[MAX_ACC];
};