#ifndef OPTIONS_H_INCLUDED
#define OPTIONS_H_INCLUDED

namespace options
{

enum fileSearchOptions
{
    showText    = 0x01,
    regexMatch  = 0x02
};

enum directorySearchOptions
{
    recursive = 0x001
};

}

#endif // OPTIONS_H_INCLUDED
