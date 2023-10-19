#include <array>
#include <fstream>
#include <iostream>

template<typename xType, typename yType, std::size_t N>
void write_points(const std::array<std::pair<xType, yType>, N> points, const std::string& dir){

    std::ofstream out;    
          
    out.open(dir + ".csv");     
    if (out.is_open())
    {
        for(auto elem: points){
            out << elem.first << "; " << elem.second << std::endl;
        }
    }
    out.close(); 
}