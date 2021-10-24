#include <bindey/binding.h>
#include <bindey/property.h>

#include <catch2/catch.hpp>

#include <string>

TEST_CASE( "Bind Property to Property" )
{
    bindey::property<std::string> source;
    bindey::property<std::string> dest;

    bindey::bind( source, dest );

    source( "radical" );
    CHECK( dest() == "radical" );
}

struct Button
{
    void setText( const std::string& text )
    {
        this->text = text;
    }

    std::string text;
};

namespace bindey
{

template <>
binding bind( property<std::string>& from, Button& to )
{
    return from.onChanged( [&]( const auto& newValue ) { to.setText( newValue ); } );
}
} // namespace bindey

TEST_CASE( "Bind Property to Object" )
{
    bindey::property<std::string> name;
    Button                        button;

    bindey::bind( name, button );

    name( "demo" );

    CHECK( button.text == "demo" );
}

TEST_CASE( "Binding Converter" )
{
    bindey::property<int>         value;
    bindey::property<std::string> stringValue;

    bindey::bind( value, stringValue, []( const auto& value ) { return std::to_string( value ); } );

    value( 7 );
    CHECK( stringValue() == "7" );
}
