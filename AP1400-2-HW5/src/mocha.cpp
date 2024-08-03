#include "mocha.h"
#include "sub_ingredients.h"

Mocha::Mocha() : EspressoBased() {
    name = "Mocha";
    this->ingredients.push_back(new Espresso(2));
    this->ingredients.push_back(new Milk(2));
    this->ingredients.push_back(new MilkFoam(1));
    this->ingredients.push_back(new Chocolate(1));
}

void Mocha::add_side_item(Ingredient* side) {
    side_items.push_back(side);
}

Mocha::Mocha(const Mocha &cap) : EspressoBased(cap){
    for (auto& ptr : cap.side_items) {
        side_items.push_back(ptr->clone());
    }
}

Mocha::~Mocha() {
    for (const auto & i : side_items) {
        delete i;
    }
    side_items.clear();
}

void Mocha::operator=(const Mocha &cap) {
    if (this != &cap) {
        for(const auto& i : ingredients)
            delete i;
        ingredients.clear();
        for(const auto& i : side_items)
            delete i;
        side_items.clear();
        for (auto& ptr : cap.side_items) {
            side_items.push_back(ptr->clone());
        }
        for (auto& ptr : cap.ingredients) {
            ingredients.push_back(ptr->clone());
        }
    }
}

std::string Mocha::get_name() {
    return name;
}

double Mocha::price() {
    double result = 0;
    for (auto& ptr : side_items) {
        result += ptr->price();
    }
    for (auto& ptr : ingredients) {
        result += ptr->price();
    }
    return result;
}

std::vector<Ingredient *> &Mocha::get_side_items() {
    return side_items;
}