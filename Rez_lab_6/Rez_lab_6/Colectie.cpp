#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>
#include <math.h>
using namespace std;

//functia care da <hashCode>-ul unui element
int hashCode(TElem elem)
{
	//complexitate thetha(1) in toate cazurile	
	return abs(elem);
}

int Colectie::dispersie(TElem elem)
{	//complexitate thetha(1) in toate cazurile
	return hashCode(elem) % nr_locatii;
}
void Colectie::actualizare_capacitate() {
	//complexitate thetha(n) in toate cazurile deoarece iteram prin toata colectia de 2 ori
	if (dim() == nr_locatii)
	{
		/*this->nr_locatii = this->nr_locatii * 2;
		Colectie copie_colectie;
		copie_colectie.nr_locatii = nr_locatii * 2;
		auto it = this->iterator();
		it.prim();
		while (it.valid())
		{
			copie_colectie.adauga(it.element());
			it.urmator();
		}
		delete(this->element);
		delete(this->urmator);
		element = new TElem[this->nr_locatii];
		urmator = new int[this->nr_locatii];
		auto it_copie = copie_colectie.iterator();
		it_copie.prim();
		while (it_copie.valid())
		{
			this->adauga(it_copie.element());
			it_copie.urmator();
		}
		actualizare_primLiber();
		copie_colectie.~Colectie();*/
		int nr_locatii_nou = nr_locatii * 2;
		TElem* elemente_vechi;
		auto it = this->iterator();
		int n = 0;
		it.prim();
		elemente_vechi = new TElem[nr_locatii_nou];
		while (it.valid())
		{
			elemente_vechi[n] = it.element();
			it.urmator();
			n++;
		}
		delete(element);
		delete(urmator);
		nr_locatii = nr_locatii_nou;
		element = new TElem[nr_locatii];
		urmator = new int[nr_locatii];
		primLiber = 0;
		for (int i = 0; i < nr_locatii; i++) {
			element[i] = NULL_TELEM;
			urmator[i] = -1;
		}
		for (int i = 0; i < n; i++)
		{
			adauga(elemente_vechi[i]);
		}
		//actualizare_primLiber();
	}
}

Colectie::Colectie() {
	/* de adaugat */
	//complexitate thetha(n) in toate cazurile deoarece iteram prin toata lista
	nr_locatii = lungime_maxima;
	element = new TElem[nr_locatii];
	urmator = new int[nr_locatii];
	for (int i = 0; i < nr_locatii; i++) {
		element[i] = NULL_TELEM;
		urmator[i] = -1;
	}
	primLiber = 0;
}

void Colectie::actualizare_primLiber()
{
	//complexitate thetha(1) in caz favorabil, daca prima locatie care contine care contine un NULL_TELEM este chiar prima din colectie
	//complexitate thetha(n) in caz defavorabil, daca prima locatie care contine care contine un NULL_TELEM este ultima din colectie
	//complexitate O(n) in caz general
	primLiber=0;
	while (primLiber < nr_locatii && element[primLiber] != NULL_TELEM)
		primLiber++;
}

void Colectie::adauga(TElem elem) {
	/* de adaugat */
	//complexitate thetha(1) in caz favorabil in care locatia in care elem se disperseaza nu este ocupata si prima
	//locatie libera este chiar urmatoarea dupa aceasta
	//complexitate thetha(n) in caz defavorabil in care colectia este plina, iar elem trebuie adaugat la finalul listei care are toate
	//elementele din colectie(de exemplu am adaugat 10 de 1(max fiind 10), iar al 10-lea 1 are complexitate la adaugare cea mai defavorabila)
	//complexitate O(n) in caz general
	actualizare_capacitate();
	int i = this->dispersie(elem);
	if (element[i] == NULL_TELEM)
	{
		element[i] = elem;
		if (i == primLiber)
			actualizare_primLiber();
		return;
	}
	int precedent = -1;
	while (i != -1)
	{
		precedent = i;
		i = urmator[i];
	}
	element[primLiber] = elem;
	urmator[precedent] = primLiber;
	actualizare_primLiber();
}

