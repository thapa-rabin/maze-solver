#ifndef SAMPLER_H
#define SAMPLER_H

#include <iostream>
#include <cstdlib>

class Sampler {

    private:
        int n;
        int *array;

    public:
    Sampler(int n);
    ~Sampler();
    int getSample();

};

#endif
