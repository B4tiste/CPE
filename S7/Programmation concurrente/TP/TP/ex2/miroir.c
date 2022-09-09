#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	// argv[1] est une chaine de caractere à retourner à l'envers
	int tailleString = strlen(argv[1]);
	printf("%d\n", tailleString);

	for(int i = 0; i<=tailleString; i++)
	{
		printf("%c", argv[1][tailleString-i]);
	}

	printf("\n");

	return 0;
}
