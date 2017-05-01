#ifndef LeftGene_INC
#define LeftGene_INC

#include "RNNet.hpp"
#include "DictCreate.hpp"

#define codedim 32


struct genesent{
    long num;
    char* schar;
    int tlen;
    double** inVec;
    double** hidLay;
    double** kLayer;
    double** outLay;
    double** energy;
    double* eng;
    //double* stdAns;
    double loss;
    double* DLDG;
    double** DLDo;
    double** DLDh;
    double** DLDx;
    struct genesent* next;

};
typedef struct genesent* Genesent;

class LeftGene{

    public:
        LeftGene(int featurenum,int hidlayernum,const char* pathRoot);
        ~LeftGene(){
           // FreeAll();
        };

        void FirstVar(const char* filePath);
        void Save2txt(const char* PathRoot);
        void RestoreVar(const char* filePath);
        double RNNForward_CROSSENTROPY(const char* pathRoot);
        double RNNForward_CROSSENTROPY_Nthread(const char* pathRoot,int Nthread);
        void RNNBackward_CROSSENTROPY(double lnrt);
        void RNNBackward_CROSSENTROPY_Nthread(double lnrt,int Nthread);

        void SetDLDG(Sentence inSen);
        void prtSent(const char* path);
        void prtPara(const char* path);

        void prtGene(const char* path);
        void prtGene_Vec(const char* path);

        ChUTF8* ccdict;
        ChUTF8* tdict;
        double** in2hid;
        double** k2out;
        double** rh2h;
        double** ro2h;

        double sigm(double x){
            return 1.0/(1.0+exp(-x));
        }

        double dsigm(double x){
            return sigm(x)*(1.0-sigm(x));
        }
        
        //static std::atomic<Sentence> asent;
    private:
        int featureNUM;
        int hidlayerNUM;
        int DictSize;
        double lnrt;
        long flag;
        long totnum;
        double** DLDGx;
        double** DLDin2hid;
        double** DLDk2out;
        double** DLDrh2h;
        double** DLDro2h;
        
        Genesent sent;
        Genesent FetchSent(const char* pathRoot);
        ChUTF8* FetchDict(const char* pathRoot);
        void FetchPara(const char* pathRoot);
        
        static void init_thread(int n);
        
        double _Forward_CROSSENTROPY(Genesent sen);
        static double _Forward_CROSSENTROPY_SingleTask(LeftGene* rnn,Genesent* sen,int n);
        void _Backward_CROSSENTROPY(Genesent sen);
        static void _Backward_CROSSENTROPY_SingleTask(LeftGene* rnn,Genesent* sen,int n);

        void softmax_add(Genesent sen,double* src,int t);
        int FreeSen();

        char** EMOLIST;

        void _save_var(const char* pathRoot);

        void FreeAll();


};

#endif