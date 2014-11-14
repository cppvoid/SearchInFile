#ifndef SEARCH_H
#define SEARCH_H

#include "options.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>


void searchInFiles( const std::string& searchTerm, const std::vector< std::string>& filesPaths, int searchOptions = 0 );

void searchInDirectories( const std::string& searchTerm, const std::vector< std::string >& directoryPaths, int dSearchOptions = 0, int fSearchOptions = 0 );

#endif // SEARCH_H
