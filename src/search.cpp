#include "search.h"

void searchInFiles( const std::string& searchTerm, const std::vector< std::string >& filePaths, int searchOptions )
{
    for( const auto& filePath : filePaths )
    {
        std::ifstream file( filePath );
        if(!file)
        {
            std::cerr << "cannot open file: " << filePath << "\n";
            continue;
        }

        std::string buffer;
        int line(1);
        const boost::regex dataRegex( searchTerm );

        while( std::getline( file, buffer ) )
        {
            if( searchOptions & options::regexMatch )
            {
                if( boost::regex_search(buffer, dataRegex ) )
                {
                    std::cout << "file: " << filePath << " -> line: " << line << "\n";
                    if( searchOptions & options::showText )
                    {
                        std::cout << buffer << "\n";
                    }
                }
            }

            else if( buffer.find( searchTerm ) != std::string::npos )
            {
                std::cout << "file: " << filePath << " -> line: " << line << "\n";
                if( searchOptions & options::showText )
                {
                    std::cout << buffer << "\n";
                }
            }
            line++;
        }
    }
}

void searchInDirectories( const std::string& searchTerm, const std::vector< std::string >& directoryPaths, int dSearchOptions, int fSearchOptions )
{
    std::vector< std::string > filePaths;

    for( const auto& directoryPath : directoryPaths )
    {
        try
        {
            if( dSearchOptions & options::recursive )
            {
                boost::filesystem::recursive_directory_iterator iter( directoryPath );
                boost::filesystem::recursive_directory_iterator end;

                for(; iter != end; ++iter )
                {
                    if( boost::filesystem::is_regular_file( *iter ) )
                    {
                        filePaths.push_back( iter->path().string() );
                    }
                }
            }
            else
            {
                boost::filesystem::directory_iterator iter( directoryPath );
                boost::filesystem::directory_iterator end;

                for(; iter != end; ++iter )
                {
                    if( boost::filesystem::is_regular_file( *iter ) )
                    {
                        filePaths.push_back( iter->path().string() );
                    }
                }
            }
        }
        catch( const boost::filesystem::filesystem_error& error )
        {
            if( error.code() == boost::system::errc::permission_denied )
            {
                std::cerr << directoryPath << ": permission denied\n";
            }
            else if( error.code() == boost::system::errc::no_such_file_or_directory )
            {
                std::cerr << directoryPath << ": is not a directory\n";
            }
            else
            {
                std::cerr << directoryPath << ". " << error.code().message() << "\n";
            }
        }
    }
    searchInFiles( searchTerm, filePaths, fSearchOptions );
}
