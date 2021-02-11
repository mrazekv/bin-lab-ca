/***
 * Geneticky algoritmus hledajici 
 *
 *
 ***/


#include <iostream>
#include <tuple>
#include "ca_sim.hpp"

using namespace std;

const int rows = 8, cols = 8;

// ocekavany vstup
const int expected[rows * cols] = {
   0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 1, 0, 0, 0, 
   0, 0, 0, 0, 0, 1, 0, 0, 
   0, 0, 0, 1, 1, 1, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0
};


void print_configuration(ostream & out, int * dataset) {
	
	int * ds = dataset;
    out << rows << " " << cols << endl;

    for(int r = 0; r < rows; r++) {
        for(int c = 0; c < cols; c++) {
            out << *(dataset++) << " "; 
        }
        out << endl;
    }
	
	// JSON format too
	dataset = ds;
	
	out << "JSON data: " << endl << "{";
    for(int r = 0; r < rows; r++) {
		if(r) out << ",";
		out << "\"" << r << "\":[";
		
		int wasout = 0;
        for(int c = 0; c < cols; c++) {
            if(*(dataset++)) {
				if(wasout) out << ",";
				out << c;
				wasout = 1;
			}
        }
		out << "]";
	
	}
		
	out << "}" << endl << endl;;
	
}

/** 
 * Vypocet fitness pro kandidatni reseni
 * sim - simulator (nutne nastavit a spustit)
 * candidate - 1D pole kandidatniho reseni
 * steps - pocet kroku, po ktery se bude provadet simulace
 * vraci dvojici integeru fitness a best_step
 *    fitness je v rozsahu 0 az rows * cols, kdy rows * cols je nejlepsi (funkcni reseni)
 *    best_step je cislo kroku, kdy se dosahlo nejvyssi hodnoty fitness, je 0 az steps
 */
std::tuple<int, int> calculate_fitness(CAsim & sim, int * candidate, int steps) {
    // TODO vas ukol!

    // nastavit candidate jako pocatecni stav v simulatori (fce sim.set_init)

    // spustit simulator (fce sim.run_sim)


    int fitness = 0;
    int best_step = 0;  // v kterem kroku simulace byla nejlepsi fintess nalezena


    // projit vsechny korky, pomoci funkce sim.get_state ziskat stav

	// navrat dvou hodnot 
	return std::make_tuple(fitness, best_step);
}


int main(int argc, char ** argv) {
    const int generation = 100000;
    const int steps = 20;
    const int lambda = 5;
	const int mutations = 5;


	srand(time(NULL));

    // geneticky algoritmus mu+lambda: vezme se mi nejlepsi, 
    // z toho se vygeneruje dalsich lambda konfiguraci. Vybere 
    // se zase mu nejlepsich

    int parent[rows * cols];
    int offsprings[lambda][rows * cols];

    int parent_fit;
    int offsprings_fits[lambda];

    // vytvoreni nahodnych populaci
	for(int j = 0; j < rows*cols; j++)
		parent[j] = rand() % 2;
	
	
	
	// novy simulator 4x4
	CAsim sim(rows, cols, steps);
	
	int br; // integer pro ukladani kroku, kdy se naslo nejlepsi reseni; casto jej nepotrebujeme
	std::tie(parent_fit, br) = calculate_fitness(sim, parent, steps);
	
	cout << "Initial:  fitness " << parent_fit << endl;
	
	int gen = 0;
	for(gen = 0; gen < generation; gen ++) 
	{
		if( parent_fit == rows * cols) {
			cout << "solution found!" << endl;
			break;
		}
		
		int next_parent = -1;

		for(int l = 0; l < lambda; l++) {
			// kopie rodice
			memcpy(offsprings[l], parent, sizeof(int) * rows * cols);

			// provedeni mutaci
			for(int m = 0; m < mutations; m++) {
				offsprings[l][rand() % ( rows * cols )] ^= 0x01; // nahodne zmutujeme nektera cisla
			}

			std::tie(offsprings_fits[l], br) = calculate_fitness(sim, offsprings[l], steps); // provedeni simulace
			

			if(offsprings_fits[l] >= parent_fit && (next_parent < 0 || offsprings_fits[l] > offsprings_fits[next_parent]) ) { 
				// lepsi nebo stejna fitness jako rodic a nez nejlepsi z generace
				next_parent = l;
			}
		}
		
		
		// kopirovani nejlepsiho
		if(next_parent >= 0)  {
				assert((offsprings_fits[next_parent] >=  parent_fit)); // musi dojit ke zlepseni fitness nebo aspon stejna (neutralni mutace)
				if(offsprings_fits[next_parent] >  parent_fit) // doslo
					cout << "Gen # " << gen << " fitness " << offsprings_fits[next_parent] << endl;

				memcpy(parent, offsprings[next_parent], sizeof(int) * rows * cols);
				#if 1
					// vyuzijeme fitness, kterou mame vypocitanou
					parent_fit = offsprings_fits[next_parent];
				#else
					// pro jistotu znovu vypocitame fitness (pouzivano pro ladeni)
					std::tie(parent_fit, br) = calculate_fitness(sim, parent, steps);
					assert(parent_fit == offsprings_fits[next_parent]);
				#endif
		}	
	}
	
	cout << "Search ended" << endl;
	cout << "Best fitness " << parent_fit << " in " << gen << " generations " << endl;
	

	print_configuration(cout, parent);
	int bf;
	std::tie(bf, br) = calculate_fitness(sim, parent, steps);
	cout << "Best fitness " << bf << "/" << (rows * cols) << " in step " << br << endl;
}

