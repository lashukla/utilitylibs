#include<list>
#include<unordered_map>
#include<iostream>
#include<string>
#include "lru.hpp"

using namespace std;

class Node{
private:
        int key;
        char *value;
public:
        Node(int k, string v){
          key = k;
          value = new char[v.size() + 1];
          copy(v.begin(), v.end(), value);
          value[v.size()] = 0;
        }
        char *get_value(){return value;}
        int get_key(){return key;}
        Node() = delete;
        ~Node(){ delete value; }
};

int main(int argc, char **argv){
  bool debug = false;
  const string &dbg = "-debug";
  if(argc > 1 && dbg.compare(argv[1]) == 0){
    debug = true;
  }
  LRUCache<Node, unordered_map<int, list<Node *>::iterator>, list<Node *>, string > lru(5, debug);
#if 1
  lru.put(1, "America");
  lru.put(2, "India");
  lru.put(3, "China");
  lru.put(4, "Australia");
  lru.put(5, "Canada");
  Node *b = lru.get();
  cout << "[" << b->get_key() << ": " << b->get_value() << "]" << endl;
  lru.process(1);
  lru.process(2);
  lru.put(6, "France");
  Node *a = lru.get();
  cout << "[" << a->get_key() << ": " << a->get_value() << "]" << endl;
#endif
  return 0;
}
