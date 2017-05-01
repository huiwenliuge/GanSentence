#include "Generator.hpp"

LeftGene::LeftGene(int featurenum,int hidlayernum,const char* pathRoot){

    featureNUM=featurenum;
    hidlayerNUM=hidlayernum;
    ccdict=NULL;
    tdict=NULL;
    sent=NULL;
    
    DLDin2hid=(double**)malloc(sizeof(double*)*hidlayerNUM);
    DLDk2out =(double**)malloc(sizeof(double*)*featureNUM);
    DLDrh2h  =(double**)malloc(sizeof(double*)*hidlayerNUM);
    DLDro2h  =(double**)malloc(sizeof(double*)*hidlayerNUM);

    int i;
    for(i=0;i<hidlayerNUM;++i){
        DLDin2hid[i]=(double*)calloc(sizeof(double),featureNUM);
        DLDrh2h[i]=(double*)calloc(sizeof(double),hidlayerNUM);
        DLDro2h[i]=(double*)calloc(sizeof(double),featureNUM);
    }
    for(i=0;i<featureNUM;++i)
        DLDk2out[i] =(double*)calloc(sizeof(double),hidlayerNUM);

    EMOLIST=(char**)malloc(sizeof(char*)*1);
    for(i=0;i<1;++i)
        EMOLIST[i]=(char*)calloc(sizeof(char),11);
    strcpy(EMOLIST[0],"ROOT");
    //strcpy(EMOLIST[2],"AWKWARD");
    //strcpy(EMOLIST[3],"HAPPY");
    //strcpy(EMOLIST[4],"MOVE");
    //strcpy(EMOLIST[5],"NOVEL");
    //strcpy(EMOLIST[6],"SAD");
    
    char* pdic=(char*)calloc(sizeof(char),41);
    int pathrootlen=strlen(pathRoot);
    strcpy(pdic,pathRoot);
    strcpy(pdic+pathrootlen,"Dictionary/GENECROSS");
    FetchDict(pdic);
    FetchPara(pdic);
    
    //
    //RNNForward_CROSSENTROPY_Nthread("../",2);
    //
    // std::cout<<"sss"<<std::endl;
    char* path=(char*)calloc(sizeof(char),41);
    strcpy(path,"tmp/GENECROSS");
    _save_var(path);
}

void LeftGene::Save2txt(const char* pathRoot){
    // char* pdic=(char*)calloc(sizeof(char),41);
    // char* ppar=(char*)calloc(sizeof(char),41);
    // int pathrootlen = strlen(pathRoot);
    // strcpy(pdic,pathRoot);
    // strcpy(ppar,pathRoot);
    // //Dictionary/CROSS
    // strcpy(pdic+pathrootlen,"Dictionary/CROSSDICT");
    // strcpy(ppar+pathrootlen,"Dictionary/CROSSPARA");

    // FILE* fp = fopen(pdic,"w");
    // prtHash2File(ccdict,fp,featureNUM);
    // prtPara(ppar);
    char* path=(char*)calloc(sizeof(char),41);
    int pathrootlen = strlen(pathRoot);
    strcpy(path,pathRoot);
    strcpy(path+pathrootlen,"Dictionary/GENECROSS");
    _save_var(path);
}

void LeftGene::_save_var(const char* pathRoot){
    char* pdic=(char*)calloc(sizeof(char),41);
    char* ppar=(char*)calloc(sizeof(char),41);
    int pathrootlen = strlen(pathRoot);
    strcpy(pdic,pathRoot);
    strcpy(ppar,pathRoot);
    strcpy(pdic+pathrootlen,"DICT");
    strcpy(ppar+pathrootlen,"PARA");
    
    FILE* fp = fopen(pdic,"w");
    prtHash2File(ccdict,fp,featureNUM);
    prtPara(ppar);
}

void LeftGene::FirstVar(const char* filePath){
    //
    std::cout << "Indeveloping\n";
}

