#include"sampler.h"
#include <iostream>
#include <cstdlib>


Sampler::Sampler(int n) {
	array = new int[n];
	for (int i=0; i<=n; i++) {
		array[i] = i;
	}
	this->n = n;
}

Sampler::~Sampler() {
        delete[] array;
}

int Sampler::getSample() {
	int sample;
	int i = rand() % n;
	sample = array[i];
	n--;
	array[i] = array[n];
        
	return sample;
}

