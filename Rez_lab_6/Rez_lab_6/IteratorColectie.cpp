#include "IteratorColectie.h"
#include "Colectie.h"
#include <stdexcept>

void IteratorColectie::deplasare() {
	//complexitate thetha(1) in caz favorabil, daca urmatoarea locatie nu contine un NULL_TELEM
	//complexitate thetha(n) in caz defavorabil in care colectia este vida cu exceptia ultimului element
	//complexitate O(n) in caz general
	while ((curent < col.nr_locatii) && col.element[curent] == NULL_TELEM)
		curent++;
}

IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	/* de adaugat */
	//complexitate thetha(1) in caz favorabil in care prima locatie din colectie nu contine un NULL_TELEM
	//complexitate thetha(n) in caz defavorabil in care ultima locatie este prima care nu contine un NULL_TELEM
	//complexitate O(n) in caz general
	curent = 0;
	deplasare();
}

void IteratorColectie::anterior() {
	if (curent == 0)
		curent = col.nr_locatii+1;
	else if (curent > 0 && curent < col.nr_locatii)
	{
		curent--;
		while ((curent < col.nr_locatii && curent>=0) && col.element[curent] == NULL_TELEM)
			curent--;
	}
	if(this->valid()==false)
		throw std::exception();
}

void IteratorColectie::prim() {
	/* de adaugat */
	//complexitate thetha(1) in caz favorabil in care prima locatie din colectie nu contine un NULL_TELEM
	//complexitate thetha(n) in caz defavorabil in care ultima locatie este prima care nu contine un NULL_TELEM
	//complexitate O(n) in caz general
	curent = 0;
	deplasare();
}


void IteratorColectie::urmator() {
	/* de adaugat */
	//complexitate thetha(1) in caz favorabil in care urmatoarea locatie din colectie nu contine un NULL_TELEM
	//complexitate thetha(n) in caz defavorabil in care ultima locatie este urmatoarea care nu contine un NULL_TELEM
	//complexitate O(n) in caz general
	curent++;
	deplasare();
	/*if (col.element[curent] == -1)
		throw std::exception();*/
}


bool IteratorColectie::valid() const {
	/* de adaugat */
	//complexitate theta(1) in toate cazurile
	return curent<col.nr_locatii;
}



TElem IteratorColectie::element() const {
	/* de adaugat */
	//complexitate theta(1) in toate cazurile
	return col.element[curent];
}
