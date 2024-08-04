#pragma once

namespace std
{
    /* Exception class to handle out of range errors */
    class out_of_range
    {
    public:
        explicit out_of_range(const char *what_arg) : message_(what_arg) {}

        const char *what() const {
            return message_;
        }

    private:
        const char *message_;
    };
}