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
#include "Abastecimento.h"

class Fabrica
{
private:
	Matriz m;
	Lista<Robot> ra;
	Queue<Posto*> aa;
	Queue<Abastecimento> abast;
	int numPostos;
	bool veri;
	int contador;
	ListAdjGrafo<Posto*,Transporte> fab;
	void procura_armazem(Vertice<Posto*,Transporte>* apinicio, int *vector, bool *chega);
	void procura_automatico(Vertice<Posto*,Transporte>* apinicio, int *vector, bool *chega, int key);
	bool cmTempo(Vertice<Posto*,Transporte> *inicio,Vertice<Posto*,Transporte> *fim, int *temp, bool print);
	int minimoVertice(int *vector, bool *processado) const;
	void mostraCaminho(int origem, int destino, const int *caminho);
	bool cmDist(Vertice<Posto*,Transporte> *inicio,Vertice<Posto*,Transporte> *fim, int *temp, bool print);
	void caminhoMinimoTempo(Vertice<Posto*,Transporte> *ini, Vertice<Posto*,Transporte> *f, float qnt, int *tempo);
	void caminhoMinimoDistancia(Vertice<Posto*,Transporte> *ini, Vertice<Posto*,Transporte> *fim, float qnt, int *distancia);
	void verificaEstado();
	void resetPosRobot();

public:
	Fabrica();
	~Fabrica();

	void lerFicheiroRobot();
	void lerFicheiroArmazem();
	void lerFicheiroAutomatico();
	void lerFicheiroTransportes();
	void lerFicheiroAbastecimento();

	bool getVeri() const;
	int getCont() const;
	Matriz getMatriz();
	Lista<Robot> getLista();
	Queue<Posto*> getQueue();
	Queue<Abastecimento> getAbastecimentos();
	ListAdjGrafo<Posto*,Transporte> getGrafo();

	void criaGrafo();

	Fabrica& operator = (const Fabrica &f);
	void escreve(ostream &out) const;

	void validaGrafo();
	void abasteceAuto(int inicio, float qnt);
	void abasteceArm(int inicio);
	void abasteceAutomatico();

	void imprimeEstado() const;
};

Fabrica::Fabrica(){
	numPostos=0;
	veri=false;
}

Fabrica::~Fabrica(){}

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

Queue<Abastecimento> Fabrica::getAbastecimentos()
{
	return abast;
}

ListAdjGrafo<Posto*,Transporte> Fabrica::getGrafo()
{
	return fab;
}


bool Fabrica::getVeri()const
{
	return veri;
}

int Fabrica::getCont()const{
	return contador;
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
		contador++;
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
	contador++;
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
		contador++;
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
		contador++;
	}

	fx.close();
}

