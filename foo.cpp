#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <iostream>
#include <tuple>

#define ARG_MACRO(r, data, i, elem) \
    BOOST_PP_IF(i, BOOST_PP_COMMA, BOOST_PP_EMPTY)() elem(std::get<i>(x))
#define ATTRIBUTE_MACRO(r, data, i, elem) std::decay_t<decltype(std::get<i>(input))> elem;

#define ADAPT_FIELDS(...)                                                                         \
    [](auto&& input) {                                                                            \
        struct nested {                                                                           \
            nested(std::decay_t<decltype(input)>&& x)                                             \
                : BOOST_PP_SEQ_FOR_EACH_I(ARG_MACRO, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)) {} \
            BOOST_PP_SEQ_FOR_EACH_I(ATTRIBUTE_MACRO, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))    \
        };                                                                                        \
        return nested{std::move(input)};                                                          \
    }

int main(int, char**) {
    auto thing = ADAPT_FIELDS(foo, bar, baz)(std::make_tuple(1, 2, 3));
    std::cout << "foo: " << thing.foo << "\n";
    std::cout << "bar: " << thing.bar << "\n";
    std::cout << "baz: " << thing.baz << "\n";
}
