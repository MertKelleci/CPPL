 #define string std::string

 #include <iostream>
 #include <string>

 class entity
 {
 public:
     virtual string getname() { return "entity"; }
 };

 class player : public entity
 {
 private:
     string m_name;

 public:
     player(const string &name) : m_name(name) {}
     string getname() override { return m_name; }
 };

 void printname(entity *entity)
 {
     std::cout << entity->getname() << std::endl;
 }

 int main()
 {
     entity *e = new entity();
     printname(e);

     player *p = new player("merdo");
     printname(p);

     std::cin.get();
 }