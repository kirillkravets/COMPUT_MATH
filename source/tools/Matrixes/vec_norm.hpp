#ifndef VEC_NORM
#define VEC_NORM
#include <vector>
#include <cmath>

template<typename T>
T Third_Norm(const std::vector<T>& vec){

    T result = 0;

    for(std::size_t i = 0; i < vec.size(); i++){
        
        result += vec[i] * vec[i];
    }

    return sqrt(result);
}

#endif