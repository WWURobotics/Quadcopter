#ifndef MBEDIO_H_INCLUDED
#define MBEDIO_H_INCLUDED

#include <iostream>
#include <iomanip>

#ifndef MBED_STREAM_H
namespace mbed
{
class Stream;
}
#endif

namespace quadcopter
{

using namespace std;

class mbedStreamBuf : public std::streambuf
{
private:
    mbed::Stream * const stream;
    const bool autoDelete;
    bool translateNewline;
    char * buffer;
    bool good, lastWasCR;
public:
    mbedStreamBuf(mbed::Stream * stream, bool autoDelete = true, bool translateNewline = true)
        : stream(stream), autoDelete(autoDelete), translateNewline(translateNewline), buffer(nullptr), good(true), lastWasCR(false)
    {
    }
    mbedStreamBuf(mbed::Stream & stream, bool autoDelete = false, bool translateNewline = true)
        : stream(&stream), autoDelete(autoDelete), translateNewline(translateNewline), buffer(nullptr), good(true), lastWasCR(false)
    {
    }
    virtual ~mbedStreamBuf();
    void setTranslateNewline(bool v)
    {
        translateNewline = v;
    }
    bool getTranslateNewline() const
    {
        return translateNewline;
    }
protected:
    virtual int overflow(int ch = char_traits<char>::eof());
    virtual int sync();
    virtual int underflow();
private:
    int internalGet();
};

class imbedStream : public istream
{
private:
    mbedStreamBuf sb;
public:
    imbedStream(mbed::Stream * stream, bool autoDelete = true, bool translateNewline = true)
        : istream(nullptr), sb(stream, autoDelete, translateNewline)
    {
        rdbuf(&sb);
    }
    imbedStream(mbed::Stream & stream, bool autoDelete = false, bool translateNewline = true)
        : istream(nullptr), sb(stream, autoDelete, translateNewline)
    {
        rdbuf(&sb);
    }
};

class ombedStream : public ostream
{
private:
    mbedStreamBuf sb;
public:
    ombedStream(mbed::Stream * stream, bool autoDelete = true, bool translateNewline = true)
        : ostream(nullptr), sb(stream, autoDelete, translateNewline)
    {
        rdbuf(&sb);
    }
    ombedStream(mbed::Stream & stream, bool autoDelete = false, bool translateNewline = true)
        : ostream(nullptr), sb(stream, autoDelete, translateNewline)
    {
        rdbuf(&sb);
    }
};

class iombedStream : public iostream
{
private:
    mbedStreamBuf sb;
public:
    iombedStream(mbed::Stream * stream, bool autoDelete = true, bool translateNewline = true)
        : iostream(nullptr), sb(stream, autoDelete, translateNewline)
    {
        rdbuf(&sb);
    }
    iombedStream(mbed::Stream & stream, bool autoDelete = false, bool translateNewline = true)
        : iostream(nullptr), sb(stream, autoDelete, translateNewline)
    {
        rdbuf(&sb);
    }
};

extern imbedStream mbedIn;
extern ombedStream mbedOut;

}

#endif // MBEDIO_H_INCLUDED
