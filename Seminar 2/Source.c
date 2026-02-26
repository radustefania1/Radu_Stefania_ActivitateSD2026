#include<stdio.h>
#include<malloc.h>


struct Film {
	int id;
	int  durata;
	char* denumire;
	float buget ;
	char varstaMinima;
};
struct Film initializare(int _id, int _durata, char* _denumire,float _buget, char _varstaMinima) {
	struct Film s;
	s.id = _id;
	s.durata = _durata;
	s.denumire = malloc((strlen(_denumire)+1)*sizeof(char));
	strcpy(s.denumire, _denumire);
	s.buget = _buget;
	s.varstaMinima = _varstaMinima;
	return s;
}

struct Film copyFilm(struct Film s) {
	return initializare(s.id,s.durata,s.denumire,s.buget,s.varstaMinima);
}

void afisare(struct Film s) {
	printf("Id: %d\n", s.id);
	printf("Titlul filmului: %s\n", s.denumire);
	printf("Durata in minute : %d\n", s.durata);
	printf("Buget: %.2f\n", s.buget);
	printf("Varsta minima: %d\n", s.varstaMinima);
}

void afisareVector(struct Film* vector, int nrElemente) {
	for (int i = 0;i < nrElemente;i++){
		afisare(vector[i]);
		printf("\n");
	}
}


struct Film* copiazaPrimeleNElemente(struct Film* vector, int nrElemente, int nrElementeCopiate) {
	struct Film* vectorNou = malloc(nrElementeCopiate * sizeof(struct Film));
	for (int i = 0;i < nrElementeCopiate;i++) {
		vectorNou[i] = copyFilm(vector[i]);
	}
	return vectorNou;
}

void dezalocare(struct Film** vector, int* nrElemente) {
	for (int i = 0; i < *nrElemente; i++) {
		free((*vector)[i].denumire);
	}
	free(*vector);
	*vector = NULL;
	*nrElemente = 0;
}

void copiazaAnumiteElemente(struct Film* vector, char nrElemente, float bugetMaxim, struct Film** vectorNou, int* dimensiune) {
	for(int i=0;i<nrElemente;i++){
		if (vector[i].buget < bugetMaxim)
			(*dimensiune)++;
	}
	*vectorNou = malloc((*dimensiune) * sizeof(struct Film));
	int k=0;
	for (int i = 0;i < nrElemente;i++) {
		if (vector[i].buget < bugetMaxim) {
			(*vectorNou)[k] = copyFilm(vector[i]);
			k++;
		}
	}
}

struct Film getPrimulElementConditionat(struct Film* vector, int nrElemente, const char* numeCautat) {
	struct Film s;
	s.id = -1;
	s.denumire = NULL;
	for(int i=0;i<nrElemente;i++){
		if (!strcmp(vector[i].denumire, numeCautat))
			return vector[i];
	}
	return s;
}
	


int main() {
	//am creat primul film si il afisez
	struct Film f = initializare(1, 120, "Star Wars", 20.6, 14);

	afisare(f);
	printf("\n");


	//se creaza un vector de filme si se afiseaaza toate filmele din vector 
	int nrFilme = 3;
	struct Film* filme = malloc(nrFilme * sizeof(struct Film));
	filme[0] = f;
	*(filme+1) = initializare(2, 180, "Dune", 16, 12);
	filme[2] = initializare(3, 150, "Home Alone", 50.4, 16);

	afisareVector(filme, nrFilme);

	//se copiaza primele 2 elemente din vectorul de filme intr-un alt vector si se afiseaza
	int nrFilmeCopiate = 2;
	struct Film* vectorNou;
	int nrElementeCopiate = 2;
	vectorNou = copiazaPrimeleNElemente(filme, nrFilme, nrFilmeCopiate);
	printf("Elemente copiate: \n");
	afisareVector(vectorNou, nrFilmeCopiate);

	dezalocare(&vectorNou, &nrElementeCopiate);
	printf("Elemente ramase dupa stergere:\n");
	afisareVector(vectorNou, nrElementeCopiate);


	struct Film* vectorFilmeIeftine;
	float prag = 50;
	int dinIeftin=0;
	copiazaAnumiteElemente(filme, nrFilme, prag, &vectorFilmeIeftine, &dinIeftin);
	afisareVector(vectorFilmeIeftine, dinIeftin);


	printf("\n ultima:\n");
	afisare(getPrimulElementConditionat(filme,nrFilme, "Dune"));

	dezAlocare(&filme, &nrFilme); 
	return 0;
}