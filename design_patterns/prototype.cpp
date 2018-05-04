#include<iostream>

class Prototype{
public:
	virtual Prototype *clone() = 0;
	virtual void display() = 0;
};

class ProductA: public Prototype{
public:
	virtual Prototype *clone(){ return new ProductA();}
	virtual void display(){
		std::cout << "Product A" << std::endl;
	}
};

class ProductB: public Prototype{
public:
	virtual Prototype *clone() { return new ProductB();}
	virtual void display(){
		std::cout << "Product B" << std::endl;
	}
};

class ProtoFactory{
private:
	static Prototype *protos[3];
public:
	static ProtoFactory *make_proto(){
		protos[0] = nullptr;
		protos[1] = new ProductA();
		protos[2] = new ProductB();	
		return new ProtoFactory();
	}
	Prototype *make_product(int i){
		return ProtoFactory::protos[i]->clone();
	}
	~ProtoFactory(){
		for(int i = 1; i < 2; i++){
			delete protos[i];
		}
	}
	
};

Prototype *ProtoFactory::protos[3] = {nullptr, nullptr, nullptr};
int main(){
	ProtoFactory *x = ProtoFactory::make_proto();
	Prototype *a = x->make_product(1);
	Prototype *b = x->make_product(2);
	a->display();
	b->display();
	delete a;
	delete b;
	delete x;
	return 0;
}
