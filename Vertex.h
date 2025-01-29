#pragma once

#include <iostream>
#include <fstream>

struct Vertex
{
    float x = 0;
    float y = 0;
    float z = 0;

    float r = 0;
    float g = 0;
    float b = 0;

    float u = 0;
    float v = 0;


    //! Overloaded ostream operator which writes all vertex data on an open textfile stream
    friend std::ostream& operator<< (std::ostream&, const Vertex&);

    //! Overloaded ostream operator which reads all vertex data from an open textfile stream
    friend std::istream& operator>> (std::istream&, Vertex&);
};
