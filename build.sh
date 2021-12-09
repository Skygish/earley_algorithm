#!/bin/bash
g++ -std=c++17 -c Algo.cpp -o Algo.o
g++ -std=c++17 -c main.cpp -o main.o
g++ main.o Algo.o -o main
./main