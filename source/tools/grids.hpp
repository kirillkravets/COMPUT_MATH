#ifndef TOOLS
#define TOOLS
#include <array>
#include <vector>
#include <cmath>

template<typename xType, unsigned int N>
std::array<xType, N> make_uniform_grid(const xType a, const xType b){
    xType step = (b - a) / (N - 1);

    std::array<xType, N> grid;

    for(unsigned int i = 0; i < N; i++){
        grid[i] = a + i * step;
    }

    return grid;
}

template<typename xType>
std::vector<xType> make_uniform_grid(const xType a, const xType b, std::size_t N){
    
    xType step = (b - a) / (N - 1);

    std::vector<xType> grid;
    grid.resize(N);

    for(std::size_t i = 0; i < N; i++){
        grid[i] = a + i * step;
    }

    return grid;
}

template<typename xType, unsigned int N>
std::array<xType, N> make_chebyshev_grid(const xType a, const xType b){
    
    std::array<xType, N> grid;
       
    grid[0]         = cos(M_PI / (2 * N));
    xType sin_beta  = sin(M_PI / (2 * N));
    xType cos_alpha = cos(M_PI / N);
    xType sin_alpha = sin(M_PI / N);
    

    for(unsigned int i = 1; i < N; i++){
        grid[i]  = grid[i-1] * cos_alpha - sin_beta     * sin_alpha;
        sin_beta = sin_beta  * cos_alpha + grid[i - 1]  * sin_alpha;
//      std::cout << "[ " << grid[i - 1] << ' ' << cos_alpha << ' ' << sin_beta << ' ' << sin_alpha << " ]\n";
    }

    for(std::size_t i = 0; i < N; i++)
    {
        grid[i] = (b + a) / 2 + (b - a) / 2 * grid[i];
    }
    
    return grid;
}


template<typename xType, std::size_t N>
std::array<xType, N - 1> make_derivative_coefs_grid(){

    std::array<xType, N - 1> grid;
    
    long int n = N;

    for(long int i = 1; i <= n/2; i++){
        grid[n/2 - i] = (-1) * i; 
    }

    for(long int i = 1; i < n - n/2; i++){
        grid[n/2 + i - 1] = i;
    }

    return grid;
}



#endif