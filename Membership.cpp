
#include <vector>
#define INPUT 1
#define OUTPUT 2

class membership {
public:
    double x1, x2, x3, x4, y1, y2, y3, y4;

public:
    double pert;
    std::vector<double> pertTrunc;

public:
    membership(double vx1, double vx2, double vx3, double vx4, double vy1, double vy2, double vy3, double vy4)
    {
        this->x1 = vx1;
        this->x2 = vx2;
        this->x3 = vx3;
        this->x4 = vx4;
        this->y1 = vy1;
        this->y2 = vy2;
        this->y3 = vy3;
        this->y4 = vy4;
        this->pert = -1.0;
    }

public:
    double getPertinence(double x)
    {
        double alpha;
        if (x < this->x1) {
            return this->y1;
        }
        else {
            if (x >= this->x4) {
                return this->y4;
            }
            else {
                if (x >= this->x1 && x < this->x2) {
                    alpha = (this->y2 - this->y1) / (this->x2 - this->x1);
                    return alpha * (x - this->x1) + this->y1;
                }
                else {
                    if (x >= this->x2 && x < this->x3) {
                        alpha = (this->y3 - this->y2) / (this->x3 - this->x2);
                        return alpha * (x - this->x2) + this->y2;
                    }
                    else {
                        if (x >= this->x3 && x < this->x4) {
                            alpha = (this->y4 - this->y3) / (this->x4 - this->x3);
                            return alpha * (x - this->x3) + this->y3;
                        }
                    }
                }
            }
        }

        return 0;
    }

public:
    double getTruncPertinence(double x)
    {
        double alpha;
        double val = 0.0;
        if (x < this->x1) {
            val = this->y1;
        }
        else {
            if (x >= this->x4) {
                val = this->y4;
            }
            else {
                if (x >= this->x1 && x < this->x2) {
                    alpha = (this->y2 - this->y1) / (this->x2 - this->x1);
                    val = alpha * (x - this->x1) + this->y1;
                }
                else {
                    if (x >= this->x2 && x < this->x3) {
                        alpha = (this->y3 - this->y2) / (this->x3 - this->x2);
                        val = alpha * (x - this->x2) + this->y2;
                    }
                    else {
                        if (x >= this->x3 && x < this->x4) {
                            alpha = (this->y4 - this->y3) / (this->x4 - this->x3);
                            val = alpha * (x - this->x3) + this->y3;
                        }
                    }
                }
            }
        }

        if (val < this->pert) {
            return val;
        }
        else {
            return this->pert;
        }
    }

public:
    void setInternalPertinence(double x)
    {
        this->pert = this->getPertinence(x);
    }

public:
    double getMaxPertTrunc()
    {
        double val = 0.0;
        for (unsigned int i = 0; i < this->pertTrunc.size(); i++) {
            if (val <= this->pertTrunc[i]) {
                val = pertTrunc[i];
            }
        }
        return val;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////

class IT2membership {
public:
    membership* lower;

public:
    membership* upper;

public:
    int IO;

public:
    IT2membership(membership* low, membership* upp, int io)
    {
        this->lower = low;
        this->upper = upp;
        this->IO = io;
    }

public:
    void setIternalPertinence(double x)
    {
        this->lower->setInternalPertinence(x);
        this->upper->setInternalPertinence(x);
    }
};
