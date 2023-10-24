#include <gtest/gtest.h>

#include "../source/tools/write_points.hpp"
#include "../source/tools/grids.hpp"
#include "../source/spline/spline.hpp"

#include <iostream>
#include<iomanip>
#include <cmath>

constexpr double scale = 2.0;
constexpr std::size_t M = 20;


TEST(test1, N3){
    
    std::size_t N = 10;
    double a = 0.0;
    double b = 10.0;


    std::array<std::pair<double, double>, M> points;


    for(std::size_t j = 0; j < M; j++){

        std::vector<double> xgrid = make_uniform_grid<double>(a, b, N);
        std::vector<double> ygrid = xgrid;

        for(std::size_t i = 0; i < ygrid.size(); i++){
            ygrid[i] = std::exp(xgrid[i]);
        }

        CubicSpline<double, double> spline(xgrid, ygrid);
        
        double result;
        double err = 0;

        for(std::size_t i = 0; i <= 1000; i++){

            double x = a + (b - a) / 1000 * i;
            result = spline.interpolate(x);

            double err_i = std::abs(result - std::exp(x));

            if(err < err_i){
                err  = err_i;
            }
        }
      
        std::cout  << j << "  " << err << ' ' << N << std::endl;
        
        points[j] = std::pair<double, double>(std::log(N), std::log(err));
    
        N *= scale;
        
    }

    std::string dir1 = "/home/kirill/git_repozitories/COMPUT_MATH/graphs/spline/test_spline";
    write_points(points, dir1);
}


int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
