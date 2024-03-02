/**
 * @tier.cpp
 *
 * Generates Tierlists with inputs from the user into an sqlite database and prints them
 * @version 1.0
 * @date 01-03-2024
 * @author A. Saikia
 *
 */

#include <iostream>
#include <string>
#include "printdb.hpp"
#include "sqlite3/sqlite3.h"

int main() {
    // Pointer to SQLite connection
    sqlite3 *db;

    // Save any error messages
    char *zErrMsg = 0;

    // Save the result of opening the file
    int rc;

    // Save any SQL
    std::string sql;

    // Save the result of opening the file
    rc = sqlite3_open("tier_A.db", &db);

    if( rc ){
        // Show an error message
        std::cout << "DB Error: " << sqlite3_errmsg(db) << "\n";
        // Close the connection
        sqlite3_close(db);
        // Return an error
        return(1);
    }


    // Take tier category from console input    
    int tier_id;
    std::cout << "Enter Tier ID to select Category\n";
    std::cout << "1 - ANIMES all time\n";
    std::cout << "2 - MOVIES watched in 2024\n";
    std::cin >> tier_id;   

    // Select table name and item type from database
    std::string category;
    std::string item_t;
    switch(tier_id) {
        case 1:
            category = "ANIMES";
            item_t = "Anime";
            break;
        case 2:
            category = "MOVIES_2024";
            item_t = "Movie";
            break;
    }

    std::string tier;
    std::string item;
    std::cout << "Type " << item_t << " Title to Enter " << item_t << " or X to Exit and Display Tier List\n";
    while(getline(std::cin >> std::ws, item) && item.compare("X")){
        std::cout << "Type Tier" << '\n';
        getline(std::cin, tier);
        std::cout << tier_id << "\n";
        // Save SQL insert data
        sql = "INSERT INTO " + category + " (" + item_t + ", Tier) "  \
                "VALUES ('" + item + "','" + tier + "'); " ;

        // Run the SQL (convert the string to a C-String with c_str() )
        rc = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);

        std::cout << "Type " << item_t << " Title to Enter " << item_t << " or X to Exit and Display Tier List\n";
    }
    
    // Close the SQL connection
    sqlite3_close(db);

    printTier(category);
    
    return 0;
}