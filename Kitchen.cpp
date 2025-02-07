/**
 * @file Kitchen.cpp
 * @brief This file contains the implementation of the Kitchen class, which is a subclass of ArrayBag.
 *
 * The Kitchen class includes attributes to represent the sum of prep times and the number of elaborate dishes.
 * It provides a constructor and several unique methods for kitchen calculations and related Dish functions.
 *
 * @date 10/04/2024
 * @author Mitchell Lipyansky
 */

#include "Kitchen.hpp"
#include "Dish.hpp"
#include <cmath>  // For rounding
#include <iomanip>  // For setting precision

/**
  * Default constructor.
  * Default-initializes all private members.
*/
Kitchen::Kitchen() : totalprep_time_(0), countelaborate(0) {
}

/**
    * @param : A reference to a `Dish` being added to the kitchen.
    * @post : If the given `Dish` is not already in the kitchen, adds the
    `Dish` to the kitchen and updates the preparation time sum and vegetarian
    dish count if the dish is vegetarian.
    * @return : Returns true if a `Dish` was successfully added to the
    kitchen, false otherwise.
           Hint: Use the above definition of equality to help determine if a
           `Dish` is already in the kitchen.
*/
bool Kitchen::newOrder(const Dish& new_dish) {
    // Check if the dish already exists in the kitchen
    if (contains(new_dish)) {
        return false;
    }

    // Add the dish to the kitchen using the ArrayBag::add method
    bool added_successfully = add(new_dish);

    if (added_successfully) {
        // Update the total preparation time
        totalprep_time_ += new_dish.getPrepTime();

        // Check if the dish is elaborate and update the count
        if (new_dish.getIngredients().size() >= 5 && new_dish.getPrepTime() >= 60) {
            countelaborate++;
        }
    }
    return added_successfully;
}

/**
    * @param : A reference to a `Dish` leaving the kitchen.
    * @return : Returns true if a dish was successfully removed from the
    kitchen (i.e.,
    items_), false otherwise.
    * @post : Removes the dish from the kitchen and updates the preparation
    time sum.
    count.
*/
bool Kitchen::serveDish(const Dish& dish) {
    // Check if the dish is in the kitchen
    if (!contains(dish)) {
        return false;
    }

    // Remove the dish using the inherited remove() method
    bool removed_successfully = remove(dish);

    if (removed_successfully) {
        // Update the total preparation time
        totalprep_time_ -= dish.getPrepTime();

        // Check and update elaborate count
        if (dish.getIngredients().size() >= 5 && dish.getPrepTime() >= 60) {
            countelaborate--;
        }
    }
    return removed_successfully;
}

/**
    * @return : The integer sum of preparation times for all the dishes
    currently in the kitchen.
*/
int Kitchen::getPrepTimeSum() const {
    return totalprep_time_;
}

/**
    * @return : The average preparation time (int) of all the dishes in the
    kitchen. The lowest possible average prep time should be 0.
    * @post : Computes the average preparation time (double) of the kitchen
    rounded to the NEAREST integer.
*/
int Kitchen::calculateAvgPrepTime() const {
    int dish_count = getCurrentSize();

    // If no dishes are in the kitchen, return 0
    if (dish_count == 0) {
        return 0;
    }

    // Calculate the average preparation time and round to the nearest integer
    double avg_prep_time = static_cast<double>(totalprep_time_) / dish_count;
    return std::round(avg_prep_time);
}

/**
    * @return : The integer count of the elaborate dishes in the kitchen.
*/
int Kitchen::elaborateDishCount() const {
    return countelaborate;
}

/**
    * @return : The percentage (double) of all the elaborate dishes in the
    kitchen. The lowest possible percentage should be 0%.
    * @post : Computes the percentage of elaborate dishes in the kitchen
    rounded up to 2 decimal places.
*/
double Kitchen::calculateElaboratePercentage() const {
    int dish_count = getCurrentSize();

    // If no dishes are in the kitchen, return 0
    if (dish_count == 0) {
        return 0;
    }

    // Calculate the percentage of elaborate dishes
    double elaborate_percentage = (static_cast<double>(countelaborate) / dish_count) * 100;

    // Round to two decimal places
    return std::round(elaborate_percentage * 100) / 100;
}

/**
    * @param : A reference to a string representing a cuisine type with a
    value in
             ["ITALIAN", "MEXICAN", "CHINESE", "INDIAN", "AMERICAN",
                "FRENCH", "OTHER"].
    * @return : An integer tally of the number of dishes in the kitchen of the
    given cuisine type.
             If the argument string does not match one of the expected
                cuisine types, the tally is zero.
                 NOTE: No pre-processing of the input string necessary, only
                    uppercase input will match.
*/
int Kitchen::tallyCuisineTypes(const std::string& cuisine_type) const {
    int count = 0;

    // Iterate over all dishes in the kitchen
    for (int i = 0; i < getCurrentSize(); i++) {
        Dish dish = items_[i];

        // Check if the dish's cuisine type matches the input string
        if (dish.getCuisineType() == cuisine_type) {
            count++;
        }
    }
    return count;
}

