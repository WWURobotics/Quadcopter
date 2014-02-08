#include "mbedio.h"
#include <string>

using namespace std;
using namespace quadcopter;

int main()
{
    while(true)
    {
        string str;
        mbedIn >> str;
        mbedOut << str << endl;
    }
}
