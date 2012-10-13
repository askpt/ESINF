#include <iostream>
#include <string>

using namespace std;

#include "Robot.h"
#include "Posto.h"
#include "Armazem.h"
#include "Automatico.h"
#include "Transporte.h"

void main(){

	Automatico at1(123, 123, 1221, 112);
	Armazem ar1(1231, 122, 123);
	Robot r1 (225, 25878, 4858, &ar1);
	Transporte tr(at1.getKey(), ar1.getKey(), 12312,1222);

	cout << at1;
	cout << ar1;
	cout << r1;
	cout << tr;
	cin.get();

}