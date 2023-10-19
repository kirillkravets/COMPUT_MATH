#define NUM_DIFFERENTIATION
#ifdef NUM_DIFFERENTIATION

#include "../interpolant/interpolant.hpp"
#include "../tools/Matrixes/dense_matrix.hpp"
#include "../tools/Matrixes/vec_norm.hpp"
#include <array>
#include <vector>


template<typename RealType, std::size_t N>
struct DerivativeCoef {
    RealType centralCoef;
    std::array<RealType, N> otherCoefs;
};

template<typename RealType, std::size_t N>
DerivativeCoef<RealType, N> calcDerivativeCoef(const std::array<RealType, N>& points, const RealType x0) noexcept
{
    std::vector<RealType> matrix.reserve(N * N);
    DerivativeCoef<RealType, N> derivative_coefs;
    
    coefs.centralCoef = x0;

    std::vector<RealType> others_coefs_0.reserve(N); 
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

    DenseMatrix A(matrix, N, N);
    
    std::vector<RealType> x(others_coefs_0);
    std::vector<RealType> r_i;
    
    RealType norm = r + 1;
    
    size_t it = 1;

    while(norm > r)
    { 
        r_i = b - A * x;
        
        x = x + t * r_i;

        norm = Third_Norm(r_i);
        fout1 << log(norm) << '\n';
        it++;
    }
    fout.close();
    fout1.close();

    return x;

    return x;
}

    
    




















#endif