#include <iostream>
#include "StationManager.hpp"
#include "KitchenStation.hpp"
#include "Dish.hpp"

int main() {
    // Initialize StationManager
    StationManager manager;

    // Create KitchenStations
    KitchenStation* station1 = new KitchenStation("Grill Station");
    KitchenStation* station2 = new KitchenStation("Prep Station");
    KitchenStation* station3 = new KitchenStation("Dessert Station");

    // Add stations to the manager
    manager.addStation(station1);
    manager.addStation(station2);
    manager.addStation(station3);

    std::cout << "Stations added to StationManager.\n";

    // Test findStation
    KitchenStation* foundStation = manager.findStation("Grill Station");
    std::cout << "Found Station: " << (foundStation ? foundStation->getName() : "None") << "\n";

    // Test assignDishToStation and replenishIngredientAtStation
    Ingredient ingredient1("Tomato", 20, 2, 0.5);
    Ingredient ingredient2("Lettuce", 15, 1, 0.3);

    // Dish 1 assigned to Grill Station
    Dish* dish1 = new Dish("Grilled Chicken Sandwich", {ingredient1, ingredient2}, 15, 12.99, Dish::CuisineType::AMERICAN);
    manager.assignDishToStation("Grill Station", dish1);

    // Replenish Grill Station ingredients
    manager.replenishIngredientAtStation("Grill Station", Ingredient("Tomato", 30, 0, 0.5));
    manager.replenishIngredientAtStation("Grill Station", Ingredient("Lettuce", 20, 0, 0.3));

    std::cout << "Dishes and ingredients assigned to stations.\n";

    // Test moveStationToFront
    manager.moveStationToFront("Dessert Station");
    std::cout << "Moved Dessert Station to the front.\n";

    // Test mergeStations
    manager.mergeStations("Grill Station", "Prep Station");
    std::cout << "Merged Prep Station into Grill Station.\n";

    // Test canCompleteOrder
    bool canCompleteOrder = manager.canCompleteOrder("Grilled Chicken Sandwich");
    std::cout << "Can complete order for 'Grilled Chicken Sandwich': " << (canCompleteOrder ? "Yes" : "No") << "\n";

    // Test prepareDishAtStation
    bool dishPrepared = manager.prepareDishAtStation("Grill Station", "Grilled Chicken Sandwich");
    std::cout << "Prepared 'Grilled Chicken Sandwich' at Grill Station: " << (dishPrepared ? "Yes" : "No") << "\n";

    // Test removeStation
    manager.removeStation("Dessert Station");
    std::cout << "Removed Dessert Station from StationManager.\n";

    // Clean up
    manager.clear();

    return 0;
}
