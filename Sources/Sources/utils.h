#ifndef H_UTILS
#define H_UTILS
int pgcd(int a, int b) {
    if(a<0)a=-a;
    if(b<0)b=-b;
    while (a*b!=0)
    {
        if (a > b)
            a = a - b;
        else
            b = b - a;
    }
    if (a == 0)
        return b;
    else
        return a;
}


#endif
