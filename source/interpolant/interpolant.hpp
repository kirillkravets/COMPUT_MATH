#ifndef INTERPOLYANT
#define INTERPOLYANT
#include <array>


template<typename xType, typename yType, std::size_t N>
class NewtonInterpolator {
private:
    std::array<xType, N> points;
    std::array<yType, N> values;

public:
    NewtonInterpolator(const std::array<xType, N>& points_, const std::array<yType, N>& values_) noexcept;
    
    yType interpolate(const xType& x) const noexcept;
    
};


template<typename xType, typename yType, std::size_t N>
NewtonInterpolator<xType, yType, N>::NewtonInterpolator(const std::array<xType, N>& points_, const std::array<yType, N>& values_) noexcept
{
    points = points_;
    values = values_;

    for(std::size_t j = 0; j < N - 1; j++)
    {
        yType a = values[0];

        for(std::size_t i = 0; i < N - 1 - j; i++)
        {
            values[i] = (values[i+1] - values[i]) / (points[i + 1 + j] - points[i]);
        }

        values[N - 1 - j] = a;
    }

}

template<typename xType, typename yType, std::size_t N>
yType NewtonInterpolator<xType, yType, N>::interpolate(const xType&   x) const noexcept
{   
    yType result = values[0];

    for(std::size_t j = 0; j < N - 1; j++){
        result *= (x - points[N - 2 - j]);
        result += values[j + 1];
    }
    
    return result; 
}




template<typename xType, typename yType, std::size_t N >
class HermiteInterpolator {
private:    
    std::array<xType, 2 * N> points;
    std::array<yType, 2 * N> values;
    std::array<yType, N> deriv;

public:
    HermiteInterpolator(const std::array<xType, N> &points, const std::array<yType, N>& values, const std::array<yType, N>& deriv) noexcept;

    yType interpolate(const xType& x) const noexcept;
};

template<typename xType, typename yType, std::size_t N >
HermiteInterpolator<xType, yType, N>::HermiteInterpolator(const std::array<xType, N> &points_, const std::array<yType, N>& values_, const std::array<yType, N>& deriv_) noexcept
{

    deriv  = deriv_;

    for(std::size_t i = 0; i < 2 * N; i += 2)
    {
        points[i]     = points_[i];
        points[i + 1] = points_[i];

        values[i]     = values_[i];
        values[i + 1] = values_[i];

    }

    yType a = values[0];
    
    for(std::size_t i = 0; i < 2 * N - 1; i += 2)
    {
        values[i] = this->deriv[i];
        values[i + 1] = (values[i + 2] - values[i + 1]) / (points[i + 2] - points[i + 1]); 
    }
    
    values[2 * N - 1] = a;

    for(std::size_t j = 1; j < 2 * N - 1; j++)
    {
        a = values[0];

        for(std::size_t i = 0; i < 2 * N - 1 - j; i++)
        {
            values[i] = (values[i+1] - values[i]) / (points[i + 1 + j] - points[i]);
        }

        values[2 * N - 1 - j] = a;
    } 

};

template<typename xType, typename yType, std::size_t N >
yType HermiteInterpolator<xType, yType, N>::interpolate(const xType& x) const noexcept
{   
    yType result = values[0];


    for(std::size_t j = 0; j < 2 * N - 1; j++){
        result *= (x - points[2 * N - 2 - j]);
        result += values[j + 1];
    }

    return result; 
}



#endif