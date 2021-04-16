#include <bindey/property.h>

#include <catch2/catch.hpp>

TEST_CASE( "Default ctor / Basic Contract" )
{
    bindey::property<bool> boolProp;

    // properties are default initialized
    CHECK( boolProp.get() == false );

    boolProp.set( false );
    CHECK( boolProp.get() == false );

    boolProp.set( true );
    CHECK( boolProp.get() == true );
}

TEST_CASE( "Value ctor" )
{
    bindey::property<bool> boolProp( true );

    // properties are default initialized
    CHECK( boolProp.get() == true );

    boolProp.set( false );
    CHECK( boolProp.get() == false );

    boolProp.set( true );
    CHECK( boolProp.get() == true );
}

TEST_CASE( "Change Notitfcations" )
{
    bindey::property<bool> boolProp;
    REQUIRE( boolProp.get() == false );

    bool wasCalled = false;
    boolProp.onChanged( [&]( const auto& ) { wasCalled = true; } );

    boolProp.set( false );
    REQUIRE( wasCalled == false );

    boolProp.set( true );
    REQUIRE( wasCalled == true );
}
