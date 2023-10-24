#ifndef THREEDIAGONAL_MATRIX_HPP
#define THREEDIAGONAL_MATRIX_HPP

#include <vector>

namespace triple{
    template <typename T>
    struct Triple{
        T a;
        T b;
        T c;
    };
};

template <typename T, typename cType>
class ThreeDiagonalMatrix{
private:

    std::vector<triple::Triple<T>> triples;

    std::size_t matrix_order;

public:

    ThreeDiagonalMatrix(const std::vector<triple::Triple<T>>& _triples);


    std::size_t Get_Order() const;

    triple::Triple<T> Get_Triple(std::size_t i) const;

    triple::Triple<T> operator [] (std::size_t i) const;

    std::vector<T> Run_Through_method(const std::vector<cType>& right_column) const;

    void Stability_Check() noexcept;
};

template<typename T, typename cType>
ThreeDiagonalMatrix<T, cType>::ThreeDiagonalMatrix(const std::vector<triple::Triple<T>>& _triples)
{
    triples = _triples;
    matrix_order = triples.size();
}

template<typename T, typename cType>
std::size_t ThreeDiagonalMatrix<T, cType>::Get_Order() const
{
    return matrix_order;
}

template<typename T, typename cType>
triple::Triple<T>  ThreeDiagonalMatrix<T, cType>::Get_Triple(std::size_t i) const
{
    return triples[i];
}

template<typename T, typename cType>
triple::Triple<T> ThreeDiagonalMatrix<T, cType>::operator [] (std::size_t i) const
{
    return triples[i];
}

template<typename T, typename cType>
std::vector<T> ThreeDiagonalMatrix<T, cType>::Run_Through_method(const std::vector<cType>& right_column) const
{
    std::vector<T> alpha;
    std::vector<T> beta;

    alpha.resize(matrix_order);
    beta.resize(matrix_order);
   
    alpha[0] = -triples[0].c / triples[0].b;
    beta[0] = right_column[0]/ triples[0].b;
    

    for(std::size_t i = 1; i < matrix_order; i++){
        
        T denominator = triples[i].a * alpha[i-1] + triples[i].b;

        alpha[i] = -triples[i].c / denominator;
        beta[i] = (right_column[i] - triples[i].a * beta[i - 1]) / denominator;
    }


    for(std::size_t i = matrix_order - 2; i == 0; i--){
        beta[i] = alpha[i] * beta[i+1] + beta[i];
    }

    return beta;
}


template<typename T, typename cType>
void ThreeDiagonalMatrix<T, cType>::Stability_Check() noexcept
{
    std::size_t rg = triples.Get_Order();

    
    static_assert(abs(triples[0].c) >= abs(triples[0].b), "unstable method");

    for(std::size_t i = 1; i < matrix_order - 1; i++)
    {
        static_assert(abs(triples[i].b) >= (abs(triples[i].a) + abs(triples[i].c)), "unstable method");
    }


    static_assert(abs(triples[rg-1].a) >= abs(triples[rg-1].b), "unstable method");
    
}



#endif /*THREEDIAGONAL_MATRIX_HPP*/