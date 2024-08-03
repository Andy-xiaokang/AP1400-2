#ifndef ESPRESSO_BASED_H
#define ESPRESSO_BASED_H
#include "ingredient.h"
#include <vector>

class EspressoBased
{
public:
    virtual std::string get_name() = 0;
    virtual double price() = 0;

    void brew();
    std::vector<Ingredient*>& get_ingredients();

    virtual ~EspressoBased();

protected:
    EspressoBased();
    EspressoBased(const EspressoBased& esp);
    void operator=(const EspressoBased& esp);
    // ingredient* 所指向的对象实际上是 sub_ingredients 的实例 Espresso Milk MilkFoam
    // 所以在调用 ptr->clone 时 调用的是子类对象的 clone 函数
    std::vector<Ingredient*> ingredients;
    std::string name;
};

#endif // ESPRESSO_BASED_H