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
};
typedef struct Nod Nod;

void afisareCarte(Carte carte) {
	printf("\nId: %d", carte.id);
	printf("\nTitlu: %s", carte.titlu);
	printf("\nAutor: %s", carte.autor);
	printf("\nnrPagini: %d", carte.nrPagini);
	printf("\nPret: %5.2f", carte.pret);
	printf("\nColectie: %c", carte.colectie);
	printf("\n");
}

Carte citireCarteDinFisier(FILE* f) {
	char linie[100];
	fgets(linie, 100, f);
	char del[3] = ",\n";
	Carte carte;
	char* aux;

	carte.id = atoi(strtok(linie, del));

	aux = strtok(NULL, del);
	carte.titlu = malloc(sizeof(char) * (strlen(aux)+1));
	strcpy(carte.titlu, aux);

	aux = strtok(NULL, del);
	carte.autor = malloc(sizeof(char) * (strlen(aux)+1));
	strcpy(carte.autor, aux);

	carte.nrPagini = atoi(strtok(NULL, del));

	carte.pret = atof(strtok(NULL, del));
	
	aux = strtok(NULL, del);
	carte.colectie = aux[0];

	return carte;
}

void adaugaCarteInLista(Nod** lista, Carte carteNoua) {
	Nod* nou = malloc(sizeof(Nod));  //un pointer(nou) care pointeaza spre o structura de tip nod
									//se face un nou nod si se pun in el datele cartii pe care o adaugi si apoi se face legatura intre pointer ul asta si restul listei

	nou->info = carteNoua;
	nou->next = NULL;

	Nod* aux=*lista;

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

Nod* inserareLaInceput(Carte c, Nod* urmator) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));

	nou->info = c;	//shallow copy

	nou->info.titlu = (char*)malloc(sizeof(char) * (strlen(c.titlu) + 1));	//
	strcpy(nou->info.titlu, c.titlu);										//
	nou->info.autor = (char*)malloc(sizeof(char) * (strlen(c.autor) + 1));	//  deep copy 
	strcpy(nou->info.autor, c.autor);										//

	nou->next = urmator;

	return nou;

}

void afisareListaCarti(Nod* lista) {
	while (lista != NULL) {
		afisareCarte(lista->info);
		lista = lista->next;
	}
}

 Nod* citireListaDinFisier(const char* numefisier) {
	 FILE* file = fopen(numefisier, "r");
	 Nod* lista = NULL;
	 while (!feof(file)) {
		 adaugaCarteInLista(&lista, citireCarteDinFisier(file));
	 }
	 fclose(file);
	 return lista;
}

 void dezalocare(Nod** lista) {
	 Nod* cap = *lista;
	 Nod* next = NULL;
	 while (cap!=NULL) {
		 free(cap->info.titlu);
		 free(cap->info.autor);
		 free(cap);
		 cap = next;
	 }
	 *lista = NULL;
 }

int main() {
	Nod* lista;
	Carte carte;

	//FILE* file = fopen("Carte.txt", "r");

	lista = citireListaDinFisier("Carte.txt");
	afisareListaCarti(lista);

	return 0;
}