#include <iostream>
#include <string>
#include <fstream>
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
	//Ficheiros

	int i = 0;
	int s=0;
	string linha;

	ifstream fx;
	fx.open("C:\\Users\\Joni\\Desktop\\Robot.txt");
	if(!fx)
		cout << "Ficheiro não existe! " << endl;
	else{
		string *temp = new string [1000];
		while(!fx.eof()){
			getline(fx, linha, '\n');
			if(linha.size() > 0) {
				int inicio = 0;
				int pos = linha.find(',', inicio);
				if(s == 0){
					/* Simplesmente para retirar o primeiro atributo
					do ficheiro de robots. Simplesmente troca-se esta validação pela
					validação pelo nome do ficheiro e está feito.*/
					temp[0] = (linha.substr(inicio, pos-inicio));
					s++;
					i++;
				}else{
					/*Lista Ligada */temp[i] = (linha.substr(inicio, pos-inicio)); 
					i++;
					pos++;
					inicio = pos;
					pos = linha.find(',', inicio);
					temp[i] = (linha.substr(inicio,pos-inicio));
					i++;
					pos++;
					inicio = pos;
					pos = linha.find(',',inicio);
					temp[i] = (linha.substr(inicio, pos-inicio));
					i++;
					pos++;
					inicio=pos;
					pos = linha.find(',',inicio);
					temp[i] = (linha.substr(inicio,pos-inicio));
					i++;
					pos++;
				}
			}
		}
		fx.close();
		for(int j = 0; j < i; j++){
			cout << temp[j] << endl;
		}
	}

	cin.get();

	//
	cout << at1;
	cout << ar1;
	cout << r1;
	cout << tr;
	cin.get();

	ar1.getRobots().insere(1, &r1);
	cout << ar1;

}