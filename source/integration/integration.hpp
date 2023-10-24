#include <array>
#include <type_traits>

template<typename A>
struct ArgumentGetter;

template<typename R, typename Arg>
struct ArgumentGetter<R(Arg)> {
    using Argument = Arg;
};

template<typename T>
using Dif = decltype(std::declval<T>() - std::declval<T>());

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

    std::array<RealType, 6> gauss_nodes;
    std::array<RealType, 6> gauss_weights;
    
    switch (N)
    {
        case 3:
            gauss_nodes = {-0.7745967, 0.0, 0.7745967};
            gauss_weights = {0.5555556, 0.8888889, 0.5555556};

            break;

        case 6:
            gauss_nodes = {-0.9324700, -0.6612094, -0.2386142, 0.2386142, 0.6612094, 0.9324700};
            gauss_weights = {0.1713245, 0.3607616, 0.4679140, 0.4679140, 0.3607616, 0.1713245};

            break;

        default:
            static_assert(N == 3 || N == 6, "Compile-time error: This program will not compile, because N != 3 or 6.");
            break;
    }

    Dif<typename ArgumentGetter<Callable>::Argument> diap = end - start;

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