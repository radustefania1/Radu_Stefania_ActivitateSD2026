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

//creare structura pentru un nod dintr-o lista simplu inlantuita
typedef struct Nod Nod;
struct Nod {
	Masina masina;
	Nod* next;
};

//creare structura pentru tabela de dispersie
// aceasta este un vector de liste
struct HashTable {
	int dim;
	Nod** lista;
};
typedef struct HashTable HashTable;

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

void afisareListaMasini(Nod* nod) {
	while (nod) {
		afisareMasina(nod->masina);
		nod = nod->next;
	}
}

void adaugaMasinaInLista(Nod** nod, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->masina = masinaNoua;
	nou->next = NULL;

	if (!(*nod)) {
		*nod = nou;
	}
	else {
		Nod* aux=*nod;
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
}


HashTable initializareHashTable(int dimensiune) {
	HashTable ht;
	ht.dim = dimensiune;
	ht.lista = malloc(sizeof(Nod*) * ht.dim);
	for (int i = 0;i < ht.dim;i++) {
		ht.lista[i] = NULL;
	}
	return ht;
}

int calculeazaHash(int id, int dimensiune) {
	return (id * 31) % dimensiune;  // se inmulteste cu un numar prim ca sa se micsoreze probabilitatea de coliziune
}

void inserareMasinaInTabela(HashTable ht, Masina masina) {
	int hash = calculeazaHash(masina.id, ht.dim);

	if (ht.lista[hash] == NULL) {
		adaugaMasinaInLista(&(ht.lista[hash]), masina);
			return;
	}
	Nod* nod = malloc(sizeof(Nod));
	nod->masina = masina;
	nod->next = NULL;

	ht.lista[hash] = nod;
}

HashTable citireMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	HashTable ht = initializareHashTable(5);
	while (!feof(f)) {
		Masina masina = citireMasinaDinFisier(f);
		inserareMasinaInTabela(ht, masina);
	}
	fclose(f);

	return ht;
}

void afisareTabelaDeMasini(HashTable ht) {
	for (int i = 0;i < ht.dim;i++) {
		if (ht.lista[i] != NULL) {
			printf("Clusterul %d\n", i+1);

			afisareListaMasini(ht.lista[i]);

			printf("===========================================\n");
		}
	}
}

void dezalocareTabelaDeMasini(HashTable *ht) {
	for (int i = 0;i < ht->dim;i++) {
		if (ht->lista[i]!=NULL) {
			Nod* p = ht->lista[i];
			Nod* next = NULL;

			while (p != NULL) {
				free(p->masina.model);
				free(p->masina.numeSofer);

				next = p->next;
				free(p);
				p = next;
			}
		}
	}
	free(ht->lista);
	ht->dim = 0;
	ht->lista = NULL;
}

float* calculeazaPreturiMediiPerClustere(HashTable ht, int* nrClustere) {
	int nr = 0;
	for (int i = 0; i < ht.dim; i++)
	{
		if (ht.lista[i] != NULL)
		{
			nr++;
		}
	}

	float* mediePerCluster = malloc(nr * sizeof(float));
	int j = 0;
	for (int i = 0; i < ht.dim; i++)
	{
		if (ht.lista[i] != NULL)
		{
			int nrNoduri = 0;
			float  sum = 0;

			Nod* aux = ht.lista[i];
			while (aux != NULL)
			{
				nrNoduri++;
				sum += aux->masina.pret;

				aux = aux->next;
			}

			mediePerCluster[j++] = sum / nrNoduri;
		}
	}

	return mediePerCluster;
}

Masina getMasinaById(HashTable ht, int id) {
	Masina m;
	m.id = -1;
	//cauta masina dupa valoarea atributului cheie folosit in calcularea hash-ului
	//trebuie sa modificam numele functiei 
	int hash = calculeazaHash(id, ht.dim);
	//trebuie sa mai verificam daca hash ul e intre 0 si hash
	Nod* aux = ht.lista[hash];
	while (aux != NULL)
	{
		if (aux->masina.id == id)
		{
			m = aux->masina;
			m.model = malloc((strlen(aux->masina.model) + 1) * sizeof(char));
			strcpy(m.model, aux->masina.numeSofer);

			return m;
		}
	}

	return m;
}

int main() {
	HashTable ht = citireMasiniDinFisier("Masinile.txt");
	afisareTabelaDeMasini(ht);
	afisareMasina(getMasinaById(ht, 3));
	int nrClustere;
	float* medii = calculeazaPreturiMediiPerClustere(ht, &nrClustere);
	for (int i = 0; i < nrClustere; i++)
		printf("media din clusterul %d este: %.2f", i + 1, medii[i]);
	dezalocareTabelaDeMasini(&ht);
	return 0;
}
