#include "Generator.hpp"

int main(void){
    
    RNNet rnn(32,8,"./");
    LeftGene lg(32,8,"./"); 
    lg.RNNForward_CROSSENTROPY("./");
    lg.prtGene_Vec("Material/GENE");

    rnn.prtPara("tmp/para");
    rnn.RNNForward_CROSSENTROPY("./");
    rnn.RNNBackward_CROSSENTROPY_Without_Update();
    rnn.prtSent("tmp/ASSSENT");
    // //while(1);
    // lg.SetDLDG(rnn.getsent());
    // lg.RNNBackward_CROSSENTROPY(0.1);
    // lg.prtSent("tmp/GENESENT");

    // int i;
    // for(i=0;i<100;++i){
    //     lg.RNNForward_CROSSENTROPY("./");
    //     lg.prtGene("Material/GENE");
    //     rnn.RNNForward_CROSSENTROPY("./");
    //     rnn.RNNBackward_CROSSENTROPY_Without_Update();
    //     lg.SetDLDG(rnn.getsent());
    //     lg.RNNBackward_CROSSENTROPY(0.1);
        
    // }
    // rnn.prtSent("tmp/ASSSENT2");
    // lg.prtSent("tmp/GENESENT2");
}