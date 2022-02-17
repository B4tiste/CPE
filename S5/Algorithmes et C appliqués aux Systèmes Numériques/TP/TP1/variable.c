#include <stdio.h>

int main()
{
    char t1;
    short t2;
    int t3;
    long int t4;
    long long int t5;
    float t6;
    double t7;
    long double t8;

    unsigned char ut1;
    unsigned short ut2;
    unsigned int ut3;
    unsigned long int ut4;
    unsigned long long int ut5;
    
    // On demande à l'utilisateur de saisir les valeurs, et on les affiche

    printf("Entrez un char : \n");
    scanf("%c",&t1);
    printf("vous avez entré : %c \n",t1);

    printf("Entrez un short : \n");
    while(getchar()!='\n');
    scanf("%hd",&t2);
    printf("vous avez entré : %hd \n",t2);

    printf("Entrez un int : \n");
    while(getchar()!='\n');
    scanf("%i",&t3);
    printf("vous avez entré : %i \n",t3);

    printf("Entrez un long int : \n");
    while(getchar()!='\n');
    scanf("%ld",&t4);
    printf("vous avez entré : %ld \n",t4);

    printf("Entrez un long long int  : \n");
    while(getchar()!='\n');
    scanf("%lld",&t5);
    printf("vous avez entré : %lld \n",t5);

    printf("Entrez un float : \n");
    while(getchar()!='\n');
    scanf("%f",&t6);
    printf("vous avez entré : %f \n",t6);

    printf("Entrez un double : \n");
    while(getchar()!='\n');
    scanf("%lg",&t7);
    printf("vous avez entré : %lg \n",t7);

    printf("Entrez un long double : \n");
    while(getchar()!='\n');
    scanf("%Lg",&t8);
    printf("vous avez entré : %Lg \n",t8);

    printf("Entrez un unsigned char : \n");
    while(getchar()!='\n');
    scanf("%c",&ut1);
    printf("vous avez entré : %c \n",ut1);

    printf("Entrez un unsigned short : \n");
    while(getchar()!='\n');
    scanf("%hu",&ut2);
    printf("vous avez entré : %hu \n",ut2);

    printf("Entrez un unsigned int : \n");
    while(getchar()!='\n');
    scanf("%u",&ut3);
    printf("vous avez entré : %u \n",ut3);

    printf("Entrez un unsigned long int : \n");
    while(getchar()!='\n');
    scanf("%lu",&ut4);
    printf("vous avez entré : %lu \n",ut4);

    printf("Entrez un  unsigned long long int  : \n");
    while(getchar()!='\n');
    scanf("%llu",&ut5);
    printf("vous avez entré : %llu \n",ut5);

    return 0;
}