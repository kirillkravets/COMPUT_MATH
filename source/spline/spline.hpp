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

    std::vector<taylor::Taylor_func<yType>> c_spline;
    std::vector<xType> xgrid;
    std::size_t N;

public:
    CubicSpline( const std::vector<xType> & oth_points,  // Значения x
                 const std::vector<yType>& oth_values  // значения y
                        );

    yType interpolate(const xType& x) const noexcept;
};

template<typename xType, typename yType>
CubicSpline<xType, yType>::CubicSpline( const std::vector<xType>& points, 
                                        const std::vector<yType>& values )
{    
    N = points.size() - 1;
    xgrid = points;
 
    std::vector<yType> column;
    column.resize(N - 1);
    c_spline.resize(N);

    std::vector<yType> copy_values = values;

    for(std::size_t j = 1; j <= 2; j++)
    {
        for(std::size_t i = 0; i < N  + 1 - j; i++)
        {
            copy_values[i] = (copy_values[i + 1] - copy_values[i]) / (points[i + j] - points[i]);
        }
    }

    for(std::size_t i = 0; i <= N - 2; i++){
        column[i] = copy_values[i] * 6;
    }


    std::vector<triple::Triple<xType>> triples;
    triples.resize(N - 1);

    triples[0] = {0, 2, (points[2] - points[1]) / (points[2] - points[0])};

    for(std::size_t i = 1; i < N - 2; i++){      
        triples[i].a = (points[i] - points[i - 1]) / (points[i + 1] - points[i - 1]);
        triples[i].b = 2;
        triples[i].c = (points[i + 1] - points[i]) / (points[i + 1] - points[i - 1]);
    }

    triples[N - 2] = {(points[N - 1] - points[N - 2]) / (points[N] - points[N - 2]), 2 , 0};

    ThreeDiagonalMatrix<xType, yType> matrix(triples);

    column = matrix.Run_Through_method(column);

    column.resize(N);
    column[N - 1] = 0;

    c_spline[0].f    = values[1];
    c_spline[0].der2 = column[0];
    c_spline[0].der1 = column[0] * (points[1] - points[0]) / 3 + (values[1] - values[0]) / (points[1] - points[0]);
    c_spline[0].der3 = column[0] / (points[1] - points[0]);

    for(std::size_t i = 1; i < N; i++){
        
        c_spline[i].f = values[i + 1];

        c_spline[i].der1 = (column[i] + column[i - 1] / 2) * (points[i + 1] - points[i]) / 3
                         + (values[i + 1] - values[i]) / (points[i + 1] - points[i]);

        c_spline[i].der2 = column[i];
        c_spline[i].der3 = (column[i] - column[i - 1]) / (points[i + 1] - points[i]);
    }
}

template<typename xType, typename yType>
yType CubicSpline<xType, yType>::interpolate(const xType& x) const noexcept{

    std::size_t spl_ind = 0;

    for(std::size_t i = 0; i < xgrid.size(); i++){
        if(xgrid[i + 1] - x >= 0){
            spl_ind = i;

            i = xgrid.size();
        }
    }

    yType h = x - xgrid[spl_ind];

    yType result = c_spline[spl_ind].f + h * (c_spline[spl_ind].der1 + h / 2 * (c_spline[spl_ind].der2 + h / 3 * c_spline[spl_ind].der3));

    return result;
}