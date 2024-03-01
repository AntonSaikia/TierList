/**
 * @printdb.h
 *
 * @version 1.0
 * @date 01-03-2024
 * @author A. Saikia
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "sqlite3/sqlite3.h"

using namespace std;

int callback2v(void *p, int size, char **column_text, char **column_name);

vector<string> tier(vector<pair<string, string>> &v, string tier);

void printvector(vector<string> &v);

void printTier(string category);