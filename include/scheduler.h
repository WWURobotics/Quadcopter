#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <memory>
#include "utility.h"

using namespace std;

namespace quadcopter
{

struct Runnable
{
    virtual ~Runnable()
    {
    }
    virtual void update() = 0;
};

class FnRunnable final : public Runnable
{
private:
    void (*fn)();
public:
    explicit FnRunnable(void (*fn)())
        : fn(fn)
    {
    }
    virtual void update() override
    {
        fn();
    }
};

class Scheduler final : public Runnable
{
public:
    virtual void update() override
    {
        for(shared_ptr<Runnable> runnable : tasks)
        {
            runnable->update();
        }
    }
    void add(shared_ptr<Runnable> runnable)
    {
        tasks.push_back(runnable);
    }
    void add(Runnable & runnable)
    {
        add(shared_ptr<Runnable>(&runnable, NullDeleter()));
    }
    bool remove(Runnable * runnable)
    {
        auto iter = tasks.begin();
        while(iter != tasks.end() && iter->get() != runnable)
        {
            iter++;
        }
        if(iter != tasks.end())
        {
            tasks.erase(iter);
            return true;
        }
        return false;
    }
    bool remove(Runnable & runnable)
    {
        return remove(&runnable);
    }
private:
    vector<shared_ptr<Runnable>> tasks;
};

}

#endif // SCHEDULER_H
