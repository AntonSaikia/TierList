#include <iostream>
#include <string>
#include "sqlite3/sqlite3.h"

using namespace std;

// Create a callback function  
int callback(void *data, int argc, char **argv, char **azColName){
    fprintf(stderr, "%s: ", (const char*)data);
    // int argc: holds the number of results
    // (array) azColName: holds each column returned
    // (array) argv: holds each value

    for(int i = 0; i < argc; i++) {
        
        // Show column name, value, and newline
        cout << azColName[i] << ": " << argv[i] << endl;
    
    }

    // Insert a newline
    cout << endl;

    // Return successful
    return 0;
}
  
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
    cout << "Type Item Title to Enter Item or X to Exit" << '\n';
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
        rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

        cout << "Type Item Title to Enter Item or X to Exit" << '\n';
    }
    
    // Close the SQL connection
    sqlite3_close(db);
    
    return 0;
}