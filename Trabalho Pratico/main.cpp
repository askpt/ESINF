#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <math.h>
#include <iomanip>
using namespace std;

#include "Robot.h"
#include "Posto.h"
#include "Armazem.h"
#include "Automatico.h"
#include "Transporte.h"
#include "Matriz.h"
#include "Queue.h"
#include "Lista.h"
#include "Fabrica.h"
#include "ListAdjGrafo.h"

Fabrica fab;
int op;

void menu(){
	
	string nome;
	int esc=0,opcao=0;
	do{
		cout << "1 - Leitura De Ficheiro" << endl;
		cout << "2 - Apresentar Matriz" << endl;
		cout << "3 - Apresentar Lista" << endl;
		cout << "4 - Apresentar Queue" << endl;
		cout << "5 - Apresentar Grafo" << endl;
		cout << "6 - Insere no Grafo" << endl;
		cout << "7 - Valida o Grafo" << endl;
		cout << "8 - Abastecer um posto automatico" << endl;
		cout << "9 - Abastecer um posto armazem" << endl;
		cout << "10 - Mostra estado fabrica" << endl;
		cout << "0 - Sair" << endl;
		cin >> op;
		switch(op){
		case 1:
			cout << endl;
			if(fab.getVeri() == false){
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
			if(fab.getVeri()==false){
				switch(opcao){
				case 1:
					fab.lerFicheiroArmazem();
					break;
				case 2:
					fab.lerFicheiroTransportes();
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
					fab.lerFicheiroArmazem();
					break;
				case 2:
					fab.lerFicheiroTransportes();
					break;
				case 3:
					fab.lerFicheiroRobot();
					break;
				case 4:
					fab.lerFicheiroAutomatico();
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
			cout << fab.getMatriz();
			cout << endl;
			cout << "------------------------------------------------------------------------------" << endl;
			break;
		case 3:
			cout << "Lista: "  << endl;
			cout << "Robot: " << endl;
			cout << fab.getLista();
			cout << "------------------------------------------------------------------------------" << endl;
			break;
		case 4:
			cout << "Queue: " << endl;
			cout << fab.getQueue();
			cout << "------------------------------------------------------------------------------" << endl;
			break;
		case 5:
			cout << "Grafo: " << endl;
			fab.getGrafo().escreve_grafo();
			break;
		case 6:
			fab.criaGrafo();
			break;
		case 7:
			fab.validaGrafo();
			break;
		case 8:
			fab.abasteceAuto(10,15);
			break;
		case 9:
			//fab.caminhoMinimoDistancia(1,2,50);
			break;
		case 10:
			fab.imprimeEstado();
			break;

		case 112: //TODO remover
			fab.lerFicheiroArmazem();

			fab.lerFicheiroAutomatico();
			fab.lerFicheiroRobot();					
			fab.lerFicheiroTransportes();					
			fab.criaGrafo();			
			
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
	
}