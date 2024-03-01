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

using namespace std;

int main() {
    // Pointer to SQLite connection
    sqlite3 *db;

    // Save any error messages
    char *zErrMsg = 0;

    // Save the result of opening the file
    int rc;

    // Save any SQL
    string sql;

    // Save the result of opening the file
    rc = sqlite3_open("tier_A.db", &db);
    
    // Take tier category from console input
    string category;
    cout << "Type to select Category\n";
    cout << "- ANIMES\n";
    cout << "- MOVIES_2024\n";
    getline(cin, category);

    if( rc ){
        // Show an error message
        cout << "DB Error: " << sqlite3_errmsg(db) << endl;
        // Close the connection
        sqlite3_close(db);
        // Return an error
        return(1);
    }

    string tier;
    string item;
    cout << "Type Item Title to Enter Item or X to Exit and Display Tier List\n";
    while(getline(cin, item) && item.compare("X")){
        cout << "Type Tier" << '\n';
        getline(cin, tier);

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

        cout << "Type Item Title to Enter Item or X to Exit and Display Tier List\n";
    }
    
    // Close the SQL connection
    sqlite3_close(db);

    printTier(category);
    
    return 0;
}