#ifndef Automatico_
#define Automatico_

class Automatico:public Posto{
private:
	float qntReq;
	float vel;

public:
	Automatico();
	Automatico(int key, float qntS, float qntR, float v);
	Automatico(const Automatico &a);
	~Automatico();

	float getQntReq() const;
	float getVel() const;
	void setQntReq(float qntR);
	void setVel(float v);

	virtual Automatico & operator = (const Automatico &t);
	virtual void escreve(ostream &out) const;
	virtual bool operator == (const Automatico &t);
	virtual bool operator > (const Automatico &t);

	virtual Posto* clone() const;
};

Automatico::Automatico():Posto(){
	setQntReq(0);
	setVel(0);
}

Automatico::Automatico(int key, float qntS, float qntR, float v):Posto(key, qntS){
	setQntReq(qntR);
	setVel(v);
}

Automatico::Automatico(const Automatico &a):Posto(a){
	setQntReq(a.qntReq);
	setVel(a.vel);
}

Automatico::~Automatico(){
}

float Automatico::getQntReq() const{
	return qntReq;
}

float Automatico::getVel() const{
	return vel;
}

void Automatico::setQntReq(float qntR){
	qntReq=qntR;
}

void Automatico::setVel(float v){
	vel=v;
}

Automatico & Automatico :: operator = (const Automatico &t){
	if(this != &t){
		Posto::operator=(t);
		qntReq = t.qntReq;
		vel = t.vel;
	}
	return *this;
}

bool Automatico::operator==(const Automatico &t){
	return(Posto::operator==(t) && qntReq == t.qntReq && vel == t.vel);
}

bool Automatico::operator > (const Automatico &t){
	return(Posto::operator>(t));
}

void Automatico::escreve(ostream &out) const{
	Posto::escreve(out);
	out << "; Quantidade Req: " << qntReq << "; Vel: " << vel << endl;
}

ostream & operator << (ostream &out, Automatico &t){
	t.escreve(out);
	return out;
}

Posto* Automatico::clone() const{
	return new Automatico(*this);
}

#endif