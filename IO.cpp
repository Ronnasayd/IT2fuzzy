#include "Rules.cpp"

class IT2output {

public:
    std::vector<IT2membership*> memberships;

public:
    double initial_value;

public:
    double final_value;

public:
    IT2output(double init, double fin, IT2membership* m, ...)
    {
        this->initial_value = init;
        this->final_value = fin;
        va_list lt;
        va_start(lt, m);
        IT2membership* aux;
        for (aux = m; aux != NULL; aux = va_arg(lt, IT2membership*)) {
            memberships.push_back(aux);
        }
    }
};

class IT2outputs {

public:
    std::vector<IT2output*> foutputs;

public:
    IT2outputs(IT2output* m, ...)
    {
        va_list lt;
        va_start(lt, m);
        IT2output* aux;
        for (aux = m; aux != NULL; aux = va_arg(lt, IT2output*)) {
            foutputs.push_back(aux);
        }
    }
};

class IT2input {

public:
    std::vector<IT2membership*> memberships;

public:
    double initial_value;

public:
    double final_value;

public:
    IT2input(double init, double fin, IT2membership* m, ...)
    {
        this->initial_value = init;
        this->final_value = fin;
        va_list lt;
        va_start(lt, m);
        IT2membership* aux;
        for (aux = m; aux != NULL; aux = va_arg(lt, IT2membership*)) {
            memberships.push_back(aux);
        }
    }
};

class IT2inputs {

public:
    std::vector<IT2input*> finputs;

public:
    IT2inputs(IT2input* m, ...)
    {
        va_list lt;
        va_start(lt, m);
        IT2input* aux;
        for (aux = m; aux != NULL; aux = va_arg(lt, IT2input*)) {
            finputs.push_back(aux);
        }
    }
};
