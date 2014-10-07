#include "plotVarMVA.C"
#include <stdlib.h>


int main(int argc, char** argv)
{
  
  system("mkdir plots");


  if(argc<=1) {
    cout<<"makePlots needs at least one file name."<<endl;
    return 0;
  }
    
  int nhyp = argc-1;


  TString files[argc-1];
  for(int i=0;i<argc-1;i++) {
    
    files[i] = argv[i+1];
    cout<<files[i]<<endl;
  }
      

  //plotVarMVA("DPhill",argc-1,files);
  //plotVarMVA("Mll",argc-1,files);
  //plotVarMVA("MT",argc-1,files);
  //plotVarMVA("Ptll",argc-1,files);
  //  plotVarMVA("WminM",argc-1,files);
  //plotVarMVA("WplusM",argc-1,files);
  //plotVarMVA("METRel",argc-1,files);
  //plotVarMVA("phi3",argc-1,files);
  //plotVarMVA("theta1",argc-1,files);
  //plotVarMVA("theta3",argc-1,files);
  //plotVarMVA("yPt",argc-1,files);
  //plotVarMVA("lepminEta",argc-1,files);
  //plotVarMVA("lepplusEta",argc-1,files);
  //plotVarMVA("Phi",argc-1,files);
  //plotVarMVA("Phi1",argc-1,files);
  //plotVarMVA("cosThetaStar",argc-1,files);
  //plotVarMVA("cosTheta1",argc-1,files);
  //plotVarMVA("cosTheta2",argc-1,files);
  //plotVarMVA("BDPhill",argc-1,files);
  //plotVarMVA("DPsill",argc-1,files);
  //plotVarMVA("BDPsill",argc-1,files);
  //plotVarMVA("DEtall",argc-1,files);
  plotVarMVA("DPhiLeadLepMET",argc-1,files);
  //plotVarMVA("DPhiSubLeadLepMET",argc-1,files);
  

  return 0;


}
