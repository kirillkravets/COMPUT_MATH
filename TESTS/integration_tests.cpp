#include <gtest/gtest.h>

#include "../source/tools/write_points.hpp"
#include "../source/integration/integration.hpp"

#include <iostream>
#include<iomanip>
#include <cmath>

constexpr double scale = 1.5;
constexpr std::size_t M = 40;


TEST(test1, N3){
    
    constexpr std::size_t N = 3;
    double a = 0;
    double b = 10;
    double b_i = b;

    std::array<std::pair<double, double>, M> points;

    for(std::size_t i = 0; i < M; i++){

        
        auto integral = integrate<double(double), double, N>(std::sin, a, b, b_i - a);

        //std::cout << integral << std::endl;

        points[i] = std::pair<double, double>(std::log(b_i), std::log(std::abs(integral - (std::cos(0) - std::cos(b)))));

        b_i /= scale;
        
    }

    std::string dir1 = "/home/kirill/git_repozitories/COMPUT_MATH/graphs/integration/test_integration_N3";
    write_points(points, dir1);
}






TEST(test2, N6){
    
    constexpr std::size_t N = 6;
    double a = 0;
    double b = 10;
    double b_i = b;

    std::array<std::pair<double, double>, M> points;

    for(std::size_t i = 0; i < M; i++){

        
        auto integral = integrate<double(double), double, N>(std::sin, a, b, b_i - a);

        //std::cout << integral << std::endl;

        points[i] = std::pair<double, double>(std::log(b_i), std::log(std::abs(integral - (std::cos(0) - std::cos(b)))));

        b_i /= scale;
        
    }

    std::string dir1 = "/home/kirill/git_repozitories/COMPUT_MATH/graphs/integration/test_integration_N6";
    write_points(points, dir1);
}



int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
