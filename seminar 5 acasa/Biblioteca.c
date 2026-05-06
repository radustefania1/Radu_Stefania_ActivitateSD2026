#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Carte {
	int id;
	char* titlu;
	char* autor;
	int nrPagini;
	float pret;
	unsigned char colectie;
};
typedef struct Carte Carte;

struct Nod {
	Carte info;
	struct Nod* next;
	struct Nod* prev;
};
typedef struct Nod Nod;

struct ListaDubla {
	Nod* prim;
	Nod* ultim;
};
typedef struct ListaDubla ListaDubla;

Carte citireCarteDinFisier(FILE* f) {
	char del[3] = ",\n";
	char linie[100];
	fgets(linie, 100, f);

	Carte c;

	c.id = atoi(strtok(linie, del));

	char* aux;

	aux = strtok(NULL, del);
	c.titlu = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
	strcpy(c.titlu, aux);

	aux = strtok(NULL, del);
	c.autor = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
	strcpy(c.autor, aux);

	c.nrPagini = atoi(strtok(NULL, del));

	c.pret = atof(strtok(NULL, del));

	aux = strtok(NULL, del);
	c.colectie = aux[0];

	return c;
}

void adaugaCarteInListaDublaF( ListaDubla* lista, Carte c) {
	Nod* nou=malloc(sizeof(Nod));
	nou->info = c;
	nou->next = NULL;
	nou->prev = lista->ultim;

	if (lista->ultim) {
		lista->ultim->next = nou;
	}
	else {
		lista->prim = nou;
	}
	lista->ultim = nou;
}

void adaugaCarteInListaDublaI(ListaDubla* lista,Carte c){
	Nod* nou = malloc(sizeof(Nod));
	nou->info = c;
	nou->prev = NULL;
	nou->next = lista->prim;

	if (lista->prim) {
		lista->prim->prev = nou;
	}
	else{
		lista->ultim = nou;
	}
	lista->prim = nou; 
}

ListaDubla citireListaDublaDinFisier(const char* numefisier){
	FILE* f = fopen(numefisier, "r");
	ListaDubla lista;
	lista.prim = lista.ultim = NULL;

	while (!feof(f)) {
		adaugaCarteInListaDublaF(&lista, citireCarteDinFisier(f));
	}

	fclose(f);
	return lista;
}

void afisareCarte(Carte carte) {
	printf("\nId: %d", carte.id);
	printf("\nTitlu: %s", carte.titlu);
	printf("\nAutor: %s", carte.autor);
	printf("\nnrPagini: %d", carte.nrPagini);
	printf("\nPret: %5.2f", carte.pret);
	printf("\nColectie: %c", carte.colectie);
	printf("\n");
}

void afisareListaCarteInOrdine(ListaDubla lista) {
	Nod* nod = lista.prim;

	while (nod) {
		afisareCarte(nod->info);
		nod = nod->next;
	}
}

void afisareListaCarteInversa(ListaDubla lista) {
	Nod* nod = lista.ultim;

	while (nod) {
		afisareCarte(nod->info);
		nod = nod->prev;
	}
}

void stergereCarteDinLista(ListaDubla* lista, int id) {
	Nod* p = lista->prim;

	while (p && p->info.id != id) {
		p = p->next;
	}

	if (p) {
		if (p->prev) {
			p->prev->next = p->next;
		}
		else {
			lista->prim = p->next;
		}

		if (p->next) {
			p->next->prev = p->prev;
		}
		else {
			lista->ultim = p->prev;
		}
	}

	free(p->info.autor);
	free(p->info.titlu);
	free(p);
}

int main() {
	ListaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	lista = citireListaDublaDinFisier("Carte.txt");

	afisareListaCarteInOrdine(lista);
	afisareListaCarteInversa(lista);

	int id = 112;

	stergereCarteDinLista(&lista, id);

	afisareListaCarteInversa(lista);

	return 0;
}