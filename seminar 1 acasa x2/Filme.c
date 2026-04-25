#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct film {
	int id;
	int durata;
	char* titlu;
	float buget;
	char rating;
};

struct film initializare(int _id, int _durata, char* _titlu, float _buget, char _rating) {
	struct film f;

	f.id = _id;
	f.durata = _durata;
	f.titlu = malloc(sizeof(char) * (strlen (_titlu)+1));
	strcpy(f.titlu, _titlu);
	f.buget = _buget;
	f.rating = _rating;

	return f;
}

void afisare(struct film f) {
	printf("Id-ul filumului este: %d", f.id);
	printf("\nDurata filumului este de %d minute", f.durata);
	printf("\nTitlul filumului este: %s", f.titlu);
	printf("\nBugetul filumului este: %5.2f", f.buget);
	printf("\nRating-ul filumului este: %c", f.rating);

}

void dezalocare(struct film* f){
	if (f->titlu != NULL) {
		free(f->titlu);
	}
}

void modificareId(struct film* f, int _id) {
	f->id = _id;
}

void modificareDurata(struct film* f, int _durata) {
	f->durata = _durata;
}

void modificareTitlu(struct film* f, char* _titlu) {
	free(f->titlu);
	f->titlu = malloc(sizeof(char) * (strlen(_titlu) + 1));
	strcpy(f->titlu, _titlu);
}

void modificareBuget(struct film* f, float _buget) {
	f->buget = _buget;
}

void modificareRating(struct film* f, char _rating) {
	f->rating = _rating;
}

int main() {
	struct film f;

	f = initializare(1, 180, "Billy Elliot", 23.6, 'A');
	afisare(f);

	printf("\n\n");

	modificareTitlu(&f, "Whiplash");
	afisare(f);

	printf("\n\n");

	modificareId(&f, 2);
	afisare(f);
	printf("\n\n");

	modificareBuget(&f, 203.56);
	afisare(f);
	printf("\n\n");


	dezalocare(&f);

	return 0;
}