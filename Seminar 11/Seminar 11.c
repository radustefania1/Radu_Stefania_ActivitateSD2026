#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

//creare structura pentru un nod dintr-un arbore binar de cautare

struct NodArbore {
	Masina info;
	struct NodArbore* left;
	struct NodArbore* right;
};
typedef struct NodArbore NodArbore;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

int calculeazaInaltimeArbore(NodArbore* radacina) {
	if (radacina) {
		return max(calculeazaInaltimeArbore(radacina->left), calculeazaInaltimeArbore(radacina->right)) + 1;
	}
	else {
		return 0;
	}
}

char calculGE(NodArbore* radacina) {
	if (radacina) {
		return(calculeazaInaltimeArbore(radacina->left) - calculeazaInaltimeArbore(radacina->right));
	}
	else {
		return 0;
	}
}

void rotireStanga(NodArbore** radacina) {
	NodArbore* aux = (*radacina)->right;
	(*radacina)->right = aux->left;
	aux->left = (*radacina);
	(*radacina) = aux;
}

void rotireDreapta(NodArbore** radacina) {
	NodArbore* aux = (*radacina)->left;
	(*radacina)->left = aux->right;
	aux->right = (*radacina);
	(*radacina) = aux;
}

void adaugaMasinaInArboreEchilibrat(NodArbore** radacina, Masina masinaNoua) {
	if (*radacina) {
		if ((*radacina)->info.id > masinaNoua.id) {
			adaugaMasinaInArboreEchilibrat(&(*radacina)->left, masinaNoua);
		}
		else {
			adaugaMasinaInArboreEchilibrat(&(*radacina)->right, masinaNoua);
		}

		int grad = calculGE((*radacina));

		if(grad == 2) {	//dezechilibru stanga
			if (calculGE((*radacina)->left) == -1) {
				rotireStanga(&(*radacina)->left);
			}
			rotireDreapta(radacina);
		}
		if (grad == -2) {
			if (calculGE(&(*radacina)->right) == 1) {
				rotireDreapta(&(*radacina)->right);
			}
			rotireStanga(radacina);
		}
	}
	else {
		NodArbore* nou = (NodArbore*)malloc(sizeof(NodArbore));
		nou->info = masinaNoua;
		nou->left = NULL;
		nou->right = NULL;
		(*radacina) = nou;
	}
}

void* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	NodArbore* radacina = NULL;
	while (!feof(f)) {
		Masina masina = citireMasinaDinFisier(f);
		adaugaMasinaInArboreEchilibrat(&radacina, masina);
	}
	fclose(f);
	return radacina;
}

void afisareMasiniDinArbore(NodArbore* radacina) {
	if (radacina) {
		afisareMasina(radacina->info);
		afisareMasiniDinArbore(radacina->left);
		afisareMasiniDinArbore(radacina->right);
	}
}

void dezalocareArboreDeMasini(NodArbore** radacina) {
	if ((*radacina)) {
		dezalocareArboreDeMasini(&(*radacina)->left);
		dezalocareArboreDeMasini(&(*radacina)->right);
		free((*radacina)->info.model);
		free((*radacina)->info.numeSofer);
		free(*radacina);
		*radacina = NULL;
	}
}

//Preluati urmatoarele functii din laboratorul precedent.
//Acestea ar trebuie sa functioneze pe noul arbore echilibrat.

Masina getMasinaByID(/*arborele de masini*/int id);

int determinaNumarNoduri(/*arborele de masini*/);

float calculeazaPretTotal(/*arbore de masini*/);

float calculeazaPretulMasinilorUnuiSofer(NodArbore* radacina, const char* numeSofer){
	float sum = 0;
	if (radacina) {
		sum += calculeazaPretTotal(radacina->left);
		sum += calculeazaPretTotal(radacina->right);
		if (strcmp(radacina->info.numeSofer, numeSofer) == 0) {
			sum += radacina->info.pret;
		}
	}
	return sum;
}

int main() {
	NodArbore* radacina = citireArboreDeMasiniDinFisier("Masini.txt");
	afisareMasiniDinArbore(radacina);
	dezalocareArboreDeMasini(&radacina);

	return 0;
}