#include "mbedio.h"
#include "gtimer.h"
#include <string>

using namespace std;
using namespace quadcopter;

int main()
{
    while(true)
    {
        mbedOut << global_time::get() << endl;
    }
}
