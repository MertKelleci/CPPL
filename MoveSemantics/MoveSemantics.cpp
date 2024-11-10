#include <iostream>
#include <string.h>

class String
{
public:
    String() = default;
    String(const char *string)
    {
        printf("Created\n");
        m_Size = strlen(string);
        m_Data = new char[m_Size];
        memcpy(m_Data, string, m_Size);
    }
    String(const String &string) : m_Size(string.m_Size)
    {
        printf("Copied\n");
        m_Data = new char[m_Size];
        memcpy(m_Data, string.m_Data, m_Size);
    }
    String(String &&string)
    {
        printf("Moved\n");
        m_Data = new char[m_Size];
        m_Size = string.m_Size;
        // Instead of copying, we get the pointer of the original data.
        m_Data = string.m_Data;

        // The reason for this is when the previous String instance is deleted, we don't lose the 'm_Data'.
        string.m_Size = 0;
        string.m_Data = nullptr;
    }
    ~String()
    {
        printf("Destroyed\n");
        delete m_Data;
    }

    // This is a move constructor.
    String(const String &&other) {}

    void Print()
    {
        for (__UINT32_TYPE__ i = 0; i < m_Size; i++)
            printf("%c", m_Data[i]);

        printf("\n");
    }

private:
    char *m_Data;
    __UINT32_TYPE__ m_Size;
};

class Entity
{
public:
    Entity(const String &name) : m_Name(name)
    {
    }
    // This constructor changed from taking a reference to taking a rvalue reference, in order to move the string instead of copying it.
    // You have to explicitly cast it as a rvalue reference for this to call correct String constructor.
    Entity(String &&name) : m_Name((String &&)name)
    {
    }

    void PrintName() { m_Name.Print(); }

private:
    String m_Name;
};

int main()
{
    // The string gets created on main function, and get coppied when creating the Entity instance.
    Entity entity("Peter");
    entity.PrintName();
    std::cin.get();
}