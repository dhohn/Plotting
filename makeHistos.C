#include "TH1.h"
#include "TCut.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include <iostream>

using namespace std;

struct histo {
  TString var_name, xtitle, ytitle, unit;
  Int_t nbins;
  Float_t xmin, xmax;

  histo() {}
  histo(TString thisvar_name, Int_t thisnbins, Float_t thisxmin, Float_t thisxmax, TString thisunit=""):var_name(thisvar_name),nbins(thisnbins),xmin(thisxmin),xmax(thisxmax),unit(thisunit) {
    GuessUnit();
    MakeXtitle();
    MakeYtitle();  
  }

  void GuessUnit() {
    //later
    return;
  }

  void MakeXtitle() {
    xtitle = var_name+" ["+unit+"]";
  }
  
  void MakeYtitle() {
    Float_t eventsperbin = (xmax-xmin)/nbins;
    char s[10];
    sprintf(s,"%g",eventsperbin);
    ytitle = "/ ";
    ytitle +=s;
    ytitle +=" "+unit;
  }
};

int main(int argc, char* argv[])
{


  TDirectory *where = gDirectory;
  TString f_name = argv[1];
  TFile *f_input = TFile::Open(f_name);
  TTree *t_input = (TTree*) f_input->Get("HWWTree");
  cout<<"opened file "<<f_name<<endl;
  
  TString f_id = f_name.Remove(f_name.Length()-5,f_name.Length());

  TFile *f_output = new TFile("./"+f_id+"_hist.root","RECREATE");

  cout<<"create outfile"<<endl;
  
  int nhistos = 2;
  histo *histos[nhistos];
  histos[0] = new histo("nJets_OR_T",10,0,10);
  histos[1] = new histo("nJets_OR_T_MV1_70",10,0,10);
  
  
  TH1F *h[nhistos];
  
  cout<<"created histo structs"<<endl;
  
  TCut cut = "(EF_mu24i_tight || EF_mu36_tight || EF_e24vhi_medium1 || EF_e60_medium1) && ((onelep_type>0) && total_leptons==1) && (nTaus_OR_Pt25==2) && passEventCleaning";
  TString cut_name = "1l2t";
  
  for(int i=0;i<nhistos;++i) {
    //where->cd();
    cout<<"loop: "<<i<<endl;
    TString h_name = cut_name+histos[i]->var_name;
    cout<<"histo name "<<h_name<<endl;
    h[i] = new TH1F(h_name,histos[i]->var_name,histos[i]->nbins,histos[i]->xmin,histos[i]->xmax);
    cout<<"TH1F created "<<h[i]->GetEntries()<<endl;
    cout<<t_input->Project(h_name,histos[i]->var_name,cut)<<endl;
    cout<<"TH1F entries "<<h[i]->GetEntries()<<endl;
    //f_output->cd();
    h[i]->Write();
    //    delete h;
  }

  cout<<"file write NAO"<<endl;
  //  f_output->Write();
  cout<<"file written "<<endl;
  f_output->Close();
  cout<<"file closed"<<endl;
  f_input->Close();
}
