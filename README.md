SearchInFile
============
-> Windows, Linux and MacOS <-

Command line tool for searching a term in files. 

FindInFile --search { text } --files { filename } --directories { directory }:
  -  [ --help ]            show options
  -  [ --version ]         show version
  -  [ --search ] arg      search term
  -  [ --files ] arg       files to search
  -  [ --directories ] arg directories to search
  -  [ --recursive ]       search in directories recursively
  -  [ --text ]            show text line at found
  -  [ --regex ]           search for regex match


Examples:

FindInFile --search hello --files hello.txt world.txt
file: hello.txt -> line: 1
file: world.txt -> line: 2

FindInFile --search hello --files *.txt
file: hello.txt -> line: 1
file: world.txt -> line: 2

FindInFile --search hello --files hello.txt world.txt --text
file: hello.txt -> line: 1
hello
file: world.txt -> line: 2
hello

FindInFile --regex --search [a-z] --files hello.txt world.txt 
file: hello.txt -> line: 1
file: hello.txt -> line: 2
file: world.txt -> line: 1
file: world.txt -> line: 2

FindInFile --search hello --directories example
file: example/hello.txt -> line: 1
file: example/world.txt -> line: 2

FindInFile --search hello --directories /home/user/Documents/Projects --recursive
file: /home/user/Documents/Projects/FindInFile/build/src/example/hello.txt -> line: 1
file: /home/user/Documents/Projects/FindInFile/build/src/example/world.txt -> line: 2


