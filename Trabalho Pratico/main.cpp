#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "Robot.h"
#include "Posto.h"
#include "Armazem.h"
#include "Automatico.h"
#include "Transporte.h"
#include "Matriz.h"

void lerFicheiro(string nome) {
	
	int i = 0;
	int s=0;
	string linha;

	ifstream fx;
	fx.open(nome);
	if(!fx)
		cout << "Ficheiro não existe! " << endl;
	else{
		string *temp = new string [1000];
		while(!fx.eof()){
			getline(fx, linha, '\n');
			if(linha.size() > 0) {
				int inicio = 0;
				int pos = linha.find(',', inicio);
				if(nome == "Robot" && s == 0){
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
}

void main(){

	Automatico at1(123, 123, 1221, 112);
	Armazem ar1(1231, 122, 123);
	Robot r1 (225, 25878, 4858, 2222);
	Transporte tr(1,2);

	cout << at1;
	cout << ar1;
	cout << r1;
	cout << tr;
	cin.get();

	lerFicheiro("Robot");
	cin.get();

	ar1.getRobots().insere(1, &r1);
	cout << ar1;

	cin.get();

	Matriz m(4);
	m.addValor(at1.getKey(), ar1.getKey(), 12312, 1222);
	m.retValor(tr, at1.getKey(), ar1.getKey());
	cout << tr;
}