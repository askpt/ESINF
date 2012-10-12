#ifndef Transporte_
#define Transporte_

class Transporte{
private:
	int key1;
	int key2;
	float distanciametros;
	float tempominutos;

public:
	Transporte();
	Transporte(int k1, int k2, float distm, float tmpm);	
	~Transporte();

	void setDistanciametros(float distm);
	void setTempominutos(float tmpmin);
	void setKey1(int k1);
	void setKey2(int k2);

	float getDistanciametros() const;
	float getTempominutos() const;
	int getKey1() const;
	int getKey2() const;

	bool operator==(const Transporte &t);
	bool operator>(const Transporte &t);
	Transporte& operator=(const Transporte &t);
	void escreve(ostream& out) const;
};

Transporte::Transporte(){
	setKey1(0);
	setKey2(0);
	setDistanciametros(0);
	setTempominutos(0);
}

Transporte::Transporte(int k1, int k2, float distm, float tmpm){
	setKey1(k1);
	setKey2(k2);
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

void Transporte::setKey1(int k1){
	key1=k1;
}

void Transporte::setKey2(int k2){
	key2=k2;
}

float Transporte::getDistanciametros() const{
	return distanciametros;
}
	
float Transporte::getTempominutos() const{
	return tempominutos;
}

int Transporte::getKey1() const{
	return key1;
}

int Transporte::getKey2() const{
	return key2;
}

bool Transporte::operator==(const Transporte &t){
	return (key1==t.key1 && key2==t.key2 && distanciametros==t.distanciametros && tempominutos==t.tempominutos);
}
	
bool Transporte::operator>(const Transporte &t){
	return (distanciametros>t.distanciametros); //TODO: discutir se é a distancia ou o tempo
}

Transporte& Transporte::operator=(const Transporte &t){
	key1=t.key1;
	key2=t.key2;
	distanciametros=t.distanciametros;
	tempominutos=t.tempominutos;
}

void Transporte::escreve(ostream& out) const{
	out << "Viagem entre " << key1 << " e " << key2 << " é de " << tempominutos << " minutos, com uma distancia de " << distanciametros << " metros." << endl;
}

ostream & operator << (ostream &out, Transporte &t){
	t.escreve(out);
	return out;
}

#endif