Genesent LeftGene::FetchSent(const char* pathRoot){

    //Genesent ret;
//    char** filelist=(char**)malloc(sizeof(char*)*featureNUM);
    char* filel;
    int i,j,len,pathrootlen;
    FILE* sentfp;
    char* line=(char*)calloc(sizeof(char),421);
    totnum = 0;
    pathrootlen=strlen(pathRoot);
//    for(i=0;i<featureNUM;++i){
    filel=(char*)calloc(sizeof(char),101);
    strcpy(filel,pathRoot);
    strcpy(filel+pathrootlen,EMOLIST[0]);
    //std::cout<< filelist[i] <<std::endl;

    sentfp=fopen(filel,"r");
    // const double* ans=(double*)calloc(sizeof(double),featureNUM);
    // ans[i]=1.0;

    while(fscanf(sentfp,"%s\n",line)!=-1){

        len=strLenUTF8(line);
        Genesent sentunit=(Genesent)malloc(sizeof(struct genesent));
        sentunit->num = totnum;
        totnum++;
        sentunit->schar=line;
        sentunit->tlen=len;
        sentunit->inVec=crtInvec(line,featureNUM,ccdict);
        sentunit->hidLay=(double**)malloc(sizeof(double*)*len);
        sentunit->kLayer=(double**)malloc(sizeof(double*)*len);
        sentunit->outLay=(double**)malloc(sizeof(double*)*len);
        
        sentunit->DLDo  =(double**)malloc(sizeof(double*)*len);
        sentunit->DLDh  =(double**)malloc(sizeof(double*)*len);
        sentunit->DLDx  =(double**)malloc(sizeof(double*)*len);
        sentunit->energy=(double**)malloc(sizeof(double*)*len);
//            sentunit->stdAns=(double*)calloc(sizeof(double),featureNUM);
        sentunit->eng=(double*)calloc(sizeof(double),featureNUM);
        sentunit->DLDG=(double*)calloc(sizeof(double),featureNUM);
        for(j=0;j<len;++j){
            // for(int k=0;k<featureNUM;++k){
            //     std::cout<<sentunit->inVec[j][k];
            // }
            //std::cout<<std::endl;
            sentunit->energy[j]=(double*)calloc(sizeof(double),featureNUM);
            sentunit->hidLay[j]=(double*)calloc(sizeof(double),hidlayerNUM);
            sentunit->kLayer[j]=(double*)calloc(sizeof(double),hidlayerNUM);
            sentunit->outLay[j]=(double*)calloc(sizeof(double),featureNUM);
            sentunit->DLDo[j]  =(double*)calloc(sizeof(double),featureNUM);
            sentunit->DLDh[j]  =(double*)calloc(sizeof(double),hidlayerNUM);
            sentunit->DLDx[j]  =(double*)calloc(sizeof(double),featureNUM);
        }

//            sentunit->stdAns[i]=1.0;
        sentunit->next=sent;
        sent=sentunit;

        
        line=(char*)calloc(sizeof(char),421);
    }
    fclose(sentfp);

//    }

    // for(i=0;i<featureNUM;++i)
    //     free(filelist[i]);
    //fclose(sentfp);
    free(filel);
    std::cout<< totnum <<std::endl;
    return sent;

}

ChUTF8* LeftGene::FetchDict(const char* pathRoot){

    char* path=(char*)calloc(sizeof(char),41);
    strcpy(path,pathRoot);
    strcpy(path+strlen(pathRoot),"DICT");
    
    ChUTF8* ret;
    std::cout<< path<<std::endl;
    FILE* dicfp=fopen(path,"r");
    FILE* dictmp=fopen("tmp/genedictmp","w");
    ret=fldDic(dicfp,featureNUM);
    prtHash2File(ret,dictmp,featureNUM);
    free(path);
    ccdict=ret;
    return ret;

}

void LeftGene::prtPara(const char* path){
    FILE* paratmp=fopen(path,"w");
    
    int i,j;
    fprintf(paratmp,"%s %d\n","Para_Mat_W",hidlayerNUM);
    for(i=0;i<featureNUM;++i){
        for(j=0;j<hidlayerNUM;++j)
            fprintf(paratmp,"#%lf#",k2out[i][j]);
        fputc('\n',paratmp);
    }

    fprintf(paratmp,"Para_Mat_B %d\n",hidlayerNUM);
    for(i=0;i<hidlayerNUM;++i){
        for(j=0;j<featureNUM;++j)
            fprintf(paratmp,"#%lf#",ro2h[i][j]);
        fputc('\n',paratmp);
    }

    fprintf(paratmp,"Para_Mat_T\n");
    for(i=0;i<hidlayerNUM;++i){
        for(j=0;j<hidlayerNUM;++j)
            fprintf(paratmp,"#%lf#",rh2h[i][j]);
        fputc('\n',paratmp);
    }

    fprintf(paratmp,"Para_Mat_U");
    for(i=0;i<hidlayerNUM;++i){
        fputc('\n',paratmp);
        for(j=0;j<featureNUM;++j)
            fprintf(paratmp,"#%lf#",in2hid[i][j]);
    }
    
    fclose(paratmp);
}

