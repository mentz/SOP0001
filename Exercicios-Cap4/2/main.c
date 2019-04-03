#include <stdio.h>

int contabits(int a);

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		printf("Falta o parâmetro \"<número>\"\n");
		return 1;
	}
	int numero;
	if (!sscanf(argv[1], "%d", &numero))
		printf("Houve um erro.\nVerifique se o parâmetro 1 é o único parâmetro e\nele é um número inteiro\n");
	printf("O numero %d possui %d bits em 1.\n", numero, contabits(numero));
	return 0;
}

int contabits(int a)
{
	int bits = 0;
	while (a > 0)
	{
		bits += a & 1;
		a /= 2;
	}
	return bits;
}
