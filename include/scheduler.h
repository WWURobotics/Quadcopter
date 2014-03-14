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
    void (*fn)(void *);
    void *arg;
    void (*deleteFn)(void *);
public:
    template <typename T>
    explicit FnRunnable(void (*fn)(T *arg), T *arg, void (*deleteFn)(T *arg) = nullptr)
        : fn((void (*)(void *))fn), arg((void *)arg), deleteFn((void (*)(void *))deleteFn)
    {
    }
    template <typename Function>
    explicit FnRunnable(Function fnObject)
        : fn([](void * fnObjectIn){(*(Function *)fnObjectIn)();}), arg((void *)new Function(fnObject)), deleteFn([](void * objIn){delete (Function *)objIn;})
    {
    }
    virtual ~FnRunnable()
    {
        if(deleteFn != nullptr)
            deleteFn(arg);
    }
    virtual void update() override
    {
        fn(arg);
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
