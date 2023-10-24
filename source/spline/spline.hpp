#include <vector>
#include <type_traits>
#include "../tools/threediagonal_matrix/threediagonal_matrix.hpp"


// template<typename numeratorType, typename denominatorType>
// using DivisType = decltype(std::declval<numeratorType>() / std::declval<denominatorType>());

// /** Функция для решения методом  прогонки **/
// template<typename mType, typename cType>
// std::vector<DivisType<cType, mType>> solve( const ThreeDiagonalMatrix<mType, cType>& matrix,
//                                             const std::vector<cType>& column){
    


// }


/**
* xType - тип аргумента x.
* yType - тип значения функции y
*/

namespace taylor{
    template<typename RealType>
    struct Taylor_func
    {
        RealType f, der1, der2, der3;
};
};

template<typename xType, typename yType>
class CubicSpline {
private:

    const std::vector<xType> points;
    const std::vector<yType> values;

    std::size_t N;

public:
    CubicSpline( const std::vector<xType> & oth_points,  // Значения x
                 const std::vector<yType>& oth_values  // значения y
                        );

    yType interpolate(const xType& x) const noexcept;
};

template<typename xType, typename yType>
CubicSpline<xType, yType>::CubicSpline( const std::vector<xType>& oth_points, 
                                        const std::vector<yType>& oth_values )
{
    
    points = oth_points;
    values = oth_values;
    
    N = points.size();

 
    std::vector<yType> column.reverse(N - 2);


    for(std::size_t j = 1; j <= 2; j++)
    {
        for(std::size_t i = 0; i < N - j; i++)
        {
            values[i] = (values[i + 1] - values[i]) / (points[i + j] - points[i]);
        }
    }

    for(std::size_t i = 0; i < N - 2; i++){
        column[i] = values[i] * 6;
    }


    std::size_t n = N - 2;
    std::vector<triple::Triple<xType>> triples.reserve(n);

    triples[0] = {0, 2, (points[2] - points[1]) / (points[2] - points[0])};

    for(std::size_t i = 1; i < n - 1; i++){
        triples[i].a = (points[i] - points[i - 1]) / (points[i + 1] - points[i - 1]);
        triples[i].b = 2;
        triples[i].c = (points[i + 1] - points[i]) / (points[i + 1] - points[i - 1]);
    }

    triples[n - 1] = {(points[n - 2] - points[n - 3]) / (points[n - 1] - points[n - 3]), 2 , 0};

    ThreeDiagonalMatrix matrix;


}