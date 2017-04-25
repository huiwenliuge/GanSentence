#include "Generator.hpp"

int main(void){
    
    RNNet rnn(32,8,"./");
    // const char *pa = "../";
    rnn.RNNForward_CROSSENTROPY("./");
    rnn.RNNBackward_CROSSENTROPY(0.1);
    rnn.prtSent("tmp/ASSSENT");

    LeftGene lg(32,8,"./"); 
    //while(1);
    lg.RNNForward_CROSSENTROPY("./");
    lg.SetDLDG(rnn.getsent());
    lg.RNNBackward_CROSSENTROPY(0.1);
    lg.prtSent("tmp/GENESENT");
}