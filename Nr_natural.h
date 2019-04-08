#ifndef NR_NATURAL_H_INCLUDED
#define NR_NATURAL_H_INCLUDED

#pragma once
#include <iostream>
#include "Lista.h"

class nr_natural
{
    protected:
    lista<int> nr;
    int nr_cifre;

    public:
        nr_natural(){nr_cifre = 0;}
        ~nr_natural(){nr_cifre = 0;}
        nr_natural(const nr_natural &);
        nr_natural operator= (const nr_natural &);
        nr_natural operator= (const int &);
        bool operator== (const nr_natural &);
        bool operator< (const nr_natural &);
        bool operator> (const nr_natural &);
        nr_natural operator+ (nr_natural &);
        nr_natural operator- (nr_natural &);
        nr_natural operator* (nr_natural &);
        virtual void citire(std::istream &);
        virtual void scrie(std::ostream &) const;
        friend std::istream & operator >> (std::istream &, nr_natural &);
        friend std::ostream & operator << (std::ostream &, const nr_natural &);
};

#endif // NR_NATURAL_H_INCLUDED
