#include"circuit_func.h"

bool* create_in_bool_vect(int size);
void reset_bit_array(bool* array, int size);
void depthFirstSearch(circuit* myCircuit, int index);
void propagate_in(circuit* myCircuit);
void propagate_fanout(circuit* muCircuit);

