
#include<vector>
#define INPUT 1
#define OUTPUT 2


class membership{
public:double x1,x2,x3,x4,y1,y2,y3,y4;
public:double pert;
std::vector <double> pertTrunc;

public:membership(double x1,double x2, double x3, double x4, double y1, double y2, double y3, double y4){
    this->x1 = x1;
    this->x2 = x2;
    this->x3 = x3;
    this->x4 = x4;
    this->y1 = y1;
    this->y2 = y2;
    this->y3 = y3;
    this->y4 = y4;
 ;
}

public:double getPertinence(double x){
double alpha;
if(x < this->x1){
    return this->x1;
}
else{
    if(x >= this->x4){
        return this->x4;
    }
    else{
        if(x>=this->x1 && x<this->x2){
            alpha = (this->y2 - this->y1)/(this->x2 - this->x1);
            return alpha*(x - this->x1) + this->y1;
        }
        else{
            if(x>=this->x2 && x<this->x3){
                alpha = (this->y3 - this->y2)/(this->x3 - this->x2);
                return alpha*(x - this->x2) + this->y2;
            }
            else{
                if(x>=this->x3 && x<this->x4){
                    alpha = (this->y4 - this->y3)/(this->x4 - this->x3);
                    return alpha*(x - this->x3) + this->y3;
                }
            }
        }
    }
}

return 0;
}

public:void setInternalPertinence(double x){
this->pert = this->getPertinence(x);
}

};

//////////////////////////////////////////////////////////////////////////////////////////////////

class I2membership{
    public:membership *lower;
    public:membership *upper;
    public:int Id;
    public:int IO;

public:I2membership(membership *low, membership *upp, int io, int id){
    this->lower = low;
    this->upper = upp;
    this->Id = id;
    this->IO = io;
}
public:void setIternalPertinence(double x){
    this->lower->setInternalPertinence(x);
    this->upper->setInternalPertinence(x);
}
};
