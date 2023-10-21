#include <gtest/gtest.h>
#include "../source/interpolant/interpolant.hpp"
#include "../source/tools/grids.hpp"
#include "../source/tools/write_points.hpp"
#include "../source/num_differentiation/num_differentiation.hpp"

#include <iostream>
#include<iomanip>
#include <cmath>

constexpr std::size_t M = 17;

TEST(test1, N3){
    
    constexpr std::size_t N = 3;
    double step = 1;
    double x0 = 1;

    std::array<std::pair<double, double>, M> points;

    for(std::size_t i = 0; i < M; i++){

        
        std::array<double, N - 1> grid = make_derivative_coefs_grid<double, N>();

        DerivativeCoef<double, N - 1> der_coefs = calcDerivativeCoef<double, N - 1>(grid);

        DerivativeCoef<double, N - 1> f_coefs = der_coefs;

        f_coefs.centralCoef = std::exp(1);

        for(std::size_t i = 0; i < N - 1; i++){
            f_coefs.otherCoefs[i] = std::exp(grid[i] * step + x0);
        }

        double derivative = calcFirstDerivative<double, double, N - 1>(der_coefs, f_coefs, step); 
        //std::cout << derivative << std::endl;

        //std::cout << std::endl << std::exp(1.0) << std::endl;
        step /= 10;

        points[i] = std::pair<double, double>(std::log(step), std::log(std::abs(f_coefs.centralCoef - derivative)));

    }

    std::string dir1 = "/home/kirill/git_repozitories/COMPUT_MATH/graphs/derivative/test_derivative_N3";
    write_points(points, dir1);
}

TEST(test2, N4){
    
    constexpr std::size_t N = 4;
    double step = 1;
    double x0 = 1;

    std::array<std::pair<double, double>, M> points;

    for(std::size_t i = 0; i < M; i++){

        
        std::array<double, N - 1> grid = make_derivative_coefs_grid<double, N>();

        DerivativeCoef<double, N - 1> der_coefs = calcDerivativeCoef<double, N - 1>(grid);

        DerivativeCoef<double, N - 1> f_coefs = der_coefs;

        f_coefs.centralCoef = std::exp(1);

        for(std::size_t i = 0; i < N - 1; i++){
            f_coefs.otherCoefs[i] = std::exp(grid[i] * step + x0);
        }

        double derivative = calcFirstDerivative<double, double, N - 1>(der_coefs, f_coefs, step); 
        //std::cout << derivative << std::endl;

        //std::cout << std::endl << std::exp(1.0) << std::endl;
        step /= 10;

        points[i] = std::pair<double, double>(std::log(step), std::log(std::abs(f_coefs.centralCoef - derivative)));

    }

    std::string dir1 = "/home/kirill/git_repozitories/COMPUT_MATH/graphs/derivative/test_derivative_N4";
    write_points(points, dir1);
}

TEST(test3, N5){
    
    constexpr std::size_t N = 5;
    double step = 1;
    double x0 = 1;

    std::array<std::pair<double, double>, M> points;

    for(std::size_t i = 0; i < M; i++){

        
        std::array<double, N - 1> grid = make_derivative_coefs_grid<double, N>();

        DerivativeCoef<double, N - 1> der_coefs = calcDerivativeCoef<double, N - 1>(grid);

        DerivativeCoef<double, N - 1> f_coefs = der_coefs;

        f_coefs.centralCoef = std::exp(1);

        for(std::size_t i = 0; i < N - 1; i++){
            f_coefs.otherCoefs[i] = std::exp(grid[i] * step + x0);
        }

        double derivative = calcFirstDerivative<double, double, N - 1>(der_coefs, f_coefs, step); 
        //std::cout << derivative << std::endl;

        //std::cout << std::endl << std::exp(1.0) << std::endl;
        step /= 10;

        points[i] = std::pair<double, double>(std::log(step), std::log(std::abs(f_coefs.centralCoef - derivative)));

    }

    std::string dir1 = "/home/kirill/git_repozitories/COMPUT_MATH/graphs/derivative/test_derivative_N5";
    write_points(points, dir1);
}


int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
