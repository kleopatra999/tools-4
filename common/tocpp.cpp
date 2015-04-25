#!/usr/bin/env cppsh

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>

void usage() {
    std::cout << "Usage" << std::endl;
    std::cout << "    tocpp.cpp <file>" << std::endl;
    std::cout << std::endl;
}

std::string fromFile( const std::string& filename ) {
    std::ifstream file( filename.c_str(), std::ifstream::binary );
    return std::string( ( std::istreambuf_iterator<char>( file ) ), ( std::istreambuf_iterator<char>() ) );
}

std::string toValidVarName( const std::string& filename ) {
    std::string varName = filename;
    std::replace_if( varName.begin(), varName.end(), []( char c ) {
        if( std::isalnum( c ) || c == '_' ) {
            return false;
        }

        return true;
    }, '_' );
    return varName;
}

std::string convert( const std::string& data ) {
    std::stringstream ss;
    int i = 0;
    ss << "{";

    for( const char & c : data ) {
        if( i++ % 40 == 0 ) {
            ss << "\n    ";
        }

        ss << std::setw( 3 ) << ( int )c << ",";
    }

    ss << "\n}";
    return ss.str();
}

int main( int argc, char* argv[] ) {

    if( argc != 2 ) {
        usage();
        return 1;
    }

    std::string filename = argv[1];
    std::string var = toValidVarName( filename );
    std::string data = fromFile( filename );

    std::cout << "// " << filename << std::endl;
    std::cout << "const char " << var << "[] = " << convert( data ) << ";" << std::endl;

    return 0;
}
