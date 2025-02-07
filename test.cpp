#include "Kitchen.hpp"
#include <iostream>

int main() {
    // Test: kitchenReport function
    std::cout << "---- Testing kitchenReport Function ----" << std::endl;

    // Create a Kitchen object
    Kitchen kitchen;

    // Create some dishes
    Dish dish1("Spaghetti", {"Pasta", "Tomato Sauce", "Basil"}, 20, 12.50, Dish::CuisineType::ITALIAN);
    Dish dish2("Beef Stew", {"Beef", "Potatoes", "Carrots", "Onions", "Garlic"}, 90, 20.99, Dish::CuisineType::AMERICAN);  // Elaborate
    Dish dish3("Tacos", {"Tortilla", "Beef", "Lettuce"}, 15, 9.99, Dish::CuisineType::MEXICAN);
    Dish dish4("Pizza", {"Dough", "Tomato Sauce", "Cheese"}, 30, 14.99, Dish::CuisineType::ITALIAN);  // Elaborate

    // Add dishes to the kitchen
    kitchen.newOrder(dish1);
    kitchen.newOrder(dish2);  // Elaborate
    kitchen.newOrder(dish3);
    kitchen.newOrder(dish4);  // Elaborate

    // Call kitchenReport to output the current state of the kitchen
    kitchen.kitchenReport();

    return 0;
}
