#include <iostream>
#include <string>

class Entity
{
private:
    int m_X;
    std::string m_Name;
    int *m_Y;
    mutable int var;

public:
	// Since GetX is declared const, it can't change any member variables of the class, but since var is declared mutable, it can be changed inside a const function
    int GetX() const
    {
        var = 2;
        return m_X;
    }

	// 'const int *const' means that the pointer itself is constant and the value it points to is also constant. So you can't change where m_Y points to and you can't change the value of m_Y. And the final 'const' at the end of the function declaration means that this function can't change any member variables of the class.
    const int *const GetY() const
    {
        return m_Y;
    }

	// 'const std::string&' means that the function returns a reference to a constant string. So you can't change the value of the string that is returned by this function, but you can change where m_Name points to. And the final 'const' at the end of the function declaration means that this function can't change any member variables of the class.
    const std::string& GetName() const { return m_Name; }
};

// Since Entity is declaraed const you can't call any method that isn't declared const because what if the function were to make changes to the object.
void PrintEntity(const Entity& e)
{
    std::cout << e.GetX() << std::endl;
}

int main()
{
    const int MAX_AGE = 90;
    // const int* a = new int == int const* a =new int;;
	// *a = 2; -> Won't work. You can change where a points to but you can't change the value of a.
    // a = (int*)&MAX_AGE;

    // int* const a = new int;
    // *a = 2;
	// a = (int*)&MAX_AGE; -> Won't work. You can change the value of a but you can't change where a points to.

    // const int* const a = new int;
    // *a = 2 -> won't work;
	// a = (int*)&MAX_AGE; -> Won't work. You can't change the value of a and you can't change where a points to.

    Entity e;

    int x = 8;
    // f = [&x] can be used also, no need to declare mutable in that case.
	// The following is a lambda function that captures x by value (creating a copy). Since x is captured by value, it is a copy of the original x, and any changes made to x inside the lambda function will not affect the original x outside the lambda function. However, since the lambda function is declared mutable, it allows us to modify the captured variable x inside the lambda function.
    auto f = [=]() mutable
    {
        x++;
        std::cout << x << std::endl;
    };

    f();
	// Since we captured x by value, the original x is not modified by the lambda function, so it will still be 8 when we print it here.
    std::cin.get();
}