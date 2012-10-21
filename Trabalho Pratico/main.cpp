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
					temp[i] = (linha.substr(inicio, pos-inicio)); 
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

Lista<Robot> ra;

void inserirLista(){

	int key,keyPosto,pos;
	float limite,qntStock; 

	cout << "Em que posição da lista deseja inserir?"; cin >> pos; cout << endl;
	cout << "Introduza os atributos do Robot: " << endl;
	cout << "Key : "; cin >> key; cout << endl;
	cout << "Limite : "; cin >> limite; cout << endl;
	cout << "Quantidade Stock : "; cin >> qntStock; cout << endl;
	cout << "Key Posto : "; cin >> keyPosto; cout << endl;
    Robot r(key,limite,qntStock,keyPosto);
	ra.insere(pos,r);
	cout << "Robot inserido" << endl;
}

Queue<Posto*> aa;

void inserirAutomatico(){

	int key;
	float qntStock,qntSeg,vel;

	cout << "Introduza os atributos do Armazém: " << endl;
	cout << "Key : "; cin >> key; cout << endl;
	cout << "Quantidade de Stock : "; cin >> qntStock; cout << endl;
	cout << "Quantidade de Segurança : " << endl; cin >> qntSeg; cout << endl;
	cout << "Velocidade : " << endl; cin >> vel; cout << endl;
	Automatico a(key,qntStock,qntSeg,vel);
	aa.insere(&a);
	cout << "Posto Automático inserido" << endl;
}

void inserirArmazem(){
	
	int key, keyRobot;
	float qntStock,qntSeg;

	cout << "Introduza os atributos do Armazém: " << endl;
	cout << "Key : "; cin >> key; cout << endl;
	cout << "Quantidade de Stock : "; cin >> qntStock; cout << endl;
	cout << "Quantidade de Segurança : " << endl; cin >> qntSeg; cout << endl;
	cout << "Key Robot : " << endl; cin >> keyRobot; cout << endl;
	Armazem a(key,qntStock,qntSeg,keyRobot);
	aa.insere(&a);
	cout << "Armazém inserido" << endl;
}

int op = -1;

void menu(){
	
	Matriz m(8);
	string nome;
	int it = 0,esc=0;
	do{
		cout << "1 - Leitura De Ficheiro" << endl;
		cout << "2 - Apresentar Matriz" << endl;
		cout << "3 - Adicionar Robot à Lista" << endl;
		cout << "4 - Adicionar Postos à Queue" << endl;
		cout << "5 - Apresentar Lista" << endl;
		cout << "6 - Apresentar Queue" << endl;
		cout << "0 - Sair" << endl;
		cin >> op;
		switch(op){
		case 1:
			cout << "Introduza o ficheiro que quer ler, Ex: Robot, Armazem" << endl;
			cin >> nome;
			lerFicheiro(nome);
			cout << endl;
			cout << "------------------------------------------------------------------------------" << endl;
			break;
		case 2:
			cout << "Matriz:" << endl;;
			cout << m;
			cout << endl;
			cout << "------------------------------------------------------------------------------" << endl;
			break;
		case 3:
			inserirLista();
			break;
		case 4:
			cout << endl;
			cout << "1 - Posto Automático" << endl;
			cout << "2 - Armazém" << endl;
			cin >> esc;
			switch(esc){
			case 1:
				inserirAutomatico();
				break;
			case 2:
				inserirArmazem();
				break;
			default:
				cout << "Valor inválido" << endl;
				menu();
			}
			break;
		case 5:
			cout << "Lista: "  << endl;
			cout << ra;
			break;
		case 6:
			cout << "Queue: " << endl;
			cout << aa;
			break;
		case 0:
			cout << "Programa Terminado" << endl;
			exit(0);
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