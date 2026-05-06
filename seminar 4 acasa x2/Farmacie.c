#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct medicament {
	int id;
	char* denumire;
	char* producator;
	float gramaj;
	int stoc;
	unsigned char reteta;
};
typedef struct medicament medi;

struct Nod {
	medi medicament;
	struct Nod* next;
};
typedef struct Nod nod;

void afisareMedicament(medi m) {
	printf("\n Id: %d", m.id);
	printf("\n Denumire: %s", m.denumire);
	printf("\n Producator: %s", m.producator);
	printf("\n Gramaj: %5.2f", m.gramaj);
	printf("\n Stoc: %d", m.stoc);
	printf("\n Reteta: %c\n", m.reteta);
}

void afisareListaMedicamente(nod* lista) {
		while (lista) {
			afisareMedicament(lista->medicament);
			lista = lista->next;
		}
}

medi citireMedicamentDinFisier(FILE* f) {
	char del[3] = ",\n";
	char linie[100];
	fgets(linie, 100, f);

	medi m;
	char* aux;

	m.id = atoi(strtok(linie, del));

	aux = strtok(NULL, del);
	m.denumire = malloc(sizeof(char) * (strlen(aux) + 1));
	strcpy(m.denumire, aux);

	aux = strtok(NULL, del);
	m.producator = malloc(sizeof(char) * (strlen(aux) + 1));
	strcpy(m.producator, aux);

	m.gramaj = atof(strtok(NULL, del));

	m.stoc = atoi(strtok(NULL, del));

	aux = strtok(NULL, del);
	m.reteta = aux[0];

	return m;
}

void* adaugareMedicamentInLista(nod** lista, medi m) {
	nod* nou = malloc(sizeof(nod));

	nou->medicament = m;
	nou->next = NULL;

	nod* aux = *lista;
	if(*lista!=NULL) {
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else {
		*lista = nou;
	}
}

void* adaugaMedicamentInListaLaInceput(nod** lista, medi m) {
	nod* nou = malloc(sizeof(nod));

	nou->medicament = m;

	nou->medicament.denumire = (char*)malloc(sizeof(char) * (strlen(m.denumire) + 1));
	strcpy(nou->medicament.denumire, m.denumire);

	nou->medicament.producator = (char*)malloc(sizeof(char) * (strlen(m.producator) + 1));
	strcpy(nou->medicament.producator, m.producator);

	nou->next = *lista;

	*lista = nou;
}

nod* citireListaDinFisier(const char* numefisier) {
	FILE* f = fopen(numefisier, "r");

	nod* lista;

	while (!feof(f)) {
		adaugareMedicamentInLista(&lista,citireMedicamentDinFisier(f));
	}

	fclose(f);
	return lista ;
}

void dezalocareLista(nod** lista) {	//pun ** pentru ca vreau sa modific lista in cadrul functiei
	nod* cap = *lista;
	nod* next = NULL;

	while (cap != NULL) {
		next = cap->next;
		free(cap->medicament.denumire);
		free(cap->medicament.producator);
		free(cap);
		cap = next;
	}
	*lista = NULL;
}

//void stergereMedicament(nod** lista, char tipReteta) {
//	nod* curent = *lista;
//	nod* prev = NULL;
//
//	while (curent != NULL) {
//		if (curent->medicament.reteta == tipReteta) {
//			prev->next = curent->next;
//		}
//		else {
//			*lista = curent->next;
//		}
//	}
//}

int main() {
	nod* lista = NULL;

	lista = citireListaDinFisier("Farmacie.txt");
	afisareListaMedicamente(lista);

	dezalocareLista(&lista);

	return 0;
}