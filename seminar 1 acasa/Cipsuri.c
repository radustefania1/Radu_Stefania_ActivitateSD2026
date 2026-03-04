#define _CRT_SECURE_NO_WARNINGS	
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Cipsuri {
	int id;
	int grame;
	char* denumire;  //* alocare dinamica 
	float pret;
	char firma;
};

struct Cipsuri initializare(int _id, int _grame, char* _denumire, float _pret, char _firma) {  
	struct Cipsuri c;
	c.id = _id;
	c.grame = _grame;
	c.denumire = malloc(strlen(_denumire) * (sizeof(char) + 1));
	strcpy(c.denumire, _denumire);
	c.pret = _pret;
	c.firma = _firma;
	return c;
};

void afisare(struct Cipsuri c) {  
	printf("Id: %d\n", c.id);
	printf("Gramaj: %d\n", c.grame);
	printf("Aroma: %s\n", c.denumire);
	printf("Pret: %5.2f\n", c.pret);
	printf("Firma: %c\n", c.firma);

	printf("\n");
}

void dezalocare(struct Cipsuri* c) {
	if (c->denumire != NULL) {
		free(c->denumire);
	}
}

//void modificareAtribut(struct Cipsuri* c) {
//
//}

int main() {
	struct Cipsuri c;

	c = initializare(1, 350, "Cu cheese", 9.2, 'L');
	afisare(c);

	dezalocare(&c);

	int numarPungiCipsuri = 5;
	struct Cipsuri* pungi;

	pungi = malloc(numarPungiCipsuri * sizeof(struct Cipsuri));

	pungi[0] = initializare(1, 250, "Paprika Max", 10, 'L');
	pungi[1] = initializare(2, 250, "Barbecue", 10, 'L');
	pungi[2] = initializare(3, 250, "Sour Cream", 10, 'P');
	pungi[3] = initializare(4, 250, "Salt", 10, 'C');
	pungi[4] = initializare(5, 250, "Nacho Cheese", 10, 'D');

	for(int i=0;i<numarPungiCipsuri;i++)
		afisare(*(pungi + 1));

	return 0;

}

