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

    boolProp.onChangedAndNow( [&]( const auto& val ) { REQUIRE( val == true ); } );
}

TEST_CASE( "Always Update" )
{
    bindey::property<bool, bindey::always_update> boolProp;
    REQUIRE( boolProp() == false );

    int count = 0;
    boolProp.onChanged( [&]( const auto& val ) {
        switch ( count )
        {
            case 0:
                REQUIRE( val == true );
                break;

            case 1:
                REQUIRE( val == false );
                break;

            case 2:
                REQUIRE( val == false );
                break;

            default:
                FAIL( "callback should not have occured" );
                break;
        }

        count++;
    } );

    boolProp( true );

    boolProp( false );

    boolProp( false );
}

TEST_CASE( "safe_property" )
{
    bindey::safe_property<bool> boolProp;
    REQUIRE( boolProp.get() == false );

    bool wasCalled = false;
    boolProp.onChanged( [&]( const auto& ) { wasCalled = true; } );

    boolProp.set( false );
    REQUIRE( wasCalled == false );

    boolProp.set( true );
    REQUIRE( wasCalled == true );

    boolProp.onChangedAndNow( [&]( const auto& val ) { REQUIRE( val == true ); } );
}
