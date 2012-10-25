#ifndef Matriz_
#define Matriz_

class Matriz{
private:
	Transporte* *mat;

	int *keys;

	int key_atual;
	int dim;

	void aumenta();
	int encontra(int key);
public:
	Matriz(int d);
	Matriz(const Matriz& m);
	~Matriz();

	void addValor(int key1, int key2, float temp, float dist);
	void retValor(Transporte &x, int key1, int key2);

	void escreve(ostream &out) const;
	Matriz& operator=(const Matriz& m);
};

Matriz::Matriz(int d){
	key_atual=0;
	dim=d;

	mat=new Transporte*[dim];
	for(int i=0;i<dim;i++)
		mat[i]=new Transporte[dim];

	keys=new int[dim];
}

Matriz::Matriz(const Matriz &m){
	key_atual=m.key_atual;
	dim=m.dim;

	mat=new Transporte*[dim];
	for(int i=0;i<key_atual;i++)
		mat[i]=new Transporte[dim];

	for(int i=0;i<key_atual;i++)
		for(int j=0;j<key_atual;j++)
			mat[i][j]=m.mat[i][j];

	keys=new int[dim];
	for(int i=0;i<key_atual;i++)
		keys[i]=m.keys[i];
}

Matriz::~Matriz(){
	for(int i=0;i<key_atual;i++){		
		delete [] mat[i];		
	}
	delete[]mat;

	delete [] keys;

}

void Matriz::aumenta(){
	Transporte ** tmp;
	tmp = new Transporte *[2*dim];
	for(int i=0;i<key_atual;i++)
		tmp[i]=new Transporte[2*dim];

	for(int i=0;i<key_atual;i++)
		for(int j=0;j<key_atual;j++)
			tmp[i][j]=mat[i][j];
	delete[]mat;
	mat=tmp;

	int* tmpk;
	tmpk=new int[2*dim];
	for(int i=0;i<key_atual;i++)
		tmpk[i]=keys[i];
	delete[]keys;
	keys=tmpk;

	dim*=2;
}

int Matriz::encontra(int key){
	int posk=0;
	for(;posk<key_atual;posk++)
		if(keys[posk]==key)
			break;
	if(posk==key_atual)
		if(key_atual!=dim){
			keys[posk]=key;
			key_atual++;
		}else{
			aumenta();
			keys[posk]=key;
			key_atual++;
		}

		return posk;
}

void Matriz::addValor(int key1, int key2, float temp, float dist){
	int posk1=encontra(key1);
	int posk2=encontra(key2);

	Transporte tmp(dist, temp);
	mat[posk1][posk2]=tmp;
}

void Matriz::retValor(Transporte &x, int key1, int key2){
	int posk1=encontra(key1);
	int posk2=encontra(key2);

	x=mat[posk1][posk2];
}

void Matriz::escreve(ostream &out) const{

	out << "0" ;

	for(int i = 0; i < key_atual; i++){                
		out << keys[i] << " ";
	}

	for(int j = 0; j < key_atual; j++){
		out << endl;
		out << keys[j] << " ";
		for(int k = 0; k < key_atual; k++){                                                                             
			out << mat[j][k] << " ";
		}
	}
}

ostream & operator << (ostream &out, Matriz &m ){
	m.escreve(out);
	return out;
}

Matriz& Matriz::operator=(const Matriz& m){
	if(this != &m){
		for(int i=0;i<key_atual;i++){		
			delete [] mat[i];		
		}
		delete[]mat;
		delete[]keys;
		dim=m.dim;
		key_atual=m.key_atual;

		mat=new Transporte*[dim];
		for(int i=0;i<key_atual;i++)
			mat[i]=new Transporte[dim];

		for(int i=0;i<key_atual;i++)
			for(int j=0;j<key_atual;j++)
				mat[i][j]=m.mat[i][j];

		keys=new int[dim];
		for(int i=0;i<key_atual;i++)
			keys[i]=m.keys[i];
	}

	return *this;
}

#endif