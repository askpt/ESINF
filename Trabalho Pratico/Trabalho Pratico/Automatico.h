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
#endif