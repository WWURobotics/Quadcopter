#include "mbedio.h"
#include "gtimer.h"
#include <string>

using namespace std;
using namespace quadcopter;

int main()
{
    while(true)
    {
        mbedOut << std::setprecision(9) << global_time::get() << endl;
    }
}
