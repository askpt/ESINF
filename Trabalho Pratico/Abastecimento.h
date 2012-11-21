#ifndef Abastecimento_
#define Abastecimento_

class Abastecimento
{
private:
	int key;
	float qnt;

public:
	Abastecimento();
	Abastecimento(int key, float qnt);
	Abastecimento(const Abastecimento &a);
	~Abastecimento();

	int getKey() const;
	float getQnt() const;
	void setKey(int k);
	void setQnt(float qnt);

	Abastecimento& operator=(const Abastecimento &a);
	bool operator==(const Abastecimento &a);
	bool operator<(const Abastecimento &a);
	void escreve(ostream &out);
};

Abastecimento::Abastecimento(){
	setKey(-1);
	setQnt(0);
}
Abastecimento::Abastecimento(int key, float qnt){
	setKey(key);
	setQnt(qnt);
}

Abastecimento::Abastecimento(const Abastecimento &a){
	setKey(a.key);
	setQnt(a.qnt);
}

Abastecimento::~Abastecimento(){}

int Abastecimento::getKey() const{
	return key;
}

float Abastecimento::getQnt() const{
	return qnt;
}

void Abastecimento::setKey(int k){
	key=k;
}

void Abastecimento::setQnt(float q){
	qnt=q;
}

Abastecimento& Abastecimento::operator=(const Abastecimento &a){
	key=a.key;
	qnt=a.qnt;
	return *this;
}

bool Abastecimento::operator==(const Abastecimento &a){
	return (key==a.key && qnt==a.qnt);
}

bool Abastecimento::operator<(const Abastecimento &a){
	return qnt<a.qnt;
}

void Abastecimento::escreve(ostream &out){
	out << "Key do posto: " << key << ". Pedido:" << qnt << endl;
}

ostream& operator << (ostream &out, Abastecimento &a){
	a.escreve(out);
	return out;
}
#endif