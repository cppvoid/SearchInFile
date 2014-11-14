set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED OFF)  
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost COMPONENTS regex filesystem system program_options)  
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
	include_directories(${root_SOURCE_DIR}/include)	
	add_executable(FindInFile main.cpp search.cpp parse_arguments.cpp)
	target_link_libraries(FindInFile ${Boost_LIBRARIES})
else()
	message( FATAL_ERROR "Boost not found" )
endif()


