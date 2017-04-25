#ifndef ASS_INC
#define ASS_INC

#include <iostream>
#include "DictCreate.hpp"

#define indim 16
#define outdim 1

typedef float* flent;

struct Sentence{
    long num;
    char* schar;
    Sentence* next;

    int len;
    flent inlay;
    flent** hidlay;
    flent outlay;

    float energy;

};

class Assess{
    public:

        Assess(int HidLayNum,int* HidLayDim,const char* dictpath);
        void fLoadsent(const char* sentpath);

    private:

//        _DEDo

        //int indim;
        //int outdim;
        int hidlaynum;
        int* hidlaydim;
        ChUTF8* dict;
        Sentence* sent;

};


#endif