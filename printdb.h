/**
 * @printdb.h
 *
 * @version 1.0
 * @date 01-03-2024
 * @author A. Saikia
 *
 */

#ifndef PRINTDB_H
#define PRINTDB_H

#include <iostream>
#include <string>
#include <vector>
#include "sqlite3/sqlite3.h"

using namespace std;

struct TierItem{
    string item;
    string tier; 
};

int callback2v(void *p, int size, char **column_text, char **column_name);

vector<string> tier(vector<TierItem> &v, string tier);

void printvector(vector<string> &v);

void printTier(string category);

#endif