#pragma once

#include "property.h"

#include <nod/nod.hpp>

namespace bindey
{

using binding = nod::connection;
using scoped_binding = nod::scoped_connection;

/**
 * base binding signature
 */
template <typename T, typename To>
binding bind( property<T>& from, To& to );
/**
 * binds two properties of the same type
 */
template<typename T>
binding bind( property<T>& from, property<T>& to )
{
    return from.onChanged( [&]( const auto& newValue ) { to( newValue ); } );
}

}
