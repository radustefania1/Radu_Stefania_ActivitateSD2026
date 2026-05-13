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

//1. 
// structuri necesare
//dorim stocarea unui graf intr-o lista de liste
//astfel avem nod ListaPrincipala si NodListaSecundara
typedef struct Nod Nod;
typedef struct NodS NodS;

struct Nod {
	Masina info;
	Nod* next;
	NodS* vecini;
};


struct NodS {
	Nod* info;
	NodS* vecin;
};

//2.
//functii de inserare in liste
//si in principala si in secundara
void inserareInListaPrincipala(Nod** graf, Masina masina) {
	Nod* nou = malloc(sizeof(Nod));
	nou->next = NULL;
	nou->vecini = NULL;
	nou->info = masina;		

	if ((*graf) == NULL) {
		(*graf) = nou;
	}
	else {
		Nod* p=(*graf);
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = nou;;
	}
}

void inserareInListaSecundara(NodS** cap,Nod* vecin) {
	NodS* nou = malloc(sizeof(NodS));
	nou->next = NULL;
	nou->info = vecin;
	if ((*cap) == NULL) {
		(*cap) = nou;
	}
	else {
		NodS* p = *cap;
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = nou;
	}
}

//3.
//functie de cautarea in lista principala dupa ID
Nod* cautaNodDupaID(Nod* graf, int id) {
		while (graf && graf->info.id != id) { // e imp sa fie graf prima pentru ca invers ar putea sa apara o eroare 
			graf = graf->next;
		}
		return graf;
}

//4.
//inserare muchie
void inserareMuchie(Nod* graf, int idStart, int idStop) {
	Nod* start = cautaNodDupaID(graf,idStart);
	Nod* stop = cautaNodDupaID(graf, idStop);

	if (start && stop) {
		inserareInListaSecundara(&start->vecini, stop);	//daca era graf neorientat foloseam doar prima inserare
		inserareInListaSecundara(&stop->vecini, start); //nu fol prioritizare pt ca -> are prioritate
	}
}

void* citireNoduriMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* graf = NULL;
	while (!feof(f)) {
		inserareInListaPrincipala(&graf, citireMasinaDinFisier(f));
	}
	fclose(f);
	return graf;
}

void citireMuchiiDinFisier(Nod* graf, const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste 
	//toate id-urile de start si stop pentru fiecare muchie
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* f = fopen(numeFisier, "r");
	int start;
	int stop;
	while (!feof(f)) {
		fscanf(f, "%d %d", &start, &stop);
		inserareMuchie(graf, start, stop);
	}
	fclose(f);
}

void dezalocareNoduriGraf(void* listaPrincipala) {
	//sunt dezalocate toate masinile din graf 
	//si toate nodurile celor doua liste
}

void afiseazaVecini(Nod* graf, int id){
	Nod* nou = cautaNodDupaID(graf, id);
	NodS* aux = nou->vecini;
	while (aux) {
		afisareMasina(aux->info->info);
		aux = aux->next;
	}
}

int main() {
	Nod* graf = citireNoduriMasiniDinFisier("masini.txt");
	citireMuchiiDinFisier(graf, "muchii.txt");
	afiseazaVecini(graf, 8);
	return 0;
}