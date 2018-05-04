#include<iostream>
#include<vector>

enum class Drink{ Coke, Pepsi, None};

class Packing{
public:
	virtual std::string Pack() = 0;
	virtual ~Packing(){};
};

class Item{
public:
	virtual std::string get_name() = 0;
	virtual Packing *get_packing() = 0;
	virtual int get_price() = 0;
	virtual ~Item() {};
};

class Wrapper: public Packing{
public:
	virtual std::string Pack(){ return "Wrapper";}
	~Wrapper(){
	  std::cout << "    Deleting Wrapper" << std::endl;
	}
};

class Bottle: public Packing{
public:
	virtual std::string Pack(){ return "Bottle";}
	~Bottle(){
	  std::cout << "    Deleting Bottle" << std::endl;
	}
};

class Burger: public Item{
private:
	Packing *p;
public:
	Burger(){ p = new Wrapper();}
	virtual Packing *get_packing(){ return p;}
	virtual ~Burger(){
	  delete p;
	}
};

class VegBurger: public Burger{
public:
	virtual std::string get_name(){ return "Veg Burger"; }
	virtual int get_price(){ return 25;}
	virtual ~VegBurger(){
	  std::cout << "  Deleting Veg Burger" << std::endl;
	}
};

class NonVegBurger: public Burger{
public:
	virtual std::string get_name(){ return "Non Veg Burger"; }
	virtual int get_price(){ return 35;}
	virtual ~NonVegBurger(){
	  std::cout << "  Deleting NonVeg Burger" << std::endl;
	}
}; 

class ColdDrink: public Item{
private:
	Packing *p;
public:
	ColdDrink(){ p = new Bottle(); }
	virtual Packing *get_packing(){ return p;}
	virtual ~ColdDrink(){
	  delete p;
	}
};

class Pepsi: public ColdDrink{
	virtual std::string get_name(){ return "Pepsi"; }
	virtual int get_price(){ return 105;}
	virtual ~Pepsi(){
	  std::cout << "  Deleting Pepsi" << std::endl;
	}
};

class Coke: public ColdDrink{
	virtual std::string get_name(){ return "Coke"; }
	virtual int get_price(){ return 65;}
	virtual ~Coke(){
	  std::cout << "  Deleting Coke" << std::endl;
	}
};

class Meal{
private:
	std::vector<Item *> items;
	std::string name;
public:
	Meal(std::string mealname): name(mealname) {}
	void AddItem(Item *i){ items.push_back(i);}
	int getCost(){ 
	  int cost = 0;
  	  for (auto i: items){
	   cost += i->get_price();
         }
	  return cost;
        }
	void showItems(){
	  std::cout << name << std::endl;
	  for(auto i: items){
	    std::cout << "  " << i->get_name() << " :: " << i->get_price() << " :: " << i->get_packing()->Pack() <<  std::endl;
	  }
	  std::cout << "  Total :: " << getCost() << std::endl;
	  std::cout << std::endl;
	}
	~Meal(){
	  std::cout << "Destroying Meal :: " << name << std::endl;
	  for(auto i: items){
	   delete i;
	  }
	  items.clear();
	  std::cout << std::endl;
	}
};
class MealBuilder{
private:
	Item *get_drink(Drink d){
	  switch(d){
	    case Drink::Coke:
	      return new Coke();
	    case Drink::Pepsi:
	      return new Pepsi();
	  }
          return nullptr;
	}
public:
	Meal *prepareVegMeal(Drink d){
	  Meal *m = new Meal("Veg");
	  m->AddItem(new VegBurger());
	  Item *drink = get_drink(d);
	  if(drink){
	    m->AddItem(get_drink(d));
          }
	  return m;
	}
	Meal *prepareNonVegMeal(Drink d){
	  Meal *m = new Meal("NonVeg");
	  m->AddItem(new NonVegBurger());
	  Item *drink = get_drink(d);
	  if(drink){
	    m->AddItem(get_drink(d));
          }
	  return m;
	}
	~MealBuilder(){
	  std::cout << "Destroying Mealbuilder" << std::endl;
	}
};

int main(){
  MealBuilder *mb = new MealBuilder(); 
  Meal *v1 = mb->prepareVegMeal(Drink::Coke);
  v1->showItems();
  Meal *nv1 = mb->prepareNonVegMeal(Drink::Pepsi);
  nv1->showItems();
  Meal *v2 = mb->prepareVegMeal(Drink::Coke);
  v2->showItems();
  Meal *nv2 = mb->prepareNonVegMeal(Drink::Coke);
  nv2->showItems();
  Meal *v3 = mb->prepareVegMeal(Drink::None);
  v3->showItems();
  delete v1;
  delete nv1;
  delete v2;
  delete nv2;
  delete v3;
  delete mb;
  return 0;
}
