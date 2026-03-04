#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;    //typedef - peste tot pe unde gaseste masina inlocuieste cu struct StructuraMasina (nu mai trebuie sa scriu cu struct, cum am lucrat in primele doua seminare)

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Numar de usi: %d\n", masina.nrUsi);
	printf("Pret: %f\n:", masina.pret);
	printf("Moel: %s\n:", masina.model);
	printf("Numele soferului: %s\n:", masina.numeSofer);
	printf("Serie: %c\n:", masina.serie);
}

void afisareVectorMasini(Masina* masini, int nrMasini) {
	for (int i = 0;i < nrMasini;i++) {
		afisareMasina(masini[i]);
	}
}

void adaugaMasinaInVector(Masina** masini, int * nrMasini, Masina masinaNoua) {
	(*nrMasini)++;
	Masina* aux = malloc(sizeof(Masina) * (*nrMasini));  // daca aveam sizeof(Masina*) aveam in fata masina** pentru ca ar fi fost pointer la pointer masina
	for (int i = 0;i < (*nrMasini) - 1;i++)//mergem pana la -1 ca l am incrementat mai sus
		aux[i] = (*masini)[i]; //putem sa facem shallow copy pt ca oricum stergem vectorul dupa
	aux[(*nrMasini) - 1] = masinaNoua;
	free(*masini);  //am facut shallow copy deci punem * ca sa nu pierdem elementele din el
	*masini = aux;
}

Masina citireMasinaFisier(FILE* file) {
	char linie[50];
	fgets(linie, 50, file);
	char del[3] = ",\n";
	Masina masina;

	masina.id = atoi(strtok(linie, del));

	masina.nrUsi = atoi(strtok(NULL, del));

	masina.pret = atof(strtok(NULL, del));

	char* model = strtok(NULL, del);
	masina.model = malloc((strlen(model) + 1) * sizeof(char));
	strcpy(masina.model, model);
	//nu dezalocam pentru ca pointerul retine o adresa din stack, deci nu trebuie sa fac free
	//stergem cu free doar elementele pentru care am dat malloc

	char* numeSofer = strtok(NULL, del);
	masina.numeSofer = malloc((strlen(numeSofer) + 1) * sizeof(char));
	strcpy(masina.numeSofer, numeSofer);

	char* serie = strtok(NULL, del);
	masina.serie = serie[0];

	return masina;
}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
	Masina* masini = NULL;
	*nrMasiniCitite = 0;
	
	FILE* file = fopen(numeFisier, "r");

	while (!feof(file)) {
		adaugaMasinaInVector(&masini, nrMasiniCitite, citireMasinaFisier(file));//nu mai pun &nrMasiniCitite pentru ca e deja pointer atunci cand e adaugat ca parametru in functia asta
	}
	fclose(file);
	return masini;
}

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {

}

int main() {

	/*FILE* file = fopen("Masini.txt", "r");
	Masina masina = citireMasinaFisier(file);
	afisareMasina(masina);*/


	Masina* masini;
	int nr = 0;
	masini=citireVectorMasiniFisier("Masini.txt", &nr);
	afisareVectorMasini(masini,nr);

	return 0;
}