#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//secvential pentru ca primul nod retine adresa urmatorului nod
// pointerul ultimului nod se initializeaza cu null

//vector - un tablou unidimensional cu elemente de acelasi tip,  care ocupa memorie contigua
//lista - un tablou unidimensional cu elemente de acelasi tip, care nu ocupa memorie contigua si fiecare element retine adresa urmatorului

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

//creare structura pentru un nod dintr-o lista simplu inlantuita

typedef struct Nod Nod;  //puteam sa pun si struct Nod* next, dar am pus asa ca sa nu mai fie nevoie sa pun struct de fiecare data cand fol structura
struct Nod {
	Masina info;
	Nod* next;
};
typedef struct Nod Nod;  //puteam sa pun si struct Nod* next, dar am pus asa ca sa nu mai fie nevoie sa pun struct de fiecare data cand fol structura

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret= atof(strtok(NULL, sep));
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

void adaugaMasinaInLista(Nod ** lista, Masina masinaNoua) {
	Nod* nou = malloc(sizeof(Nod));  // nu mai inmulim pt ca are deja nod spatiu pentru masina si nu inmultim cu altceva pt ca avem nevoie de un singur element
									//malloc returneaza void* pentru ca returneaza un pointer la tot
	nou->info = masinaNoua;  //e ok sa facem shallow copy ca sa nu facem la final de doua ori dezalocare
	nou->next = NULL;
	//luam pointer auxiliar ca sa nu pierdem adresa initiala
	Nod* aux = *lista;
	if (*lista != NULL) {
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else {
		*lista = nou;
	}
}

void afisareListaMasini(Nod * lista) {
	while (lista != NULL) {
		afisareMasina(lista->info);
		lista = lista->next;
	}
}

void adaugaLaInceputInLista(/*lista de masini*/ Masina masinaNoua) {
	//adauga la inceputul listei o noua masina pe care o primim ca parametru
}

void* citireListaMasiniDinFisier(const char* numeFisier) {    //void* - este stramosul lui template, este un pointer la orice
															  //void nu returneaza nimic, void* returneaza un pointer
															  //puteam sa punem si nod*, facea aceeasi chestie
	FILE *file = fopen(numeFisier, "r");
	Nod* lista=NULL;
	while (!feof(file)) {
		adaugaMasinaInLista(&lista, citireMasinaDinFisier(file));
		//am facut shallow copy mai devreme, deci acum e tot shallow copy, nu mai e nevoie de dezalocare
	}
	fclose(file);
	return lista;
}

void dezalocareListaMasini(Nod** lista) {
	Nod* head = *lista;
	Nod* next = NULL;
	while (head != NULL) {
		next = head->next;
		free(head->info.model);
		free(head->info.numeSofer);
		free(head);
		head = next;
	}
	*lista = NULL;
}

float calculeazaPretMediu(Nod* lista) {
	float suma = 0;
	int nrMasini = 0;
	while (lista != NULL) {
		suma += lista->info.pret;
		nrMasini++;
		lista = lista->next;
	}

	if (nrMasini!=0) {
		return suma / nrMasini;
	}
	else {
		return 0;
	}
}

void stergeMasiniDinSeria(/*lista masini*/ char serieCautata) {
	//sterge toate masinile din lista care au seria primita ca parametru.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

float calculeazaPretulMasinilorUnuiSofer(/*lista masini*/ const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	return 0;
}

int main() {
	Nod* lista = citireListaMasiniDinFisier("Masinile.txt");
	float pmediu = 0;

	afisareListaMasini(lista);

	//dezalocareListaMasini(&lista);

	//afisareListaMasini(lista);

	pmediu = calculeazaPretMediu(lista);
	printf("Pret mediu %5.2f", pmediu);

	return 0;
}