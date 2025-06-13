#include "FloatPoint.hpp"
#include "FixedPoint.hpp"
#include <iostream>

int main()
{
    FixedPoint<0, 15> fx1(1.5f);
    FixedPoint<1, 11> fx2(FixedPoint<1, 15> fx1);
    FixedPoint<0, 15> fx3(FixedPoint<0, 15>(1.25f));
    fx3.Print();
    std::cout << std::endl;

}
