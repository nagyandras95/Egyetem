//Author:   Gregorics Tibor
//Date:     2018.06.30.
//Task:     general programing theorem

#pragma once

#include <cstddef>
#include "enumerator.hpp"

//template class of general programing theorems
//template parameters:  Item    - the type of the elements that are enumerated
//new virtual methods:  init()          - initializes the programming theorem
//                      body()          - one iteration of the programming theorem
//                      first()         - first step of the enumerator
//                      whileCond()     - can stop the enumerator earlier
//                      loopCond()      - loop condition of the programming theorem
//                      run()           - executes the programing theorem
//                      addEnumerator() - gives an enumerator to the programming theorem
//representation:       Enumerator<Item> *_enor
template <typename Item >
class Procedure
{
    protected:
        Enumerator<Item> *_enor;

        Procedure():_enor(nullptr){}
        virtual void init() = 0;
        virtual void body(const Item& e) = 0;
        virtual void first() {_enor->first();}
        virtual bool whileCond(const Item& current) const { return true; }
        virtual bool loopCond() const
                   { return !_enor->end() && whileCond(_enor->current()) ; }
    public:
        enum Exceptions { MISSING_ENUMERATOR};
        virtual void run() final;
        virtual void addEnumerator(Enumerator<Item>* en) final { _enor = en;}
        virtual ~Procedure(){}
};

//Task: 	runs the programming theorem
//Input:    Enumerator<Item> *_enor - enumerator
//Activity: algorithm of programming theorem
template <class Item>
void Procedure<Item>::run()
{
    if(_enor==nullptr) throw MISSING_ENUMERATOR;
    init();
    for(first(); loopCond(); _enor->next()){
        body(_enor->current());
    }
}
