/**
 * @file Dish.cpp
 * @brief This file contains the implementation of the Dish class, which represents a dish in a virtual bistro simulation.
 *
 * The Dish class includes methods to manage and present the details of a dish, including name, ingredients, preparation time, price, and cuisine type.
 * The implementation ensures that the dish name is validated and correctly formatted.
 *
 * @date 10/31/2024
 * @author Mitchell Lipyansky
*/

#include "Dish.hpp"

/**
     * Default constructor.
     * Initializes all private members with default values:
     * - name: "UNKNOWN"
     * - ingredients: Empty list
     * - prep_time: 0
     * - price: 0.0
     * - cuisine_type: OTHER
*/
Dish::Dish() : name_("UNKNOWN"), ingredients_({}), prep_time_(0), price_(0.0), cuisine_type_(CuisineType::OTHER) {}

/**
     * Parameterized constructor.
     * @param name A reference to the name of the dish.
     * @param ingredients A reference to a list of ingredients (default is an empty list).
     * @param prep_time The preparation time in minutes (default is 0).
     * @param price The price of the dish (default is 0.0).
     * @param cuisine_type The cuisine type of the dish (a CuisineType enum) with default value OTHER.
     * @post The private members are set to the values of the corresponding parameters.
*/
Dish::Dish(const std::string& name, const std::vector<Ingredient>& ingredients, int prep_time, double price, CuisineType cuisine_type)
    : ingredients_(ingredients), prep_time_(prep_time), price_(price), cuisine_type_(cuisine_type) {
    setName(name);  // Use setName to validate the name
}

/**
     * @return The name of the dish.
*/
std::string Dish::getName() const {
    return name_;
}

/**
     * @return The list of ingredients used in the dish.
*/
std::vector<Ingredient> Dish::getIngredients() const {
    return ingredients_;
}

/**
     * @return The preparation time in minutes.
*/
int Dish::getPrepTime() const {
    return prep_time_;
}

/**
     * @return The price of the dish.
*/
double Dish::getPrice() const {
    return price_;
}

/**
     * @return The cuisine type of the dish in string form.
*/
std::string Dish::getCuisineType() const {
    switch (cuisine_type_) {
        case CuisineType::ITALIAN: return "ITALIAN";
        case CuisineType::MEXICAN: return "MEXICAN";
        case CuisineType::CHINESE: return "CHINESE";
        case CuisineType::INDIAN: return "INDIAN";
        case CuisineType::AMERICAN: return "AMERICAN";
        case CuisineType::FRENCH: return "FRENCH";
        default: return "OTHER";
    }
}

/**
     * Sets the name of the dish.
     * @param name A reference to the new name of the dish.
     * @post Sets the private member `name_` to the value of the parameter. If the name contains non-alphabetic characters, it is set to "UNKNOWN".
*/
void Dish::setName(const std::string& name) {
    if (isValidName(name)) {
        name_ = name;
    } else {
        name_ = "UNKNOWN";
    }
}

/**
     * Sets the list of ingredients.
     * @param ingredients A reference to the new list of ingredients.
     * @post Sets the private member `ingredients_` to the value of the parameter.
*/
void Dish::setIngredients(const std::vector<Ingredient>& ingredients) {
    ingredients_ = ingredients;
}

/**
     * Sets the preparation time.
     * @param prep_time The new preparation time in minutes.
     * @post Sets the private member `prep_time_` to the value of the parameter.
*/
void Dish::setPrepTime(const int& prep_time) {
    prep_time_ = prep_time;
}

/**
     * Sets the price of the dish.
     * @param price The new price of the dish.
     * @post Sets the private member `price_` to the value of the parameter.
*/
void Dish::setPrice(const double& price) {
    price_ = price;
}

/**
     * Sets the cuisine type of the dish.
     * @param cuisine_type The new cuisine type of the dish.
     * @post Sets the private member `cuisine_type_` to the value of the parameter.
*/
void Dish::setCuisineType(const CuisineType& cuisine_type) {
    cuisine_type_ = cuisine_type;
}

/**
     * Checks if the name is valid.
     * @param name The name to be validated.
     * @return True if the name contains only alphabetic characters and spaces; false otherwise.
*/
bool Dish::isValidName(const std::string& name) const {
    for (char c : name) {
        if (!std::isalpha(c) && !std::isspace(c)) {  // Check if each character is a letter or space
            return false;  // Name contains non-alphabetic characters other than spaces
        }
    }
    return true;  // Name is valid
}

/**
     @param : A const reference to the right-hand side of the `==` operator.
    @return : Returns true if the right-hand side dish is "equal", false
    otherwise.
                Two dishes are equal if they have the same name, same cuisine
    type, same preparation time, and the same price.
*/
bool Dish::operator==(const Dish& rhs) const {
    return name_ == rhs.name_ && prep_time_ == rhs.prep_time_ && 
    price_ == rhs.price_ && cuisine_type_ == rhs.cuisine_type_;
}

/**
     @param : A const reference to the right-hand side of the `!=` operator.
    @return : Returns true if the right-hand side dish is NOT "equal" (`!=`),
    false otherwise.
                Two dishes are NOT equal if any of their name, cuisine type,
    preparation time, or price are not equal.
*/
bool Dish::operator!=(const Dish& rhs) const {
    return !(*this == rhs);
}