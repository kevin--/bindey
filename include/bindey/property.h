#pragma once

#include <nod/nod.hpp>

#include <functional>

namespace bindey
{

/**
 * Optional always_update policy to notify subscribers everytime the property value is set, not just when it changes
 */
class always_update
{
public:
    template <typename T>
    bool operator()( const T&, const T& ) const
    {
        return true;
    }
};

template <typename T,
          typename UpdatePolicy = std::not_equal_to<T>,
          typename Signal       = nod::unsafe_signal<void( const T& )>>
class property
{
public:
    property()
    {
    }
    property( T&& value )
    : mStorage( std::move( value ) )
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
    void set( const T& value )
    {
        if ( UpdatePolicy{}( mStorage, value ) )
        {
            mStorage = value;
            changed( mStorage );
        }
    }

    void set( T&& value )
    {
        if ( UpdatePolicy{}( mStorage, value ) )
        {
            mStorage = std::move( value );
            changed( mStorage );
        }
    }

    void operator()( const T& value )
    {
        set( value );
    }

    void operator()( T&& value )
    {
        set( std::move( value ) );
    }

    /**
     * this signal is invoked whenever the the value changes per the UpdatePolicy
     * @discussion nod::unsafe_signal is used here for speed. Take care of your own threading.
     */
    Signal changed;

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
        auto connection = onChanged( std::move( c ) );
        changed( mStorage );
        return connection;
    }


private:
    T mStorage{};
};

/**
 * thread safe property type based on nod::signal
 */
template <typename T, typename UpdatePolicy = std::not_equal_to<T>>
using safe_property = property<T, UpdatePolicy, nod::signal<void( const T& )>>;

} // namespace bindey
