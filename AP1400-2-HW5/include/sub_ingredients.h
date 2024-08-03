#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H
#include "ingredient.h"
#include <string>

// 注意 \ 不可缺少，因为多行宏展开需要
#define DEFCLASS(className, price_unit)                             \
class className : public Ingredient {                               \
public:                                                             \
    className(size_t units) : Ingredient(price_unit, units) {       \
        this->name = #className;                                    \
    }                                                               \
    std::string get_name() override {                               \
        return this->name;                                          \
    }                                                               \
    Ingredient* clone() override {return new className(*this) ;}    \
};                                                                  \

DEFCLASS(Cinnamon, 5);
DEFCLASS(Chocolate, 5);
DEFCLASS(Sugar, 1);
DEFCLASS(Cookie, 10);
DEFCLASS(Espresso, 15);
DEFCLASS(Milk, 10);
DEFCLASS(MilkFoam, 5);
DEFCLASS(Water, 1);


#endif // SUB_INGREDIENTS_H