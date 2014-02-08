#include "mbedio.h"
#include <Stream.h>
#include <Serial.h>

using namespace std;

quadcopter::mbedStreamBuf::~mbedStreamBuf()
{
    if(autoDelete)
        delete stream;
    delete []buffer;
}

int quadcopter::mbedStreamBuf::overflow(int ch)
{
    if(ch == char_traits<char>::eof())
    {
        return sync();
    }

    int retval;
    if(ch == '\n' && translateNewline)
    {
        retval = stream->putc('\r');
        if(retval == EOF)
            return -1;
    }
    retval = stream->putc(ch);
    if(retval == EOF)
        return -1;
    return 0;
}

int quadcopter::mbedStreamBuf::sync()
{
    return 0; // -1 for bad, 0 for good
}

int quadcopter::mbedStreamBuf::underflow()
{
    int ch = internalGet();
    if(ch == EOF)
    {
        good = false;
        return char_traits<char>::eof();
    }
    if(buffer == nullptr)
        buffer = new char[1];
    buffer[0] = ch;
    setg(buffer, buffer, buffer + 1);
    return buffer[0];
}

int quadcopter::mbedStreamBuf::internalGet()
{
    int ch = stream->getc();
    if(lastWasCR && ch == '\n')
    {
        ch = stream->getc();
        lastWasCR = false;
    }
    if(translateNewline)
    {
        if(ch == '\r')
        {
            lastWasCR = true;
            ch = '\n';
        }
    }
    return ch;
}

namespace
{
    mbed::Serial pc(USBTX, USBRX);
}

quadcopter::imbedStream quadcopter::mbedIn(pc);
quadcopter::ombedStream quadcopter::mbedOut(pc);
