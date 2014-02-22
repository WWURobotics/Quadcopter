#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

namespace quadcopter
{
struct NullDeleter final
{
    template <typename T>
    void operator()(T *)
    {
    }
};
}

#endif // UTILITY_H_INCLUDED
