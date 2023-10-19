#define NUM_DIFFERENTIATION
#ifdef NUM_DIFFERENTIATION

#include "../interpolant/interpolant.hpp"
#include <array>

template<typename RealType, std::size_t N>
struct DerivativeCoef {
    RealType centralCoef;
    std::array<RealType, N> otherCoefs;
};

template<typename RealType, std::size_t N>
DerivativeCoef<RealType, N> calcDerivativeCoef(const std::array<RealType, N>& points, const RealType x0) noexcept
{
    std::array<RealType, N * N> matrix;
    DerivativeCoef<RealType, N> derivative_coefs;
    coefs.centralCoef = x0;

    std::array<RealType, N> others_coefs_0; 
    for(std::size_t i = 0; i < N; i++){
        others_coefs_0[i] = 1 / N;
    }

    


    for(std::size_t k = 0; k < N; k++){
        matrix[k] = points[k]
    }

    for(std::size_t i = 1; i < N; i++){
        for(std::size_t j = 0; j < N; j++){
            matrix[i * N + j] = matrix[(i - 1) * N + j] * matrix[j] / (i + 1);
        }
    }




}














#endif