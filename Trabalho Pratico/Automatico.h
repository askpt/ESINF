#ifndef Automatico_
#define Automatico_

#include "Posto.h"

class Automatico:public Posto{
private:
	float qntStock;
	float qntReq;
	float vel;

public:
	Automatico();
	Automatico(float qntS, float qntR, float v);
	Automatico(const Automatico &a);
	~Automatico();

	float getQntStock() const;
	float getQntReq() const;
	float getVel() const;
	void setQntStock(float qntS);
	void setQntReq(float qntR);
	void setVel(float v);

	virtual Automatico & operator = (const Automatico &t);
	virtual void escreve(ostream &out) const;
};

Automatico::Automatico():Posto(){
	setQntStock(0);
	setQntReq(0);
	setVel(0);
}

Automatico::Automatico(float qntS, float qntR, float v):Posto(){
	setQntStock(qntS);
	setQntReq(qntR);
	setVel(v);
}

Automatico::Automatico(const Automatico &a):Posto(a){
	setQntStock(a.qntStock);
	setQntReq(a.getQntReq);
	setVel(a.vel);
}

Automatico::~Automatico(){
}

float Automatico::getQntStock() const{
	return qntStock;
}

float Automatico::getQntReq() const{
	return qntReq;
}

float Automatico::getVel() const{
	return vel;
}

void Automatico::setQntStock(float qntS){
	qntStock=qntS;
}

void Automatico::setQntReq(float qntR){
	qntReq=qntR;
}

void Automatico::setVel(float v){
	vel=v;
}

Automatico & Automatico :: operator = (const Automatico &t){
	if(this != &t){
		Automatico::operator=(t);
		qntStock = t.qntStock;
		qntReq = t.qntReq;
		vel = t.vel;
	}
	return *this;
}

void Automatico::escreve(ostream &out) const{
	out << "Automatico: " << endl;
	out << "Quantidade Stock: " << qntStock << "; Quantidade Req: " << qntReq << "; Vel: " << vel << endl;
}

ostream & operator << (ostream &out, Automatico &t){
	t.escreve(out);
	return out;
}

#endif