#include<iostream>
#include<vector>
#include<algorithm>

enum class ComponentType { FILE, DIRECTORY};
class Component{
private:
	std::string name;
	ComponentType type;
public:
	Component(ComponentType T, std::string nm): type(T), name(nm){}
	virtual void iterate() = 0;
	virtual std::string get_name() { return name ; }
	virtual ComponentType get_type() { return type; }
	virtual void Add(Component *item) = 0;
	virtual ~Component(){}
};

class Element: public Component{
public:
	Element(std::string nm): Component(ComponentType::FILE, nm) {}
	virtual void iterate(){
	  std::cout << get_name() << std::endl;
	}
	void Add(Component *item) {};
};

class Composite: public Component{
private:
	std::vector<Component *>items;
public:
	Composite(std::string nm): Component(ComponentType::DIRECTORY, nm) {}
	void iterate(){
	  for(auto i: items){
	    if(i->get_type() == ComponentType::DIRECTORY){
	      std::cout << i->get_name() << std::endl;
	    }
	    i->iterate();
	  }
	}
	void Add(Component *item){items.push_back(item);}
	Component *Get(std::string s){
	  for(auto i: items){
	    if(i->get_name() == s) return i;
	  }
	  return nullptr;
	}
	~Composite(){
	  std::cout << "Deleting " << get_name() << std::endl;
	  for(auto i: items){
	    delete i;
	  }
	  items.clear();
	}
};

int main(){
  Composite *a = new Composite("a");
  a->Add(new Composite("b"));
  a->Add(new Composite("c"));
  a->Add(new Composite("d"));
  a->Add(new Element("e"));
  a->Add(new Element("f"));
  a->Add(new Composite("g"));
  a->Get("g")->Add(new Composite ("h"));
  a->Get("g")->Add(new Composite ("i"));
  a->Get("g")->Add(new Composite ("j"));
  a->Get("c")->Add(new Composite ("k"));
  a->Get("c")->Add(new Composite ("l"));
  a->iterate();
  delete a;
  return 0;
}
