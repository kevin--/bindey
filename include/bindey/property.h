#pragma once

#include <nod/nod.hpp>

#include <functional>

namespace bindey
{

template <typename T, typename UpdatePolicy = std::not_equal_to<T>>
class property
{
public:
    property()
    {
    }
    property( T&& value )
    : mStorage( std::move(value) )
    {
    }

    /**
     * gets the current value
     * @return const reference to the value
     */
    const T& get() const
    {
        return mStorage;
    }

    /**
     * gets the current value
     * @return mutable reference to the value
     */
    T& get()
    {
        return mStorage;
    }

    const T& operator()() const
    {
        return get();
    }

    T& operator()()
    {
        return get();
    }

    /**
     * sets the value of the property.
     * @param value the new value
     * @discussion the value will only be updated if the UpdatePolicy's critera is met.
     * if the value is changed, then the @ref changed event will be fired.
     */
    void set( T&& value )
    {
        if ( UpdatePolicy{}( mStorage, value ) )
        {
            mStorage = std::forward<T>( value );
            changed( mStorage );
        }
    }

    void operator()( T&& value )
    {
        set( std::forward<T>( value ) );
    }

    /**
     * this signal is invoked whenever the the value changes per the UpdatePolicy
     * @discussion nod::unsafe_signal is used here for speed. Take care of your own threading.
     */
    nod::unsafe_signal<void( const T& newValue )> changed;

    /**
     * convience function to attach a change listener to this property
     */
    auto onChanged( typename decltype( changed )::slot_type&& c )
    {
        return changed.connect( std::move( c ) );
    }

    /**
     * convience function to attach a change listener to this property and call it right away
     */
    auto onChangedAndNow( typename decltype( changed )::slot_type&& c )
    {
        auto connection = onChanged( c );
        changed( mStorage );
        return connection;
    }


private:
    T mStorage{};
};

} // namespace bindey