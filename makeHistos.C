#include "TString.h"
#include "TFile.h"
#include "TTree.h"

struct histo {
  TString var_name, xtitle, ytitle, unit;
  Int_t nbins;
  Float_t xmin, xmax;

  histo(TString thisvar_name, Int_t thisnbins, Float_t thisxmin, Float_t thisxmax, TString thisunit=""):var_name(thisvar_name),xmin(thisxmin),xmax(thisxmax),unit(thisunit) {
    GuessUnit();
    MakeXtitle();
    MakeYtitle();  
  }

  GuessUnit() {
    //later
  }

  void MakeXtitle() {
    xtitle = var_name+" ["+unit+"]";
  }
  
  void MakeYtitle() {
    Float_t eventsperbin = (xmax-xmin)/nbins;
    char s[10];
    sprintf(s,"%g",eventsperbin);
    ytitle = "/ "+s+" "+unit;
  }
};

int main(int argc, char* argv[])
{

  TString f_name = argv[1];
  TFile *f_input = TFile::Open(f_name);
  TTree *t_input = (TTree*) f_input->Get("HWWTree");

  int nhistos = 2;
  histo histos[nhistos];
  histos[0] = new histo("nJets_OR_T",10,0,10);
  histos[1] = new histo("nJets_OR_T_MV1_70",10,0,10);
  
  
}
