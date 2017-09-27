#include <iostream>
#include "IT2fuzzy.cpp"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main()
{

    membership upperBI = membership(0, 0, 2, 4, 1, 1, 1, 0);
    membership lowerBI = membership(0, 0, 0, 2, 1, 1, 1, 0);
    IT2membership BaixaI = IT2membership(&lowerBI, &upperBI, INPUT);

    membership upperAI = membership(1, 3, 5, 5, 0, 1, 1, 1);
    membership lowerAI = membership(3, 5, 5, 5, 0, 1, 1, 1);
    IT2membership AltaI = IT2membership(&lowerAI, &upperAI, INPUT);

    membership upperBO = membership(0, 0, 2, 4, 1, 1, 1, 0);
    membership lowerBO = membership(0, 0, 0, 2, 1, 1, 1, 0);
    IT2membership BaixaO = IT2membership(&lowerBO, &upperBO, OUTPUT);

    membership upperAO = membership(1, 3, 5, 5, 0, 1, 1, 1);
    membership lowerAO = membership(3, 5, 5, 5, 0, 1, 1, 1);
    IT2membership AltaO = IT2membership(&lowerAO, &upperAO, OUTPUT);

    IT2output output = IT2output(0.0, 5.0, &BaixaO, &AltaO, NULL);
    IT2outputs outputs = IT2outputs(&output, NULL);

    IT2input finput = IT2input(0.0, 5.0, &BaixaI, &AltaI, NULL);
    IT2inputs inputs = IT2inputs(&finput, NULL);

    Rule r1 = Rule(&BaixaI, &AltaO, NULL);
    Rule r2 = Rule(&AltaI, &BaixaO, NULL);

    Rules rules = Rules(&r1, &r2, NULL);

    IT2fuzzy fuzzy = IT2fuzzy(&rules, &inputs, &outputs, 123);

    for (double val = 0.0; val < 6.0; val = val + 1.0) {
        fuzzy.fuzzyfy(val);
        double y = fuzzy.defuzzyfy(1);
        std::cout << fuzzy.yl[0] << " " << fuzzy.yr[0] << " " << y << std::endl;
    }

    return 0;
}
