#include "TString.h"
#include "TFile.h"
#include "TTree.h"

struct histo {
  TString var_name, xtitle, ytitle, unit;
  Int_t nbins;
  Float_t xmin, xmax;

  TString GetXtitle() {
    xtitle = var_name+" ["+unit+"]";
    return xtitle;
  };
  TString GetYtitle() {
    Float_t eventsperbin = (xmax-xmin)/nbins;
    char s[10];
    sprintf(s,"%g",eventsperbin);
    ytitle = "/ "+s+" "+unit;
    return ytitle;
  }
};

int main(int argc, char* argv[])
{

  TString f_name = argv[1];
  TFile *f_input = TFile::Open(f_name);
  TTree *t_input = (TTree*) f_input->Get("HWWTree");

  
  
}
