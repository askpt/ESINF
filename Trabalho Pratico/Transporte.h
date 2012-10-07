#ifndef Transporte_
#define Transporte_

#include "Posto.h"

//como ligar a key posto com as keys aqui definidas?

class Transporte{
private:
	float distanciametros;
	float tempominutos;

public:
	Transporte();
	Transporte(int keyAuto, int keyAuto2, float distm, float tmpm);
	Transporte(int keyArm, int keyArm2, float distm, float tmpm);
	Transporte(int keyArm, int keyAuto, float distm, float tmpm);
	~Transporte();

	void setDistanciametros(float distm);
	void setTempominutos(float tmpmin);

	float getDistanciametros() const;
	float getTempominutos() const;
};

Transporte::Transporte(){

}

Transporte::Transporte(int keyAuto, int keyAuto2, float distm, float tmpm){

}
	
Transporte::Transporte(int keyArm, int keyArm2, float distm, float tmpm){

}
	
Transporte::Transporte(int keyArm, int keyAuto, float distm, float tmpm){

}

Transporte::~Transporte(){

}

	
void Transporte::setDistanciametros(float distm){
	distanciametros=distm;
}

void Transporte::setTempominutos(float tmpmin){
	tempominutos=tmpmin;
}

float Transporte::getDistanciametros() const{
	return distanciametros;
}
	
float Transporte::getTempominutos() const{
	return tempominutos;
}


#endif
