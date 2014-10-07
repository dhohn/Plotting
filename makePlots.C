#include "plotVar.C"
#include <stdlib.h>


int main(int argc, char** argv)
{
  
  system("mkdir plots");


  if(argc<=1) {
    cout<<"makePlots needs at least one file name."<<endl;
    return 0;
  }
    
  TString files[argc-1];
  for(int i=0;i<argc-1;i++) {
    
    files[i] = argv[i+1];
    cout<<files[i]<<endl;
  }
  
  plotVar("DPhill",argc-1,files);
  
  
  plotVar("Mll",argc-1,files);
  plotVar("Mt",argc-1,files);
  plotVar("Ptll",argc-1,files);
  plotVar("WminM",argc-1,files);
  plotVar("WplusM",argc-1,files);
  plotVar("METRel",argc-1,files);
  plotVar("phi3",argc-1,files);
  plotVar("theta1",argc-1,files);
  plotVar("theta3",argc-1,files);
  plotVar("yPt",argc-1,files);
  plotVar("lepminEta",argc-1,files);
  plotVar("lepplusEta",argc-1,files);
  plotVar("Phi",argc-1,files);
  plotVar("Phi1",argc-1,files);
  plotVar("cosThetaStar",argc-1,files);
  plotVar("cosTheta1",argc-1,files);
  plotVar("cosTheta2",argc-1,files);
  plotVar("BDPhill",argc-1,files);
  plotVar("DPsill",argc-1,files);
  plotVar("BDPsill",argc-1,files);
  plotVar("DEtall",argc-1,files);
  plotVar("DPhiLeadLepMET",argc-1,files);
  plotVar("DPhiSubLeadLepMET",argc-1,files);
  plotVar("WonShellM",argc-1,files);
  plotVar("WoffShellM",argc-1,files);
  plotVar("DLepPt",argc-1,files);
  plotVar("DPtcharge",argc-1,files);
  plotVar("DPhiLepPlusMET",argc-1,files);
  plotVar("DPhiLepMinMET",argc-1,files);
  plotVar("BLepPlusPhi",argc-1,files);
  plotVar("BLepMinPhi",argc-1,files);
  
  

  return 0;


}
