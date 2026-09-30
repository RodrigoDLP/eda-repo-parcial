#include <bits/stdc++.h>
using namespace std;











class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> output;
        vector<short> tested; tested.reserve(n*2);
        for (int i=0; i<n*2; ++i) tested.push_back(-1);
        string current = "";
        int diff = 0;
        int level = 1;
        while (level > 0) {
            tested[level-1]++;
            if (tested[level-1] == 0) {current += "("; diff++;}
            else if (tested[level-1] == 1) {current[current.size()-1] = ')'; diff -= 2;}
            if (level == n*2 && diff == 0) output.push_back(current);
            if (level < n*2 && diff >= 0 && diff <= n) ++level;
            else {
                if (tested.size() < level) throw runtime_error("??????");
                while (level > 0 && tested[level-1] == 1) {
                    if (current[current.size()-1] == '(') --diff;
                    else ++diff;
                    tested[level-1] = -1;
                    current = current.substr(0, current.size()-1);
                    --level;
                    if (tested.size() < level) throw runtime_error("???");
                }
            }

        }
        return output;
    }
};


auto backtrack() {
    OutputContainer<string> output;
    vector<short> tested; tested.reserve(INPUT_NUMBER);
    for (int i=0; i<INPUT_NUMBER; ++i) tested.push_back(-1);
    string current;

    int level = 1;
    while (level > 0) {
        tested[level-1]++;

        if (tested[level-1] == 0) {current += "("; diff++;}
        else if (tested[level-1] == 1) {current[current.size()-1] = ')'; diff -= 2;}
        //there has to be a for with the action of each element. ex: tested = -1 means no tests (constant, could be input).
        //tested = 1 currently testing number 1, from numbers 1 to 9
        //there has to be an action, a condition to verify if valid, to verify if solution
        //and an undo action, all as inputs, most likely lambdas




        if (level == INPUT_NUMBER && diff == 0) output.push_back(current);
        if (level < INPUT_NUMBER && diff >= 0 && diff <= n) ++level;
        else {
            while (level > 0 && tested[level-1] == 1) {
                if (current[current.size()-1] == '(') --diff;
                else ++diff;
                tested[level-1] = -1;
                current = current.substr(0, current.size()-1);
                --level;
            }
        }

    }
    return output;

}