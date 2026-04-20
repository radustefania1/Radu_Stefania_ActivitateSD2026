//daca faci hashtable, sa ai grija sa fie unica(daca o fol pe aia de la seminar s ar putea sa o fol mai multe persoane, deci nu mai e unica)
//daac ai subiect cu stiva/coada sa tin minte sa tii cont de lifo(last in first out) si fifo(first in first out)

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
typedef struct StructuraMasina Masina;

//creare structura pentru Heap
//un vector de elemente, lungimea vectorului si numarul de elemente din vector
struct Heap {
	int lungime;
	int nrMasini;
	Masina* masini;
};
typedef struct Heap Heap;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
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

Heap initializareHeap(int lungime) {
	Heap heap;

	heap.lungime = lungime;
	heap.masini = malloc(lungime * sizeof(Masina));
	heap.nrMasini = 0;		//initializeaza heap-ul cu 0 elemente 

	return heap;
}

void filtreazaHeap(Heap heap, int pozitieNod) {
	if (pozitieNod >= 0 && pozitieNod < heap.nrMasini) {
		int pozS = 2 * pozitieNod + 1;						//determina formulele pentru pozitia elementelor care reprezinta nodul din stanga si nodul din dreapta
		int pozD = 2 * pozitieNod + 2;
		int pozMax = pozitieNod;

		if (pozS < heap.nrMasini && heap.masini[pozMax].pret < heap.masini[pozS].pret) {
			pozMax = pozS;
		}

		if (pozD < heap.nrMasini && heap.masini[pozMax].pret < heap.masini[pozD].pret) {
			pozMax = pozD;
		}

		if (pozMax != pozitieNod) {
			Masina aux = heap.masini[pozMax];
			heap.masini[pozMax] = heap.masini[pozitieNod];
			heap.masini[pozitieNod] = aux;

			if (pozMax < (heap.nrMasini - 2) / 2) {
				filtreazaHeap(heap, pozMax);
			}
		}
	}
}

Heap citireHeapDeMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Heap heap = initializareHeap(10);
	heap.nrMasini = 0;

	while (!feof(f)) {
		Masina m = citireMasinaDinFisier(f);
		heap.masini[heap.nrMasini] = m;			//heap.masini[heap.nrMasini++] = citireMasinaDinFisier(f); linia asta e acelasi lucru ca cele trei dint stanga ei, frac aceeasi chestie + aici ai folosit shallowcopy
		heap.nrMasini++;
	}

	fclose(f);

	for (int i = (heap.nrMasini - 2) / 2;i >= 0;i--) {
		filtreazaHeap(heap, i);
	}
	
	return heap;
}

void afisareHeap(Heap heap) {
	for (int i = 0;i < heap.nrMasini;i++) {
		afisareMasina(heap.masini[i]);
	}
}

void afiseazaHeapAscuns(Heap heap) {
	for (int i =heap.nrMasini;i < heap.lungime;i++) {
		afisareMasina(heap.masini[i]);
	}
}

Masina extrageMasina(Heap* heap) {
	//extrage si returneaza masina de pe prima pozitie
	//elementul extras nu il stergem...doar il ascundem
	if (heap->nrMasini > 0) {
		Masina aux = heap->masini[0];
		heap->masini[0] = heap->masini[heap->nrMasini - 1];
		heap->masini[heap->nrMasini - 1] = aux;

		heap->nrMasini--;

		for (int i = (heap->nrMasini - 2) / 2;i >= 0;i--) {
			filtreazaHeap(*heap, i);
		}

		return heap->masini[heap->nrMasini];
	}
	else {
		Masina m;
		m.id = -1;
		return m;
	}
}


void dezalocareHeap(Heap* heap) {
	//sterge toate elementele din Heap
}

int main() {
	Heap heap = citireHeapDeMasiniDinFisier("Maasini.txt");
	afisareHeap(heap);
	
	printf("\nExtrage: ");
	afisareMasina(extrageMasina(&heap));
	afisareMasina(extrageMasina(&heap));
	afisareMasina(extrageMasina(&heap));

	printf("\nHeap ascuns:");
	afiseazaHeapAscuns(heap);

	return 0;
}