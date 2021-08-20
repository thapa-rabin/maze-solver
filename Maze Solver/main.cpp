// Rabin Thapa

#include<iostream>
#include<cstdlib>
#include<ctime>
#include "pathfinder.h"
#include"disjointset.h"
#include"sampler.h"
#include"stack.h"

using namespace std;

int nR, nC;
unsigned char maze[MAX_ROWS][MAX_COLS];
void GenerateMaze(int nR, int nC);
void FindPath(unsigned char maze[][50]);

int main(int argc, char *argv[]) {
	srand(time(NULL));

	 if (!(argc == 3)) {
        cout << "Enter two parameters!\n";
        return 1;
    }
    nR = atoi(argv[1]);
    nC = atoi(argv[2]);

    GenerateMaze(nR,nC);
    FindPath(maze);
    printMaze(maze,nR,nC);
    return 0;
}


void GenerateMaze(int nR, int nC) {
	 int i, r, c, d, e;
	 for (r = 0; r < nR; r++) {
		for (c = 0; c < nC; c++) {
        	maze[r][c] = 15;
       }
    }
	DisjointSet ds(nR*nC);
	Sampler sample(4*(nR*nC));
	i = 0;
	while(i < (nR*nC - 1)) {
		e = sample.getSample();
		//Decode
		d = e % 4; 
		e = e / 4;
		c = e % nC;
		r = e / nC;

		//looking up
		if(d == 0) {
			if(r == 0)
				continue;
			if((maze[r][c] & WALL_UP) == 0)
				continue;
			if(ds.find(r * nC + c) ==  ds.find((r-1) * nC + c))
				continue;
			maze[r][c] &= ~WALL_UP;
			maze[r-1][c] &= ~WALL_DOWN;
			ds.join(r * nC + c,(r-1) * nC + c);
			i++;
		}
		//looking right
		else if(d == 1) {
			if(c == nC - 1)
				continue;
            if ((maze[r][c] & WALL_RIGHT) == 0)
                continue;
             if (ds.find(r * nC + c) == ds.find(r * nC + (c + 1))) //Find Loop
             	continue;
            maze[r][c] &= ~WALL_RIGHT;
            maze[r][c+1] &= ~WALL_LEFT;
            ds.join(r * nC + c,r * nC + (c + 1));
            i++;
		}
		//looking down
		else if(d == 2) {

			if(r == nR - 1)
				continue;
			 if ((maze[r][c] & WALL_DOWN) == 0)
                continue;
            if (ds.find(r * nC + c) == ds.find((r + 1) * nC + c)) 
                continue; 
            maze[r][c] &= ~WALL_DOWN;
            maze[r + 1][c] &= ~WALL_UP;
            ds.join(r * nC + c,(r + 1) * nC + c);
            i++;
		}
		else {
				if (c == 0)
		            continue;
		        if ((maze[r][c] & WALL_LEFT) == 0)
		            continue;
		        if (ds.find(r * nC + c) == ds.find(r * nC + (c - 1))) 
		            continue; 
		        maze[r][c] &= ~WALL_LEFT;
		        maze[r][c -1] &= ~WALL_RIGHT;

		        ds.join(r * nC + c,r * nC + (c - 1));
		        i++;
		}
	}
}

void FindPath(unsigned char maze[][50]) {
	Stack<int> S;
    int temp;
    int R, C;
    S.push(0);
    maze[0][0] |= VISITED;

    while (true) {
        int e = S.peek();
        int c = e % nC;
        e /= nC;
        int r = e % nR;
        int d = e / nR;

        if ((r == nR - 1) && (c == nC - 1)) {
            break;
        }

        if (d == 4) {
            maze[r][c] |= DEAD_END;
            S.pop();
        }
        else if (d == 0) {
            R = r - 1;
            C = c;
            temp = S.peek();
            S.pop();
            temp += nR * nC;
            S.push(temp);
            if ((maze[r][c] & WALL_UP) == 0 && (maze[R][C] & VISITED) == 0) {
                S.push(C + nC * R);
                maze[R][C]  |= VISITED;
            }
        }
        else if (d == 1) {
            R = r;
            C = c + 1;
            temp = S.peek();
            S.pop();
            temp += nR * nC;
            S.push(temp);
            if ((maze[r][c] & WALL_RIGHT) == 0 && (maze[R][C] & VISITED) == 0) {
                S.push(C + nC * R);
                maze[R][C] |= VISITED;
            }
        }
        else if (d == 2) {
            R = r + 1;
            C = c;
            temp = S.peek();
            S.pop();
            temp+= nR* nC;
            S.push(temp);
            if( (maze[r][c] & WALL_DOWN) == 0 && (maze[R][C] & VISITED) == 0) {
                S.push(C + nC * R);
                maze[R][C] |= VISITED;
            }
        }
        else {
            R = r;
            C = c-1;
            temp = S.peek();
            S.pop();
            temp+= nR * nC;
            S.push(temp);
            if ((maze[r][c] & WALL_LEFT) == 0 && (maze[R][C] & VISITED) == 0) {
                S.push(C + nC *R);
                maze[R][C] |= VISITED;
            }
        }
    }

}
