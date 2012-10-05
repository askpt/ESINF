#ifndef Armazem_
#define Armazem_

#include "Posto.h"

class Armazem:public Posto{
private:
	float qntStock;
	float qntSeg;
	//lista ligada Robot

public:
	Armazem();
	Armazem(float qntS, float qntSe); //falta pointer de LL
	Armazem(const Armazem &a);
	~Armazem();

	void setQntStock(float qntS);
	void setQntSeg(float qntSe);
	//SET LL	 robot
	
	float getQntStock() const;
	float getQntSeq() const;
	//get LL robot

	virtual Armazem & operator = (const Armazem &a);
	virtual void escreve(ostream &out) const;

};

Armazem::Armazem(){
	setQntStock(0);
	setQntSeg(0);
	//LL
}

Armazem::Armazem(float qntS, float qntSe){
	setQntStock(qntS);
	setQntSeg(qntSe);
	//LL
}

Armazem::Armazem(const Armazem &a){
	setQntStock(a.qntStock);
	setQntSeg(a.qntSeg);
	//LL
}

Armazem::~Armazem(){
}

void Armazem::setQntStock(float qntS){
	qntStock=qntS;
}

void Armazem::setQntSeg(float qntSe){
	qntSeg=qntSe;
}

//set LL

float Armazem::getQntStock() const{
	return qntStock;
}

float Armazem::getQntSeg() const{
	return qntSeg;
}

Armazem & Armazem::operator=(const Armazem &a){
	if(this != &a){
		Armazem::operator=(a);
		qntSeg = a.qntSeg;
		qntStock = a.qntStock;
	}
	return *this;
}

void Armazem:: escreve(ostream &out) const{
	out << "Armazem: " << endl;
	out << "Quantidade em Stock: " << qntStock << "; Quantidade Seg: " << qntSeg << endl;
}

ostream & operator << (ostream &out, Armazem &a){
	a.escreve(out);
	return out;
}

//get LL
#endif