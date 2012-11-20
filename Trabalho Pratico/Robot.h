#ifndef Robot_
#define Robot_

class Robot{
private:
	int key;
	float limite;
	float qntStock;
	int keyPosto;

public:
	Robot();
	Robot(int key, float lim, float qntS, int keyP);
	Robot(const Robot &r);
	~Robot();

	void setKey(int k);
	void setLimite(float lim);
	void setQntStock(float qntS);
	void setKeyPosto(int keyPosto);

	int getKey() const;
	float getQntStock() const;
	float getLimite() const;
	int getKeyPosto() const;

	Robot & operator = (const Robot &r);
	void escreve(ostream &out) const;	
	bool operator == (const Robot &r);
	bool operator > (const Robot &r);

};

Robot::Robot(){
	setKey(-1);
	setLimite(0);
	setQntStock(0);
	setKeyPosto(0); 
}

Robot::Robot(int key, float lim, float qntS, int keyP){
	setKey(key);
	setLimite(lim);
	setQntStock(qntS);
	setKeyPosto(keyP);
}

Robot::Robot(const Robot &r){
	setKey(r.key);
	setQntStock(r.qntStock);
	setLimite(r.limite);
	setKeyPosto(r.keyPosto);
}

Robot::~Robot(){
}

void Robot::setKey(int k){
	key=k;
}

void Robot::setLimite(float lim){
	limite=lim;
}

void Robot::setQntStock(float qntS){
	qntStock=qntS;
}

void Robot::setKeyPosto(int keyP){
	keyPosto=keyP;
}

int Robot::getKey() const{
	return key;
}

float Robot::getQntStock() const{
	return qntStock;
}
	
float Robot::getLimite() const{
	return limite;
}

int Robot::getKeyPosto() const{
	return keyPosto;
}

Robot & Robot:: operator = (const Robot &r){
	if (this != &r){
		key = r.key;
		limite = r.limite;
		qntStock = r.qntStock;
		keyPosto = r.keyPosto;
	}

	return *this;
}

bool Robot::operator ==(const Robot &r){
	return(key == r.key && limite == r.limite && qntStock == r.qntStock && keyPosto == r.keyPosto);
}

bool Robot::operator > (const Robot &r){
	return(qntStock > r.qntStock);
}

void Robot:: escreve(ostream &out) const {
	//out << "Robot: <- Key: " << key << "; Limite: " << limite << ";Quantidade stock: " << qntStock << "; Posicao: " << keyPosto << endl;
	out << "Key" << setw(2) << " " << "Limite" << setw(2) << " " << "QuantidadeStock" << setw(2) << " " << "Posicao" << endl;
	out << key << setw(6) << " " << limite << setw(10) << " " << qntStock << setw(12) << " " << keyPosto << "" << endl;
}

ostream & operator << (ostream &out, const Robot &r){
	r.escreve(out);
	return out;
}

#endif