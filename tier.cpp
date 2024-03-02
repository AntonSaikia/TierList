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
#include "printdb.h"
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
    
    // Take tier category from console input
    std::string category;
    std::cout << "Type to select Category\n";
    std::cout << "- ANIMES\n";
    std::cout << "- MOVIES_2024\n";
    getline(std::cin, category);

    if( rc ){
        // Show an error message
        std::cout << "DB Error: " << sqlite3_errmsg(db) << "\n";
        // Close the connection
        sqlite3_close(db);
        // Return an error
        return(1);
    }

    std::string tier;
    std::string item;
    std::cout << "Type Item Title to Enter Item or X to Exit and Display Tier List\n";
    while(getline(std::cin, item) && item.compare("X")){
        std::cout << "Type Tier" << '\n';
        getline(std::cin, tier);

        // Save SQL insert data
        if (!category.compare("ANIMES")){
            sql = "INSERT INTO ANIMES (Anime, Tier) "  \
                "VALUES ('" + item + "','" + tier + "'); " ;
        }
        else if (!category.compare("MOVIES_2024")){
            sql = "INSERT INTO MOVIES_2024 (Movie, Tier) "  \
                "VALUES ('" + item + "','" + tier + "'); " ;
        }

        // Run the SQL (convert the string to a C-String with c_str() )
        rc = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);

        std::cout << "Type Item Title to Enter Item or X to Exit and Display Tier List\n";
    }
    
    // Close the SQL connection
    sqlite3_close(db);

    printTier(category);
    
    return 0;
}