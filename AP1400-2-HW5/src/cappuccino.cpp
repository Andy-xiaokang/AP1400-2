#include "cappuccino.h"
#include "sub_ingredients.h"

Cappuccino::Cappuccino() : EspressoBased() {
    name = "Cappuccino";
    this->ingredients.push_back(new Espresso(2));
    this->ingredients.push_back(new Milk(2));
    this->ingredients.push_back(new MilkFoam(1));
}

void Cappuccino::add_side_item(Ingredient* side) {
    side_items.push_back(side);
}

Cappuccino::Cappuccino(const Cappuccino &cap) : EspressoBased(cap){
//    for(const auto& i : ingredients)
//        delete i;
//    ingredients.clear();
//    for(const auto& i : side_items)
//        delete i;
//    side_items.clear();
    for (auto& ptr : cap.side_items) {
        side_items.push_back(ptr->clone());
    }
//    for (auto& ptr : cap.ingredients) {
//        ingredients.push_back(ptr->clone());
//    }
}

Cappuccino::~Cappuccino() {
    for (const auto & i : side_items) {
        delete i;
    }
    side_items.clear();
}

void Cappuccino::operator=(const Cappuccino &cap) {
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

std::string Cappuccino::get_name() {
    return name;
}

double Cappuccino::price() {
    double result = 0;
    for (auto& ptr : side_items) {
        result += ptr->price();
    }
    for (auto& ptr : ingredients) {
        result += ptr->price();
    }
    return result;
}

std::vector<Ingredient *> &Cappuccino::get_side_items() {
    return side_items;
}