void LeftGene::FetchPara(const char* pathRoot){
    char* path=(char*)calloc(sizeof(char),41);
    strcpy(path,pathRoot);
    strcpy(path+strlen(pathRoot),"PARA");
    
    //std::cout<< path<<std::endl;
    FILE* parafp=fopen(path,"r");
    //FILE* paratmp=fopen("paratmp","w");

    char* line=(char*)calloc(sizeof(char),81);
    int i,j;
    fscanf(parafp,"%s %d\n",line,&i);
    //std::cout<<line<<" "<<"line"<<std::endl;
    
    k2out=(double**)malloc(sizeof(double*)*featureNUM);
    
    for(i=0;i<featureNUM;++i){
        k2out[i]=(double*)malloc(sizeof(double)*hidlayerNUM);   
        for(j=0;j<hidlayerNUM;++j){
            fscanf(parafp,"#%lf#",k2out[i]+j);
      //      std::cout<<k2out[i][j]<<std::endl;
        }
        fgetc(parafp);
    }
    fscanf(parafp,"%s %d\n",line,&i);
    std::cout<<line<<std::endl;

    ro2h=(double**)malloc(sizeof(double*)*hidlayerNUM);
    for(i=0;i<hidlayerNUM;++i){
        ro2h[i]=(double*)malloc(sizeof(double)*featureNUM);
        for(j=0;j<featureNUM;++j){
            fscanf(parafp,"#%lf#",ro2h[i]+j);
        }
        fgetc(parafp);
    }

    fscanf(parafp,"%s\n",line);
    std::cout<<line<<std::endl;

    rh2h=(double**)malloc(sizeof(double*)*hidlayerNUM);
    for(i=0;i<hidlayerNUM;++i){
        rh2h[i]=(double*)malloc(sizeof(double)*hidlayerNUM);
        for(j=0;j<hidlayerNUM;++j){
            fscanf(parafp,"#%lf#",rh2h[i]+j);
        }
        fgetc(parafp);
    } 
    fscanf(parafp,"%s\n",line);
    std::cout<<line<<std::endl;

    in2hid=(double**)malloc(sizeof(double*)*hidlayerNUM);
    for(i=0;i<hidlayerNUM;++i){
        in2hid[i]=(double*)malloc(sizeof(double)*featureNUM);
        for(j=0;j<featureNUM;++j){
            fscanf(parafp,"#%lf#",in2hid[i]+j);
        }
        fgetc(parafp);
    }

    //prtPara("paratmp");
    free(path);
    free(line);
    fclose(parafp);
}

double LeftGene::RNNForward_CROSSENTROPY(const char* pathRoot){

    int pathrootlen=strlen(pathRoot);
    char* psen=(char*)calloc(sizeof(char),41);
    strcpy(psen,pathRoot);
    strcpy(psen+pathrootlen,"Material/");
    FreeSen();
    Genesent sentmp=FetchSent(psen);
    free(psen);
    
    while(sentmp){
        _Forward_CROSSENTROPY(sentmp);
        sentmp=sentmp->next;
    }

    return 0;
} 

double LeftGene::RNNForward_CROSSENTROPY_Nthread(const char* pathRoot,int Nthread){
    
    char* psen=(char*)calloc(sizeof(char),41);
    int pathrootlen=strlen(pathRoot);   
    strcpy(psen,pathRoot);
    strcpy(psen+pathrootlen,"Material/");
    FreeSen();
    Genesent sentmp=FetchSent(psen);
    free(psen);
    flag = totnum-1;
    
    std::thread th[Nthread];
    int n;
   
    for(n=0;n<Nthread;++n){
        th[n]=std::thread(_Forward_CROSSENTROPY_SingleTask,\
            this,&sentmp,n);
    }
    for(n=0;n<Nthread;++n)
        th[n].join();
    
    return 0;
}

