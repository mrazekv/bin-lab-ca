#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cassert>
#include <cstring>


class CAsim
{
public:

    CAsim(int rows, int cols, int steps_max) : rows_(rows), cols_(cols), steps_max_(steps_max) {
        elements_ = rows * cols;

        states_mem_ = new int[steps_max_ * elements_];
        

        for(int r = 0; r < rows_; r++) {
            for(int c = 0; c < cols_; c++) {
                
            }
        }

    }

    ~CAsim() {
        delete[] states_mem_;
    }

	/** 
	 * nastaveni pocatecniho stavu simulace
	 **/
    void set_init(int * states) {
        memcpy(states_mem_, states, sizeof(int) * elements_);
    }

    /***
     * Vrati 1D pole o delce rows * cols
     **/
    int * get_states(int step) {

        assert(step >= 1 && step < steps_max_);  // nebudeme cist nulty stav

        return states_mem_ + (step * elements_);
    }


	/***
	 * Spusteni simulace na urcity pocet kroku
	 */
    void run_sim(int steps) {
        assert(steps <= steps_max_);

        for(int i = 1; i < steps; i++) {
            int * src = states_mem_ + ((i - 1) * elements_);
            int * dest = states_mem_ + (i * elements_);

			for(int r = 0; r < rows_; r++) {
				for(int c = 0; c < cols_; c++) {
					applyRules(src, dest, r, c);
				}
				
			}

        }
    }

private:
    int rows_, cols_;

    int * states_mem_;
    int states_count_;
    int elements_; // pocet prvku
    int steps_max_;
	
	// RULES
	// Any live cell with fewer than two live neighbours dies, as if caused by under-population.
	// Any live cell with two or three live neighbours lives on to the next generation.
	// Any live cell with more than three live neighbours dies, as if by overcrowding.
	// Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
	void applyRules(int * grid, int * nextGrid, int row, int col) {
		int numNeighbors = countNeighbors(grid, row, col);
		nextGrid[row * cols_ + col] = grid[row * cols_ + col];
		if (grid[row * cols_ + col] == 1) {
			if (numNeighbors < 2) {
				nextGrid[row * cols_ + col] = 0;
			} else if (numNeighbors == 2 || numNeighbors == 3) {
				nextGrid[row * cols_ + col] = 1;
			} else if (numNeighbors > 3) {
				nextGrid[row * cols_ + col] = 0;
			}
		} else if (grid[row * cols_ + col] == 0) {
				if (numNeighbors == 3) {
					nextGrid[row * cols_ + col] = 1;
				}
		}
    }

	int getAddr(int r, int c) {
		return r * cols_ + c;
	}

	/***
	 * modulo vracejici positivni vysledek (-1 % n = n - 1)
	 */
	int posmod(int a, int b) {
		int ret = a % b;
		if(ret < 0) ret += b;
		return ret;
	}

	/**
	 * zjisteni poctu zivych sousedu
	 */
	int countNeighbors(int * grid, int row, int col) {
		int count = 0;
		if (grid[getAddr(posmod(row-1, rows_), col)] == 1) count++;
    	if (grid[getAddr(posmod(row-1, rows_), posmod(col-1, cols_))] == 1) count++;
		if (grid[getAddr(posmod(row-1, rows_), posmod(col+1, cols_))] == 1) count++;
		if (grid[getAddr(row, posmod(col-1, cols_))] == 1) count++;
		if (grid[getAddr(row, posmod(col+1, cols_))] == 1) count++;
		if (grid[getAddr(posmod(row+1, rows_), col)] == 1) count++;
		if (grid[getAddr(posmod(row+1, rows_), posmod(col-1, cols_))] == 1) count++;
		if (grid[getAddr(posmod(row+1, rows_), posmod(col+1, cols_))] == 1) count++;
		return count;
	}

};