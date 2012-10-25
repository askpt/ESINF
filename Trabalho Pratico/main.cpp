#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <math.h>
using namespace std;

#include "Robot.h"
#include "Posto.h"
#include "Armazem.h"
#include "Automatico.h"
#include "Transporte.h"
#include "Matriz.h"
#include "Queue.h"
#include "Lista.h"

Matriz m(1000);
Lista<Robot> ra;
Queue<Posto*> aa;
int numPostos=0;
bool veri = false;

void lerFicheiroRobot() {	
	int i = 0;
	int cont=0;
	string linha;
	int tam = ra.comprimento()+1;
	int key,keyPosto;
	float limite,qntStock;
	Lista<Robot> auxi;

	ifstream fx;
	fx.open("FX3.csv");
	if(!fx)
		cout << "Ficheiro nao existe! " << endl;
	else{
		string *temp = new string [1000];
		while(!fx.eof()){
			getline(fx, linha, '\n');
			if(linha.size() > 0) {
				int inicio = 0;
				int pos = linha.find(',', inicio);
				temp[i] = (linha.substr(inicio, pos-inicio)); 
				if(temp[i] == ""){
					cout << "Falta o atributo Key para formar o robot!" << endl;
					//auxi.destroilista();
					fx.close();
					return;
				}else{
					key = atoi(temp[i].c_str());
					i++;
					pos++;
					inicio = pos;
					pos = linha.find(',', inicio);
					temp[i] = (linha.substr(inicio,pos-inicio));
					if(temp[i] == ""){
						cout << "Falta o atributo limite para formar o robot!" << endl;
						//auxi.destroilista();
						fx.close();
						return;
					}else{
						limite = atof(temp[i].c_str());
						i++;
						pos++;
						inicio = pos;
						pos = linha.find(',',inicio);
						temp[i] = (linha.substr(inicio, pos-inicio));
						if(temp[i] == ""){
							cout << "Falta o atributo Quantidade de Stock para formar o robot!" << endl;
							//auxi.destroilista();
							fx.close();
							return;
						}else{
							qntStock = atof(temp[i].c_str());
							i++;
							pos++;
							inicio=pos;
							pos = linha.find(',',inicio);
							temp[i] = (linha.substr(inicio,pos-inicio));
							if(temp[i] == ""){
								cout << "Falta o atributo Posicao para formar o robot!" << endl;
								//auxi.destroilista();
								fx.close();
								return;
							}else{
								keyPosto = atoi(temp[i].c_str());
								i++;
								pos++;
								Robot r(key, limite, qntStock, keyPosto);				
								auxi.insere(tam, r);			
								cont++;
							}
						}
					}
				}
			}
		}
	}
	if(cont == numPostos){
		cout << "Ficheiro Carregado Com Sucesso" << endl;
		ra = auxi;
	}else if(cont < numPostos){
		cout << "Falhou o carregamento do ficheiro. Numero de robots insuficientes!" << endl;
		//auxi.destroilista();
	}else{
		cout << "Falhou o carregamento do ficheiro.Numero de robots em excesso!" << endl;
		//auxi.destroilista();
	}

	fx.close();
}

