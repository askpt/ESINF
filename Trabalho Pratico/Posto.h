#ifndef Posto_
#define Posto_

class Posto{
private:
	int key;
	float qntStock;

public:
	Posto();
	Posto(int key, float qntStock); 
	Posto(const Posto &p);
	~Posto();

	int getKey() const;
	float getQntStock() const;

	void setKey(int k);
	void setQntStock(float qntS);

	virtual Posto & Posto :: operator = (const Posto &p);
	virtual void escreve(ostream &out) const;
	bool operator == (const Posto &p);
	bool operator > (const Posto &p);
};

Posto::Posto(){
	setKey(0);
	setQntStock(0);
}

Posto::Posto(int key, float qntStock){
	setKey(key);
	setQntStock(qntStock);
}

Posto::Posto(const Posto &p){
	setKey(p.key);
}

Posto::~Posto(){
}

int Posto::getKey() const{
	return key;
}

float Posto::getQntStock() const{
	return qntStock;
}

void Posto::setKey(int k){
	key=k;
}

void Posto::setQntStock(float qntS){
	qntStock=qntS;
}

Posto & Posto::operator=(const Posto &p){
	if (this != &p){
		key = p.key;
		qntStock=p.qntStock;
	}
	return *this;
}

bool Posto::operator==(const Posto &p){
	return(key == p.key && qntStock == p.qntStock);
}

bool Posto:: operator > (const Posto &p){
	return(qntStock > p.qntStock);
}

void Posto::escreve(ostream &out) const{
	out << "Posto: <- Key:" << key << endl;
	out << "Quantidad de Stock: " << qntStock << endl;
}

ostream & operator << (ostream &out, const Posto &p){
	p.escreve(out);
	return out;
}

#endif