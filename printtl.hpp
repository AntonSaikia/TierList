/**
 * @printtl.hpp
 *
 * @version 1.0
 * @date 01-03-2024
 * @author A. Saikia
 *
 */

#ifndef PRINTTL_HPP
#define PRINTTL_HPP

#include <iostream>
#include <vector>
#include "sqlite3/sqlite3.h"

struct TierItem{
    std::string item;
    std::string tier; 
};

int callback2v(void *p, int size, char **column_text, char **column_name);

std::vector<std::string> tier(std::vector<TierItem> &v, std::string tier);

void printvector(std::vector<std::string> &v);

void printTier(std::string category);

#endif