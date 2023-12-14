#include <array>
#include <type_traits>
#include <iostream>
#include <cmath>

template<typename A>
struct ArgumentGetter;

template<typename R, typename Arg>
struct ArgumentGetter<R(Arg)> {
    using Argument = Arg;
};

template<typename T>
using Dif = decltype(std::declval<T>() - std::declval<T>());


template<typename RealType, typename T, std::size_t N>
RealType Legendre(T x){
    
    RealType Legendre0 = 1;
    RealType Legendre1 = x;
    RealType Legendre;

    for(std::size_t i = 1; i < N; i++){
        Legendre = (2 * i + 1) / (i + 1) * x * Legendre1 - i / (i + 1) * Legendre0;
        Legendre0 = Legendre1;
        Legendre1 = Legendre;
    }

    return Legendre;
}

template<typename RealType, typename T, std::size_t N>
RealType DerivativeLegendre(T x){
    
    return N / (1 - x * x) * (Legendre<RealType, T, N - 1>(x) - x * Legendre<RealType, T, N>(x)); 
}


/* Функция производит интегрирование на одном отрезке */
template<typename Callable, typename RealType, std::size_t N>
decltype(auto) integrate(   
    const Callable& func,  // Интегрируемая функция
    const typename ArgumentGetter<Callable>::Argument& start,  // начало отрезка
    const typename ArgumentGetter<Callable>::Argument&   end  // конец отрезка
                        );

/* Функция производит интегрирование, разбивая отрезок на подотрезки длиной не более dx */
template<typename Callable, typename RealType, std::size_t N>
decltype(auto) integrate(   
    const Callable& func,  // Интегрируемая функция
    const typename ArgumentGetter<Callable>::Argument& start,  // начало отрезка
    const typename ArgumentGetter<Callable>::Argument& end,  // конец отрезка
    const Dif<typename ArgumentGetter<Callable>::Argument>& dx  // Длина подотрезка
                        );


template<typename Callable, typename RealType, std::size_t N>
decltype(auto) integrate(
    const Callable& func,
    const typename ArgumentGetter<Callable>::Argument& start,
    const typename ArgumentGetter<Callable>::Argument& end
                        ){

    using ArgType = typename ArgumentGetter<Callable>::Argument;

    std::array<RealType, 6> gauss_nodes;
    std::array<RealType, 6> gauss_weights;
    
    switch (N)
    {
        case 3:
            gauss_nodes = {-0.7745966692414834, 0, 0.7745966692414834};
            gauss_weights = {0.555555555555556, 0.888888888888889, 0.555555555555556};

            break;

        case 6:
            gauss_nodes = {-0.932469514203152, -0.661209386466265, -0.238619186083197, 0.238619186083197, 0.661209386466265, 0.932469514203152};
            gauss_weights = {0.171324492379170, 0.360761573048139, 0.467913934572691, 0.467913934572691, 0.360761573048139, 0.171324492379170};

            break;

        default:
            static_assert((N == 3 || N == 6), "Compile-time error: This program will not compile, because N != 3 or 6.");
            
            break;
    }


//    for(std::size_t i = 0; i < N; i++){  
        
//        RealType a = Legendre<RealType, ArgType, N>(gauss_nodes[i]);
        
//        RealType b =  DerivativeLegendre<RealType, ArgType, N>(gauss_nodes[i]);
        
//         while( std::abs(a) > 1e-16){
// //          std::cout << gauss_nodes[i] - phi[i] << '\n';

//             gauss_nodes[i]  = gauss_nodes[i] - a / b;
//             a = Legendre<RealType, ArgType, N>(gauss_nodes[i]);  
//             b = DerivativeLegendre<RealType, ArgType, N>(gauss_nodes[i]);
//             //std::cout << gauss_nodes[i] << ' ' <<  a  << '\n';      
//         }
    
    //     RealType legendre_node_0 = gauss_nodes[i];
    //     RealType legendre_node_1 = 1.000001 * gauss_nodes[i];

    //     while(std::abs(legendre_node_1 - legendre_node_0) > 1e-16 ){
    //         gauss_nodes[i] = legendre_node_0 - (Legendre<RealType, ArgType, N>(legendre_node_0) * (legendre_node_1 - legendre_node_0)) / (Legendre<RealType, ArgType, N>(legendre_node_1) - Legendre<RealType, ArgType, N>(legendre_node_0));
    //         legendre_node_0 = legendre_node_1;
    //         legendre_node_1 = gauss_nodes[i];
    //     } 
    // }

    
    // for(std::size_t i = 0; i < N; i++){
        
    //     RealType derLeg = DerivativeLegendre<RealType, ArgType, N>(gauss_nodes[i]);
    //     gauss_weights[i] = 2 / ( (1 - gauss_nodes[i] * gauss_nodes[i]) * derLeg * derLeg);

    // }




    Dif<ArgType> diap = end - start;

    RealType integral = func(((end + start) + diap * gauss_nodes[0]) / 2) * gauss_weights[0];
    
    for(std::size_t i = 1; i < N; i++){

        integral += func(((end + start) + diap * gauss_nodes[i]) / 2) * gauss_weights[i];
    }

    integral *= diap / 2;

    return integral;
}


template<typename Callable, typename RealType, std::size_t N>
decltype(auto) integrate(   
    const Callable& func,  // Интегрируемая функция
    const typename ArgumentGetter<Callable>::Argument& start,  // начало отрезка
    const typename ArgumentGetter<Callable>::Argument& end,  // конец отрезка
    const Dif<typename ArgumentGetter<Callable>::Argument>& dx  // Длина подотрезка
                        ){

    decltype(auto) integral = integrate<Callable, RealType, N>(func, start, start + dx);

    Dif<typename ArgumentGetter<Callable>::Argument> diap = end - start;

    std::size_t n = static_cast<std::size_t>(diap / dx);

    for(std::size_t i = 1; i < n; i++)
    {
        integral += integrate<Callable, RealType, N>(func, start + dx * i, start + dx * (i + 1));
    }
    
    if( end == static_cast<typename ArgumentGetter<Callable>::Argument>(start + dx * n)){
        return integral;
    }

    integral += integrate<Callable, RealType, N>(func, start + dx * n, end);

    return integral;
}


