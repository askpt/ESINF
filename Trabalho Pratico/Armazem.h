#ifndef Armazem_
#define Armazem_

class Armazem:public Posto{
private:
	float qntSeg;
	int keyRobot;

public:
	Armazem();
	Armazem(int key, float qntS, float qntSe, int keyR);
	Armazem(const Armazem &a);
	~Armazem();

	void setQntSeg(float qntSe);
	void setKeyRobots(int keyR);
		
	float getQntSeg() const;
	int getKeyRobot() const;

	virtual Armazem & operator = (const Armazem &a);
	virtual void escreve(ostream &out) const;
	virtual bool operator == (const Armazem &a);
	virtual bool operator > (const Armazem &a);

	virtual Posto* clone() const;
};

Armazem::Armazem():Posto(){
	setQntSeg(0);
}

Armazem::Armazem(int key, float qntS, float qntSe, int keyR):Posto(key, qntS){
	setQntSeg(qntSe);
	setKeyRobots(keyR);
}

Armazem::Armazem(const Armazem &a):Posto(a){
	setQntSeg(a.qntSeg);
	keyRobot=a.keyRobot;
}

Armazem::~Armazem(){
}

void Armazem::setQntSeg(float qntSe){
	qntSeg=qntSe;
}

void Armazem::setKeyRobots(int keyR){
	keyRobot=keyR;
}

int Armazem::getKeyRobot() const{
	return keyRobot;
}

float Armazem::getQntSeg() const{
	return qntSeg;
}

Armazem & Armazem::operator=(const Armazem &a){
	if(this != &a){
		Posto::operator=(a);
		qntSeg = a.qntSeg;
		keyRobot = a.keyRobot;
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
	Posto::escreve(out);
	out << "; Quantidade Seg: " << qntSeg;
	out << "; Robot:" << keyRobot << endl;
}

ostream & operator << (ostream &out, Armazem &a){
	a.escreve(out);
	return out;
}

Posto* Armazem::clone() const{
	return new Armazem(*this);
}

#endif