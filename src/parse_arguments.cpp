#include "parse_arguments.h"

std::string getProgramName( const std::string& path )
{
    std::string filename( path );
    auto pos = filename.find_last_of("/");
    if( pos == std::string::npos )
    {
        pos = filename.find_last_of("\\");
    }
    if( pos == std::string::npos )
    {
        filename = "unknow";
    }
    else
    {
        filename = filename.substr( pos+1 );
    }
    return filename;
}

constexpr const char* getVersionMessage()
{
    return "version 1.0\n";
}

void parseArguments( int argc, char** argv )
{
    boost::program_options::options_description description( getProgramName(argv[0]) + " --search { text } --files { filename } --directories { directory }" );

    description.add_options()
    ( "help, h", "show options" )
    ( "version, v", "show version" )
    ( "search, s", boost::program_options::value< std::vector<std::string >>()->multitoken(), "search term" )
    ( "files, f", boost::program_options::value< std::vector<std::string >>()->multitoken(), "files to search")
    ( "directories, d", boost::program_options::value< std::vector<std::string >>()->multitoken(), "directories to search")
    ( "recursive", "search in directories recursively")
    ( "text, t", "show text line at found")
    ( "regex", "search for regex match");

    boost::program_options::variables_map vm;
    boost::program_options::store( boost::program_options::command_line_parser( argc, argv )
                                  .options(description )
                                  .style( boost::program_options::command_line_style::unix_style
                                        | boost::program_options::command_line_style::allow_long_disguise ).run(), vm );

    boost::program_options::notify( vm );

    if( vm.count( "help" ) )
    {
        std::cout << description;
        return;
    }
    if( vm.count( "version" ) )
    {
        std::cout << getVersionMessage();
        return;
    }

    std::string searchTerm;
    std::vector< std::string > files;
    std::vector< std::string > directorys;

    if( vm.count( "search" ) )
    {
        const auto text = vm["search"].as< std::vector< std::string >>();

        if( text.size() == 1 )
        {
            searchTerm = text.at(0);
        }
        else
        {
            std::ostringstream oss;
            std::copy( text.begin(), text.end(), std::ostream_iterator<std::string>( oss, " " ) );

            searchTerm = oss.str();
        }

        boost::algorithm::trim( searchTerm );
    }

    if( vm.count( "files" ) )
    {
        files = vm["files"].as< std::vector< std::string >>();
    }

    if( vm.count( "directories" ) )
    {
        directorys = vm["directories"].as< std::vector< std::string >>();
    }

    if( searchTerm.empty() || ( files.empty() && directorys.empty() ) )
    {
        std::cerr << getProgramName( argv[0] ) << ": --search and --files or --directories explicit required\n";
        return;
    }

    int fileSearchOptions(0);
    int directorySearchOptions(0);

    if( vm.count( "regex" ) )
    {
        fileSearchOptions = options::regexMatch;
    }

    if( vm.count( "text" ) )
    {
        fileSearchOptions |= options::showText;
    }

    if( vm.count( "recursive" ) )
    {
        directorySearchOptions = options::recursive;
    }

    if( !files.empty() )
    {
        searchInFiles( searchTerm, files, fileSearchOptions );
    }

    if( !directorys.empty() )
    {
        searchInDirectories( searchTerm, directorys, directorySearchOptions, fileSearchOptions );
    }
}

