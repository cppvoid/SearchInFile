#include "parse_arguments.h"
#include <stdexcept>

int main( int argc, char** argv ) try
{
    parseArguments( argc, argv );

} catch( const std::exception& ex )
{
    auto programName = getProgramName( argv[0] );
    std::cerr << programName << ": " << ex.what() << "\n";
}
