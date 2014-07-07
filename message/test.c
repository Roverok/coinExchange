struct s1{
 int a;
};

struct s2{
 int b;
};
union message{
    struct {
	int a;
    };
    struct {
	int a;
	int b;
   };
};

int main(){
  union message msg;
  msg.b =20;
}
