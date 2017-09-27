#include "IO.cpp"
#include <iostream>

class IT2fuzzy {
public:
    unsigned int qtdPoints;
    Rules* ptr;
    IT2inputs* inputs;
    IT2outputs* outputs;

public:
    std::vector<double> yl;

public:
    std::vector<double> yr;

public:
    IT2fuzzy(Rules* pt, IT2inputs* inp, IT2outputs* outs, int points)
    {
        this->ptr = pt;
        this->qtdPoints = points;
        this->inputs = inp;
        this->outputs = outs;
    }

public:
    void fuzzyfy(float val, ...)
    {

        std::vector<double> valores;
        va_list lt;
        va_start(lt, val);
        float aux = val;
        valores.push_back(aux);
        for (unsigned int i = 0; i < this->inputs->finputs.size() - 1; i++) {
            aux = va_arg(lt, double);
            valores.push_back(aux);
        }
        va_end(lt);
        for (unsigned int i = 0; i < this->inputs->finputs.size(); i++) {
            for (unsigned int j = 0; j < this->inputs->finputs[i]->memberships.size(); j++) {
                this->inputs->finputs[i]->memberships[j]->setIternalPertinence(valores[i]);
            }
        }
        this->inference();
    }

public:
    void inference()
    {
        float aux_min_lower;
        float aux_min_upper;
        for (unsigned int i = 0; i < this->ptr->rules.size(); i++) {
            for (unsigned int j = 0; j < this->ptr->rules[i]->r_input.size(); j++) {
                aux_min_lower = this->ptr->rules[i]->getMinLowerInput();
                aux_min_upper = this->ptr->rules[i]->getMinUpperInput();

                for (unsigned int k = 0; k < this->ptr->rules[i]->r_output.size(); k++) {

                      this->ptr->rules[i]->r_output[k]->lower->pertTrunc.push_back(aux_min_lower);
                      this->ptr->rules[i]->r_output[k]->upper->pertTrunc.push_back(aux_min_upper);
                }
            }
        }

        for (unsigned int i = 0; i < this->outputs->foutputs.size(); i++) {
            for (unsigned int j = 0; j < this->outputs->foutputs[i]->memberships.size(); j++) {
                this->outputs->foutputs[i]->memberships[j]->lower->pert = this->outputs->foutputs[i]->memberships[j]->lower->getMaxPertTrunc();
                this->outputs->foutputs[i]->memberships[j]->upper->pert = this->outputs->foutputs[i]->memberships[j]->upper->getMaxPertTrunc();

                this->outputs->foutputs[i]->memberships[j]->lower->pertTrunc.clear();
                this->outputs->foutputs[i]->memberships[j]->upper->pertTrunc.clear();

            }
        }
    }

public:
    void typeReduction()
    {
        std::vector<double> points;
        std::vector<double> lower;
        std::vector<double> upper;
        this->yl.clear();
        this->yr.clear();
        double aux_max_lower;
        double aux_max_upper;
        double val_lower;
        double val_upper;
        double num;
        double den;
        double interation;
        double point;
        double ykGeneral;
        unsigned int delimiterGeneral = 0;
        double yk;
        unsigned int delimiter = 0;
        double yl_aux;
        double yr_aux;
        for (unsigned int i = 0; i < this->outputs->foutputs.size(); i++) {
            interation = (this->outputs->foutputs[i]->final_value - this->outputs->foutputs[i]->initial_value) / this->qtdPoints;
            point = this->outputs->foutputs[i]->initial_value;
            num = 0.0;
            den = 1e-323;

            for (unsigned int j = 0; j <= this->qtdPoints; j++) {
                points.push_back(point);
                aux_max_lower = -1.0;
                aux_max_upper = -1.0;
                for (unsigned int k = 0; k < this->outputs->foutputs[i]->memberships.size(); k++) {
                    val_lower = this->outputs->foutputs[i]->memberships[k]->lower->getTruncPertinence(point);
                    val_upper = this->outputs->foutputs[i]->memberships[k]->upper->getTruncPertinence(point);

                    if (val_lower >= aux_max_lower) {
                        aux_max_lower = val_lower;
                    }
                    if (val_upper >= aux_max_upper) {
                        aux_max_upper = val_upper;
                    }
                }

                den = den + (aux_max_lower + aux_max_upper) / 2;
                num = num + point * ((aux_max_lower + aux_max_upper) / 2);
                lower.push_back(aux_max_lower);
                upper.push_back(aux_max_upper);

                point = point + interation;
            }

            ykGeneral = num / den;

            for (unsigned int k = 1; k <= this->qtdPoints; k++) {

                if (points[k] >= ykGeneral) {
                    delimiterGeneral = k-1;
                    break;
                }
            }
            yk = ykGeneral;
            delimiter = delimiterGeneral;
;
            while (true) {
                num = 0;
                den = 1e-323;

                for (unsigned int k = 0; k <= delimiter; k++) {

                    num = num + points[k] * upper[k];
                    den = den + upper[k];
                }
                for (unsigned int k = delimiter + 1; k <= this->qtdPoints; k++) {

                    num = num + points[k] * lower[k];
                    den = den + lower[k];
                }
                yl_aux = num / den;

                if (yl_aux == yk) {
                    this->yl.push_back(yl_aux);
                    break;
                }
                else {
                    yk = yl_aux;
                    for (unsigned int k = 1; k <= this->qtdPoints; k++) {

                        if (points[k] >= yk) {
                            delimiter = k-1;

                            break;
                        }
                    }
                }

            }
            yk = ykGeneral;
            delimiter = delimiterGeneral;

            while (true) {
                num = 0;
                den = 1e-323;

                for (unsigned int k = 0; k <= delimiter; k++) {

                    num = num + points[k] * lower[k];
                    den = den + lower[k];
                }
                for (unsigned int k = delimiter + 1; k <= this->qtdPoints; k++) {

                    num = num + points[k] * upper[k];
                    den = den + upper[k];
                }
                yr_aux = num / den;

                if (yr_aux == yk) {
                    this->yr.push_back(yr_aux);
                    break;
                }
                else {
                    yk = yr_aux;
                    for (unsigned int k = 1; k <= this->qtdPoints; k++) {

                        if (points[k] >= yk) {
                            delimiter = k-1;
                            break;
                        }
                    }
                }
            }


        }
    }

public:
    double defuzzyfy(unsigned int ind)
    {
        this->typeReduction();
        return (this->yl[ind - 1] + this->yr[ind - 1]) / 2;
    }
};
