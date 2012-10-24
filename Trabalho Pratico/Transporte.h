#ifndef Transporte_
#define Transporte_

class Transporte{
private:
	float distanciametros;
	float tempominutos;

public:
	Transporte();
	Transporte(float distm, float tmpm);	
	~Transporte();

	void setDistanciametros(float distm);
	void setTempominutos(float tmpmin);
	
	float getDistanciametros() const;
	float getTempominutos() const;
	
	bool operator==(const Transporte &t);
	bool operator>(const Transporte &t);
	Transporte& operator=(const Transporte &t);
	void escreve(ostream& out) const;
};

Transporte::Transporte(){
	setDistanciametros(0);
	setTempominutos(0);
}

Transporte::Transporte(float distm, float tmpm){
	setDistanciametros(distm);
	setTempominutos(tmpm);
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

bool Transporte::operator==(const Transporte &t){
	return (distanciametros==t.distanciametros && tempominutos==t.tempominutos);
}
	
bool Transporte::operator>(const Transporte &t){
	return (distanciametros>t.distanciametros); 
}

Transporte& Transporte::operator=(const Transporte &t){
	if(this!=&t){
		distanciametros=t.distanciametros;
		tempominutos=t.tempominutos;
	}

	return *this;
}

void Transporte::escreve(ostream& out) const{
	out << tempominutos << "," << distanciametros;
}

ostream & operator << (ostream &out, Transporte &t){
	t.escreve(out);
	return out;
}

#endif