void LeftGene::RNNBackward_CROSSENTROPY(double lnrate){

    // int i;
    // for(i=0;i<hidlayerNUM;++i){
    //     DLDin2hid[i]=(double*)calloc(sizeof(double),featureNUM);
    //     DLDrh2h[i]=(double*)calloc(sizeof(double),hidlayerNUM);
    //     DLDro2h[i]=(double*)calloc(sizeof(double),featureNUM);
    // }
    // for(i=0;i<featureNUM;++i)
    //     DLDk2out[i] =(double*)calloc(sizeof(double),hidlayerNUM);
    lnrt=lnrate;
    //DLDGx=D;
    int i;
    for(i=0;i<hidlayerNUM;++i){
        memset(DLDin2hid[i],'\0',sizeof(double)*featureNUM);
        memset(DLDrh2h[i],'\0',sizeof(double)*hidlayerNUM);
        memset(DLDro2h[i],'\0',sizeof(double)*featureNUM);
    }
    for(i=0;i<featureNUM;++i)
        memset(DLDk2out[i],'\0',sizeof(double)*hidlayerNUM);

    Genesent sentmp = sent;
    
    while(sentmp){
        _Backward_CROSSENTROPY(sentmp);
        sentmp=sentmp->next;
    }
    
    int j;
    for(i=0;i<hidlayerNUM;++i){
        for(j=0;j<featureNUM;++j){
            in2hid[i][j]-=DLDin2hid[i][j]*lnrt;
        }
        for(j=0;j<hidlayerNUM;++j){
            rh2h[i][j]-=DLDrh2h[i][j]*lnrt;
        }
        for(j=0;j<featureNUM;++j){
            ro2h[i][j]-=DLDro2h[i][j]*lnrt;
        }
    }
    for(i=0;i<featureNUM;++i){
        for(j=0;j<hidlayerNUM;++j){
            k2out[i][j]-=DLDk2out[i][j]*lnrt;
        }
    }

}

void LeftGene::RNNBackward_CROSSENTROPY_Nthread(double lnrts,int Nthread){
    lnrt=lnrts;
    int i;
    for(i=0;i<hidlayerNUM;++i){
        memset(DLDin2hid[i],'\0',sizeof(double)*featureNUM);
        memset(DLDrh2h[i],'\0',sizeof(double)*hidlayerNUM);
        memset(DLDro2h[i],'\0',sizeof(double)*featureNUM);
    }
    for(i=0;i<featureNUM;++i)
        memset(DLDk2out[i],'\0',sizeof(double)*hidlayerNUM);

    Genesent stmp = sent;
    
    flag = totnum-1;
    std::thread th[Nthread];
    int n;
    
    for(n=0;n<Nthread;++n){
       th[n]=std::thread(_Backward_CROSSENTROPY_SingleTask,\
               this,&stmp,n);
    }

    for(n=0;n<Nthread;++n){
        th[n].join();
    }
    int j;
    for(i=0;i<hidlayerNUM;++i){
        for(j=0;j<featureNUM;++j){
            in2hid[i][j]-=DLDin2hid[i][j]*lnrt;
        }
        for(j=0;j<hidlayerNUM;++j){
            rh2h[i][j]-=DLDrh2h[i][j]*lnrt;
        }
        for(j=0;j<featureNUM;++j){
            ro2h[i][j]-=DLDro2h[i][j]*lnrt;
        }
    }
    for(i=0;i<featureNUM;++i){
        for(j=0;j<hidlayerNUM;++j){
            k2out[i][j]-=DLDk2out[i][j]*lnrt;
        }
    }
}

