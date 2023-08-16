#include <iostream>
#include <stdlib.h>
#include <memory.h>
#include <bitset>
#define ARITHMETIC_ERROR_SQRT_LESS_THAN_ZERO -0xBEEF

typedef long long dlong;

dlong closest_psqrt(dlong x){
    dlong l = 1, r = x;
    dlong cpsqrt = 1;
    
    while(l <= r){
        dlong m = (l + r) / 2;
        dlong s = m * m;
        
        if(s == x){
            return m;
        } else if(s < x){
            cpsqrt = m;
            l = m+1;
        } else {
            cpsqrt = m;
            r = m-1;
        }
    }   
    return cpsqrt;
}

double c_sqrt(double x){
    if(x < 0)
        return ARITHMETIC_ERROR_SQRT_LESS_THAN_ZERO;
    if(x == 0)
        return 0;

    //find max g, max precision / scaling
    // multiply x by 2 ^ g  
    unsigned int g = 0;
    while((x*2) < 0x7FFFFFFFULL){
        g++;
        x*=2;
    } 
    // if g is odd divide by 0, we want the scale exponent to be even
    if(g & 1){
        g--;
        x/=2;
    }

    dlong cpsqrt = closest_psqrt((dlong)x);
    dlong cps = cpsqrt * cpsqrt;

    double raw_res = cpsqrt + ((x - cps) / cpsqrt) / 2;
    double res = raw_res / (1 << (g >> 1));

    // return raw_res; 
    return res; 
}

int main(int argc, char const *argv[]) {

    double val;
    // unsigned int granularity;

    std::cout << "enter value to sqrt: \n";
    std::cin >> val;
    
    if(val > (1LL << 31)-1){
        std::cout << "value too large\n";
        return 0;
    }

    double res = c_sqrt(val);
    std::cout << "sqrt of " << val << " is: " << res << "\n";
    std::cout << "res squared is: " << (res*res) << "\n";

    return 0;
}

/**
    std::cout << "new x: " << x << std::endl;
    std::cout << "cpsqrt: " << cpsqrt << std::endl;
    std::cout << "raw_res: " << raw_res << std::endl;

    std::cout << "g is: " << g << "\n";
    
    std::cout << "new x: " << x << std::endl;

    std::cout << "\tnx: " << x << std::endl;

    std::cout << "val bitset: " << std::bitset<64>(val) << "\n";
    
    // dlong xr = *((dlong*)&x);
    // std::cout << "transformed: " << xr << "\n";
    // int shift = 61;
    // while(shift >= 51 && !((1L << (shift--)) & xr));
    // g = 61-shift+1;

    
    // dlong xr = *((dlong*)&x);
    // //extract exponent
    // xr = (xr & 0x3FF0000000000000) >> 52;
    // std::cout << "xr is: " << xr << "\n";
    // g = 1023 - xr;
 */