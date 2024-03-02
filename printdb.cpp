/**
 * @printdb.cpp
 *
 * Prints a Tierlist from an sqlite database
 * @version 1.0
 * @date 01-03-2024
 * @author A. Saikia
 * 
 */

#include <iostream>
#include <vector>
#include "printdb.hpp"
#include "sqlite3/sqlite3.h"

/* Sqlite callback function enter the items into a vector */
int callback2v(void *p, int size, char **column_text, char **column_name) {
    TierItem DBitem;
    if (size == 0) {
        return -1;
    }
    auto &container = *static_cast<std::vector<TierItem>*>(p);
    DBitem.item = column_text[0];
    DBitem.tier = column_text[1];
    container.push_back(DBitem);

    return 0;
}

/* Sorts items into tier-specific vectors */
std::vector<std::string> tier(std::vector<TierItem> &v, std::string tier){
    std::vector<std::string> result;
        for (const auto &i: v){
            if(!tier.compare(i.tier)){
                result.push_back(i.item);
            }
        }
    return result;
}

/* Prints a tier vector */
void printvector(std::vector<std::string> &v){
    for (const auto &i: v){
        std::cout << " " << i << " |";
    }
    std::cout << "\n";
}

/* Takes data from the sqlite database and prints the entire tierlist*/
void printTier(std::string category){
    // Pointer to SQLite connections
    sqlite3 *db;

    // Save any error messages
    char *zErrMsg = 0;

    // Save the result of opening the file
    int rc;

    // Save any SQL
    std::string sql;

    // Save the result of opening the file
    rc = sqlite3_open("tier_A.db", &db);

    // Save entries to local vector 
    std::vector<TierItem> container;
    sql = "SELECT * FROM " + category + ";";
    rc = sqlite3_exec(db, sql.c_str(), callback2v, &container, &zErrMsg);

    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL ERROR: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else if(!category.compare("ANIMES")) {
        std::cout << "\nAnton's Anime Tier List\n\n";
    }
    else if(!category.compare("MOVIES_2024")) {
        std::cout << "\nAnton's Movies watched in 2024 Tier List\n\n";
    }

    // Close the SQL connection
    sqlite3_close(db);

    // Sort into Tiers
    std::vector<std::string> tierS = tier(container, "S");
    std::vector<std::string> tierA1 = tier(container, "A+");
    std::vector<std::string> tierA2 = tier(container, "A");
    std::vector<std::string> tierB1 = tier(container, "B+");
    std::vector<std::string> tierB2 = tier(container, "B");
    std::vector<std::string> tierC = tier(container, "C");

    std::cout << "S :";
    printvector(tierS);
    std::cout << "A+:";
    printvector(tierA1);
    std::cout << "A :";
    printvector(tierA2);
    std::cout << "B+:";
    printvector(tierB1);
    std::cout << "B :";
    printvector(tierB2);
    std::cout << "C :";
    printvector(tierC);
    std::cout << "\n";

}