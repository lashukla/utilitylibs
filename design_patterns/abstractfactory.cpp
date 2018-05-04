#include<iostream>

class ProductA{
public:
	virtual void display() = 0;
};
class ProductA1 : public ProductA{
public:
	virtual void display(){
		std::cout << "Product A1" << std::endl;
	}
};
class ProductA2 : public ProductA{
public:
	virtual void display(){
		std::cout << "Product A2" << std::endl;
	}
};

class ProductB{
public:
	virtual void display() = 0;
};
class ProductB1 : public ProductB{
public:
	virtual void display(){
		std::cout << "Product B1" << std::endl;
	}
};
class ProductB2 : public ProductB{
public:
	virtual void display(){
		std::cout << "Product B2" << std::endl;
	}
};

class Factory{
public:
	virtual ProductA *make_productA(int p) = 0;
	virtual ProductB *make_productB(int t) = 0;
};

class PFactory: public Factory{
	virtual ProductA *make_productA(int p){
		if(p == 1){
			return new ProductA1();
		}else{
			return new ProductA2();
		}
	}	
	virtual ProductB *make_productB(int p){
		if(p == 1){
			return new ProductB1();
		}else{
			return new ProductB2();
		}
	}	
};

int main(){
  Factory *f = new PFactory();
  ProductA *A = f->make_productA(2);
  ProductB *B = f->make_productB(1);
  A->display();
  B->display();
  delete f;
  delete A;
  delete B;
}