double LeftGene::_Forward_CROSSENTROPY(Genesent sen){

    int t,i,j;
    
    for(i=0;i<hidlayerNUM;++i){
        sen->hidLay[0][i]=0.0;
        for(j=0;j<featureNUM;++j)
            sen->hidLay[0][i]+=in2hid[i][j]*sen->inVec[0][j];
        sen->kLayer[0][i]=sigm(sen->hidLay[0][i]);
    }
    
    for(i=0;i<featureNUM;++i){
        sen->outLay[0][i]=0.0;
        for(j=0;j<hidlayerNUM;++j)
            sen->outLay[0][i]+=k2out[i][j]*sen->kLayer[0][j];
        sen->eng[i]=0.0;
    }
    softmax_add(sen,sen->outLay[0],0);
    // sen->loss=0.0;
    // for(i=0;i<featureNUM;++i)
    //     sen->loss+=-sen->stdAns[i]*log(sen->energy[i]);

    for(t=1;t<sen->tlen;++t){

        for(i=0;i<hidlayerNUM;++i){
            sen->hidLay[t][i]=0.0;
            for(j=0;j<featureNUM;++j)
                sen->hidLay[t][i]+=in2hid[i][j]*sen->inVec[t][j];
            for(j=0;j<hidlayerNUM;++j)
                sen->hidLay[t][i]+=rh2h[i][j]*sen->kLayer[t-1][j];
            for(j=0;j<featureNUM;++j)
                sen->hidLay[t][i]+=ro2h[i][j]*sen->outLay[t-1][j];
            sen->kLayer[t][i]=sigm(sen->hidLay[t][i]);
        }

        for(i=0;i<featureNUM;++i){
            sen->outLay[t][i]=0.0;
            for(j=0;j<hidlayerNUM;++j)
                sen->outLay[t][i]+=k2out[i][j]*sen->kLayer[t][j];  
        }
        softmax_add(sen,sen->outLay[t],t);

    }

    for(i=0;i<sen->tlen;++i)
        for(j=0;j<featureNUM;++j)
            sen->eng[j]+=sen->energy[i][j];
    for(i=0;i<featureNUM;++i)
        sen->eng[i]/=sen->tlen;
    
    sen->loss=0.0;
    //for(i=0;i<featureNUM;++i)
    //    sen->loss+=-sen->stdAns[i]*log(sen->eng[i]);
    
    return sen->loss;
}

void LeftGene::SetDLDG(Sentence inSen){

    Genesent gtmp = this->sent;
    Sentence stmp = inSen;
    while(gtmp){
        std::cout<<gtmp->num<<" "<<stmp->num<<std::endl;
        memcpy(gtmp->DLDG,stmp->DLDx[0],sizeof(double)*featureNUM);
        std::cout<<stmp->schar<<std::endl;
        std::cout<<gtmp->schar<<std::endl;
        gtmp = gtmp->next;
        stmp = stmp->next;
    }

}

void LeftGene::_Backward_CROSSENTROPY(Genesent sen){
    int t,i,j,k;
    t=sen->tlen-1;
    for(i=0;i<featureNUM;++i)
        sen->DLDo[t][i]=-sen->DLDG[i]*(sen->energy[t][i]-\
                            sen->energy[t][i]*sen->energy[t][i])/sen->tlen;
                            
    for(t=sen->tlen-2;t>-1;--t){
        for(i=0;i<featureNUM;++i){
            sen->DLDo[t][i]=-sen->DLDG[i]*(sen->energy[t][i]-\
                            sen->energy[t][i]*sen->energy[t][i])/sen->tlen;//-(sen->stdAns[i]-sen->energy[t][i]);
            for(k=0;k<featureNUM;++k){
                for(j=0;j<hidlayerNUM;++j){
                    sen->DLDo[t][i]+=sen->DLDo[t+1][k]\
                            *k2out[k][j]*dsigm(sen->hidLay[t+1][j])\
                            *ro2h[j][i];
                }
            }
        }
    }
    
    t=sen->tlen-1;
    for(i=0;i<hidlayerNUM;++i){
        sen->DLDh[t][i]=0.0;
        for(j=0;j<featureNUM;++j){
            sen->DLDh[t][i]+=sen->DLDo[t][j]*k2out[j][i]\
                    *dsigm(sen->hidLay[t][i]);
        }
    }
    for(t=sen->tlen-2;t>-1;--t){
        for(i=0;i<hidlayerNUM;++i){
            sen->DLDh[t][i]=0.0;
            for(j=0;j<featureNUM;++j){
                sen->DLDh[t][i]+=sen->DLDo[t][j]*k2out[j][i]\
                        *dsigm(sen->hidLay[t][i]);
            }
            for(j=0;j<hidlayerNUM;++j){
                sen->DLDh[t][i]+=sen->DLDh[t+1][j]*rh2h[j][i]\
                        *dsigm(sen->hidLay[t+1][i]);
            }
        }
    }
    
    t=sen->tlen-1;
    for(i=0;i<featureNUM;++i){
        sen->DLDx[t][i]=0.0;
        for(j=0;j<hidlayerNUM;++j){
            sen->DLDx[t][i]+=sen->DLDh[t][j]*in2hid[j][i];
        }
    }
    for(t=sen->tlen-2;t>-1;--t){
        for(i=0;i<featureNUM;++i){
            sen->DLDx[t][i]=0.0;
            for(j=0;j<hidlayerNUM;++j){
                sen->DLDx[t][i]+=sen->DLDh[t][j]*in2hid[j][i];
                for(k=0;k<hidlayerNUM;++k){
                    sen->DLDx[t][i]+=sen->DLDh[t+1][j]*rh2h[j][k]\
                        *dsigm(sen->hidLay[t][k])*in2hid[k][i];
                }
            }
            // for(j=0;j<hidlayerNUM;++j){
            //     for(k=0;k<hidlayerNUM;++k){
            //         sen->DLDx[t][i]+=sen->DLDh[t+1][j]*rh2h[j][k]\
            //             *dsigm(sen->hidLay[t][k])*in2hid[k][i];
            //     }
            // }
        }
    }
    
    double plnrt = lnrt/sen->tlen;
    static std::mutex g_mutex;
    g_mutex.lock();
    upgradeDict(ccdict,sen->schar,sen->DLDx,featureNUM,plnrt);    
    g_mutex.unlock();
    double pder;
    for(i=0;i<featureNUM;++i){
        for(j=0;j<hidlayerNUM;++j){
            pder=0.0;
            for(t=0;t<sen->tlen;++t){
                pder+=sen->DLDo[t][i]*sen->kLayer[t][j];
            }
            pder/=sen->tlen;
            g_mutex.lock();
            DLDk2out[i][j]=pder/sen->tlen;
            g_mutex.unlock();
        }
    }
    
    for(i=0;i<hidlayerNUM;++i){
        for(j=0;j<featureNUM;++j){
            pder=0.0;
            for(t=0;t<sen->tlen;++t){
                pder+=sen->DLDh[t][i]*sen->inVec[t][j];
            }
            pder/=sen->tlen;
            g_mutex.lock();
            DLDin2hid[i][j]+=pder;
            g_mutex.unlock();
        }
    }

    for(i=0;i<hidlayerNUM;++i){
        for(j=0;j<hidlayerNUM;++j){
            pder=0.0;
            for(t=1;t<sen->tlen;++t){
                pder+=sen->DLDh[t][i]*sen->kLayer[t-1][j];
            }
            pder/=sen->tlen;
            g_mutex.lock();
            DLDrh2h[i][j]+=pder;
            g_mutex.unlock();
        }
    }

    for(i=0;i<hidlayerNUM;++i){
        for(j=0;j<featureNUM;++j){
            pder=0.0;
            for(t=1;t<sen->tlen;++t){
                pder+=sen->DLDh[t][i]*sen->outLay[t-1][j];
            }
            pder/=sen->tlen;
            g_mutex.lock();
            DLDro2h[i][j]+=pder;
            g_mutex.unlock();
        }
    }
    
}

