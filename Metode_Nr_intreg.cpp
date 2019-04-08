#include "Nr_intreg.h"
#include <cmath>

nr_intreg nr_intreg::operator= (const nr_intreg &b)
{
    semn = b.semn;
    nr_cifre = b.nr_cifre;
    nr = b.nr;
    return (*this);
}

nr_intreg nr_intreg::operator= (const int &b)
{
    int c = b;
    nr.sterge_lista();
    nr_cifre = 0;
    if(b<0)
    {
        semn = '-';
        c = std::abs(b);
    }
    if(c==0){nr.adauga_sf(0);nr_cifre++;}
    while(c!=0)
    {
        nr.adauga_sf(c%10);
        nr_cifre++;
        c /= 10;
    }
    return (*this);
}

bool nr_intreg::operator== (const nr_intreg &b)
{
    if(semn != b.semn)
        return false;
    else
    {
        nod<int> *p = this->nr.start;
        nod<int> *q = b.nr.start;
        while(p!=NULL && q!=NULL)
        {
            if(p->key != q->key)
                return false;
            p = p->next;
            q = q->next;
        }
        if(p!=q)
            return false;
    }
    return true;
}

bool nr_intreg::operator<(const nr_intreg &b)
{
    if(b.semn == '-' && semn == '+')
        return false;
    else if(semn == '-'  && b.semn == '+' )
        return true;
    else if (b.nr_cifre == nr_cifre)
    {
        nod<int> * p = nr.stop;
        nod<int> * q = b.nr.stop;
        while(p!=NULL && q!=NULL)
        {
            if(p->key > q->key)
                return false;
            p = p->prec;
            q = q->prec;
        }
    }
    else if(b.nr_cifre < nr_cifre)
        return false;
    return true;
}

bool nr_intreg::operator>(const nr_intreg &b)
{
    if(b.semn == '-' && semn == '+')
        return true;
    else if(semn == '-'  && b.semn == '+' )
        return false;
    if( b.nr_cifre == nr_cifre )
    {
        nod<int> * p = nr.stop;
        nod<int> * q = b.nr.stop;
        while(p!=NULL && q!=NULL)
        {
            if(p->key < q->key)
                return true;
            p = p->prec;
            q = q->prec;
        }
    }
    else if(b.nr_cifre > nr_cifre)
        return true;
    return false;
}

void nr_intreg::citire(std::istream &in)
{
    std::string sir; int i = 0,c;
    in >> sir;
    if(sir[0] == '-')
    {
        semn = sir[0];
        i++;
    }
    c = sir.length();
    for(i=i;i<c;i++)
    {
        if(sir[i]-'0'<= 9 && sir[i]-'0' >=0)
             {nr.adauga_in(sir[i]-'0'); nr_cifre++;}
        else
        {
            nr.sterge_lista();
            nr_cifre = 0;
            this->citire(in);
        }
    }
    struct nod<int> *p = nr.stop, *q;
    while(p->prec != NULL && p->key==0)
    {
        q = p;
        p = p->prec;
        delete q;
        nr_cifre--;
        p->next = NULL;
        q = p;
    }
    nr.stop = p;
}

void nr_intreg::scrie(std::ostream &out) const
{
    if(semn == '-')
        out<<'-';
    struct nod<int> *p = nr.stop;
    while( p!= NULL)
    {
        out<<p->key;
        p = p->prec;
    }
}

nr_intreg nr_intreg::operator+ (nr_intreg b)
{
    nr_intreg sum;
    nr_natural *a = &(*this), *b1 = &b;
    if(semn == b.semn)
    {
        sum.semn = semn;
        sum.nr_natural::operator=(*a + *b1);
    }
    else
    {
        if(*a>*b1)
            sum.semn = (*this).semn;
        else sum.semn = b.semn;
        sum.nr_natural::operator=(*a - *b1);
    }
    if(sum.nr.stop->key == 0)
        sum.semn = '+';
    return sum;
}

nr_intreg nr_intreg::operator-(nr_intreg b)
{
    nr_intreg dif;
    nr_natural *a = &(*this), *b1 = &b;
    if(semn == b.semn)
    {
        if(b>(*this))
            dif.semn = '-';
        else dif.semn = '+';
        dif.nr_natural::operator=(*a - *b1);
    }
    else
    {
        dif.semn = semn;
        dif.nr_natural::operator=(*a + *b1);
    }

    if(dif.nr.stop->key == 0)
            dif.semn = '+';
    return dif;
}

nr_intreg nr_intreg::operator*(nr_intreg b)
{
    nr_intreg prod;
    nr_natural *a = &(*this), *b1 = &b;
    if(semn == b.semn)
        prod.semn = '+';
    else prod.semn = '-';
    prod.nr_natural::operator= (*a * *b1);
    return prod;
}


