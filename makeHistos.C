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

  const Float_t GeV = 1000;
  
  TString f_name = argv[1];
  TFile *f_input = TFile::Open(f_name);
  TTree *t_input = (TTree*) f_input->Get("HWWTree");
  cout<<"opened file "<<f_name<<endl;
  
  TString f_id = f_name.Remove(f_name.Length()-5,f_name.Length());
  if(f_id.Contains("/")) f_id = f_id.Remove(0,f_id.Length()-6);

  TFile *f_output = new TFile("./"+f_id+"_hist.root","RECREATE");

  cout<<"create outfile"<<f_id<<endl;
  
  int nhistos = 5;
  histo *histos[nhistos];
  histos[0] = new histo("nJets_OR_T",10,0,10);
  histos[1] = new histo("nJets_OR_T_MV1_70",10,0,10);
  histos[2] = new histo("lep_Pt_0",100,0,500*GeV);
  histos[3] = new histo("total_leptons",5,0,5);
  histos[4] = new histo("nTaus_OR_Pt25",5,0,5);
  
  
  //  TH1F *h[nhistos];
  vector<vector<TH1F*> > h;
  //cuts,vars
  
  cout<<"created histo structs"<<endl;

  vector<TCut> cuts;
  cuts.push_back("(EF_mu24i_tight || EF_mu36_tight || EF_e24vhi_medium1 || EF_e60_medium1)");
  //  cuts.push_back("onelep_type>0");
  cuts.push_back("total_leptons==1");
  cuts.push_back("nTaus_OR_Pt25==2");
  //cuts.push_back("lep_Pt_0>10e3");
  cuts.push_back("passEventCleaning");
  vector<TString> cut_names;
  cut_names.push_back("trig");
  //cut_names.push_back("onelep_type");
  cut_names.push_back("NLep");
  cut_names.push_back("NTau");
  //cut_names.push_back("lepPt0");  
  cut_names.push_back("clean");
  TString prefix="1l2t";

  TCut current_cut = "";
  for(int c=0;c<cuts.size();++c) {
    current_cut+=cuts.at(c);
    vector<TH1F*> VecOfHistosOfVars;
    for(int i=0;i<nhistos;++i) {
      cout<<"loop: "<<i<<endl;
      TString h_name = prefix+"_"+cut_names.at(c)+"_"+histos[i]->var_name;
      cout<<"histo name "<<h_name<<endl;
      TH1F* h_temp = new TH1F(h_name,histos[i]->var_name,histos[i]->nbins,histos[i]->xmin,histos[i]->xmax);
      cout<<"TH1F created "<<h_temp->GetEntries()<<endl;
      cout<<t_input->Project(h_name,histos[i]->var_name,current_cut)<<endl;
      VecOfHistosOfVars.push_back(h_temp);
      cout<<"TH1F entries "<<h_temp->GetEntries()<<endl;
      h_temp->Write();
      //delete h;
    }//end histo loop
    h.push_back(VecOfHistosOfVars);
    VecOfHistosOfVars.clear();
  }//end cut loop
  
  cout<<"file write NAO"<<endl;
  //  f_output->Write();
  cout<<"file written "<<endl;
  f_output->Close();
  cout<<"file closed"<<endl;
  f_input->Close();
}
