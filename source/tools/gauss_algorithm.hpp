#include <iostream>
#include <array>

// function to reduce matrix to r.e.f.  Returns a value to 
// indicate whether matrix is singular or not
template<typename T, std::size_t N>
std::size_t forwardElim(std::array<T, N * (N + 1)>& matrix) noexcept;

// function to get matrix content
template<typename T, std::size_t N>
std::array<T, N> gaussianElimination(const std::array<T, N * (N + 1)>& matrix) noexcept
{

    std::array<T, N * (N + 1) > matrix_copy(matrix);

    /* reduction into r.e.f. */
    long long int singular_flag = forwardElim<T, N>(matrix_copy);
 
    /* if matrix is singular */
    if (singular_flag != N*(N+1))
    {
        printf("Singular Matrix.\n");
 
        /* if the RHS of equation corresponding to
           zero row  is 0, * system has infinitely
           many solutions, else inconsistent*/
        if (matrix_copy[singular_flag * N + N])
            printf("Inconsistent System.");
        else
            printf("May have infinitely many "
                   "solutions.");
    }
 
    /* get solution to system and print it using
       backward substitution */
        std::array<T, N> x;  // An array to store solution
 
    /* Start calculating from last equation up to the
       first */
    for (int i = N - 1; i >= 0; i--)
    {
        /* start with the RHS of the equation */
        x[i] = matrix_copy[i * (N + 1) + N];
 
        /* Initialize j to i+1 since matrix is upper
           triangular*/
        for (std::size_t j = i + 1; j < N; j++)
        {
            /* subtract all the lhs values
             * except the coefficient of the variable
             * whose value is being calculated */
            x[i] -= matrix_copy[i * (N + 1) + j] * x[j];
        }
 
        /* divide the RHS by the coefficient of the
           unknown being calculated */

        x[i] /= matrix_copy[i * (N + 1) + i];
    }
 
    return x;
}
 
// function for elementary operation of swapping two rows
template<typename T, std::size_t N>
void swap_row(std::array<T, N * (N + 1)>& matrix, std::size_t i, std::size_t j) noexcept
{
    //printf("Swapped rows %d and %d\n", i, j);
    
    std::size_t iN = i * (N + 1), jN = j * (N + 1); 

    for (std::size_t k = 0; k <= N; k++)
    {
        T temp = matrix[iN + k];
        matrix[iN + k] = matrix[jN + k];
        matrix[jN + k] = temp;
    }
}
 
// function to reduce matrix to r.e.f.

template<typename T, std::size_t N>
std::size_t forwardElim(std::array<T, N * (N + 1)>& matrix) noexcept
{
    for (std::size_t k = 0; k < N; k++)
    {
        // Initialize maximum value and index for pivot
        std::size_t i_max = k;
        std::size_t v_max = matrix[i_max * (N + 1) + k];
 
        /* find greater amplitude for pivot if any */
        for (std::size_t i = k + 1; i < N; i++)
            if (abs(matrix[i * (N + 1) + k]) > v_max)
                v_max = matrix[i * (N + 1) + k], i_max = i;
 
        /* if a principal diagonal element  is zero,
         * it denotes that matrix is singular, and
         * will lead to a division-by-zero later. */
        if (!matrix[k * (N + 1) + i_max])
            return k; // Matrix is singular
 
        /* Swap the greatest value row with current row */
        if (i_max != k)
            swap_row<T, N>(matrix, k, i_max);
 
 
        for (std::size_t i = k + 1; i < N; i++)
        {
            /* factor f to set current row kth element to 0,
             * and subsequently remaining kth column to 0 */
            T f = matrix[i * (N + 1) + k] / matrix[k * (N + 1) + k];
 
            /* subtract fth multiple of corresponding kth
               row element*/
            for (std::size_t j = k + 1; j <= N; j++)
                matrix[i * (N + 1) + j] -= matrix[k * (N + 1) + j] * f;
 
            /* filling lower triangular matrix with zeros*/
            matrix[i * (N + 1) + k] = 0;
        }
 
    }

    return N * (N + 1);
}