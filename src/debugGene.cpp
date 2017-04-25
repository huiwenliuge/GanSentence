#include "Generator.hpp"

int main(void){

    LeftGene lg(32,8,"./"); 
    const char* pa = "../";
    lg.RNNForward_CROSSENTROPY_Nthread("./",1);

    lg.prtSent("tmp/GENESENT");
    lg.prtGene("Material/GENE");
}