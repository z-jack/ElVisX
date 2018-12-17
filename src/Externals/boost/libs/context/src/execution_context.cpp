
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "boost/context/detail/config.hpp"

#if ! defined(BOOST_CONTEXT_NO_CXX11)

#include "boost/context/execution_context.hpp"
#include <boost/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {

#if !defined(BOOST_NO_CXX11_THREAD_LOCAL)

namespace detail {

activation_record::ptr_t &
activation_record::current() noexcept {
    thread_local static ptr_t current;
    return current;
}

// zero-initialization
thread_local static std::size_t counter;

// schwarz counter
activation_record_initializer::activation_record_initializer() noexcept {
    if ( 0 == counter++) {
        activation_record::current().reset( new activation_record() );
    }
}

activation_record_initializer::~activation_record_initializer() {
    if ( 0 == --counter) {
        BOOST_ASSERT( activation_record::current()->is_main_context() );
        delete activation_record::current().detach();
    }
}

}

namespace v1 {

execution_context
execution_context::current() noexcept {
    // initialized the first time control passes; per thread
    thread_local static detail::activation_record_initializer initializer;
    return execution_context();
}

}

#endif

}}

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_SUFFIX
#endif

#endif
