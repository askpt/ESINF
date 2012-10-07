#ifndef Posto_
#define Posto_

class Posto{
private:
	int key;

public:
	Posto();
	Posto(int key); 
	Posto(const Posto &p);
	~Posto();

	int getKey() const;
	void setKey(int k);

	virtual Posto & Posto :: operator = (const Posto &p);
	virtual void escreve(ostream &out) const;
	bool operator == (const Posto &p);
	bool operator > (const Posto &p);
};

Posto::Posto(){
	setKey(0);
}

Posto::Posto(int key){
	setKey(key);
}

Posto::Posto(const Posto &p){
	setKey(p.key);
}

Posto::~Posto(){
}

int Posto::getKey() const{
	return key;
}

void Posto::setKey(int k){
	key=k;
}

Posto & Posto::operator=(const Posto &p){
	if (this != &p){
		Posto::operator=(p);
		key = p.key;
	}
	return *this;
}

bool Posto::operator==(const Posto &p){
	return(key = p.key);
}

bool Posto:: operator > (const Posto &p){
	return(key > p.key);
}

void Posto::escreve(ostream &out) const{
	out << "Posto: <- Key:" << key << endl;
}

ostream & operator << (ostream &out, const Posto &p){
	p.escreve(out);
	return out;
}

#endif