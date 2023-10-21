#define NUM_DIFFERENTIATION
#ifdef NUM_DIFFERENTIATION

#include "../interpolant/interpolant.hpp"
#include "../tools/gauss_algorithm.hpp"
#include <array>
#include <vector>


template<typename RealType, std::size_t N>
struct DerivativeCoef {
    RealType centralCoef = 0;
    std::array<RealType, N> otherCoefs;
};

template<typename RealType, std::size_t N>
DerivativeCoef<RealType, N> calcDerivativeCoef(const std::array<RealType, N>& points) noexcept
{
    std::array<RealType, N * (N +1)> matrix;
    DerivativeCoef<RealType, N> derivative_coefs;
    
    
    for(std::size_t k = 0; k < N; k++){
        matrix[k] = points[k];
    }

    matrix[N] = 1;

    for(std::size_t i = 1; i < N; i++){
        for(std::size_t j = 0; j < N; j++){
            matrix[i * (N + 1) + j] = matrix[(i - 1) * (N + 1) + j] * matrix[j];
        }
    
        matrix[ i * (N + 1) + N] = 0;
    }

    DerivativeCoef<RealType, N> result;

    result.otherCoefs = gaussianElimination<RealType, N>(matrix);

    for(std::size_t i = 0; i < N; i++){
        result.centralCoef -= result.otherCoefs[i];
    }

    return result;
}

template<typename xType, typename yType, std::size_t N>
xType calcFirstDerivative(const DerivativeCoef<xType, N>& coefs, const DerivativeCoef<yType, N>& y, const xType step) noexcept
{
    yType derivative = 0;

    for(std::size_t i = 0; i < N; i++){
        derivative += y.otherCoefs[i] * coefs.otherCoefs[i];
    }

    derivative += y.centralCoef * coefs.centralCoef;
    derivative /= step;

    return derivative;
}
    
    























#endif