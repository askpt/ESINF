#ifndef Armazem_
#define Armazem_

#include "Posto.h"

class Armazem:public Posto{
private:
	float qntSeg;
	//TODO: lista ligada Robot

public:
	Armazem();
	Armazem(int key, float qntS, float qntSe); //TODO: falta pointer de LL
	Armazem(const Armazem &a);
	~Armazem();

	void setQntSeg(float qntSe);
	//TODO: SET LL	 robot
	
	float getQntSeg() const;
	//TODO: get LL robot

	virtual Armazem & operator = (const Armazem &a);
	virtual void escreve(ostream &out) const;
	bool operator == (const Armazem &a);
	bool operator > (const Armazem &a);

};

Armazem::Armazem():Posto(){
	setQntSeg(0);
	//LL
}

Armazem::Armazem(int key, float qntS, float qntSe):Posto(key, qntS){
	setQntStock(qntS);
	//LL
}

Armazem::Armazem(const Armazem &a):Posto(a){
	setQntSeg(a.qntSeg);
	//LL
}

Armazem::~Armazem(){
}

void Armazem::setQntSeg(float qntSe){
	qntSeg=qntSe;
}

//set LL

float Armazem::getQntSeg() const{
	return qntSeg;
}

Armazem & Armazem::operator=(const Armazem &a){
	if(this != &a){
		Posto::operator=(a);
		qntSeg = a.qntSeg;
	}
	return *this;
}

bool Armazem::operator==(const Armazem &a){
	return(qntSeg == a.qntSeg && Posto::operator==(a));
}

bool Armazem::operator > (const Armazem &a){
	return(Posto::operator>(a));
}


void Armazem:: escreve(ostream &out) const{
	out << "Armazem: " << endl;
	out << Posto::escreve(out);
	out << "Quantidade Seg: " << qntSeg << endl;
}

ostream & operator << (ostream &out, Armazem &a){
	a.escreve(out);
	return out;
}

//get LL
#endif