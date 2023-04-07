#include "TestScurt.h"
#include <assert.h>
#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>
using namespace std;




void testAll() { //apelam fiecare functie sa vedem daca exista
	Colectie c;
	assert(c.vida() == true);
	assert(c.dim() == 0); //adaug niste elemente
	//c.afiseaza();
	c.adauga(5);
	//c.afiseaza();
	c.adauga(1);
	//c.afiseaza();
	c.adauga(10);
	//c.afiseaza();
	c.adauga(7);
	//c.afiseaza();
	c.adauga(1);
	//c.afiseaza();
	c.adauga(11);
	//c.afiseaza();
	c.adauga(-3);
	//c.afiseaza();
	assert(c.dim() == 7);
	assert(c.cauta(10) == true);
	assert(c.cauta(16) == false);
	assert(c.nrAparitii(1) == 2);
	assert(c.nrAparitii(7) == 1);
	assert(c.cauta(1) == true);
	assert(c.sterge(1) == true);
	//c.afiseaza();//cout << "ceva";
	assert(c.sterge(6) == false);
	assert(c.dim() == 6);
	assert(c.sterge(7) == true);
	//c.afiseaza();
	assert(c.sterge(11) == true);
	//cout << "ceva" << endl;
	//c.afiseaza();
	assert(c.nrAparitii(1) == 1);
	/*assert(c.sterge(-3) == true);
	c.afiseaza();*/
	//cout << "ceva" << endl;
	assert(c.nrAparitii(1) == 1);
	assert(c.sterge(-1) == false);
	assert(c.sterge(1) == true);
	//c.afiseaza();
	IteratorColectie ic = c.iterator();
	ic.prim();
	while (ic.valid()) {
		TElem e = ic.element();
		ic.urmator();
	}
}

void test_functionalitate_noua() {
	Colectie c;
	assert(c.vida() == true);
	assert(c.dim() == 0); //adaug niste elemente
	c.adauga(5);
	c.adauga(1);
	c.adauga(10);
	c.adauga(7);
	c.adauga(1);
	c.adauga(11);
	c.adauga(-3);
	IteratorColectie ic = c.iterator();
	ic.prim();
	try {
		ic.anterior();
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}
	//assert(ic.valid() == false);
	ic.prim();
	assert(ic.element() == 10);
	ic.urmator();
	ic.anterior();
	assert(ic.element() == 10);
	ic.prim();
	while (ic.valid()) {
		TElem e = ic.element();
		ic.urmator();
	}
}