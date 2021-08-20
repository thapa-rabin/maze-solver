#ifndef DISJOINTSET_H
#define DISOINTSET_H

class DisjointSet {
    private:
        int *elements, *rank;

    public:
        DisjointSet(int n);
        ~DisjointSet();
        int find(int a);
        void join(int a, int b);
};

#endif
