// k13
// Kyle J Burgess

#include "event.h"

k13::callback_persistence compute_something(int& r, int x, int y)
{
    r = x;

    for (int i = 0; i != 100; ++i)
    {
        r += (x * i) % y;
    }

    return k13::persist_callback;
}

struct Object
{
    int x;
    int y;

    k13::callback_persistence compute_something(int& r) const
    {
        r = x;

        for (int i = 0; i != 100; ++i)
        {
            r += (x * i) % y;
        }

        return k13::persist_callback;
    }
};

int main()
{
    int r = 0, rA = 0, rB = 0, rC = 0, rD = 0;

    compute_something(r, 10, 20);

    if (r == 0)
    {
        return -1;
    }

    // invoke static event
    auto eventA = std::make_shared<k13::event<int&,int,int>>();
    eventA->add_callback(compute_something);
    eventA->invoke(rA, 10, 20);

    if (rA != r)
    {
        return -1;
    }

    // forward event
    auto eventB = std::make_shared<k13::event<int&,int,int>>();
    eventB->forward_once(eventA);

    // invoke once
    eventB->invoke(rB, 10, 20);
    if (rB != r)
    {
        return -1;
    }

    // invoke again (with forward_once)
    rB = 0;
    eventB->invoke(rB, 10, 20);
    if (rB == r)
    {
        return -1;
    }

    auto object = std::make_shared<Object>();
    object->x = 10;
    object->y = 20;

    // invoke member event

    auto eventC = std::make_shared<k13::event<int&>>();
    eventC->add_callback(object, &Object::compute_something);
    eventC->invoke(rC);
    if (rC != r)
    {
        return -1;
    }

    // forward event (multiple times)
    auto eventD = std::make_shared<k13::event<int&>>();
    eventD->forward(eventC);

    // invoke multiple times
    for (int i = 0; i != 5; ++i)
    {
        rD = 0;
        eventD->invoke(rD);
        if (rD != r)
        {
            return -1;
        }
    }

    return 0;
}
