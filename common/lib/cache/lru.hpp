#ifndef __LRU_H__
#define __LRU_H__

#include<list>
#include<unordered_map>
#include<iostream>

template<typename N, typename M, typename L, typename O>
class LRUCache{
private:
        int capacity;
        int size;
        bool debug;
        L dll;
        M ma;
        N *remove_internal(){
          if(size == 0)return nullptr;
          N* lruEl =dll.front();
          ma.erase(ma.find(lruEl->get_key()));
          dll.pop_front();
          size--;
          return lruEl;
        }
public:
        LRUCache(int csize, bool dbg);
        int get_size();
        N *get();
        void put(int n, const O &value);
        N *get(int n);
        void process(int n);
        bool remove();
        bool remove(int n);
};

template<typename N, typename M, typename L, typename O>
LRUCache<N, M, L, O>::LRUCache(int csize, bool dbg): debug(dbg), capacity(csize), size(0){}

template<typename N, typename M, typename L, typename O>
int LRUCache<N, M, L, O>::get_size(){ return size ;}

template<typename N, typename M, typename L, typename O>
N *LRUCache<N, M, L, O>::get(){
  if(size != 0) return dll.back();
  return nullptr;
}

template<typename N, typename M, typename L, typename O>
void LRUCache<N, M, L, O>::put(int n, const O &value){
  N *a = nullptr;
  typename std::unordered_map<int, std::_List_iterator<N *> >::iterator it = ma.find(n);
  if(it != ma.end()){
    dll.splice(dll.end(), dll, (*it).second);
    a = *((*it).second);
  }
  if(a == nullptr){
    if(size == capacity){
      N *lruEl = nullptr;
      lruEl = remove_internal();
      if(debug)
        std::cout << "Put :: " << "[" << n << ": " << value << "] replaced " << "[" << \
               lruEl->get_key() << ": " << lruEl->get_value() <<  "]" << std::endl;
      delete lruEl;
    }
    size++;
    N *element = new N(n, value);
    auto it1 = dll.insert(dll.end(), element);
    ma.insert(make_pair(element->get_key(), it1));
  }
}

template<typename N, typename M, typename L, typename O>
N *LRUCache<N, M, L, O>::get(int n){
  N *a = nullptr;
  typename std::unordered_map<int, std::_List_iterator<N *> >::iterator it = ma.find(n);
  if(it != ma.end()){
    dll.splice(dll.end(), dll, (*it).second);
    a = *((*it).second);
  }
  return a; 
}

template<typename N, typename M, typename L, typename O>
void LRUCache<N, M, L, O>::process(int n){
  N *a  = get(n);
  if(a != nullptr){
    std::cout << "[" << n << ": " << a->get_value() << "]" << std::endl;
  }else{
    std::cout << "Process :: Cache Miss " << n << std::endl;
  }
  return;
}

template<typename N, typename M, typename L, typename O>
bool LRUCache<N, M, L, O>::remove(){
  N *lruEl = remove_internal();
  if (lruEl){
    delete lruEl;
    return true;
  }else{
    return false;
  }
}


template<typename N, typename M, typename L, typename O>
bool LRUCache<N, M, L, O>::remove(int n){
  N *lruEl = nullptr;
  typename std::unordered_map<int, std::_List_iterator<N *> >::iterator it = ma.find(n);
  if(it != ma.end()){
    lruEl = *((*it).second);
  }
  if(lruEl){
    ma.erase(n);
    dll.remove(lruEl);
    delete lruEl;
    size--;
    return true;
  }
  return false;
}

#endif
