#include <stdio.h>
#include <typeinfo>
#include <list>
template<typename t1,int param>
class TClass{
};


typedef TClass<int, 1> C1;
typedef TClass<int, 2> C2;

int main(){
   C1 c1;
   C2 c2;
   std::list<C1> clist;
   clist.push_back(c1);
   clist.push_back(c2);
/*
   if(typeid(C1) == typeid(C2)){
	printf("ok!");
   }else{
	printf("oh...");
  }
*/
}