void lerFicheiroArmazem() {
	
	int i = 0;
	Queue<Posto*> aux;
	string linha;
	int tam = ra.comprimento()+1;
	int key,keyRobot;
	float qntSeg,qntStock;

	ifstream fx;
	fx.open("FX1.csv");
	if(!fx){
		cout << "Ficheiro nao existe! " << endl;
		fx.close();
		return;
	}else{
		string *temp = new string [1000];
		while(!fx.eof()){
			getline(fx, linha, '\n');
			if(linha.size() > 0) {
				int inicio = 0;
				int pos = linha.find(',', inicio);
				if(i == 0){
					temp[i] = (linha.substr(inicio,pos-inicio));
					if(temp[i] == ""){
						cout << "Falta numeros de postos de armazem!" << endl;
						cout << "Falha no carregamento do ficheiro!" << endl;
						veri = false;
						fx.close();
						return;
					}else{
						numPostos = atoi(temp[i].c_str());
						i++;
					}
				}else{
					temp[i] = (linha.substr(inicio, pos-inicio)); 
					if(temp[i] == ""){
						cout << "Falta o atributo key para o armazem!" << endl;
						cout << "Falha no carregamento do ficheiro!" << endl;
						//aux.destroiQueue();
						veri = false;
						fx.close();
						return;
					}else{
						key = atoi(temp[i].c_str());
						i++;
						pos++;
						inicio = pos;
						pos = linha.find(',', inicio);
						temp[i] = (linha.substr(inicio,pos-inicio));
						if(temp[i] == ""){
							cout << "Falta o atributo quantidade de stock para o armazem!" << endl;
							cout << "Falha no carregamento do ficheiro!" << endl;
							//aux.destroiQueue();
							veri = false;
							fx.close();
							return;
						}else{
							qntStock = atof(temp[i].c_str());
							i++;
							pos++;
							inicio = pos;
							pos = linha.find(',',inicio);
							temp[i] = (linha.substr(inicio, pos-inicio));
							if(temp[i] == ""){
								cout << "Falta o atributo quantidade de seguranca para o armazem!" << endl;
								cout << "Falha no carregamento do ficheiro!" << endl;
								//aux.destroiQueue();
								veri = false;
								fx.close();
								return;
							}else{								
								qntSeg = atof(temp[i].c_str());
								i++;
								pos++;
								inicio=pos;
								pos = linha.find(',',inicio);
								temp[i] = (linha.substr(inicio,pos-inicio));
								if(temp[i] == ""){
									cout << "Falta o atributo key Robot para o armazem!" << endl;
									cout << "Falha no carregamento do ficheiro!" << endl;
									//aux.destroiQueue();
									veri = false;
									fx.close();
									return;
								}else{
									keyRobot = atoi(temp[i].c_str());
									i++;
									pos++;
									Armazem a(key, qntStock, qntSeg, keyRobot);				
									aux.insere(a.clone());		
								}
							}
						}
					}
				}
			}
		}
	}
	cout << "Ficheiro carregado com sucesso" << endl;
	aa = aux;
	//aux.destroiQueue();
	veri=true;
	fx.close();
}

void lerFicheiroAutomatico() {
	
	int i = 0;
	int cont=0;
	Queue<Posto*> aux;
	string linha;
	int tam = ra.comprimento()+1;
	int key;
	float qntSeg,qntStock,vel;

	ifstream fx;
	fx.open("FX2.csv");
	if(!fx)
		cout << "Ficheiro nao existe! " << endl;
	else{
		string *temp = new string [1000];
		while(!fx.eof()){
			getline(fx, linha, '\n');
			if(linha.size() > 0) {
				int inicio = 0;
				int pos = linha.find(',', inicio);
				temp[i] = (linha.substr(inicio, pos-inicio)); 
				if(temp[i] == ""){
					cout << "Falta atributo key para o posto Automatico!" << endl;
					cout << "Falha na importacao do ficheiro!" << endl;
					//aux.destroiQueue()
					fx.close();
					return;
				}else{
					key = atoi(temp[i].c_str());
					i++;
					pos++;
					inicio = pos;
					pos = linha.find(',', inicio);
					temp[i] = (linha.substr(inicio,pos-inicio));
					if(temp[i] == ""){
						cout << "Falta atributo quantidade de stock para o posto Automatico!" << endl;
						cout << "Falha na importacao do ficheiro!" << endl;
						//aux.destroiQueue()
						fx.close();
						return;
					}else{
						qntStock = atof(temp[i].c_str());
						i++;
						pos++;
						inicio = pos;
						pos = linha.find(',',inicio);
						temp[i] = (linha.substr(inicio, pos-inicio));
						if(temp[i] == ""){
							cout << "Falta atributo quantidade de seguranca para o posto Automatico!" << endl;
							cout << "Falha na importacao do ficheiro!" << endl;
							//aux.destroiQueue()
							fx.close();
							return;
						}else{
							qntSeg = atof(temp[i].c_str());
							i++;
							pos++;
							inicio=pos;
							pos = linha.find(',',inicio);
							temp[i] = (linha.substr(inicio,pos-inicio));
							if(temp[i] == ""){
								cout << "Falta atributo velocidade para o posto Automatico!" << endl;
								cout << "Falha na importacao do ficheiro!" << endl;
								//aux.destroiQueue()
								fx.close();
								return;
							}else{
								vel = atoi(temp[i].c_str());
								i++;
								pos++;
								Automatico at(key, qntStock, qntSeg, vel);				
								aux.insere(at.clone());		
								cont++;
							}
						}
					}
				}
			}
		}
	}
	if(cont == pow(2,numPostos)){
		aa = aux;
		//aux.destroiQueue();
		cout << "Ficheiro carregado com sucesso" << endl;
	}else if(cont > pow(2,numPostos)){
		cout << "Importacao do ficheiro falhou. Postos Automaticos em demasia!" << endl;
		//aux.destroiQueue();
	}else{
		cout << "Importacao do ficheiro falhou. Insuficientes Postos Automaticos!" << endl;
		//aux.destroiQueue();
	}

	fx.close();
}

