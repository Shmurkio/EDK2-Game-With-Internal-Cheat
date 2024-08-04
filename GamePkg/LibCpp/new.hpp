#pragma once

#include <stdlib.h>

typedef void(*new_handler) ();

inline new_handler get_new_handler()
{
    static new_handler global_new_handler = nullptr;
    return global_new_handler;
}

inline new_handler set_new_handler(new_handler handler)
{
    static new_handler global_new_handler = nullptr;
    new_handler old_new_handler = global_new_handler;
    global_new_handler = handler;
    return old_new_handler;
}

void* operator new(size_t size) noexcept
{
    void *ptr;

    if (size == 0) {
        size = 1;
    }

    while ((ptr = malloc(size)) == nullptr)
    {
        new_handler newhandler = get_new_handler();

        if (newhandler)
        {
            newhandler();
        }
        else
        {
            break;
        }
    }
    return ptr;
}

void operator delete(void *ptr) noexcept
{
    if (ptr)
    {
        ::free(ptr);
    }
}

void* operator new[](size_t size) noexcept
{
    return ::operator new(size);
}

void operator delete[](void *ptr) noexcept
{
    ::operator delete(ptr);
}

void operator delete(void *ptr, size_t size) noexcept
{
    ::operator delete(ptr);
}


void operator delete[](void *ptr, size_t size) noexcept
{
    ::operator delete[](ptr);
}