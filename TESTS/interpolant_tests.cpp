#include <gtest/gtest.h>
#include "../source/interpolant/interpolant.hpp"
#include "../source/tools/grids.hpp"
#include "../source/tools/write_points.hpp"

#include <iostream>
#include<iomanip>
#include <cmath>

constexpr std::size_t M = 20;
constexpr std::size_t K = 1000;

TEST(test1, N3){
        
    double a = 0, b = 2;
    const std::size_t N = 3;
        
    std::array<std::pair<double, double>, M> points1;
    std::array<std::pair<double, double>, M> points2;

    for(std::size_t m = 0; m < M; m++, b/=2){

        std::array<double, N> x1 = make_uniform_grid<double, N> (a, b);
        std::array<double, N> y1 = x1;

        std::array<double, N> x2 = make_chebyshev_grid<double, N>(a, b);
        std::array<double, N> y2 = x2;

        for(unsigned int i = 0; i < N; i++){
            y1[i] = exp(y1[i]);
            y2[i] = exp(y2[i]);

        }


        NewtonInterpolator<double, double, N> interpolator1(x1, y1);
        NewtonInterpolator<double, double, N> interpolator2(x2, y2);
        
        double err1 = abs(interpolator1.interpolate(x1[0]) - exp(x1[0])); 
        double err2 = abs(interpolator2.interpolate(x2[0]) - exp(x2[0])); 

        for(std::size_t i = 0; i < K; i++){

            double x_i = (b - a) / (K - 1) * i; 

            double err1_i = abs(interpolator1.interpolate(x_i) - exp(x_i)); 
            double err2_i = abs(interpolator2.interpolate(x_i) - exp(x_i)); 

            if( err1 < err1_i ) {
                err1 = err1_i;
            }
            
            if( err2 < err2_i ) {
                err2 = err2_i;
            }
        }

        points1[m] = std::pair<double, double>(err1, b);
        points2[m] = std::pair<double, double>(err2, b);
    }

    
    std::string dir1 = "/home/kirill/Вычматы 2023/graphs/test_graph_uniform_grid_N3";
    write_points(points1, dir1);

    std::string dir2 = "/home/kirill/Вычматы 2023/graphs/test_graph_chebyshev_grid_N3";
    write_points(points2, dir2);
}





TEST(test2, N4){
        
    double a = 0, b = 2;
    const std::size_t N = 4;
        
    std::array<std::pair<double, double>, M> points1;
    std::array<std::pair<double, double>, M> points2;

    for(std::size_t m = 0; m < M; m++, b/=2){

        std::array<double, N> x1 = make_uniform_grid<double, N> (a, b);
        std::array<double, N> y1 = x1;

        std::array<double, N> x2 = make_chebyshev_grid<double, N>(a, b);
        std::array<double, N> y2 = x2;

        for(unsigned int i = 0; i < N; i++){
            y1[i] = exp(y1[i]);
            y2[i] = exp(y2[i]);

        }


        NewtonInterpolator<double, double, N> interpolator1(x1, y1);
        NewtonInterpolator<double, double, N> interpolator2(x2, y2);
        
        double err1 = abs(interpolator1.interpolate(x1[0]) - exp(x1[0])); 
        double err2 = abs(interpolator2.interpolate(x2[0]) - exp(x2[0])); 

        for(std::size_t i = 0; i < K; i++){

            double x_i = (b - a) / (K - 1) * i; 

            double err1_i = abs(interpolator1.interpolate(x_i) - exp(x_i)); 
            double err2_i = abs(interpolator2.interpolate(x_i) - exp(x_i)); 

            if( err1 < err1_i ) {
                err1 = err1_i;
            }
            
            if( err2 < err2_i ) {
                err2 = err2_i;
            }
        }

        points1[m] = std::pair<double, double>(err1, b);
        points2[m] = std::pair<double, double>(err2, b);
    }

    std::string dir1 = "/home/kirill/Вычматы 2023/graphs/test_graph_uniform_grid_N4";
    write_points(points1, dir1);

    std::string dir2 = "/home/kirill/Вычматы 2023/graphs/test_graph_chebyshev_grid_N4";
    write_points(points2, dir2);
}

TEST(test3, N5){
        
    double a = 0, b = 2;
    const std::size_t N = 5;
        
    std::array<std::pair<double, double>, M> points1;
    std::array<std::pair<double, double>, M> points2;

    for(std::size_t m = 0; m < M; m++, b/=2){

        std::array<double, N> x1 = make_uniform_grid<double, N> (a, b);
        std::array<double, N> y1 = x1;

        std::array<double, N> x2 = make_chebyshev_grid<double, N>(a, b);
        std::array<double, N> y2 = x2;

        for(unsigned int i = 0; i < N; i++){
            y1[i] = exp(y1[i]);
            y2[i] = exp(y2[i]);

        }


        NewtonInterpolator<double, double, N> interpolator1(x1, y1);
        NewtonInterpolator<double, double, N> interpolator2(x2, y2);
        
        double err1 = abs(interpolator1.interpolate(x1[0]) - exp(x1[0])); 
        double err2 = abs(interpolator2.interpolate(x2[0]) - exp(x2[0])); 

        for(std::size_t i = 0; i < K; i++){

            double x_i = (b - a) / (K - 1) * i; 

            double err1_i = abs(interpolator1.interpolate(x_i) - exp(x_i)); 
            double err2_i = abs(interpolator2.interpolate(x_i) - exp(x_i)); 

            if( err1 < err1_i ) {
                err1 = err1_i;
            }
            
            if( err2 < err2_i ) {
                err2 = err2_i;
            }
        }

        points1[m] = std::pair<double, double>(err1, b);
        points2[m] = std::pair<double, double>(err2, b);
    }

    std::string dir1 = "/home/kirill/Вычматы 2023/graphs/test_graph_uniform_grid_N5";
    write_points(points1, dir1);

    std::string dir2 = "/home/kirill/Вычматы 2023/graphs/test_graph_chebyshev_grid_N5";
    write_points(points2, dir2);
}


int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
