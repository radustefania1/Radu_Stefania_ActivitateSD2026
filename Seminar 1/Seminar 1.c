#include<stdio.h>
#include<stdlib.h>

struct Joc {
	int id;
	int NumarJucatoriMin;
	char* Denumire;
	float Pret;
	char Rating;
};

struct Joc initializare(int _id, int _NumarJucatoriMin, char* _Denumire, float _Pret, char _Rating) {
	struct Joc s;
	s.id = 1;
	s.NumarJucatoriMin = _NumarJucatoriMin;
	s.Denumire = malloc(sizeof(char) * (strlen(_Denumire) + 1));
	strcpy(s.Denumire, _Denumire);
	s.Pret = _Pret;
	s.Rating = _Rating;
	return s;
}

void afisare(struct Joc s) {
	printf("ID: %d\n", s.id);
	printf("Nume: %s\n", s.Denumire);
	printf("Numar minim de jucatori: %d\n", s.NumarJucatoriMin);
	printf("Rating: %c\n", s.Rating);
	printf("Pret: %5.2f\n", s.Pret);
}

void modifica_Denumire(struct Joc* s, char* _den) {
	free((*s).Denumire);
	(*s).Denumire = malloc((strlen(_den) + 1) * sizeof(char));
	strcpy((*s).Denumire, _den);

}

void dezalocare(struct Joc* s) {
	if (s->denumire != NULL) {
		free(s->denumire);
	}
}

float calcPretIndividual(struct Joc s) {
	float pret;
	pret = s.Pret / s.NumarJucatoriMin;
	return pret;
}

int main() {
	struct Joc s;
	s = initializare(1, 2, "Monopoly", 120, 'A');
	afisare(s);

	modifica_Denumire(&s, "Catan");

	afisare(s);

	float pret = calcPretIndividual(s);
	printf("\npret per jucator: %5.2f\n", pret);

	int numarJocuri = 3;
	struct Joc* jocuri = malloc(sizeof(struct Joc) * numarJocuri);
	jocuri[0] = s;
	jocuri[1] = initializare(2, 2, "Catan", 60, 'A');
	jocuri[2] = initializare(2, 2, "Nu te supara frate", 50, 'B');

	afisare(*(jocuri + 1));

	dezalocare(&s);  
	return 0;
}

//un sir de caractere e salvat prin pointer la primul caracter
// -> dereferentiere +  accesare (in ordinea asta)
//[](indexare) deplasare+ dereferentiere
// . acceseaza
