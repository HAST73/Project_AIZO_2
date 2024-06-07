#include "../Headers/IncidentMatrix.h"
#include <iomanip>
#include <iostream>

IncidentMatrix::IncidentMatrix(int vertices, int edges, bool isDirected)
        : n(vertices), m(edges), directed(isDirected), incidenceMatrix(vertices, std::vector<signed char>(edges, 0)) {}

void IncidentMatrix::addEdge(int v1, int v2, int edgeIndex) {
    incidenceMatrix[v1][edgeIndex] = 1;
    incidenceMatrix[v2][edgeIndex] = directed ? -1 : 1;
}

void IncidentMatrix::printMatrix() {
    std::cout << "   ";
    for (int i = 0; i < m; i++) std::cout << std::setw(3) << i;
    std::cout << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << std::setw(3) << i;
        for (int j = 0; j < m; j++) std::cout << std::setw(3) << (int) incidenceMatrix[i][j];
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int IncidentMatrix::vertexDegree(int vertexIndex) {
    int degree = 0;
    for (int j = 0; j < m; j++) {
        if (incidenceMatrix[vertexIndex][j] != 0) {
            if (!directed || incidenceMatrix[vertexIndex][j] == 1) // jeśli graf nieskierowany lub krawędź wychodzi z wierzchołka
                degree++;
        }
    }
    return degree;
}

std::vector<int> IncidentMatrix::neighbors(int vertexIndex) {
    std::vector<int> neighborsList;
    for (int j = 0; j < m; j++) {
        if (incidenceMatrix[vertexIndex][j] != 0) {
            for (int i = 0; i < n; i++) {
                if (i != vertexIndex && incidenceMatrix[i][j] != 0) { // pomiń wierzchołek sam do siebie oraz przeciwne krawędzie
                    neighborsList.push_back(i);
                    break; // znajdujemy tylko jednego sąsiada wzdłuż danej krawędzi
                }
            }
        }
    }
    return neighborsList;
}

bool IncidentMatrix::isIsolated(int vertexIndex) {
    for (int j = 0; j < m; j++) {
        if (incidenceMatrix[vertexIndex][j] != 0) return false; // jeśli istnieje krawędź z lub do tego wierzchołka
    }
    return true; // jeśli nie istnieje żadna krawędź z lub do tego wierzchołka
}