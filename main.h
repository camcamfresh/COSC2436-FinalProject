/* Assignment: Final Project
 * Date: 7/26/2019
 * Description: This program implements a graph using a 2D int array. The program handles
 * 		weighted undirected and unweighted directed graphs the same. Disconneced edges must
 * 		be set to -1, unweighted edges to 0 and weighted edges to their respective integer
 * 		value. The manipulation methods allow graphs to be changed (e.g., weighted undirected
 * 		graph to weighted directed graph, etc.). Read graph.h for more details.
*/
#ifndef FPROJECT_MAIN_H
#define FPROJECT_MAIN_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <time.h>
#include "graph.h"

//tests graph class
int main(int, char**);

//returns a random number between min and max inclusive
int random_range(int min, int max);

#endif