void lerFicheiroTransportes() {
	
	int i = 0;
	string linha;
	Matriz aux(1000);
	int tam = ra.comprimento()+1;
	int keyAuto1,keyAuto2;
	float distMetros,tempoMinutos;

	ifstream fx;
	fx.open("FX4.csv");
	if(!fx)
		cout << "Ficheiro nao existe! " << endl;
	else{
		string *temp = new string [1000];
		while(!fx.eof()){
			getline(fx, linha, '\n');
			if(linha.size() > 0) {
				int inicio = 0;
				int pos = linha.find(',', inicio);
				temp[i] = (linha.substr(inicio, pos-inicio)); 
				if(temp[i] == ""){
					cout << "Falta o atributo Key Automatico 1 para os Transportes!" << endl;
					cout << "Falha na importacao do ficheiro!" << endl;
					fx.close();
					return;
				}else{
					keyAuto1 = atoi(temp[i].c_str());
					i++;
					pos++;
					inicio = pos;
					pos = linha.find(',', inicio);
					temp[i] = (linha.substr(inicio,pos-inicio));
					if(temp[i] == ""){
						cout << "Falta o atributo Key Automatico 2 para os Transportes!" << endl;
						cout << "Falha na importacao do ficheiro!" << endl;
						fx.close();
						return;
					}else{
						keyAuto2 = atoi(temp[i].c_str());
						i++;
						pos++;
						inicio = pos;
						pos = linha.find(',',inicio);
						temp[i] = (linha.substr(inicio, pos-inicio));
						if(temp[i] == ""){
							cout << "Falta o atributo Distancia em Metros para os Transportes!" << endl;
							cout << "Falha na importacao do ficheiro!" << endl;
							fx.close();
							return;
						}else{
							distMetros = atof(temp[i].c_str());
							i++;
							pos++;
							inicio=pos;
							pos = linha.find(',',inicio);
							temp[i] = (linha.substr(inicio,pos-inicio));
							if(temp[i] == ""){
								cout << "Falta o atributo Tempo em Minutos para os Transportes!" << endl;
								cout << "Falha na importacao do ficheiro!" << endl;
								fx.close();
								return;
							}else{
								tempoMinutos = atof(temp[i].c_str());
								i++;
								pos++;
								aux.addValor(keyAuto1, keyAuto2, distMetros, tempoMinutos);		
							}
						}
					}
				}
			}
		}
		m = aux;
		cout << "Ficheiro Carregado Com Sucesso" << endl;
	}

	fx.close();
}

void inserirLista(){

	int key,keyPosto,pos;
	float limite,qntStock; 

	cout << "Em que posicao da lista deseja inserir?"; cin >> pos; cout << endl;
	cout << "Introduza os atributos do Robot: " << endl;
	cout << "Key : "; cin >> key; cout << endl;
	cout << "Limite : "; cin >> limite; cout << endl;
	cout << "Quantidade Stock : "; cin >> qntStock; cout << endl;
	cout << "Key Posto : "; cin >> keyPosto; cout << endl;
    Robot r(key,limite,qntStock,keyPosto);
	ra.insere(pos, r);
	if (key !=0)
		cout << "Robot inserido" << endl;
}



void inserirAutomatico(){

	int key;
	float qntStock,qntSeg,vel;

	cout << "Introduza os atributos do Armazem: " << endl;
	cout << "Key : "; cin >> key; cout << endl;
	cout << "Quantidade de Stock : "; cin >> qntStock; cout << endl;
	cout << "Quantidade de Seguranca : " << endl; cin >> qntSeg; cout << endl;
	cout << "Velocidade : " << endl; cin >> vel; cout << endl;
	Automatico at(key,qntStock,qntSeg,vel);
	aa.insere(at.clone());
	
	cout << "Posto Automatico inserido" << endl;
}

