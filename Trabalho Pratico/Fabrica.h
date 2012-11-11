#ifndef Fabrica_
#define Fabrica_

#define MAX 1000

#include "Robot.h"
#include "Posto.h"
#include "Armazem.h"
#include "Automatico.h"
#include "Transporte.h"
#include "Matriz.h"
#include "Queue.h"
#include "Lista.h"

class Fabrica
{
private:
	Matriz m;
	Lista<Robot> ra;
	Queue<Posto*> aa;
	int numPostos;
	bool veri;

public:
	Fabrica();
	void lerFicheiroRobot();
	void lerFicheiroArmazem();
	void lerFicheiroAutomatico();
	void lerFicheiroTransportes();

	bool getVeri() const;
	Matriz getMatriz();
	Lista<Robot> getLista();
	Queue<Posto*> getQueue();

	bool operator == (const Fabrica &f) const;
	Fabrica& operator = (const Fabrica &f);
	void escreve(ostream &out) const;
};

Fabrica::Fabrica(){
	numPostos=0;
	veri=false;
}

Matriz Fabrica::getMatriz()
{
	return m;
}

Lista<Robot> Fabrica::getLista()
{
	return ra;
}

Queue<Posto*> Fabrica::getQueue()
{
	return aa;
}


bool Fabrica::getVeri()const
{
	return veri;
}

void Fabrica::lerFicheiroRobot() {	
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
	}else{
		cout << "Falhou o carregamento do ficheiro.Numero de robots em excesso!" << endl;
	}

	fx.close();
}

void Fabrica::lerFicheiroArmazem() {
	
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

	do{
		Posto *at;
		aux.retira(at);
		aa.insere(at);
	}while(aux.comprimento()>0);
	veri=true;
	fx.close();
}

void Fabrica::lerFicheiroAutomatico() {
	
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
		do{
			Posto *at;
			aux.retira(at);
			aa.insere(at);
		}while(aux.comprimento()>0);		
		cout << "Ficheiro carregado com sucesso" << endl;
	}else if(cont > pow(2,numPostos)){
		cout << "Importacao do ficheiro falhou. Postos Automaticos em demasia!" << endl;
	}else{
		cout << "Importacao do ficheiro falhou. Insuficientes Postos Automaticos!" << endl;
	}

	fx.close();
}

void Fabrica::lerFicheiroTransportes() {
	
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

Fabrica& Fabrica::operator=(const Fabrica &f)
{
	m=f.m;
	ra=f.ra;
	aa=f.aa;
	numPostos=f.numPostos;
	veri=f.veri;

	return *this;
}

//bool Fabrica::operator==(const Fabrica &f) const
//{
//	return m==f.m && ra==f.ra && aa==f.aa && numPostos==f.numPostos && veri==f.veri;
//}

void Fabrica::escreve(ostream &out) const
{
	out << "Lista de Postos" << endl;
	out << aa;
	out << "Lista de Robots" << endl;
	out << ra;
	out << "Matriz" << endl;
	out << m;
}

ostream& operator << (ostream &out, const Fabrica &f)
{
	f.escreve(out);
	return out;
}

#endif