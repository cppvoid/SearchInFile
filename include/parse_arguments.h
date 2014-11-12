#ifndef PARSE_ARGUMENTS_H
#define PARSE_ARGUMENTS_H

#include "search.h"
#include "options.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <sstream>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>

std::string             getProgramName( const std::string& path );

constexpr const char*   getVersionMessage();

void                    parseArguments( int argc, char** argv );

#endif // PARSE_ARGUMENTS_H
