#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "sqlite3.h"

using namespace std;

int callback(void *p, int size, char **column_text, char **column_name) {
    if (size == 0) return -1;
    auto &container = *static_cast<vector<pair<string, string>>*>(p);
    if (!column_text[0]) container.push_back(make_pair(column_text[1],column_text[0]));
    else container.push_back(make_pair(column_text[1],column_text[0]));
    return 0;
}

void printvector(vector<string> &v){
    for (const auto &i: v){
        cout << " " << i << " |";
    }
    cout << "\n";
}

vector<string> tier(vector<pair<string, string>> &v, string tier){
    vector<string> result;
        for (const auto &i: v){
            if(!tier.compare(i.first)){
                result.push_back(i.second);
            }
    }

    return result;
}

int main(){
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
vector<pair<string, string>> container;
sql = "SELECT * FROM ANIMES;";
rc = sqlite3_exec(db, sql.c_str(), callback, &container, &zErrMsg);

if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL ERROR: %s\n", zErrMsg);
   sqlite3_free(zErrMsg);
} else {
   cout << "Anton's Anime Tier List\n\n";
   //cout << "Anton's Movies watched in 2024 Tier List\n\n";
}
   // Close the SQL connection
    sqlite3_close(db);

    vector<string> tierS = tier(container, "S");
    vector<string> tierA1 = tier(container, "A+");
    vector<string> tierA2 = tier(container, "A");
    vector<string> tierB1 = tier(container, "B+");
    vector<string> tierB2 = tier(container, "B");

    cout << "S :";
    printvector(tierS);
    cout << "A+:";
    printvector(tierA1);
    cout << "A :";
    printvector(tierA2);
    cout << "B+:";
    printvector(tierB1);
    cout << "B :";
    printvector(tierB2);
    
    return 0;
}