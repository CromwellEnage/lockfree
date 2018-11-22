// boost lockfree
//
// Copyright (C) 2011, 2016 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_DETAIL_PARAMETER_HPP
#define BOOST_LOCKFREE_DETAIL_PARAMETER_HPP

#include <boost/lockfree/policies.hpp>
#include <boost/parameter/parameters.hpp>
#include <boost/parameter/binding.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/identity.hpp>

#include <boost/lockfree/detail/allocator_rebind_helper.hpp>


namespace boost {
namespace lockfree {
namespace detail {

template <typename bound_args>
struct extract_capacity
{
    typedef typename boost::mpl::eval_if<
        typename boost::mpl::has_key<bound_args, tag::capacity>::type
      , boost::parameter::binding<bound_args, tag::capacity>
      , boost::mpl::size_t< 0 >
    >::type capacity_t;

    static const std::size_t capacity = capacity_t::value;
};


template <typename bound_args, typename T>
struct extract_allocator
{
    typedef typename boost::mpl::eval_if<
        typename boost::mpl::has_key<bound_args, tag::allocator>::type
      , boost::parameter::binding<bound_args, tag::allocator>
      , boost::mpl::identity<std::allocator<T> >
    >::type allocator_arg;

    typedef typename detail::allocator_rebind_helper<allocator_arg, T>::type type;
};

template <typename bound_args, bool default_ = false>
struct extract_fixed_sized
{
    typedef typename mpl::eval_if<
        typename boost::mpl::has_key<bound_args, tag::fixed_sized>::type
      , boost::parameter::binding<bound_args, tag::fixed_sized>
      , boost::mpl::bool_<default_>
    >::type type;

    static const bool value = type::value;
};


} /* namespace detail */
} /* namespace lockfree */
} /* namespace boost */

#endif /* BOOST_LOCKFREE_DETAIL_PARAMETER_HPP */
