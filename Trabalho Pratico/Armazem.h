#ifndef Armazem_
#define Armazem_

#include "Posto.h"
#include "Lista.h"
#include "No.h"

class Armazem:public Posto{
private:
	float qntSeg;
	Lista <Robot*> robots;

public:
	Armazem();
	Armazem(int key, float qntS, float qntSe);
	Armazem(const Armazem &a);
	~Armazem();

	void setQntSeg(float qntSe);
		
	float getQntSeg() const;
	Lista <Robot*>& getRobots();

	virtual Armazem & operator = (const Armazem &a);
	virtual void escreve(ostream &out) const;
	bool operator == (const Armazem &a);
	bool operator > (const Armazem &a);

};

Armazem::Armazem():Posto(){
	setQntSeg(0);
}

Armazem::Armazem(int key, float qntS, float qntSe):Posto(key, qntS){
	setQntSeg(qntSe);
}

Armazem::Armazem(const Armazem &a):Posto(a){
	setQntSeg(a.qntSeg);
	robots=a.robots;
}

Armazem::~Armazem(){
	robots.~Lista();
}

void Armazem::setQntSeg(float qntSe){
	qntSeg=qntSe;
}

Lista <Robot*>& Armazem::getRobots(){
	return robots;
}

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
	Posto::escreve(out);
	out << "Quantidade Seg: " << qntSeg << endl;
	out << "Robots:" << endl;
	out << robots;
}

ostream & operator << (ostream &out, Armazem &a){
	a.escreve(out);
	return out;
}

#endif