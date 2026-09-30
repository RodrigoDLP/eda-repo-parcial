#include <bits/stdc++.h>
using namespace std;

void generate(vector<string>& output, string& current, int n, int diff, const int& maxeach) {
    if (n == 0) {
        if (diff == 0) output.push_back(current);
        return;
    }
    if (diff > 0) {
        current += ")";
        generate(output, current, n-1, diff-1, maxeach);
        current = current.substr(0, current.size()-1);
    }
    if (diff <= n) {
        current += "(";
        generate(output, current, n-1, diff+1, maxeach);
        current = current.substr(0, current.size()-1);
    }
}

vector<string> generateParenthesis(int n) {
vector<string> output;
        string current = "";
        generate(output, current, n*2, 0, n);
        return output;
    }


void procesar(Estado actual) {

}


bool esSolucionCompleta(Estado actual) {

}

vector<Opcion> opcionesPosibles(Estado actual) {

}

bool esValida(Estado actual, Operacion op) {

}

void aplicar(Estado actual, Operacion op) {

}

void deshacer(Estado actual, Operacion op) {

}


void backtrack(Estado actual) {
    if (esSolucionCompleta(actual)) {
        procesar(actual);
        return;
    }
    for (Opcion op : opcionesPosibles(actual)) {
        if (!esValida(actual, op)) continue;
        aplicar(actual, op);
        backtrack(actual);
        deshacer(actual, op);
    }
}