void inserirArmazem(){
	
	int key, keyRobot;
	float qntStock,qntSeg;

	cout << "Introduza os atributos do Armazem: " << endl;
	cout << "Key : "; cin >> key; cout << endl;
	cout << "Quantidade de Stock : "; cin >> qntStock; cout << endl;
	cout << "Quantidade de Seguranca : " << endl; cin >> qntSeg; cout << endl;
	cout << "Key Robot : " << endl; cin >> keyRobot; cout << endl;
	Armazem a(key,qntStock,qntSeg,keyRobot);
	aa.insere(a.clone());
	cout << "Armazem inserido" << endl;
}

int op = -1;

void menu(){
	
	string nome;
	int esc=0,opcao=0;
	do{
		cout << "1 - Leitura De Ficheiro" << endl;
		cout << "2 - Apresentar Matriz" << endl;
		cout << "3 - Adicionar Robot a Lista" << endl;
		cout << "4 - Adicionar Postos a Queue" << endl;
		cout << "5 - Apresentar Lista" << endl;
		cout << "6 - Apresentar Queue" << endl;
		cout << "0 - Sair" << endl;
		cin >> op;
		switch(op){
		case 1:
			cout << endl;
			if(veri == false){
				cout << "Introduza o ficheiro que quer ler:" << endl;
				cout << "1 - Armazem" << endl;
				cout << "2 - Transportes" << endl;
				cout << "0 - Menu Anterior" << endl;
				cin >> opcao;
			}else{
				cout << "Introduza o ficheiro que quer ler:" << endl;
				cout << "1 - Armazem" << endl;
				cout << "2 - Transportes" << endl;
				cout << "3 - Robot" << endl;
				cout << "4 - Posto Automatico" << endl;
				cout << "0 - Menu Anterior" << endl;
				cin >> opcao;
			}
			if(veri==false){
				switch(opcao){
				case 1:
					lerFicheiroArmazem();
					break;
				case 2:
					lerFicheiroTransportes();
					break;
				case 0:
					menu();
					break;
				default:
					cout << "Opcao Invalida" << endl;
					break;
				}
				cout << "------------------------------------------------------------------------------" << endl;
				break;
			}else{
				switch(opcao){
				case 1:
					lerFicheiroArmazem();
					break;
				case 2:
					lerFicheiroTransportes();
					break;
				case 3:
					lerFicheiroRobot();
					break;
				case 4:
					lerFicheiroAutomatico();
					break;
				case 0:
					menu();
					break;
				default:
					cout << "Opcao Invalida" << endl;
					break;
				}
				cout << "------------------------------------------------------------------------------" << endl;
				break;
			}
		case 2:
			cout << "Matriz:" << endl;;
			cout << m;
			cout << endl;
			cout << "------------------------------------------------------------------------------" << endl;
			break;
		case 3:
			inserirLista();
			cout << "------------------------------------------------------------------------------" << endl;
			break;
		case 4:
			cout << endl;
			cout << "1 - Posto Automatico" << endl;
			cout << "2 - Armazem" << endl;
			cout << "0 - Menu Anterior" << endl;
			cin >> esc;
			switch(esc){
			case 1:
				inserirAutomatico();
				cout << "------------------------------------------------------------------------------" << endl;
				break;
			case 2:
				inserirArmazem();
				cout << "------------------------------------------------------------------------------" << endl;
				break;
			case 0:
				cout << "------------------------------------------------------------------------------" << endl;
				menu();
			default:
				cout << "Valor invalido" << endl;
				cout << "------------------------------------------------------------------------------" << endl;
				menu();
			}
			cout << "------------------------------------------------------------------------------" << endl;
			break;
		case 5:
			cout << "Lista: "  << endl;
			cout << ra;
			cout << "------------------------------------------------------------------------------" << endl;
			break;
		case 6:
			cout << "Queue: " << endl;
			cout << aa;
			cout << "------------------------------------------------------------------------------" << endl;
			break;
		case 0:
			cout << "Programa Terminado" << endl;
			exit(0);
		default:
			cout << "Valor invalido" << endl;
			cout << "------------------------------------------------------------------------------" << endl;
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
	
	//Teste Matriz
	Matriz m(4);
	m.addValor(at1.getKey(), ar1.getKey(), 12312, 1222);
	m.addValor(1,2, 111, 222);
	m.retValor(tr, at1.getKey(), ar1.getKey());
	cout << tr;
	cin.get();
	cout << m;

	//Teste queue
	Queue<Posto*> aa;	
	aa.insere(at1.clone());
	aa.insere(ar1.clone());
	cout << aa;
	cin.get();

	//Teste lista
	Lista<Robot> ra;
	ra.insere(1,r1);
	cout<<ra;
	*/
	
}