void Fabrica::lerFicheiroAbastecimento() {	
	int i = 0;
	int cont=0;
	string linha;
	int tam = ra.comprimento()+1;
	int key;
	float qnt;
	Queue<Abastecimento> auxi;

	ifstream fx;
	fx.open("FX5.csv");
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
					cout << "Falta o atributo Key para formar o abastecimento!" << endl;
					fx.close();
					return;
				}else{
					key = atoi(temp[i].c_str());
					i++;
					pos++;
					inicio = pos;
					pos = linha.find(',',inicio);
					temp[i] = (linha.substr(inicio, pos-inicio));
					if(temp[i] == ""){
						cout << "Falta o atributo Quantidade para formar o abastecimento!" << endl;
						fx.close();
						return;
					}else{
						qnt = atof(temp[i].c_str());
						i++;
						pos++;
						Abastecimento abs(key, qnt);				
						auxi.insere(abs);			
						cont++;
					}
				}
			}
		}

	}

	if(cont == numPostos){
		cout << "Ficheiro Carregado Com Sucesso" << endl;
		abast = auxi;
	}else if(cont < numPostos){
		cout << "Falhou o carregamento do ficheiro. Numero de robots insuficientes!" << endl;
	}else{
		cout << "Falhou o carregamento do ficheiro.Numero de robots em excesso!" << endl;
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
	abast=f.abast;

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
	bool checkArma=true, checkAuto=true;
	int key=0;
	if(fab.NumVert()!=0)
	{
		Vertice<Posto*,Transporte> *apvert=fab.encvert_key(1);
		int *vectorArm=new int[fab.NumVert()+1];
		int *vectorAut=new int[fab.NumVert()+1];
		bool *chegaArm=new bool[fab.NumVert()+1];
		bool *chegaAut=new bool[fab.NumVert()+1];
		for(int i=1;i<=fab.NumVert();i++)
		{
			vectorArm[i]=0;
			vectorAut[i]=0;
			chegaArm[i]=false;
			chegaAut[i]=false;
		}

		while(apvert!=NULL && checkArma)
		{
			Posto* teste = apvert->GetConteudo();
			if(strcmp("class Armazem",typeid(*teste).name())==0)
			{
				Armazem* tst = dynamic_cast<Armazem*>(apvert->GetConteudo());
				if(tst->getKeyRobot()<0)
				{
					checkArma=true;
					key=tst->getKey();
				}
				chegaArm[apvert->GetKey()]=true;
				chegaAut[apvert->GetKey()]=true;
				vectorArm[apvert->GetKey()]=1;
			}
			apvert=apvert->GetVertice();
		}
		if(!checkArma)
		{
			cout << "Armazem " << key << " nao possui robots estacionados." << endl;
		}
		checkArma=true;
		for(int i=1;i<=fab.NumVert();i++)
		{
			Vertice<Posto*,Transporte> *apvert=fab.encvert_key(i);
			Posto* teste = apvert->GetConteudo();
			apvert=fab.encvert_key(i);
			if(chegaArm[i]&&strcmp("class Armazem",typeid(*teste).name())==0)
			{				
				procura_armazem(apvert,vectorArm,chegaArm);				
				if(!chegaArm[i])
					checkArma=false;				
			}
			if(!chegaAut[i]&&strcmp("class Automatico",typeid(*teste).name())==0)
			{
				for(int j=1;j<=fab.NumVert();j++)
					vectorAut[j]=0;
				procura_automatico(apvert,vectorAut,chegaAut, apvert->GetKey());
				if(!chegaAut[i])
					checkAuto=false;
			}
		}
		if(checkArma && checkAuto)
			cout << "Grafo construido corretamente!" << endl;
		else if(!checkArma)
		{
			cout << "Automatico ";
			for(int i=1;i<=fab.NumVert();i++)
			{
				if(!chegaArm[i])
				{
					Vertice<Posto*,Transporte> *apvert=fab.encvert_key(i);
					Posto* teste = apvert->GetConteudo();
					cout << teste->getKey() << ", ";
				}
			}
			cout << "nao tem ligacao de entrada de nenhum armazem." << endl;
		}
		else if(!checkAuto)
		{
			cout << "Automatico ";
			for(int i=1;i<=fab.NumVert();i++)
			{
				if(!chegaAut[i])
				{
					Vertice<Posto*,Transporte> *apvert=fab.encvert_key(i);
					Posto* teste = apvert->GetConteudo();
					cout << teste->getKey() << ", ";
				}
			}
			cout << "nao tem ligacao de saida para nenhum armazem." << endl;
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

void Fabrica::procura_automatico(Vertice<Posto*,Transporte>* apinicio, int *vector, bool *chega, int key)
{
	Ramo<Posto*,Transporte> *apramo;
	vector[apinicio->GetKey()]=1;
	apramo=apinicio->GetRamo();
	bool check=false;
	while(apramo!=NULL)
	{
		int outrovert=apramo->GetVertice()->GetKey();
		Posto* teste=apramo->GetVertice()->GetConteudo();
		if(strcmp("class Armazem",typeid(*teste).name())==0)
			chega[key]= true;
		if(vector[outrovert]==0 && !chega[outrovert])
			procura_automatico(apramo->GetVertice(),vector,chega,key);			
		apramo=apramo->GetRamo();
	}
}

bool Fabrica::cmTempo(Vertice<Posto*,Transporte> *inicio,Vertice<Posto*,Transporte> *fim, int *temp, bool print){
	bool *processados=new bool[fab.NumVert()+1];
	int *caminho= new int [fab.NumVert()+1];
	int *tempo = new int [fab.NumVert()+1];
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

	if(print && tempo[f->GetKey()]==9999){
		cout << "nao existe caminho entre " << ini->GetConteudo()->getKey() << " e " << f->GetConteudo()->getKey()<< endl;
		return false;
	}else if(print){
		cout << "Ira demorar " << tempo[f->GetKey()] << " entre " << ini->GetConteudo()->getKey() << " e " << f->GetConteudo()->getKey() << endl;
		mostraCaminho(ini->GetKey(), f->GetKey(), caminho);
		cout << endl;
		return true;
	}else if(!print && tempo[f->GetKey()]==9999){
		*temp=9999;
		return false;
	}else{
		*temp=tempo[f->GetKey()];
		return true;
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

void Fabrica::abasteceAuto(int inicio, float qnt)
{
	int *tempo=new int[fab.NumVert()+1];
	for(int i=1;i <=fab.NumVert();i++)
		tempo[i]=9999;

	Vertice<Posto*,Transporte> *ini=fab.encvert_keyPosto(inicio);
	if(ini==NULL){
		cout << "Par de vertices nao encontrado" << endl;
		return;
	}
	Posto *teste=ini->GetConteudo();
	if(strcmp("class Automatico",typeid(*teste).name())!=0)
		cout << "Vertice inicial nao e um posto automatico" << endl;
	else
		caminhoMinimoTempo(NULL,ini,qnt, tempo);
}


void Fabrica::caminhoMinimoTempo(Vertice<Posto*,Transporte> *ini, Vertice<Posto*,Transporte> *f, float qnt, int *tempo)
{
	Posto *testeIni;
	Robot rob;
	if(ini!=NULL)
	{	
		testeIni=ini->GetConteudo();
		if(strcmp("class Armazem",typeid(*ini->GetConteudo()).name())==0)
		{
			int key=dynamic_cast<Armazem*>(ini->GetConteudo())->getKeyRobot();
			int pos = 1;
			while (pos <= ra.comprimento())
			{
				Robot temp;
				ra.encontra(pos,temp);
				if(temp.getKey()==key)
					rob=temp;			
				pos++;
			}

		}
		cout << "Segunda Movimentacao" << endl;


	}else
	{
		int min=9999;
		for(int i=1;i<=fab.NumVert();i++){
			ini=fab.encvert_key(i);
			cmTempo(ini,f,&tempo[i],false);
		}
		ini=NULL;
		for(int i=1;i<=ra.comprimento();i++)
		{
			Robot tmp;
			ra.encontra(i,tmp);
			Vertice<Posto*,Transporte> *key=fab.encvert_keyPosto(tmp.getKeyPosto());
			if(min>tempo[key->GetKey()]&& tempo[key->GetKey()]!=0)
			{
				testeIni=key->GetConteudo();
				rob=tmp;
				min=tempo[key->GetKey()];
				ini=fab.encvert_key(key->GetKey());
			}
		}
		cout << "Primeira Movimentacao" << endl;
	}
	if(ini==NULL)
	{
		cout << "Nao existem robots disponiveis" << endl;
		return;
	}
	Posto *testeFim=f->GetConteudo();
	testeIni=ini->GetConteudo();
	float quantidadeReq = dynamic_cast<Automatico*>(f->GetConteudo())->getQntReq() - qnt;

	if(cmTempo(ini,f, tempo, true)){


		int pos = 1, key=-1;
		while (pos <= ra.comprimento())
		{
			Robot temp;
			ra.encontra(pos,temp);
			if(temp.getKey()==rob.getKey())
				break;			
			pos++;
		}
		cout << endl;
		cout << "Estado inicial do abastecimento:" << endl;
		cout << "________________________________________________________________________________" << endl;
		cout << *testeIni;
		cout << *testeFim;
		cout << ra;
		cout << "________________________________________________________________________________" << endl;
		Robot temp;

		if(rob.getQntStock()-qnt>=0){
			float stock=rob.getQntStock()-qnt;
			rob.setQntStock(stock);
			if(strcmp("class Armazem",typeid(*testeIni).name())==0)
				dynamic_cast<Armazem*>(testeIni)->setKeyRobots(-1);
			stock=testeFim->getQntStock()+qnt;
			testeFim->setQntStock(stock);
		}else if(rob.getQntStock()-qnt<0){
			float stock=testeIni->getQntStock()+(rob.getQntStock()-rob.getLimite());
			testeIni->setQntStock(stock);
			if(strcmp("class Armazem",typeid(*testeIni).name())==0)
				dynamic_cast<Armazem*>(testeIni)->setKeyRobots(-1);
			float req=dynamic_cast<Automatico*>(testeFim)->getQntReq()-rob.getLimite();
			dynamic_cast<Automatico*>(testeFim)->setQntReq(req);
			stock=dynamic_cast<Automatico*>(testeFim)->getQntStock()+rob.getLimite();
			dynamic_cast<Automatico*>(testeFim)->setQntStock(stock);
			rob.setQntStock(0);
		}

		rob.setKeyPosto(testeFim->getKey());
		ra.remove(pos,temp);
		ra.insere(pos,rob);

		cout << "Estado final do abastecimento: " << endl;
		cout << "________________________________________________________________________________" << endl;
		cout << *testeIni;
		cout << *testeFim;
		cout << ra;
		cout << "________________________________________________________________________________" << endl;

	}
	if(rob.getLimite()<qnt)
	{
		fflush(stdin);
		cin.get();
		int min=9999;
		tempo[ini->GetKey()]=9999;
		float req=qnt-rob.getLimite();
		Robot robTemp;
		Vertice<Posto*,Transporte> *iniTemp=NULL;
		for(int i=1;i<=ra.comprimento();i++)
		{
			Robot tmp;
			ra.encontra(i,tmp);
			Vertice<Posto*,Transporte> *key=fab.encvert_keyPosto(tmp.getKeyPosto());
			if(min>tempo[key->GetKey()] && tempo[key->GetKey()]!=0)
			{
				testeIni=key->GetConteudo();
				robTemp=tmp;
				min=tempo[key->GetKey()];
				iniTemp=fab.encvert_key(key->GetKey());
			}
		}
		if(iniTemp!=NULL)
			caminhoMinimoTempo(iniTemp,f,req,tempo);
		else
		{
			cout << "Nao existem robots disponiveis para satisfazer o pedido!" << endl;
			return;
		}
	}
}

bool Fabrica::cmDist(Vertice<Posto*,Transporte> *inicio,Vertice<Posto*,Transporte> *fim, int *temp, bool print){
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
	if(print && distancia[f->GetKey()]==9999){
		cout << "nao existe caminho entre " << ini->GetConteudo()->getKey() << " e " << f->GetConteudo()->getKey()<< endl;
		return false;
	}else if(print){
		cout << "Ira demorar " << distancia[f->GetKey()] << " entre " << ini->GetConteudo()->getKey() << " e " << f->GetConteudo()->getKey() << endl;
		mostraCaminho(ini->GetKey(), f->GetKey(), caminho);
		cout << endl;
		return true;
	} else if(!print && distancia[f->GetKey()]==9999){
		*temp=9999;
		return false;
	} else{
		*temp=distancia[f->GetKey()];
		return true;
	}
}

void Fabrica::caminhoMinimoDistancia(Vertice<Posto*,Transporte> *ini, Vertice<Posto*,Transporte> *fim, float qnt, int *distancia)
{
	Posto *testeIni;
	Robot rob;
	if(ini!=NULL)
	{	

		testeIni=ini->GetConteudo();
		if(strcmp("class Armazem",typeid(*ini->GetConteudo()).name())==0)
		{

			int key=dynamic_cast<Armazem*>(ini->GetConteudo())->getKeyRobot();
			int pos = 1;
			while (pos <= ra.comprimento())
			{
				Robot temp;
				ra.encontra(pos,temp);
				if(temp.getKey()==key)
					rob=temp;			
				pos++;
			}

		}
		cout << "Segunda Movimentacao" << endl;
	}else
	{
		int min=9999;
		for(int i=1;i<=fab.NumVert();i++){
			ini=fab.encvert_key(i);
			cmDist(ini,fim,&distancia[i],false);
		}
		ini=NULL;
		for(int i=1;i<=ra.comprimento();i++)
		{
			Robot tmp;
			ra.encontra(i,tmp);
			Vertice<Posto*,Transporte> *key=fab.encvert_keyPosto(tmp.getKeyPosto());
			if(min>distancia[key->GetKey()]&& distancia[key->GetKey()]!=0)
			{
				testeIni=key->GetConteudo();
				rob=tmp;
				min=distancia[key->GetKey()];
				ini=fab.encvert_key(key->GetKey());
			}
		}
		cout << "Primeira Movimentacao" << endl;
	}
	Posto *testeFim=fim->GetConteudo();

	if(ini==NULL){
		cout << "Nao existem caminhos para o armazem " << fim->GetConteudo()->getKey() << endl;
		return;
	}
	testeIni=ini->GetConteudo();
	if(cmDist(ini,fim, distancia, true)){
		int pos = 1, key=-1;
		while (pos <= ra.comprimento())
		{
			Robot temp;
			ra.encontra(pos,temp);
			if(temp.getKey()==rob.getKey())
				break;			
			pos++;
		}
		float movimentado=qnt-rob.getLimite();
		if(movimentado<0)
			movimentado=rob.getLimite();
		cout << endl;
		cout << "Estado inicial do abastecimento:" << endl;
		cout << "________________________________________________________________________________" << endl;
		cout << *testeIni;
		cout << *testeFim;
		cout << ra;
		cout << "________________________________________________________________________________" << endl;
		cout << *testeIni;
		cout << *testeFim;
		cout << ra;
		Robot temp;

		if(rob.getQntStock()-qnt>=0){
			fflush(stdin);
			cin.get();
			float stock=rob.getQntStock()-qnt;
			rob.setQntStock(stock);
			if(strcmp("class Armazem",typeid(*testeIni).name())==0)
				dynamic_cast<Armazem*>(testeIni)->setKeyRobots(-1);
			stock=testeFim->getQntStock()+qnt;
			testeFim->setQntStock(stock);
		}else if(rob.getQntStock()-qnt<0){
			float stock=testeIni->getQntStock()+(rob.getQntStock()-rob.getLimite());
			testeIni->setQntStock(stock);
			if(strcmp("class Armazem",typeid(*testeIni).name())==0)
				dynamic_cast<Armazem*>(testeIni)->setKeyRobots(-1);			
			stock=testeFim->getQntStock()+rob.getLimite();
			testeFim->setQntStock(stock);
			rob.setQntStock(0);
		}

		rob.setKeyPosto(testeFim->getKey());
		ra.remove(pos,temp);
		ra.insere(pos,rob);

		cout << "Estado final do abastecimento: " << endl;
		cout << "________________________________________________________________________________" << endl;
		cout << *testeIni;
		cout << *testeFim;
		cout << ra;
		cout << "________________________________________________________________________________" << endl;
		cout << *testeIni;
		cout << *testeFim;
		cout << ra;

	}

	if(rob.getLimite()<qnt)
	{
		int min=9999;
		distancia[ini->GetKey()]=9999;
		float req=qnt-rob.getLimite();
		Robot robTemp;
		Vertice<Posto*,Transporte> *iniTemp=NULL;
		for(int i=1;i<=ra.comprimento();i++)
		{
			Robot tmp;
			ra.encontra(i,tmp);
			Vertice<Posto*,Transporte> *key=fab.encvert_keyPosto(tmp.getKeyPosto());

			if(min>distancia[key->GetKey()] && distancia[key->GetKey()]!=0)
			{
				testeIni=key->GetConteudo();
				robTemp=tmp;
				min=distancia[key->GetKey()];
				iniTemp=fab.encvert_key(key->GetKey());
			}
		}
		if(iniTemp!=NULL)
			caminhoMinimoDistancia(iniTemp,fim,req,distancia);
		else
			cout << "Robots nao disponiveis" << endl;
	}
}

void Fabrica::abasteceArm(int inicio)
{
	int *dist=new int[fab.NumVert()+1];
	for(int i=1;i <=fab.NumVert();i++)
		dist[i]=9999;

	Vertice<Posto*,Transporte> *ini=fab.encvert_keyPosto(inicio);

	if(ini==NULL){
		cout << "Par de vertices nao encontrado" << endl;
		return;
	}
	Posto *teste=ini->GetConteudo();
	if(strcmp("class Armazem",typeid(*teste).name())!=0)
		cout << "Vertice inicial nao e um posto armazem" << endl;
	else
	{
		int qnt = 3*dynamic_cast<Armazem*>(teste)->getQntSeg();
		caminhoMinimoDistancia(NULL,ini,qnt, dist);
	}
}

void Fabrica::imprimeEstado() const
{
	system("cls");
	cout << "Grafo da Fabrica" << endl;
	fab.escrevegrafo();
	fflush(stdin);
	cin.get();
	system("cls");
	cout << "Lista de Armazens e Postos Automaticos" << endl;
	for(int i=1;i<=fab.NumVert();i++)
	{
		Vertice<Posto*,Transporte> *vert=fab.encvert_key(i);
		cout << *vert->GetConteudo();
	}	
	fflush(stdin);
	cin.get();
	system("cls");
	cout << "Lista de Robots" << endl;
	cout << ra;	
	fflush(stdin);
	cin.get();	
	system("cls");
}

void Fabrica::abasteceAutomatico(){
	Abastecimento temp;
	if(abast.vazia()){
		cout << "Queue de abastecimentos vazia" << endl;
		return;
	}
	while(!abast.vazia()){
		resetPosRobot();

		verificaEstado();
		abast.retira(temp);
		resetPosRobot();
		abasteceAuto(temp.getKey(),temp.getQnt());
	}
}

void Fabrica::verificaEstado(){
	for(int i=1; i<=fab.NumVert(); i++){
		Vertice<Posto*,Transporte> *posto=fab.encvert_key(i);
		if(strcmp("class Armazem",typeid(*posto->GetConteudo()).name())==0){
			Posto *apposto = posto->GetConteudo();
			float stock = dynamic_cast<Armazem*>(apposto)->getQntStock();
			float seg = dynamic_cast<Armazem*>(apposto)->getQntSeg();
			if(stock<seg)
				abasteceArm(apposto->getKey());
		}
	}
}

void Fabrica::resetPosRobot(){
	Queue<Posto*> aux=aa;
	while(!aa.vazia()){
		Posto *appostoQ;
		aa.retira(appostoQ);
		Vertice<Posto*,Transporte> *posto=fab.encvert_keyPosto(appostoQ->getKey());
		Posto *postoV=posto->GetConteudo();		
		if(strcmp("class Armazem",typeid(*posto->GetConteudo()).name())==0){
			int keyR=dynamic_cast<Armazem*>(appostoQ)->getKeyRobot();
			int keyP=postoV->getKey();
			dynamic_cast<Armazem*>(postoV)->setKeyRobots(keyR);
			for(int i=1;i<=ra.comprimento();i++){
				Robot temp;
				ra.remove(i,temp);
				if(temp.getKey()==keyR)
					temp.setKeyPosto(keyP);			
				ra.insere(i,temp);
			}
		}
	}
}

#endif