Genesent gonext(Genesent sen,long target){
    Genesent ret=sen;
    if(target < 0) return NULL;
    while(ret->num>target){
        ret = ret->next;
    }
    return ret;
}

double LeftGene::_Forward_CROSSENTROPY_SingleTask(LeftGene* rnn,Genesent* sen,int n){
    Genesent tsen = *sen;
    long num = tsen->num;
    std::mutex g_mutex;
    while( rnn->flag > -1){
        g_mutex.lock();
        num = rnn->flag;
        //printf("%ld\n",num);
        rnn->flag--;
        g_mutex.unlock();
        tsen = gonext(tsen,num);
        if(tsen!=NULL){
            //std::cout<<tsen->schar<<std::endl;
            rnn->_Forward_CROSSENTROPY(tsen);
        }
    }
    return 0;
}

void LeftGene::_Backward_CROSSENTROPY_SingleTask(LeftGene* rnn,Genesent* sen,int n){
    Genesent tsen = *sen;
    std::mutex g_mutex;
    long num = tsen->num;
    while(rnn->flag > -1){
        g_mutex.lock();
        num = rnn->flag;
        //printf("%ld\n",num);
        rnn->flag--;
        g_mutex.unlock();
        tsen = gonext(tsen,num);
        if(tsen!=NULL){
            rnn->_Backward_CROSSENTROPY(tsen);
        }
    }
}

void LeftGene::softmax_add(Genesent sen,double* src,int t){
    double normal=0.0;
    int i;
    for(i=0;i<featureNUM;++i)
        normal+=exp(src[i]);
    
    for(i=0;i<featureNUM;++i){
        sen->energy[t][i]=exp(src[i])/normal;
     //   std::cout<<sen->energy[t][i]<<std::endl;
    }
}

