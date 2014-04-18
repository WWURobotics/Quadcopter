#ifndef OUTPUT_H_INCLUDED
#define OUTPUT_H_INCLUDED

#include "scheduler.h"
#include <array>
#include <ostream>
#include <cassert>

using namespace std;

namespace quadcopter
{

template <size_t N>
class Output : public Runnable
{
    static_assert(N >= 1, "can't have output with less than 1 channel");
    Output(const Output &) = delete;
    const Output & operator =(const Output &) = delete;
private:
    array<float, N> channels;
public:
    Output()
    {
    }
    static constexpr size_t channelCount = N;
    const float & operator [](int channel) const
    {
        assert(channel >= 0 && (unsigned)channel < channelCount);
        return channels[channel];
    }
    const float & operator *() const
    {
        return operator [](0);
    }
    float & operator [](int channel)
    {
        assert(channel >= 0 && (unsigned)channel < channelCount);
        return channels[channel];
    }
    float & operator *()
    {
        return operator [](0);
    }
    float get(int channel = 0) const
    {
        return operator [](channel);
    }
    void set(int channel, float value)
    {
        operator [](channel) = value;
    }
    void set(float value)
    {
        set(0, value);
    }
    auto begin() const -> decltype(channels.cbegin())
    {
        return channels.cbegin();
    }
    auto cbegin() const -> decltype(channels.cbegin())
    {
        return channels.cbegin();
    }
    auto begin() -> decltype(channels.begin())
    {
        return channels.begin();
    }
    auto end() const -> decltype(channels.cend())
    {
        return channels.cend();
    }
    auto cend() const -> decltype(channels.cend())
    {
        return channels.cend();
    }
    auto end() -> decltype(channels.end())
    {
        return channels.end();
    }
    virtual void dump(ostream & os) const = 0;
    friend ostream & operator <<(ostream & os, const Output & o)
    {
        o.dump(os);
        return os;
    }
};

typedef Output<1> SingleChannelOutput;
typedef Output<2> DoubleChannelOutput;
typedef Output<3> TripleChannelOutput;
}

#endif // OUTPUT_H_INCLUDED
