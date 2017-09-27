#include "Membership.cpp"
#include <stdarg.h>
#include <stdio.h>

class Rule {

public:
    std::vector<IT2membership*> r_input;

public:
    std::vector<IT2membership*> r_output;

public:
    Rule(IT2membership* ptr, ...)
    {
        va_list lt;
        va_start(lt, ptr);
        IT2membership* aux;
        for (aux = ptr; aux != NULL; aux = va_arg(lt, IT2membership*)) {
            if (aux->IO == INPUT) {
                r_input.push_back(aux);
            }
            if (aux->IO == OUTPUT) {
                r_output.push_back(aux);
            }
        }
        va_end(lt);
    }

public:
    double getMinLowerInput()
    {
        double val = 1.0;
        for (unsigned int i = 0; i < this->r_input.size(); i++) {
            if (val >= this->r_input[i]->lower->pert) {
                val = this->r_input[i]->lower->pert;
            }
        }
        return val;
    }

public:
    double getMinUpperInput()
    {
        double val = 1.0;
        for (unsigned int i = 0; i < this->r_input.size(); i++) {
            if (val >= this->r_input[i]->upper->pert) {
                val = this->r_input[i]->upper->pert;
            }
        }
        return val;
    }
};

class Rules {
public:
    std::vector<Rule*> rules;

public:
    Rules(Rule* ptr, ...)
    {
        va_list lt;
        va_start(lt, ptr);
        Rule* aux;
        for (aux = ptr; aux != NULL; aux = va_arg(lt, Rule*)) {
            rules.push_back(aux);
        }
    }
};
