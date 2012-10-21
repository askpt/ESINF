#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

#include "Robot.h"
#include "Posto.h"
#include "Armazem.h"
#include "Automatico.h"
#include "Transporte.h"
#include "Matriz.h"
#include "Queue.h"
#include "Lista.h"

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

int op = -1;

void menu(){
	
	Matriz m(8);
	string nome;
	do{
		cout << "1 - Leitura De Ficheiro" << endl;
		cout << "2 - Apresentar Matriz" << endl;
		cout << "3 - Coisao" << endl;
		cout << "0 - Sair" << endl;
		cin >> op;
		switch(op){
		case 0:
			cout << "Programa Terminado" << endl;
			exit(0);
		case 1:
			cout << "Introduza o ficheiro que quer ler, Ex: Robot, Armazem" << endl;
			cin >> nome;
			lerFicheiro(nome);
			cout << "--------------------------------------------------------------------------------------" << endl;
			break;
		case 2:
			m.addValor(1,2,10,5);
			m.addValor(3,4,15,10);
			cout << "Matriz:" << endl;;
			cout << m;
			cout << "---------------------------------------------------------------------------------------" << endl;
			break;
		case 3:
			break;
		default:
			cout << "Valor inválido" << endl;
		}
	}while(op != 0);
}

void main(){

	menu();

	/*
	Automatico at1(123, 123, 1221, 112);
	Armazem ar1(1231, 122, 123, 123);
	Robot r1 (225, 25878, 4858, 2222);
	Transporte tr(1,2);

	//testes basicos
	cout << at1;
	cout << ar1;
	cout << r1;
	cout << tr;
	cin.get();

	//Teste leitura
	lerFicheiro("Robot");
	cin.get();	

	//Teste Matriz
	Matriz m(4);
	m.addValor(at1.getKey(), ar1.getKey(), 12312, 1222);
	m.retValor(tr, at1.getKey(), ar1.getKey());
	cout << tr;
	cin.get();

	//Teste queue
	Queue<Posto*> aa;	
	aa.insere(&at1);
	aa.insere(&ar1);
	cout << aa;
	cin.get();

	//Teste lista
	Lista<Robot> ra;
	ra.insere(1,r1);
	cout<<ra;
*/
	
}