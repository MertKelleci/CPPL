#include <iostream>

class Entity
{
public:
    // We've added this because 'dynamic_cast' requires only works with polymorphic class types.
    virtual void PrintName() {}
};

class Player : public Entity
{
};
class Enemy : public Entity
{
};

int main()
{
    Player *player = new Player();
    Entity *actuallyPlayer = player;
    Entity *actuallyEnemy = new Enemy();

    // Even though e1 is an Enemy type, this still works. If the enemy and player classes share a common function, you can even call that from this pointer.
    Player *p = (Player *)actuallyEnemy;

    // 'dynamic_cast' may seem like working for both of them but 'p0' will be a nullpointer.
    // It achieves that by storing Run-Time Type Information or RTTI. This adds some overhead because a) types need to store more information about themselves b) 'dynamic_cast' has to check if these two types are compatible in the runtime.
    Player *p0 = dynamic_cast<Player *>(actuallyEnemy);
    Player *p0 = dynamic_cast<Player *>(actuallyPlayer);
    std::cin.get();
}