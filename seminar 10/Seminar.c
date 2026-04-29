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

struct Nod {
	struct Nod* stanga;
	struct Nod* dreapta;
	Masina info;
};
typedef struct Nod Nod;

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

void adaugaMasinaInArbore(Nod** radacina, Masina masinaNoua) {
	if (*radacina == NULL) {
		Nod* nou = malloc(sizeof(Nod));
		nou->info = masinaNoua;
		nou->dreapta = NULL;
		nou->stanga = NULL;
		*radacina = nou;
		return; //pus ca sa intrerupa
	}

	if (masinaNoua.id < (*radacina)->info.id) {
		adaugaMasinaInArbore(&(*radacina)->stanga, masinaNoua);
	}
	else {
			adaugaMasinaInArbore(&(*radacina)->dreapta, masinaNoua);
	}
}

Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* radacina = NULL;

	while (!feof(f)) {
		adaugaMasinaInArbore(&radacina, citireMasinaDinFisier(f));
	}
	fclose(f);
	return radacina;
}

void afisareMasiniDinArbore(Nod* radacina) {		//parcurgeri: stanga-radacina-dreapta, stanga-dreapta-radacina, radacina-stanga-dreapta  de fiecare data stanga e inainte de dreapta!!!!!!!!
													//				in ordine					pre ordine				post ordine
	if (radacina != NULL) {
		afisareMasiniDinArbore(radacina->stanga);
		afisareMasina(radacina->info);
		afisareMasiniDinArbore(radacina->dreapta);
	}
	
}

void afisareMasinaDinArborePostOrdine(Nod* radacina) {
	if (radacina) {
		afisareMasinaDinArborePostOrdine(radacina->stanga);
		afisareMasinaDinArborePostOrdine(radacina->dreapta);
		afisareMasina(radacina->info);
	}
}

void dezalocareArboreDeMasini(Nod** radacina) {
	if (*radacina) {
		dezalocareArboreDeMasini(&((*radacina)->stanga));
		dezalocareArboreDeMasini(&((*radacina)->dreapta));

		free((*radacina)->info.model);
		free((*radacina)->info.numeSofer);
		free(*radacina);

		*radacina = NULL;
	}
}

Masina getMasinaByID(Nod* radacina, int id) {
	Masina m;

	if (radacina) {
		if (radacina->info.id == id) {
			m = radacina->info;

			m.model = malloc(strlen(radacina->info.model) + 1);
			strcpy(m.model, radacina->info.model);

			m.numeSofer = malloc(strlen(radacina->info.numeSofer) + 1);
			strcpy(m.numeSofer, radacina->info.numeSofer);

			return m;
		}
		else {
			if (radacina->info.id < id) {
				m = getMasinaByID(radacina->dreapta, id);
			}
			else {
				m = getMasinaByID(radacina->stanga, id);
			}
		}
	}
	else {
		m.id = -1;
	}
	return m;
}

int determinaNumarNoduri(Nod* radacina) {
	if (radacina) {
		int nrNoduriS = determinaNumarNoduri((radacina->stanga));
		int nrNoduriD = determinaNumarNoduri((radacina->dreapta));
		return 1 + nrNoduriD + nrNoduriS;
	}
	return 0;
}

int calculeazaInaltimeArbore(Nod* radacina) {
	if (radacina == NULL) 
		return -1;
	else {
		return 1 + max(calculeazaInaltimeArbore(radacina->stanga), calculeazaInaltimeArbore(radacina->dreapta));
	}
}

float calculeazaPretTotal(Nod* radacina) {
	if (radacina == NULL)
		return 0;
	else {
		float Stanga = calculeazaPretTotal(radacina->stanga);
		float Dreapta = calculeazaPretTotal(radacina->dreapta);
		return radacina->info.pret + Stanga + Dreapta;
	}
}

float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	return 0;
}

int main() {
	Nod* arbore = citireArboreDeMasiniDinFisier("masini_arbore.txt");

	afisareMasiniDinArbore(arbore);

	afisareMasina(getMasinaByID(arbore,5));

	printf("\n%d", determinaNumarNoduri(arbore));

	printf("\n %d",calculeazaInaltimeArbore(arbore));

	printf("\n %5.2f", calculeazaPretTotal(arbore));

	dezalocareArboreDeMasini(arbore);
	return 0;
}