#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<malloc.h>
#include <string.h>

struct Zbor {
	int id;
	int durata;
	char* destinatie;
	float pret;
	char poartaImbarcare;
};

struct Zbor initializare(int _id, int _durata, char* _destinatie, float _pret, char _poartaImbarcare) {
	struct Zbor z;
	z.id = _id;
	z.durata = _durata;
	z.destinatie = malloc(sizeof(char) * (strlen(_destinatie) + 1));
	strcpy(z.destinatie, _destinatie);
	z.pret = _pret;
	z.poartaImbarcare = _poartaImbarcare;
	return z;
}

void afisare(struct Zbor z) {
	printf("\nId-ul zborului este: %d", z.id);
	printf("\nDurata zborului este de %d minute", z.durata);
	printf("\nDestinatia zborului este: %s", z.destinatie);
	printf("\nPretul biletului este de %5.2f lei", z.pret);
	printf("\nPoarta de imbarcare pentru zbor este: %c", z.poartaImbarcare);
}

void afisareVector(struct Zbor* z, int nrZboruri) {
	for (int i = 0;i < nrZboruri;i++) {
		afisare(z[i]);
		printf("\n");
	}
}

void dezalocare(struct Zbor z) {
	if (z.destinatie != NULL) {
		free(z.destinatie);
	}
}

struct Zbor copiereaUnuiSingurElement(struct Zbor z) {
	return initializare(z.id,z.durata,z.destinatie,z.pret,z.poartaImbarcare);
}

struct Zbor* copiereaPrimelorNElemente(struct Zbor* z, int nrZboruriCopiate) {
	struct Zbor* aux = malloc(sizeof(struct Zbor) * nrZboruriCopiate);

	for (int i = 0;i < nrZboruriCopiate; i++) {
		aux[i] = copiereaUnuiSingurElement(z[i]);
	}
	return aux;
}

struct Zbor detPrimulElementCautat(struct Zbor* z, int nrZboruri, char* destinatie) {
	struct Zbor s;
	s.id = -1;
	s.destinatie = NULL;
	if (z != NULL) {
		for (int i = 0;i < nrZboruri;i++) {
			if (strcmp(z[i].destinatie, destinatie)==0) {
				return z[i];
			}
		}
	}
	return s;
}

int main() {
	struct Zbor z;

	z = initializare(1, 120, "Budapesta", 250.6, 'D');
	afisare(z);

	printf("\n");

	int nrZboruri = 5;
	struct Zbor* zboruri = malloc(sizeof(struct Zbor) * nrZboruri);

	zboruri[0] = initializare(2, 100, "Roma", 260.8, 'D');
	zboruri[1] = initializare(3, 80, "Venetia", 169.9, 'B');
	zboruri[2] = initializare(4, 50, "Barcelona", 296.4, 'B');
	zboruri[3] = initializare(5, 190, "Milano", 125.4, 'G');
	zboruri[4] = initializare(6, 200, "Praga", 300.8, 'A');

	afisareVector(zboruri, nrZboruri);
	printf("\n");

	int nrZboruriDeCopiat; 

	printf("\nCate zboruri se vor copia:");
	scanf_s("%d", &nrZboruriDeCopiat);

	struct Zbor* noileZboruri = NULL;

	printf("\n------------------------Copierea primelor %d zboruri --------------------------------------------------------------------", nrZboruriDeCopiat);
	noileZboruri = copiereaPrimelorNElemente(zboruri, nrZboruriDeCopiat);

	afisareVector(noileZboruri, nrZboruriDeCopiat);

	char D[50];

	/*printf("\nSpre ce destinatie se cauta zboruri? :");
	scanf_s("%s", &D);*/

	printf("\n------------------------Zbor spre destinatia data: --------------------------------------------------------------------");
	afisare( detPrimulElementCautat(zboruri, nrZboruri, "Roma") );

	dezalocare(z);

	for (int i = 0;i < nrZboruri;i++) {
		dezalocare(zboruri[i]);
	}
	free(zboruri);

	for (int i = 0;i < nrZboruriDeCopiat;i++) {
		dezalocare(noileZboruri[i]);
	}
	free(noileZboruri);

	return 0;
}