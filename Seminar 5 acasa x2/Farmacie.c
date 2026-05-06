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
	medi info;
	struct Nod* next;
	struct Nod* prev;
};
typedef struct Nod Nod;

struct ListaDubla {
	Nod* prim;
	Nod* ultim;
};
typedef struct ListaDubla ListaDubla;

medi citireMedicamentDinFisier(FILE* f) {
	char linie[100];
	char del[3] = ",\n";
	fgets(linie, 100, del);

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
	m.id = aux[0];

	return m;
}

void adaugaMedicamentInListaLaFinal(ListaDubla* lista, medi m) {
	Nod* nou = malloc(sizeof(Nod));
	nou->info = m;
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

void adaugaMedicamentInListaLaInceput(ListaDubla* lista, medi m) {
	Nod* nou = malloc(sizeof(Nod));
	nou->info = m;
	nou->next = lista->prim;
	nou->prev = NULL;

	if (lista->prim) {
		lista->prim->prev = nou;
	}
	else {
		lista->ultim = nou;
	}
	lista->prim = nou;
}

ListaDubla citireListaDinFisier(const char* numefisier) {
	FILE* f = fopen(numefisier, "r");

	if (f) {
		ListaDubla lista;
		lista.prim = NULL;
		lista.ultim = NULL;
		while (!feof(f)) {
			adaugaMedicamentInListaLaFinal(&lista, citireMedicamentDinFisier(f));
		}
		fclose(f);
		return lista;
	}
}

void afisareMedicament(medi m) {
	printf("\n Id: %d", m.id);
	printf("\n Denumire: %s", m.denumire);
	printf("\n Producator: %s", m.producator);
	printf("\n Gramaj: %5.2f", m.gramaj);
	printf("\n Stoc: %d", m.stoc);
	printf("\n Reteta: %c\n", m.reteta);
}

void afisareListaInOrdine(ListaDubla lista) {
	Nod* p = lista.prim;

	while (p) {
		afisareMedicament(p->info);
		p = p->next;
	}
}

void afisareListaInOrdineInversa(ListaDubla lista) {
	Nod* p = lista.ultim;

	while (p) {
		afisareMedicament(p->info);
		p = p->prev;
	}
}

void stergereMedicamentDinLista(ListaDubla* lista, int id) {
	Nod* p = lista->prim;

	while (p && p->info.id!=id) {
		p = p->next;
	}
	if (p) {
		if (p->prev) {
			p->prev->next = p->next;
		}
		else {
			p->prev->next = NULL;
		}
		if (p->next) {
			p->next->prev = p->prev;
		}
		else {
			p->next->prev = NULL;
		}
	}
	free(p->info.denumire);
	free(p->info.producator);
	free(p);
}

void dezalocare(ListaDubla* lista) {
	while (lista->prim && lista->prim->next) {
		free(lista->prim->info.denumire);
		free(lista->prim->info.producator);
		lista->prim = lista->prim->next;
		free(lista->prim->prev);
	}
}

int main() {
	/*ListaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;*/

	ListaDubla ld = citireListaDinFisier("Farmacie.txt");
	afisareListaInOrdine(ld);
	afisareListaInOrdineInversa(ld);

	dezalocareLDMasini(&ld);
	return 0;
}