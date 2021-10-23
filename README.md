# bindey

Everyone knows Model-View-ViewModel is the best architecture, but how can we realize it in C++ applications with minimal overhead, and no complicated framework impositions?

`bindey` provides the basic building block of MVVM -- an observable "Property" and a databinding mechanism.

## Property Usage

At minimum, `bindey::property` can allow you to avoid writing getters and setters. Consider this example:

```
#include <bindey/property.h>

using namespace bindey;

class Person
{
public:
    property<std::string> name;
    property<int> age;
};
```
Then we can use it like this:
```
Person p;
p.name("Kevin");
p.age(666);

auto thatDudesName = p.name();
auto ageIsJustANumber = p.age();
```

`property` default initializes its value with `{}`, and of course allows initialization.
```
Person::Person()
: name("Default Name")
, age(0)
{}
```
## Data Binding
`bindey` provides a simple binding mechanism to connect a "source" `property` to an arbitrary object. This base signature is
```
template <typename T, typename To>
binding bind( property<T>& from, To& to );
```
And a specialization for `property` to `property` binding of the same type is provided.
```
template<typename T>
binding bind( property<T>& from, property<T>& to )
{
    return from.onChanged( [&]( const auto& newValue ) { to( newValue ); } );
}
```

### Writing Your Own Bindings
Where this becomes fun is when you get to reduce boilerplate. For example, assume a `Button` class from some UI Framework.
```
struct Button
{
    void setText(const std::string& text)
    {
        this->text = text;
    }

    std::string text;
};
```
To make your life better, simply implement a template speciailization in the `bindey` namespace.
```
namespace bindey
{
template <>
binding bind( property<std::string>& from, Button& to )
{
    return from.onChanged( [&]( const auto& newValue ){ to.setText( newValue ); } );
}
} // namespace bindey
```
Then, bind your property to the button as needed:
```
bindey::property<std::string> name;
...
Button someButton;
...
bindey::bind( name, someButton );
```

### Binding Lifetimes
The result of a call to `bind` is a `bindey::binding` object. If this return value is discarded, then the binding's lifetime is coupled to the `property`'s.

Otherwise, this token can be used to disconnect the binding as needed, the easiest way is to capture it in a `scoped_binding` object.

For example, if your binding involves objects who's lifetime you do not control, you should certainly capture the binding to avoid crashes.
```
struct GreatObj
{
    GreatObj(Button* b)
    {
        mSomeButton = b;
        mButtonBinding = bindey::bind( name, *mSomeButton );
    }

    void updateButton(Button* newB)
    {
        mSomeButton = nullptr;
        mButtonBinding = {}; // disconnect from old button
        if( newB != nullptr )
        {
            mSomeButton = newB;
            mButtonBinding = bindey::bind( name, *mSomeButton );
        }
    }

    bindey::scoped_binding mButtonBinding;
};
```
