#include "Nr_natural.h"

nr_natural::nr_natural(const nr_natural &copiat)
{
    nr_cifre = copiat.nr_cifre;
    nr = copiat.nr;
}

nr_natural nr_natural::operator= (const nr_natural &b)
{
    nr_cifre = b.nr_cifre;
    nr = b.nr;
    return (*this);
}

nr_natural nr_natural::operator= (const int &b)
{
    int c = b;
    nr.sterge_lista();
    nr_cifre = 0;
    if(c==0){nr.adauga_sf(0);nr_cifre++;}
    while(c!=0)
    {
        nr.adauga_sf(c%10);
        nr_cifre++;
        c /= 10;
    }
    return (*this);
}

bool nr_natural::operator== (const nr_natural &b)
{
    if(nr_cifre == b.nr_cifre)
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

bool nr_natural::operator<(const nr_natural &b)
{
    if( b.nr_cifre == nr_cifre )
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

bool nr_natural::operator>(const nr_natural &b)
{
    if( b.nr_cifre == nr_cifre )
    {
        nod<int> * p = nr.stop;
        nod<int> * q = b.nr.stop;
        while(p!=NULL && q!=NULL)
        {
            if(p->key < q->key)
                return false;
            p = p->prec;
            q = q->prec;
        }
    }
    else if(b.nr_cifre > nr_cifre)
        return false;
    return true;
}

void nr_natural::citire(std::istream &in)
{
    std::string sir; int i = 0,c;
    in >> sir;
    c = sir.length();
    for(i=i;i<c;i++)
    {
        if(sir[i]-'0'<= 9 && sir[i]-'0' >=0)
        {
            nr.adauga_in(sir[i]-'0');
            nr_cifre++;
        }
        else
        {
            nr.sterge_lista();
            nr_cifre = 0;
            this->citire(in);
        }
    }
    nod<int> *p = nr.stop, *q;
    while(p->prec != NULL && p->key==0)
    {
        q = p;
        p = p->prec;
        delete q;
        p->next = NULL;
        q = p;
        nr_cifre--;
    }
    nr.stop = p;
}

std::istream & operator >> (std::istream &in, nr_natural &n)
{
    n.citire(in);
    return in;
}

void nr_natural::scrie(std::ostream &out) const
{
    nod<int> *p = nr.stop;
    while( p!= NULL)
    {
        out<<p->key;
        p = p->prec;
    }
}

std::ostream & operator << (std::ostream &out, const nr_natural &n)
{
    n.scrie(out);
    return out;
}

nr_natural nr_natural::operator+ (nr_natural &b)
{
    int r = 0;
    nod<int> *p = this->nr.start;
    nod<int> *q = b.nr.start;
    nr_natural c;
    while( p!=NULL && q!=NULL )
    {
        c.nr.adauga_sf((p->key + q->key +r )%10);
        c.nr_cifre++;
        r = (p->key + q->key)/10;
        p = p->next;
        q = q->next;
    }
    if( p==q )
    {
         if(r){
            c.nr.adauga_sf(r);
            c.nr_cifre++;
         }
    }
    else
    {
        if( p==NULL )
            p = q;
        while( p!=NULL )
        {
            c.nr.adauga_sf((p->key+r)%10);
            c.nr_cifre++;
            r = (p->key +r)/10;
            p = p->next;
        }
        if(r)
        {
            c.nr.adauga_sf(r);
            c.nr_cifre++;
        }
    }
    return c;
}

nr_natural nr_natural::operator- (nr_natural &b)
{
    int r = 0;
    struct nod<int> *p, *q;
    nr_natural c;
    if(b>(*this))
    {
        p = b.nr.start;
        q = nr.start;
    }
    else
    {
        p = nr.start;
        q = b.nr.start;
    }
    while( p!=NULL && q!=NULL )
    {
        c.nr.adauga_sf((p->key + 10 - q->key - r )%10);
        c.nr_cifre++;
        r = (p->key - r < q->key);
        p = p->next;
        q = q->next;
    }
    if( p!=NULL )
    {
        while( p!=NULL )
        {
            c.nr.adauga_sf((p->key + 10 - r)%10);
            c.nr_cifre++;
            r = (p->key - r < 0);
            p = p->next;
        }

    }
    p = c.nr.stop;
    while(p->prec != NULL && p->key==0)
    {
        q = p;
        p = p->prec;
        delete q;
        p->next = NULL;
        c.nr_cifre--;
        q = p;
    }
    c.nr.stop = p;
    return c;
}

nr_natural nr_natural::operator*(nr_natural &b)
{
    nr_natural prod, sum;
    prod.nr.adauga_in(0);
    int r = 0, i = 0, j;
    nod<int> *p = nr.start, *q = b.nr.start;
    while(p != NULL)
    {
        while(q != NULL)
        {
            sum.nr.adauga_sf((p->key*q->key + r)%10);
            sum.nr_cifre++;
            r = (p->key*q->key + r)/10;
            q = q->next;
        }
        if(r){sum.nr.adauga_sf(r);sum.nr_cifre++;}
        for(j = 0; j < i; j++)
            {sum.nr.adauga_in(0);sum.nr_cifre++;}
        prod = prod + sum;
        i++;
        sum.nr.sterge_lista();
        sum.nr_cifre = 0;
        p = p->next;
        q = b.nr.start;
        r = 0;
    }
    p = prod.nr.stop;
    while(p->prec != NULL && p->key==0)
    {
        q = p;
        p = p->prec;
        delete q;
        prod.nr_cifre--;
        p->next = NULL;
        q = p;
    }
    prod.nr.stop = p;
    return prod;
}
