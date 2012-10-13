#ifndef Robot_
#define Robot_

#include "Posto.h"

class Robot{
private:
	int key;
	float limite;
	float qntStock;
	Posto* posicao;

public:
	Robot();
	Robot(int key, float lim, float qntS, Posto *p);
	Robot(const Robot &r);
	~Robot();

	void setKey(int k);
	void setLimite(float lim);
	void setQntStock(float qntS);
	void setPosicao(Posto *p);

	int getKey() const;
	float getQntStock() const;
	float getLimite() const;
	Posto* getPosicao() const;

	virtual Robot & operator = (const Robot &r);
	virtual void escreve(ostream &out) const;	
	bool operator == (const Robot &r);
	bool operator > (const Robot &r);

};

Robot::Robot(){
	setKey(0);
	setLimite(0);
	setQntStock(0);
	setPosicao(NULL); 
	//TODO: Apontador null???
}

Robot::Robot(int key, float lim, float qntS, Posto *p){
	setKey(key);
	setLimite(lim);
	setQntStock(qntS);
	setPosicao(p);
}

Robot::Robot(const Robot &r){
	setKey(r.key);
	setQntStock(r.qntStock);
	setLimite(r.limite);
	setPosicao(r.posicao);
}

Robot::~Robot(){
}

void Robot::setKey(int k){
	key=k;
}

void Robot::setLimite(float lim){
	limite=lim;
}

void Robot::setQntStock(float qntS){
	qntStock=qntS;
}

void Robot::setPosicao(Posto *p){
	posicao=p;
}

int Robot::getKey() const{
	return key;
}

float Robot::getQntStock() const{
	return qntStock;
}
	
float Robot::getLimite() const{
	return limite;
}

Posto* Robot::getPosicao() const{
	return posicao;
}

Robot & Robot:: operator = (const Robot &r){
	if (this != &r){
		Robot::operator=(r);
		key = r.key;
		limite = r.limite;
		qntStock = r.qntStock;
		posicao = r.posicao;
	}

	return *this;
}

bool Robot::operator ==(const Robot &r){
	return(key == r.key && limite == r.limite && qntStock == r.qntStock && posicao == r.posicao);
}

bool Robot::operator > (const Robot &r){
	return(qntStock > r.qntStock);
}

void Robot:: escreve(ostream &out) const {
	out << "Robot: <- Key: " << key << "; Limite: " << limite << ";Quantidade stock: " << qntStock << "; Posicao: " << posicao->getKey() << endl;
}

ostream & operator << (ostream &out, Robot &r){
	r.escreve(out);
	return out;
}

#endif