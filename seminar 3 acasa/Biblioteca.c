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

typedef struct Carte carte;

void afisareCarte(carte c) {
	printf("\nId-ul cartii este: %d", c.id);
	printf("\nTitlul cartii este: %s", c.titlu);
	printf("\nAutorul cartii este: %s", c.autor);
	printf("\nNumar pagini: %d", c.nrPagini);
	printf("\nPretul cartii a fost: %5.2f", c.pret);
	printf("\nCartea face parte din colectia: %c\n\n", c.colectie);
}

void afisareVector(carte* c,int nrCarti) {
	for (int i = 0;i < nrCarti;i++) {
		afisareCarte(c[i]);
	}
}

void adaugaCarteInVector(carte** raft, int* nrCarti, carte carteNoua) {
	(*nrCarti)++;  //incrementez numarul de carti, adica njumarul de elemente pe care vreau sa il aiba vectorul meu dupa ce mai adaug o carte

	carte* aux = malloc(sizeof(carte) * (*nrCarti)); //creez un auxiliar care are dimensiunea egala cu noul numar de carti pe crae vreau sa il am in vectorul meu(vectorul raft)

	for (int i = 0;i < (*nrCarti)-1;i++) {
		aux[i] = (*raft)[i];					//copiez tot ce se afla in vectorul initial in vectorul auxiliar
	}

	aux[(*nrCarti) - 1] = carteNoua;	//adaug cartea noua in vectorul meu auxiliar

	free(*raft);  
						// am sters degetul care arata spre locatia(adresa) vectorului raft si l am redirectionat spre adresa vectorului aux
	*raft = aux;

}

carte citireCarteDinFisier(FILE* f) {
	carte c;
	char del[3] = ",\n";
	char linie[100];
	fgets(linie, 100, f);

	c.id = atoi(strtok(linie, del));

	char* aux = strtok(NULL, del);
	c.titlu = malloc(sizeof(char) * (strlen(aux) + 1));
	strcpy(c.titlu, aux);

	aux = strtok(NULL, del);
	c.autor = malloc(sizeof(char) * (strlen(aux) + 1));
	strcpy(c.autor, aux);

	c.nrPagini = atoi(strtok(NULL, del));

	c.pret = atof(strtok(NULL, del));

	aux = strtok(NULL, del);
	c.colectie = aux[0];

	return c;
}

carte* citireVectorDinFisier(const char* numef, int* nrCarti) {
	FILE* file;
	file = fopen(numef, "r");

	carte* raft = NULL;
	*nrCarti = 0;

	while (!feof(file)) {
		carte carte = citireCarteDinFisier(file);
		adaugaCarteInVector(&raft, nrCarti, carte);
	}

	fclose(file);
	return raft;
}

void dezalocareVectorCarti(carte** raft, int* nrCarti) {
	for (int i = 0;i < (*nrCarti);i++) {
		free((*raft)[i].titlu);
		free(((*raft)[i].autor));
	}
}

int main() {
	/*FILE* file = fopen("Carte.txt", "r");

	carte carteP;
	carteP = citireCarteDinFisier(file);

	afisareCarte(carteP);*/

	carte* carti;
	int nr = 0;

	carti = citireVectorDinFisier("Carte.txt", &nr);
	afisareVector(carti,nr);

	//fclose(file);

	return 0;
}