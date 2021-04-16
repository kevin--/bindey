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
Coming soon.
You'll love it.
