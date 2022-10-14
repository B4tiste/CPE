#define CLE1 1
#define CLE2 2
#include "../tp4.h"

void ex1() {
    int my_semaphore;
    my_semaphore = sem_create(CLE, 0);
    printf("P2 : Sémaphore %d\n", my_semaphore);

    // J'attends de pouvoir prendre un jeton
    P(my_semaphore);

    printf("P2 : Exécute T2 quand T1 est fini\n");
    for(int i = 0; i < 3; i++) {
        printf("-- T2 : étape %d\n", i+1);
        sleep(2);
    }
    printf("T2 : FIN\n"); 
    
    sem_delete(my_semaphore);
}

void RDV2(int sem) {
    printf("P2 : Je suis en RDV\n");
    P(sem);
    printf("P2 : Je sors du RDV\n");
    exit(0);
}

void ex2() {
    int sem1, sem2;
    sem1 = sem_create(CLE1, 0);
    sem2 = sem_create(CLE2, 0);
    printf("P2 : Sem1 %d - Sem2 %d\n", sem1, sem2);

    printf("P2 : Je suis prêt pour le rdv.\n");
    V(sem1);cx

    RDV2(sem2);

    printf("P2 : FIN\n");
}

int main(int argc, char *argv[]) {
    // ex1();
    ex2();
    return 0;
}
