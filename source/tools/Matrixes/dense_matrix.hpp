#ifndef CSR_MATRIX
#define CSR_MATRIX

#include "./vector_overloads.hpp"
#include <vector>

template <typename T>
class DenseMatrix{
private:

    constexpr std::size_t size_column;
    constexpr std::size_t size_string;
    
    std::vector<T> matrix;

    vector<T> Get_vec() const{
        return matrix;
    }

public:

    DenseMatrix(const std::vector<std::vector<T>>& other_matrix):size_column(other_matrix.size()), size_string(other_matrix[0].size())
    {
        matrix.reserve(size_column * size_string);

        for(std::size_t i = 0; i < size_column; i++){
            for(std::size_t j = 0; j < size_string; j++){
                matrix.push_back(other_matrix[i][j]);
            }
        }
    }

    DenseMatrix(const std::vector<T> other_matrix, std::size_t size_col, std::size_t size_str):size_column(size_col), size_string(size_str)
    {
        matrix = other_matrix;
    }

    const std::size_t Get_Column_Size() const{
        return size_column;
    }

    const std::size_t Get_String_Size() const{
        return size_string;
    }

    T& operator()(std::size_t i, std::size_t j) const{
        return matrix[i * size_column + j];
    }

    std::vector<T>& operator()(std::size_t i) const
    {    
        std::vector<T> result;
        result.reserve(size_string);
        
        for(std::size_t k = i * size_string; k < (i + 1) * size_string; k++)
        {
            result.push_back(matrix[k]);
        }

        return result;
    }

    DenseMatrix<T>& operator+(const DenseMatrix<T>& other_matr) const{
        
        DenseMatrix<T> result(matrix + other_matr.Get_vec());
        
        return result;
    }

    DenseMatrix<T>& operator-(const DenseMatrix<T>& other_matr) const{
        
        DenseMatrix<T> result(matrix - other_matr.Get_vec());
        
        return result;
    }

    DenseMatrix<T>& operator*(const T& alpha) const{
        
        DenseMatrix<T> result(matrix * alpha);
        
        return result;
    }

    std::vector<T>& operator*(const std::vector<T>& other_vec) const{
        std::vector<T> result;
        result.reserve(other_vec.size());

        for(std::size_t i = 0; i < size_column; i++)
        {
            result.push_back(matrix(i) * other_vec);
        }    

        return result;
    }

};



#endif