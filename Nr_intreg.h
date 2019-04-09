#ifndef NR_INTREG_H_INCLUDED
#define NR_INTREG_H_INCLUDED
#include "Nr_natural.h"

class nr_intreg: public nr_natural
{
    char semn;

    public:
        nr_intreg(){semn = '+';}
        ~nr_intreg(){semn = '+';}
        nr_intreg(const nr_intreg &n):nr_natural(n){semn = n.semn;}
        nr_intreg operator= (const nr_intreg &);
        nr_intreg operator= (const int &);
        bool operator== (const nr_intreg &);
        bool operator< (const nr_intreg &);
        bool operator> (const nr_intreg &);
        nr_intreg operator+ (nr_intreg &);
        nr_intreg operator- (nr_intreg &);
        nr_intreg operator* (nr_intreg &);
        void citire(std::istream &);
        void scrie(std::ostream &) const;
};

#endif // NR_INTREG_H_INCLUDED
