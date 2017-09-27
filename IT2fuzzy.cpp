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
        float aux_max_lower;
        float aux_max_upper;
        for (unsigned int i = 0; i < this->ptr->rules.size(); i++) {
            aux_max_lower = 0.0;
            aux_max_upper = 0.0;
            for (unsigned int j = 0; j < this->ptr->rules[i]->r_input.size(); j++) {
                if (this->ptr->rules[i]->r_input[j]->lower->pert > aux_max_lower) {
                    aux_max_lower = this->ptr->rules[i]->r_input[j]->lower->pert;
                }
                if (this->ptr->rules[i]->r_input[j]->upper->pert > aux_max_upper) {
                    aux_max_upper = this->ptr->rules[i]->r_input[j]->upper->pert;
                }
            }
            for (unsigned int k = 0; k < this->ptr->rules[i]->r_output.size(); k++) {
                this->ptr->rules[i]->r_output[k]->lower->pertTrunc.push_back(aux_max_lower);
                this->ptr->rules[i]->r_output[k]->upper->pertTrunc.push_back(aux_max_upper);
            }
        }
        float aux_min_lower;
        float aux_min_upper;
        for (unsigned int i = 0; i < this->outputs->foutputs.size(); i++) {
            for (unsigned int j = 0; j < this->outputs->foutputs[i]->memberships.size(); j++) {
                aux_min_lower = 1.0;
                aux_min_upper = 1.0;
                for (unsigned int k = 0; k < this->outputs->foutputs[i]->memberships[j]->lower->pertTrunc.size(); k++) {
                    if (this->outputs->foutputs[i]->memberships[j]->lower->pertTrunc[k] < aux_min_lower) {
                        aux_min_lower = this->outputs->foutputs[i]->memberships[j]->lower->pertTrunc[k];
                    }
                }
                this->outputs->foutputs[i]->memberships[j]->lower->pert = aux_min_lower;
                this->outputs->foutputs[i]->memberships[j]->lower->pertTrunc.clear();
                for (unsigned int k = 0; k < this->outputs->foutputs[i]->memberships[j]->upper->pertTrunc.size(); k++) {
                    if (this->outputs->foutputs[i]->memberships[j]->upper->pertTrunc[k] < aux_min_upper) {
                        aux_min_upper = this->outputs->foutputs[i]->memberships[j]->upper->pertTrunc[k];
                    }
                }
                this->outputs->foutputs[i]->memberships[j]->upper->pert = aux_min_upper;
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
            //std::cout<<interation<<std::endl;
            //std::cout<<point<<std::endl;
            //std::cout<<num<<std::endl;
            //std::cout<<den<<std::endl;
            for (unsigned int j = 0; j <= this->qtdPoints; j++) {
                points.push_back(point);
                aux_max_lower = -1.0;
                aux_max_upper = -1.0;
                for (unsigned int k = 0; k < this->outputs->foutputs[i]->memberships.size(); k++) {
                    val_lower = this->outputs->foutputs[i]->memberships[k]->lower->getTruncPertinence(point);
                    val_upper = this->outputs->foutputs[i]->memberships[k]->upper->getTruncPertinence(point);
                    //std::cout<<k<<"/"<<val_lower<<"/"<<val_upper<<std::endl;
                    if (val_lower >= aux_max_lower) {
                        aux_max_lower = val_lower;
                    }
                    if (val_upper >= aux_max_upper) {
                        aux_max_upper = val_upper;
                    }
                }
                //std::cout<<point<<" "<<aux_max_lower<<" "<<aux_max_upper<<std::endl;
                den = den + (aux_max_lower + aux_max_upper) / 2;
                num = num + point * ((aux_max_lower + aux_max_upper) / 2);
                lower.push_back(aux_max_lower);
                upper.push_back(aux_max_upper);
                //std::cout<<point<<"/"<<num<<"/"<<den<<std::endl;
                point = point + interation;
            }
            //for(unsigned int x = 0; x < upper.size(); x++)
            //std::cout<<x<<"/"<<upper[x]<<std::endl;
            ykGeneral = num / den;
            //std::cout<<ykGeneral<<"/"<<num<<"/"<<den<<std::endl;
            //std::cout<<points.size()<<std::endl;
            //std::cout<<lower.size()<<std::endl;
            //std::cout<<upper.size()<<std::endl;
            //std::cout<<points[1000]<<std::endl;
            //std::cout<<lower[1000]<<std::endl;
            //std::cout<<upper[1000]<<std::endl;
            for (unsigned int k = 0; k <= this->qtdPoints; k++) {
                //std::cout<<k<<"/"<<points[k]<<"/"<<ykGeneral<<std::endl;
                if (points[k] >= ykGeneral) {
                    delimiterGeneral = k-1;
                    break;
                }
            }
            yk = ykGeneral;
            delimiter = delimiterGeneral;
            ///// ATE ESTA PARTE EU SEI QUE ESTA CERTO!!!!!!

            //std::cout<<yk<<"/"<<delimiter<<std::endl;
            while (true) {
                num = 0;
                den = 1e-323;
                //std::cout<<delimiterGeneral<<"/"<<delimiter<<std::endl;
                //std::cout<<0<<"-"<<delimiter<<"/"<<delimiter+1<<" "<<this->qtdPoints<<std::endl;
                for (unsigned int k = 0; k <= delimiter; k++) {
                    //std::cout<<k<<"/"<<points[k]<<"/"<<upper[k]<<"/"<<delimiter<<"/"<<delimiterGeneral<<std::endl;
                    num = num + points[k] * lower[k];
                    den = den + lower[k];
                }
                for (unsigned int k = delimiter + 1; k <= this->qtdPoints; k++) {
                    //std::cout<<k<<"/"<<points[k]<<"/"<<lower[k]<<"/"<<delimiter<<"/"<<delimiterGeneral<<std::endl;
                    num = num + points[k] * upper[k];
                    den = den + upper[k];
                }
                yl_aux = num / den;
                //std::cout<<yl_aux<<" "<<yk<<" "<<delimiter<<std::endl;
                if (yl_aux == yk) {
                    this->yl.push_back(yl_aux);
                    break;
                }
                else {
                    yk = yl_aux;
                    for (unsigned int k = 0; k <= this->qtdPoints; k++) {
                        //std::cout<<k<<std::endl;
                        if (points[k] >= yk) {
                            delimiter = k;
                            break;
                        }
                    }
                }
            }
            yk = ykGeneral;
            delimiter = delimiterGeneral;
            //std::cout<<yk<<"/"<<delimiter<<std::endl;
            while (true) {
                num = 0;
                den = 1e-323;
                //std::cout<<delimiterGeneral<<"/"<<delimiter<<std::endl;
                for (unsigned int k = 0; k <= delimiter; k++) {
                    //std::cout<<k<<"/"<<points[k]<<"/"<<upper[k]<<"/"<<delimiter<<"/"<<delimiterGeneral<<std::endl;
                    num = num + points[k] * upper[k];
                    den = den + upper[k];
                }
                for (unsigned int k = delimiter + 1; k <= this->qtdPoints; k++) {
                    //std::cout<<k<<"/"<<points[k]<<"/"<<lower[k]<<"/"<<delimiter<<"/"<<delimiterGeneral<<std::endl;
                    num = num + points[k] * lower[k];
                    den = den + lower[k];
                }
                yr_aux = num / den;
                //std::cout<<yr_aux<<" "<<yk<<" "<<delimiter<<std::endl;
                if (yr_aux == yk) {
                    this->yr.push_back(yr_aux);
                    break;
                }
                else {
                    yk = yr_aux;
                    for (unsigned int k = 0; k <= this->qtdPoints; k++) {
                       //std::cout<<k<<std::endl;
                        if (points[k] >= yk) {
                            delimiter = k-1;
                            break;
                        }
                    }
                }
            }


        }
        //points.clear();
        //upper.clear();
        //lower.clear();
    }

public:
    double defuzzyfy(unsigned int ind)
    {
        this->typeReduction();
        return (this->yl[ind - 1] + this->yr[ind - 1]) / 2;
    }
};
