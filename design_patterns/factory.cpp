#include<iostream>

class Product{
public:
	virtual void display() = 0;
};

class Prod1: public Product{
public:
	virtual void display(){
		std::cout << "Prod 1" << std::endl;	
	}	
};
class Prod2: public Product{
public:
	virtual void display(){
		std::cout << "Prod 2" << std::endl;	
	}	
};
class Factory{
public:
	virtual Product * make_product(int ptype) = 0;  
};

class PFactory: public Factory{
public:
	virtual Product * make_product(int ptype){
		if(ptype == 1){
			return new Prod1();
		}
		if(ptype == 2){
			return new Prod2();
		}
	}
};

int main(){
  Factory *f = new PFactory();
  Product *a = f->make_product(1);
  Product *b = f->make_product(2);
  a->display();
  b->display();
  delete a;
  delete b;
  delete f;
  return 0;
}
