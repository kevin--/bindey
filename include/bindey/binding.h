#pragma once

#include "property.h"

#include <nod/nod.hpp>

#include <functional>
#include <type_traits>

namespace bindey
{

using binding        = nod::connection;
using scoped_binding = nod::scoped_connection;

/**
 * base binding signature
 */
template <typename T, typename To>
binding bind( property<T>& from, To& to );

/**
 * binds two properties of the same type
 */
template <typename T>
binding bind( property<T>& from, property<T>& to )
{
    return from.onChanged( [&]( const auto& newValue ) { to( newValue ); } );
}

/**
 * binds two properties of differing types using a Converter callable
 * @param   from  property to observe
 * @param   to  property to write to
 * @param   bindingConverter    a callable to invoke to convert between the types
 */
template <typename TFrom, typename TTo, typename Converter>
binding bind( property<TFrom>& from, property<TTo>& to, Converter&& bindingConverter )
{
    static_assert( std::is_convertible<Converter&&, std::function<TTo( const TFrom& )>>::value,
                   "Wrong Signature for binding converter!" );

    return from.onChanged(
        [&to, converter = bindingConverter]( const auto& newValue ) { to( converter( newValue ) ); } );
}

} // namespace bindey