int LeftGene::FreeSen(){
    if(sent==NULL) return 0;
    Genesent tmp;
    int i,j;
    while(sent){
        tmp = sent;
        sent=sent->next;
        free(tmp->schar);
        for(i=0;i<tmp->tlen;++i){
            free(tmp->inVec[i]);
            free(tmp->hidLay[i]);
            free(tmp->outLay[i]);
            free(tmp->kLayer[i]);
            free(tmp->energy[i]);
            free(tmp->DLDh[i]);
            free(tmp->DLDo[i]);
            free(tmp->DLDx[i]);
        }
        free(tmp->inVec);
        free(tmp->hidLay);
        free(tmp->kLayer);
        free(tmp->outLay);
        free(tmp->energy);
        free(tmp->eng);
        //free(tmp->stdAns);
        free(tmp->DLDh);
        free(tmp->DLDo);
        free(tmp->DLDx);
        free(tmp);
    }
    return 1;
}

void LeftGene::FreeAll(){
    FreeSen();
    if(ccdict!=NULL) hashFree(ccdict);
    int i,j;
    for(i=0;i<featureNUM;++i){
        free(k2out[i]);
        free(DLDk2out[i]);
    }
    for(i=0;i<hidlayerNUM;++i){
        free(in2hid[i]);
        free(ro2h[i]);
        free(rh2h[i]);
        free(DLDro2h[i]);
        free(DLDrh2h[i]);
        free(DLDin2hid[i]);
    }
}

void LeftGene::prtSent(const char* path){
    Genesent tmp=sent;

    FILE* fp = fopen(path,"w");
    int i,j;

    while(tmp){
        fprintf(fp,"{\n");
        fprintf(fp,"%s %d\ninVec:{\n",tmp->schar,tmp->tlen);
        for(i=0;i<tmp->tlen;++i){
            for(j=0;j<featureNUM;++j)
                fprintf(fp,"%f ",tmp->inVec[i][j]);
            fprintf(fp,"\n");
        }
        // fprintf(fp,"}\nhidLay:{\n");
        // for(i=0;i<tmp->tlen;++i){
        //     for(j=0;j<hidlayerNUM;++j)
        //         fprintf(fp,"%f ",tmp->hidLay[i][j]);
        //     fprintf(fp,"\n");
        // }
        // fprintf(fp,"}\nkLayer:{\n");
        // for(i=0;i<tmp->tlen;++i){
        //     for(j=0;j<hidlayerNUM;++j)
        //         fprintf(fp,"%f ",tmp->kLayer[i][j]);
        //     fprintf(fp,"\n");
        // }
        // fprintf(fp,"}\noutLay:{\n");
        // for(i=0;i<tmp->tlen;++i){
        //     for(j=0;j<featureNUM;++j)
        //         fprintf(fp,"%f ",tmp->outLay[i][j]);
        //     fprintf(fp,"\n");
        // }
        fprintf(fp,"}\nDLDG:{\n");
        for(j=0;j<featureNUM;++j)
            fprintf(fp,"%f ",tmp->DLDG[j]);
        fprintf(fp,"}\neng:{\n");
        for(j=0;j<featureNUM;++j)
            fprintf(fp,"%f ",tmp->eng[j]);
        //fprintf(fp,"\n}\nstdAns:{\n");
        //for(j=0;j<featureNUM;++j)
        //    fprintf(fp,"%f ",tmp->stdAns[j]);
        fprintf(fp,"\n}\nloss:%f\n\n",tmp->loss);
        tmp=tmp->next;
    }

}

void LeftGene::prtGene(const char* path){
    FILE* fp = fopen(path,"w");
    Genesent tmp=sent;
    ChUTF8 ctmp;
    while(tmp){
        ctmp = minAngle(ccdict,tmp->eng,featureNUM);
        fprintf(fp,"%s%s\n",ctmp->schar,tmp->schar);
        tmp=tmp->next;
    }
    fclose(fp);
}

void LeftGene::prtGene_Vec(const char* path){
    FILE* fp = fopen(path,"w");
    Genesent tmp=sent;
    
    int i;
    while(tmp){
        fprintf(fp,"%s\n",tmp->schar);
        for(i=0;i<featureNUM;++i){
            fprintf(fp,"#%lf#",tmp->eng[i]);
        }
        fputc('\n',fp);
        tmp=tmp->next;
    }
    fclose(fp);
}

void LeftGene::init_thread(int n){
    std::cout<<"thread\n";
}