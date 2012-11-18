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
#include "ListAdjGrafo.h"

class Fabrica
{
private:
	Matriz m;
	Lista<Robot> ra;
	Queue<Posto*> aa;
	int numPostos;
	bool veri;
	ListAdjGrafo<Posto*,Transporte> fab;
	void procura_armazem(Vertice<Posto*,Transporte>* apinicio, int *vector, bool *chega);
	void cmTempo(Vertice<Posto*,Transporte> *inicio,Vertice<Posto*,Transporte> *fim);
	int minimoVertice(int *vector, bool *processado) const;
	void mostraCaminho(int origem, int destino, const int *caminho);
	void cmDist(Vertice<Posto*,Transporte> *inicio,Vertice<Posto*,Transporte> *fim);


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
	ListAdjGrafo<Posto*,Transporte> getGrafo();

	void criaGrafo();

	Fabrica& operator = (const Fabrica &f);
	void escreve(ostream &out) const;

	void validaGrafo();
	void caminhoMinimoTempo(int inicio, int fim);
	void caminhoMinimoDistancia(int inicio, int fim);
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

ListAdjGrafo<Posto*,Transporte> Fabrica::getGrafo()
{
	return fab;
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

void Fabrica::criaGrafo()
{
	if(aa.vazia())
		cout << "Postos nao inseridos" << endl;
	else if(m.vazia())
		cout << "Distancias/tempos nao inseridos" << endl;
	else
	{
		for (int pos = 0; pos < aa.comprimento(); pos++)
		{
			Posto* tmp;
			aa.retira(tmp);
			fab.juntar_vertice(tmp->clone());
			aa.insere(tmp->clone());		
		}
		for (int x=0;x<m.getComprimento();x++)
		{
			for(int y=0;y<m.getComprimento();y++)
			{
				Transporte tmp;
				m.retValor(tmp,x,y);
				if(tmp.getDistanciametros()!=0 && tmp.getTempominutos()!=0) 
				{
					Vertice<Posto*,Transporte> *ini = fab.encvert_keyPosto(x);
					Vertice<Posto*,Transporte> *fim = fab.encvert_keyPosto(y);

					fab.juntar_ramo(tmp,ini->GetConteudo(),fim->GetConteudo());						
				}
			}		
		}
	}
}

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

void Fabrica::validaGrafo(){
	bool check=true;
	int key=0;
	if(fab.NumVert()!=0)
	{
		Vertice<Posto*,Transporte> *apvert=fab.encvert_key(1);
		int *vector=new int[fab.NumVert()+1];
		for(int i=1;i<=fab.NumVert();i++)
			vector[i]=0;
		bool *chega=new bool[fab.NumVert()+1];
		for(int i=1;i<=fab.NumVert();i++)
			chega[i]=false;

		while(apvert!=NULL && check)
		{
			Posto* teste = apvert->GetConteudo();
			if(strcmp("class Armazem",typeid(*teste).name())==0)
			{
				Armazem* tst = dynamic_cast<Armazem*>(apvert->GetConteudo());
				if(tst->getKeyRobot()<0)
				{
					check=true;
					key=tst->getKey();
				}
				chega[apvert->GetKey()]=true;
				vector[apvert->GetKey()]=1;
			}
			apvert=apvert->GetVertice();
		}
		if(!check)
		{
			cout << "Armazem " << key << " nao possui robots estacionados." << endl;
		}
		bool check=true;
		for(int i=1;i<=fab.NumVert();i++)
		{
			Vertice<Posto*,Transporte> *apvert=fab.encvert_key(i);
			Posto* teste = apvert->GetConteudo();
			if(chega[i]&&strcmp("class Armazem",typeid(*teste).name())==0)
			{
				apvert=fab.encvert_key(i);
				procura_armazem(apvert,vector,chega);
				if(!chega[i])
					check=false;
			}
		}
		if(check)
			cout << "Grafo construido corretamente!" << endl;
		else
		{
			cout << "Automatico ";
			for(int i=1;i<=fab.NumVert();i++)
			{
				Vertice<Posto*,Transporte> *apvert=fab.encvert_key(i);
				Posto* teste = apvert->GetConteudo();
				cout << teste->getKey() << ", ";
			}
			cout << "nao tem ligacao a nenhum armazem." << endl;
		}
	}else
	{
		cout << "Grafo vazio!" << endl;
	}
}

void Fabrica::procura_armazem(Vertice<Posto*,Transporte>* apinicio, int *vector, bool *chega)
{
	Ramo<Posto*,Transporte> *apramo;
	vector[apinicio->GetKey()]=1;
	apramo=apinicio->GetRamo();
	while(apramo!=NULL)
	{
		int outrovert=apramo->GetVertice()->GetKey();
		Posto* teste=apramo->GetVertice()->GetConteudo();
		if(strcmp("class Automatico",typeid(*teste).name())==0)
			chega[outrovert]=true;
		if(vector[outrovert]==0 && chega[outrovert])
			procura_armazem(apramo->GetVertice(),vector,chega);			
		apramo=apramo->GetRamo();
	}
}

void Fabrica::cmTempo(Vertice<Posto*,Transporte> *inicio,Vertice<Posto*,Transporte> *fim){
	bool *processados=new bool[fab.NumVert()+1];
	int *tempo = new int [fab.NumVert()+1];
	int *caminho= new int [fab.NumVert()+1];
	Vertice<Posto*,Transporte> *ini=inicio;
	Vertice<Posto*,Transporte> *f=fim;
	for (int i = 1; i <= fab.NumVert();++i)
	{
		processados[i]=false;
		caminho[i]=0;
		tempo[i]=9999;
	}
	int indOrg=inicio->GetKey();
	tempo[inicio->GetKey()]=0;
	while(indOrg!=-1){
		processados[indOrg]=true;
		inicio=fab.encvert_key(indOrg);
		Ramo<Posto*,Transporte>* apramo=inicio->GetRamo();
		while(apramo!=NULL){
			int indDest=apramo->GetVertice()->GetKey();
			if(!processados[indDest]&&tempo[indDest]>tempo[indOrg]+apramo->GetConteudo().getTempominutos()){
				tempo[indDest]=tempo[indOrg]+apramo->GetConteudo().getTempominutos();
				caminho[indDest]=indOrg;
			}
			apramo=apramo->GetRamo();
		}
		indOrg=minimoVertice(tempo,processados);
	}
	if(tempo[f->GetKey()]==9999){
		cout << "nao existe caminho entre " << ini->GetConteudo()->getKey() << " e " << f->GetConteudo()->getKey()<< endl;
	}else{
		cout << "Ira demorar " << tempo[f->GetKey()] << " entre " << ini->GetConteudo()->getKey() << " e " << f->GetConteudo()->getKey() << endl;
		mostraCaminho(ini->GetKey(), f->GetKey(), caminho);
		cout << endl;
	}
}

int Fabrica::minimoVertice(int *vector, bool *processado) const 
{
	int minimo=INT_MAX,indvertice=-1;
	for (int i = 1; i < fab.NumVert(); i++)
	{
		if(!processado[i]&&vector[i]<minimo)
		{
			minimo=vector[i];
			indvertice=i;
		}
	}
	return indvertice;
}

void Fabrica::mostraCaminho(int origem, int destino, const int *caminho)
{
	if(origem!=destino){
		mostraCaminho(origem,caminho[destino],caminho);
		cout << "-->";
	}
	Vertice<Posto*,Transporte>* apvert=fab.encvert_key(destino);
	cout << apvert->GetConteudo()->getKey();
}

void Fabrica::caminhoMinimoTempo(int inicio, int fim)
{
	Vertice<Posto*,Transporte> *ini=fab.encvert_keyPosto(inicio);
	Vertice<Posto*,Transporte> *f=fab.encvert_keyPosto(fim);
	if(ini==NULL || f==NULL)
		cout << "Par de vertices nao encontrados." << endl;
	else
		cmTempo(ini,f);

}

void Fabrica::cmDist(Vertice<Posto*,Transporte> *inicio,Vertice<Posto*,Transporte> *fim){
	bool *processados=new bool[fab.NumVert()+1];
	int *distancia = new int [fab.NumVert()+1];
	int *caminho= new int [fab.NumVert()+1];
	Vertice<Posto*,Transporte> *ini=inicio;
	Vertice<Posto*,Transporte> *f=fim;
	for (int i = 1; i <= fab.NumVert();++i)
	{
		processados[i]=false;
		caminho[i]=0;
		distancia[i]=9999;
	}
	int indOrg=inicio->GetKey();
	distancia[inicio->GetKey()]=0;
	while(indOrg!=-1){
		processados[indOrg]=true;
		inicio=fab.encvert_key(indOrg);
		Ramo<Posto*,Transporte>* apramo=inicio->GetRamo();
		while(apramo!=NULL){
			int indDest=apramo->GetVertice()->GetKey();
			if(!processados[indDest]&&distancia[indDest]>distancia[indOrg]+apramo->GetConteudo().getDistanciametros()){
				distancia[indDest]=distancia[indOrg]+apramo->GetConteudo().getDistanciametros();
				caminho[indDest]=indOrg;
			}
			apramo=apramo->GetRamo();
		}
		indOrg=minimoVertice(distancia,processados);
	}
	if(distancia[f->GetKey()]==9999){
		cout << "nao existe caminho entre " << ini->GetConteudo()->getKey() << " e " << f->GetConteudo()->getKey()<< endl;
	}else{
		cout << "Ira demorar " << distancia[f->GetKey()] << " entre " << ini->GetConteudo()->getKey() << " e " << f->GetConteudo()->getKey() << endl;
		mostraCaminho(ini->GetKey(), f->GetKey(), caminho);
		cout << endl;
	}
}

void Fabrica::caminhoMinimoDistancia(int inicio, int fim)
{
	Vertice<Posto*,Transporte> *ini=fab.encvert_keyPosto(inicio);
	Vertice<Posto*,Transporte> *f=fab.encvert_keyPosto(fim);
	if(ini==NULL || f==NULL)
		cout << "Par de vertices nao encontrados." << endl;
	else
		cmDist(ini,f);
}

#endif