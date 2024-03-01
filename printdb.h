#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "sqlite3/sqlite3.h"

using namespace std;

int callback2v(void *p, int size, char **column_text, char **column_name);

void printvector(vector<string> &v);

vector<string> tier(vector<pair<string, string>> &v, string tier);

void printTier(string category);