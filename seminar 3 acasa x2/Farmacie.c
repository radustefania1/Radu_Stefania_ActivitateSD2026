#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Medicament {
	int id;
	char* denumire;
	char* producator;
	float concentratie;
	int stoc;
	unsigned char reteta;
};

typedef struct Medicament medi;

void afisareMedicament(medi m) {
	printf("\nId:%d",m.id);
	printf("\nDenumire:%s", m.denumire);
	printf("\nProducator:%s", m.producator);
	printf("\nConcentratie:%5.2f", m.concentratie);
	printf("\nStoc:%d", m.stoc);
	printf("\nReteta:%c", m.reteta);
}

void afisareVectorMedicamente(medi* medicamente, int nrMedicamente) {
	for (int i = 0;i < nrMedicamente;i++) {
		afisareMedicament(medicamente[i]);
	}
}

medi citireMedicamentDinFisier(FILE* f) {
	char linie[100];
	char del[3]=",\n";
	fgets(linie, 100, f);
	medi m;
	
	m.id = atoi(strtok(linie, del));

	char* aux = strtok(NULL, del);
	m.denumire = malloc(sizeof(char) * (strlen(aux) + 1));
	strcpy(m.denumire, aux);

	aux = strtok(NULL, del);
	m.producator = malloc(sizeof(char) * (strlen(aux) + 1));
	strcpy(m.producator, aux);

	m.concentratie = atof(strtok(NULL, del));

	m.stoc = atoi(strtok(NULL, del));

	char* aux = strtok(NULL, del);
	m.reteta = aux[0];

	return m;
}

void adaugaMedicamentInVector(medi** vector, int* nrMedicamente, medi medicament) {
	(*nrMedicamente)++;

	medi* aux = malloc(sizeof(medi) * (*nrMedicamente));

	for (int i = 0;i < (*nrMedicamente) - 1;i++) {
		aux[i] = (*vector)[i];
	}

	aux[(*nrMedicamente) - 1] = medicament;

	free(*vector);

	vector = aux;
}

medi* citireVectorDinFisier(const char* numefisier, int* nrMedicamente) {
	medi* vector;
	*nrMedicamente = 0;


}

void dezalocare(medi* m, int nrMedicamente) {
	for (int i = 0;i < nrMedicamente;i++) {
		free(m[i].denumire);
		free(m[i].producator);
	}
}

int main() {

	return 0;
}