/**
    * @param : A reference to an integer representing the preparation time
    threshold of the dishes to be removed from
             the kitchen, with a default value of 0.
    * @post : Removes all dishes from the kitchen whose preparation time is
    less than the given time.
           If no time is given, removes all dishes from the kitchen. Ignore
    negative input.
    * @return : The number of dishes removed from the kitchen.
*/
int Kitchen::releaseDishesBelowPrepTime(int prep_time_threshold) {
    if (prep_time_threshold < 0) {
        return 0;  // Ignore negative input
    }

    int removed_count = 0;

    // If the threshold is 0, remove all dishes from the kitchen
    if (prep_time_threshold == 0) {
        removed_count = getCurrentSize();  // All dishes will be removed, so removed count equals the current size
        clear();  // Use ArrayBag clear function to remove all items from the kitchen
        return removed_count;
    }

    // Iterate through the kitchen starting from last element
    for (int i = getCurrentSize() - 1; i >= 0; --i) {
        // If the dish's prep time is less than the threshold, remove it
        if (items_[i].getPrepTime() < prep_time_threshold) {
            bool removed = remove(items_[i]);
            if (removed) {
                removed_count++;
            }
        }
    }
    return removed_count;
}

/**
    * @param : A reference to a string representing a cuisine type with a
    value in
             ["ITALIAN", "MEXICAN", "CHINESE", "INDIAN", "AMERICAN",
            "FRENCH", "OTHER"],
        or a default value of "ALL" if no cuisine type is given.
    * @post : Removes all dishes from the kitchen whose cuisine type matches
    the given type.
           If no cuisine type is given, removes all dishes from the kitchen.
    * @return : The number of dishes removed from the kitchen.
           NOTE: No pre-processing of the input string necessary, only
        uppercase input will match.
           If the input string does not match one of the expected cuisine
    types, do not remove any dishes.
*/
int Kitchen::releaseDishesOfCuisineType(const std::string& cuisine_type) {
    int removed_count = 0;

    // If the input is "ALL", remove all dishes
    if (cuisine_type == "ALL") {
        removed_count = getCurrentSize();  // All dishes will be removed, so removed count equals the current size
        clear();  // Use ArrayBag clear function to remove all items from the kitchen
        return removed_count;
    }

    // Match the string input to the corresponding CuisineType enum
    Dish::CuisineType type;
    if (cuisine_type == "ITALIAN") {
        type = Dish::CuisineType::ITALIAN;
    } else if (cuisine_type == "MEXICAN") {
        type = Dish::CuisineType::MEXICAN;
    } else if (cuisine_type == "CHINESE") {
        type = Dish::CuisineType::CHINESE;
    } else if (cuisine_type == "INDIAN") {
        type = Dish::CuisineType::INDIAN;
    } else if (cuisine_type == "AMERICAN") {
        type = Dish::CuisineType::AMERICAN;
    } else if (cuisine_type == "FRENCH") {
        type = Dish::CuisineType::FRENCH;
    } else if (cuisine_type == "OTHER") {
        type = Dish::CuisineType::OTHER;
    } else {
        return 0;
    }

    // Iterate through the kitchen starting from the last element
    for (int i = getCurrentSize() - 1; i >= 0; --i) {
        // Convert the enum to a string for comparison
        std::string current_cuisine = items_[i].getCuisineType();

        // If the dish's cuisine type matches the input type, remove it
        if (current_cuisine == cuisine_type) {
            bool removed = remove(items_[i]);
            if (removed) {
                removed_count++;
            }
        }
    }
    return removed_count;
}

/**
    * @post : Outputs a report of the dishes currently in the kitchen in the
    form:
             "ITALIAN: {x}\nMEXICAN: {x}\nCHINESE: {x}\nINDIAN:
    {x}\nAMERICAN: {x}\nFRENCH: {x}\nOTHER: {x}\n\n
              AVERAGE PREP TIME: {x}\nELABORATE: {x}%\n"
             Note that the average preparation time should be rounded to the
             NEAREST integer, and the
             percentage of elaborate dishes in the kitchen should be
    rounded to 2 decimal places.
     Example output:
    ITALIAN: 2
    MEXICAN: 3
    CHINESE: 2
    INDIAN: 1
    AMERICAN: 1
    FRENCH: 2
    OTHER: 2

    AVERAGE PREP TIME: 62
    ELABORATE: 53.85%
*/
void Kitchen::kitchenReport() const {
    // Cuisine type counts
    int italianCount = tallyCuisineTypes("ITALIAN");
    int mexicanCount = tallyCuisineTypes("MEXICAN");
    int chineseCount = tallyCuisineTypes("CHINESE");
    int indianCount = tallyCuisineTypes("INDIAN");
    int americanCount = tallyCuisineTypes("AMERICAN");
    int frenchCount = tallyCuisineTypes("FRENCH");
    int otherCount = tallyCuisineTypes("OTHER");

    // Calculate the average preparation time
    int avgPrepTime = calculateAvgPrepTime();

    // Calculate the percentage of elaborate dishes
    double elaboratePercentage = calculateElaboratePercentage();

    // Output the cuisine type counts
    std::cout << "ITALIAN: " << italianCount << std::endl;
    std::cout << "MEXICAN: " << mexicanCount << std::endl;
    std::cout << "CHINESE: " << chineseCount << std::endl;
    std::cout << "INDIAN: " << indianCount << std::endl;
    std::cout << "AMERICAN: " << americanCount << std::endl;
    std::cout << "FRENCH: " << frenchCount << std::endl;
    std::cout << "OTHER: " << otherCount << std::endl;

    // Output the average preparation time
    std::cout << "\nAVERAGE PREP TIME: " << avgPrepTime << std::endl;

    // Output the percentage of elaborate dishes, rounded to two decimal places
    std::cout << "ELABORATE: " << std::fixed << std::setprecision(2) << elaboratePercentage << "%" << std::endl;
}
