/**
 * @file KitchenStation.cpp
 * @brief This file contains the implementation of the KitchenStation class, which represents a kitchen station in a virtual bistro simulation.
 *
 * The KitchenStation class includes methods to manage and present the details of a kitchen station, including name, dishes, and ingredient stock.
 * The implementation ensures that dishes are assigned to the station, ingredients are replenished, and dishes are prepared.
 *
 * @date 11/02/2024
 * @author Mitchell Lipyansky
*/

#include "KitchenStation.hpp"
#include <algorithm>  // For std::remove

/**
 * Default Constructor
 * @post: Initializes an empty kitchen station with default values.
*/
KitchenStation::KitchenStation() : station_name_("UNKNOWN") {}

/**
 * Parameterized Constructor
 * @param station_name A string representing the station's name.
 * @post: Initializes a kitchen station with the given name.
*/
KitchenStation::KitchenStation(const std::string& station_name) : station_name_(station_name) {}

/**
 * Destructor
 * @post: Deallocates all dynamically allocated dishes in the station.
*/
KitchenStation::~KitchenStation() {
    for (auto dish : dishes_) {
        delete dish;
    }
    dishes_.clear();  // Clear the list of dishes
}

/**
 * Retrieves the name of the kitchen station.
 * @return: The name of the station.
*/
std::string KitchenStation::getName() const {
    return station_name_;
}

/**
 * Sets the name of the kitchen station.
 * @param name A string representing the new station name.
 * @post: Updates the station's name.
*/
void KitchenStation::setName(const std::string& name) {
    station_name_ = name;
}

/**
 * Retrieves the list of dishes assigned to the kitchen station.
 * @return A vector of pointers to Dish objects assigned to the station.
*/
std::vector<Dish*> KitchenStation::getDishes() const {
    return dishes_;
}

/**
 * Retrieves the ingredient stock available at the kitchen station.
* @return A vector of Ingredient objects representing the station's
ingredient stock.
*/
std::vector<Ingredient> KitchenStation::getIngredientsStock() const {
    return ingredients_stock_;
}

/**
 * Assigns a dish to the station.
 * @param dish A pointer to a Dish object.
 * @post: Adds the dish to the station's list of dishes if not
already present.
 * @return: True if the dish was added successfully; false
otherwise.
*/
bool KitchenStation::assignDishToStation(Dish* dish) {
    // Check if dish already assigned
    for (auto assigned_dish : dishes_) {
        if (assigned_dish == dish) {
            return false;  // Dish already assigned, return false
        }
    }
    dishes_.push_back(dish);  // Add dish to the list
    return true;
}

/**
 * Replenishes the station's ingredient stock.
 * @param ingredient An Ingredient object.
 * @post: Adds the ingredient to the station's stock or updates the
quantity if it already exists.
*/
void KitchenStation::replenishStationIngredients(const Ingredient& ingredient) {
    for (auto& stock_ingredient : ingredients_stock_) {
        if (stock_ingredient.name == ingredient.name) {
            stock_ingredient.quantity += ingredient.quantity;  // Update quantity if ingredient exists
            return;
        }
    }
    // If ingredient does not exist, add it
    ingredients_stock_.push_back(ingredient);
}

/**
 * Checks if the station can complete an order for a specific dish.
 * @param dish_name A string representing the name of the dish.
 * @return: True if the station has the dish assigned and all
required ingredients are in stock; false otherwise.
*/
bool KitchenStation::canCompleteOrder(const std::string& dish_name) const {
    for (auto dish : dishes_) {
        if (dish->getName() == dish_name) {
            for (const auto& ingredient : dish->getIngredients()) {
                bool found = false;
                for (const auto& stock_ingredient : ingredients_stock_) {
                    if (stock_ingredient.name == ingredient.name && stock_ingredient.quantity >= ingredient.required_quantity) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    return false;  // Required ingredient not found
                }
            }
            return true;  // All ingredients are in stock
        }
    }
    return false;  // Dish is not assigned to this station
}

/**
 * Prepares a dish if possible.
 * @param dish_name A string representing the name of the dish.
 * @post: If the dish can be prepared, reduce the quantities of the
used ingredients accordingly. If the stock ingredient is depleted to
0, remove the ingredient from the Kitchen Station.
* @return: True if the dish was prepared successfully; false
 otherwise.
*/
bool KitchenStation::prepareDish(const std::string& dish_name) {
    // Check if station has the required dish and ingredients
    if (!canCompleteOrder(dish_name)) {
        return false;
    }

    for (Dish* dish : dishes_) {
        if (dish->getName() == dish_name) {
            const auto& dish_ingredients = dish->getIngredients();

            // For each dish ingredient, look for it in the station's ingredient stock
            for (const auto& dish_ingredient : dish_ingredients) {
                for (auto& stock_ingredient : ingredients_stock_) {
                    if (dish_ingredient.name == stock_ingredient.name) {
                        // Subtract the required quantity
                        stock_ingredient.quantity -= dish_ingredient.required_quantity;
                        if (stock_ingredient.quantity <= 0) {
                            stock_ingredient.quantity = 0;
                        }
                        break;
                    }
                }
            }
        }
    }

    // Remove ingredients with 0 quantity
    ingredients_stock_.erase(
            std::remove_if(ingredients_stock_.begin(), ingredients_stock_.end(),
                           [](const Ingredient& ingredient) { return ingredient.quantity == 0; }),
            ingredients_stock_.end()
    );

    return true;
}
