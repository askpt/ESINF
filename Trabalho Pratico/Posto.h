#ifndef Posto_
#define Posto_

class Posto{
private:
	int key;

public:
	Posto();	
	Posto(const Posto &p);
	~Posto();

	int getKey() const;
	void setKey(int k);
};

Posto::Posto(){
	setKey(0);
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

#endif