void Colectie::afiseaza() {
	//complexitate thetha(n) in toate cazurile deoarece iteram prin toata colectia
	for (int i = 0; i < nr_locatii; i++)
		cout << element[i] << " ";
	cout << endl;
	for (int i = 0; i < nr_locatii; i++)
		cout << urmator[i] << " ";
	cout << endl;
}

bool Colectie::sterge(TElem elem) {
	/* de adaugat */
	//complexitate theta(1) in cazul favorabil in care elementul de sters este pe prima locatie din colectie si 
	//nu mai are nici o alta valoare care se disperseaza in ea
	//complexitate thetha(n) in cazul defavorabil in care elementul de sters este ultimul din colectie si 
	//are o lista care contine toate valorile din colectie
	//(spre exemplu daca adaugam 10 de multiplii de 10,de la 10 la 100 intr-o colectie cu m=10. Pentru stergerea
	// elementului 10 va presupune iterarea prin lista intrepatrunsa si mutarea tuturor valorilor din colectie
	//complexitate in cazul general O(n)
	/*if (cauta(elem) == false)
		return false;*/
	int i = dispersie(elem);
	int j = -1;
	int k = 0;
	while (k < nr_locatii && j == -1)
	{
		if (urmator[k] == i)
			j = k;
		else
			k++;
	}
	while (i != -1 && element[i] != elem)
	{
		j = i;
		i = urmator[i];
	}
	if(i==-1)
		return false;
	else
	{
		bool gata = false;
		int p,pp;
		do {
			p = urmator[i];
			pp = i;
			//cout << i << " " << p << std::endl;
			/*if (dispersie(element[p]) != i)
				p = -1;*/
			while (p != -1 && dispersie(element[p]) !=i)
			{
				pp = p;
				p = urmator[p];
			}

			if (p == -1)
			{
				gata = true; //cout << "haide\n";
			}
			else {
				//cout << i << " "<<p<<std::endl;
				element[i] = element[p];
				//urmator[i] = -1;
				j = pp;
				i = p;
			}
		} while (gata==false);
		//cout << i << " " << j << endl;
		if (j != -1)// && dispersie(element[j]) == dispersie(elem))
			urmator[j] = urmator[i];
		//else urmator[j] = -1;
		element[i] = NULL_TELEM;
		urmator[i] = -1;
		if (primLiber > i)
			primLiber = i;
	}
	return true;
}


bool Colectie::cauta(TElem elem) const {
	/* de adaugat */
	////complexitate thetha(n) in toate cazruile deoarece iteram prin toata colectia si vida() are thetha(n)
	auto it = this->iterator();
	if (vida() == true)
		return false;
	it.prim();
	while (it.valid())
	{
		if (it.element() == elem)
			return true;
		it.urmator();
	}
	return false;
}

int Colectie::nrAparitii(TElem elem) const {
	/* de adaugat */
	//complexitate thetha(n) in toate cazruile deoarece iteram prin toata colectia si vida() are thetha(n)
	if (vida() == true)
		return 0;
	auto it = this->iterator();
	it.prim();
	int nr_aparitii = 0;
	while (it.valid())
	{
		if (it.element() == elem)
			nr_aparitii++;
		it.urmator();
	}
	return nr_aparitii;
	return 0;
}


int Colectie::dim() const {
	/* de adaugat */ 
	//complexitate thetha(n) in toate cazurile deoarece iteram prin toata colectia
	auto it = this->iterator();
	it.prim();
	int dimensiune = 0;
	while (it.valid())
	{
		dimensiune++;
		it.urmator();
	}
	return dimensiune;
}


bool Colectie::vida() const {
	/* de adaugat */
	//complexitate thehta(n) in toate cazurie deoarece dim() are thetha(n)
	if(dim()==0)
		return true;
	return false;
}

IteratorColectie Colectie::iterator() const {
	//complexitate thetha(1) in toate cazurile
	return  IteratorColectie(*this);
}


Colectie::~Colectie() {
	/* de adaugat */
	//complexitate thetha(1) in toate cazurile
	delete(element);
	delete(urmator);
}


