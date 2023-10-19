#ifndef VEC_OVERLOADS
#define VEC_OVERLOADS

#include <vector>

template<typename T>
std::vector<T> operator+(const std::vector<T>& a, const std::vector<T>& b)  {
    
    std::vector<T> result;
    result.reserve(a.size());

    for (std::size_t i = 0; i < a.size(); i++){
        result.push_back(a[i] + b[i]);
    }

    return result;
}

template<typename T>
std::vector<T> operator-(const std::vector<T>& a, const std::vector<T>& b)  {
    
    std::vector<T> result;
    result.reserve(a.size());

    for (std::size_t i = 0; i < a.size(); i++){
        result.push_back(a[i] - b[i]);

    }

    return result;
}

template<typename T>
std::vector<T> operator*(const std::vector<T>& a, const T& digit){
    
    std::vector<T> result;
    result.reserve(a.size());

    for (std::size_t i = 0; i < a.size(); i++){
        result.push_back(a[i] * digit); 
    }

    return result;
}

template<typename T>
std::vector<T> operator*(const T digit, const std::vector<T>& a){
    
    return a * digit;
}

template<typename T>
std::vector<T> operator*(const std::vector<T>& a, const std::vector<T>& b){

    T result = 0;

    for(std::size_t i = 0; i < a.size(); i++)
    {
        result += a[i] * b[i];
    }

    return result;
}


#endif 