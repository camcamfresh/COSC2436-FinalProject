#include "main.h"

int main(int argc, char** argv) {

}

int random_range(int min, int max) {
    return (rand() % (max - min + 1)) +min;
}