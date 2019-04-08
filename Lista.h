#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include<iostream>
#pragma once

template <class T> struct nod
{
    T key;
    nod<T> *next;
    nod<T> *prec;
};

class nr_natural;
class nr_intreg;

template <class T> class lista
{
    nod<T> *start;
    nod<T> *stop;

    public:
    lista<T>();
    lista<T>(const lista<T> &);
    ~lista<T>();
    lista<T>operator=(const lista<T> &);
    void adauga_in(T );
    void adauga_sf(T );
    void sterge_lista();
    template <typename N>
    friend std::istream & operator>>(std::istream &,lista<N> &);
    template <typename N>
    friend std::ostream & operator<<(std::ostream &,const lista<N> &);

    friend std::istream & operator >> (std::istream &, nr_natural &);
    friend std::ostream & operator << (std::ostream &, const nr_natural &);
    friend class nr_natural;
    friend class nr_intreg;
};

template <class T>
lista<T>::lista()
{
    start = new nod<T>;
    stop = new nod<T>;
    start = stop = NULL;
}

template <class T>
lista<T>::~lista()
{
    delete start;
    delete stop;
}

template <class T>
lista<T>::lista(const lista<T> &lis)
{
    (*this).sterge_lista();
    struct nod<T> *p = lis.stop;
    while(p != NULL)
    {
        (*this).adauga_in(p->key);
        p = p->prec;
    }
}

template <class T>
lista<T> lista<T>::operator=(const lista<T> & lis)
{
    (*this).sterge_lista();
    struct nod<T> *p = lis.stop;
    while(p != NULL)
    {
        (*this).adauga_in(p->key);
        p = p->prec;
    }
}

template <class T>
void lista<T>::sterge_lista()
{
    nod<T> *p = start;
    while( p != NULL )
    {
        start = p->next;
        delete p;
        p = start;
    }
    start = stop = NULL;
}

template <class T>
void lista<T>::adauga_in(T x)
{
    nod<T> *p = new nod<T>;
    p->key = x;
    p->prec = NULL;
    p->next = NULL;
    if(start == NULL)
        start = stop = p;
    else
    {
        start->prec = p;
        p->next = start;
        start = p;
    }
}

template <class T>
void lista<T>::adauga_sf(T x)
{
    nod<T> *p = new nod<T>;
    p->key = x;
    p->prec = NULL;
    p->next = NULL;
    if(start == NULL)
        start = stop = p;
    else
    {
        stop->next = p;
        p->prec = stop;
        stop = p;
    }
}

template <class T>
std::istream & operator>>(std::istream &in, lista<T> &lis)
{
    T data;
    in>>data;
    lis.adauga_sf(data);
    return in;
}

template <class T>
std::ostream & operator<<(std::ostream &out,const lista<T> &lis)
{
    nod<T> *p = lis.start;
    while(p)
    {
        out<<p->key<<" ";
        p = p->next;
    }
    return out;
}


#endif // LISTA_H_INCLUDED
