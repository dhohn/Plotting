#include <iostream>
#include <fstream>
#include "TCanvas.h"
#include "TLegend.h"
#include "TH1.h"
#include "THStack.h"
#include "TTree.h"
#include "TFile.h"
#include "TString.h"
#include "TLatex.h"
#include "helperFunc.h"


using namespace std;

void normalise(TH1F* h){
  Double_t scale = 1./h->Integral("width");
  h->Scale(scale); 
  
}


Int_t Cut();

Float_t leadlepPt, subleadlepPt, Ptll, MET, Mll, lepplusID, lepminID, Mt, METRel;
Float_t lepPt0, lepPt1;

void plotVarMVA(TString, int, TString[], TString t= "F");

void plotVarMVA(TString var, TString f1, TString f2) {
  TString files[2];
  files[0]=f1;
  files[1]=f2;
  TString F = "F";
  plotVarMVA(var, 2, files, F);
}

void plotVarMVA(TString var,int nhyp, TString files[], TString type){
  bool debug = false;
  
  setHSG3Style();

  bool doKStest = false;

  ofstream myfile;
  myfile.open("./plots/nevents");


  TString hypothesis[nhyp];
  TString files_copy[nhyp];

  for(int ii=0;ii<nhyp;ii++) {
    files_copy[ii]=files[ii];
    hypothesis[ii] = files_copy[ii].Remove(files_copy[ii].Length()-5,files_copy[ii].Length());
  }
  //hypothesis[0] = "jhu";
  //hypothesis[1] = "madgraph";
  //hypothesis[2] = "pythia";
  //hypothesis[3] = "sm_null";
  //hypothesis[4] = "zprime_s1";

  TString variable = var;

  TString f_name;
  TFile* f_input;
  TTree* t_input;

  TH1F** histos = new TH1F*[nhyp];
  TString xtitle, ytitle;

  Double_t mva_weight, event_weight=1, doubleVar;
  Float_t floatVar;

  Float_t weight_sum, xmin=0, xmax=1;
  Float_t event_sum;
  Int_t nbins=20;

  if(variable.Contains("M")) {xmin = 0; xmax=100;}
  if(variable.Contains("Pt")) {xmin = 0; xmax=100;}
  if(variable.Contains("Phi") || variable.Contains("phi")) { xmin=-3.15; xmax=3.15; nbins=20;}
  if(variable.Contains("Theta") || variable.Contains("theta")) { xmin=0; xmax=3.15; nbins=20;}
  if(variable.Contains("mva") || variable.Contains("cos")) {xmin=-1; xmax=1;}
  if(variable.Contains("Eta")) {xmin=0; xmax=3.5;}
  if(variable.Contains("Mll")) {xmin = 0; xmax=100;}
  if(variable.Contains("Ptll")) {xmin = 20; xmax=150; nbins=15;}
  if(variable.Contains("Mt")) {xmin = 0; xmax=150;}
  if(variable.Contains("MET")) {xmin = 0; xmax=200;}
  if(variable.Contains("METRel")) {xmin = 0; xmax=150;}
  if(variable.Contains("DPhi") || variable.Contains("phi3") || variable.Contains("Psi")) {xmin = 0; xmax=3.15;}


  //fill histos[]
  for(int i=0;i<nhyp;i++) {
    
    //cout<<"."<<endl;
    //if(i==0) f_name = "/atlas/users/dhohn/workarea/ggF0/ggF0pnew.root";
    //else if(i==1) f_name = "./madgraph/spin0new.root";
    //else if(i==2) f_name = "./pythia/ggF0new.root";
    f_name = files[i];
    f_input = TFile::Open(f_name,"READ");
    t_input = (TTree*) f_input->Get("HWWTree");

    //t_input->SetBranchAddress("mva_weight", &mva_weight);
    //t_input->SetBranchAddress("EventWeight", &event_weight);
    if (variable.Contains("mva_weight")) {}//do nothing
    else if(variable.Contains("Ptll")) {floatVar=Ptll;}
    else if(variable.EqualTo("MET")) {floatVar=MET;}
    else if(variable.Contains("Mll")) {floatVar=Mll;}
    else if(variable.Contains("MT")) {floatVar=Mt;}
    else if(variable.Contains("METRel")) {floatVar=METRel;}
    else if(type=="D") t_input->SetBranchAddress(variable, &doubleVar);
    else if(type=="F") t_input->SetBranchAddress(variable, &floatVar);

    

    //t_input->SetBranchAddress("leadlepPt", &leadlepPt);
    //t_input->SetBranchAddress("subleadlepPt", &subleadlepPt);

    t_input->SetBranchAddress("lepPt0", &lepPt0);
    t_input->SetBranchAddress("lepPt1", &lepPt1);

    leadlepPt = lepPt0;
    subleadlepPt = lepPt1;
    if(lepPt0<lepPt1) {
      leadlepPt = lepPt1;
      subleadlepPt = lepPt0;
    }

    t_input->SetBranchAddress("Ptll", &Ptll);
    t_input->SetBranchAddress("MET", &MET);
    t_input->SetBranchAddress("METRel", &METRel);
    t_input->SetBranchAddress("Mll", &Mll);
    t_input->SetBranchAddress("lepID0", &lepplusID);
    t_input->SetBranchAddress("lepID1", &lepminID);
    t_input->SetBranchAddress("MT", &Mt);

    

    TH1F* h_variable = new TH1F("h_"+variable,variable,nbins,xmin,xmax);


    //make the axis titles
    TString unit;

    if(variable.Contains("phi") || variable.Contains("Phi") || variable.Contains("theta") || variable.Contains("Psi") ) {
      unit = "rad";
      xtitle = variable+" ["+unit+"]";
    }
    else if( variable.Contains("Pt") || variable.Contains("Mll") || variable.Contains("MT") || variable.Contains("METRel") || variable.Contains("W") ) {
      unit = "GeV";
      xtitle = variable+" ["+unit+"]";
    }
    else xtitle = variable;

    Float_t eventsperbin = (xmax-xmin)/nbins;
    char s[10];
    sprintf(s,"%g",eventsperbin);
    ytitle = "Events / ";
    ytitle+=s;
    ytitle+=" "+unit;

    //h_variable->SetBit(TH1::kCanRebin);
    h_variable->Sumw2();

    int ncount =0;


    //event loop to fill histograms
    int nentries = t_input->GetEntries();
    for(Long64_t k=0;k<nentries;k++) {
      t_input->GetEntry(k);

      if(variable.Contains("Ptll")) {floatVar=Ptll;}
      else if(variable.EqualTo("MET")) {floatVar=MET;}
      else if(variable.Contains("Mll")) {floatVar=Mll;}
      else if(variable.Contains("MT")) {floatVar=Mt;}
      else if(variable.EqualTo("METRel")) {floatVar=METRel;}

      if(Cut()>0) {
	ncount++;
	if(variable.Contains("mva_weight")) h_variable->Fill(mva_weight, event_weight);
	else if(type=="D") h_variable->Fill(doubleVar,event_weight);
	else if(type=="F") h_variable->Fill(floatVar,event_weight);	      
      }
    }//end entry loop


  
    
    histos[i] = h_variable;
    myfile<<hypothesis[i]<<" events: "<<ncount<<endl;
    cout<<hypothesis[i]<<" events: "<<ncount<<endl;

    //delete f_input;
    f_input->Close();
  }//end file loop

  if(debug) cout<<"Creating stacked h"<<endl;

  THStack* hs = new THStack("hs_"+variable,variable);

  TCanvas* c1 = new TCanvas(variable,"",800,800);
  
  //TLegend* legend = new TLegend(0.7,0.9,1,1);
  TLegend* legend = new TLegend(0.60, 0.70, 0.94, 0.90);
  legend->SetBorderSize(0);
  legend->SetTextFont(42);
  legend->SetTextSize(0.032);
  legend->SetFillColor(0);
  //legend->SetTextSize(.03);


  for(int h=0;h<nhyp;h++) {
    normalise(histos[h]);
    setHistoHSG3Style(histos[h]);
    //colours are 0white, 1black, 2red, 3green, 4blue, 5yellow, ...
    histos[h]->SetLineColor(h+1);
    legend->AddEntry(histos[h],hypothesis[h].Remove(hypothesis[h].Length()-3,hypothesis[h].Length()));
    hs->Add(histos[h]);

  }
 

  //plotting
  if(debug) cout<<"Plotting:"<<endl;

  hs->Draw("eNOSTACK");
  //legend->Draw();

  //  hs->GetHistogram()->GetXaxis()->SetTitle(xtitle);
  hs->GetHistogram()->GetYaxis()->SetTitle(ytitle);
  //stop axis title be printed over the label
  //hs->GetHistogram()->GetYaxis()->SetTitleOffset(1.7);
  hs->GetHistogram()->SetTitleSize(0.,"x");
  hs->GetHistogram()->SetTitleSize(0.05,"y"); 
  //hs->GetHistogram()->SetLabelSize(0.05,"x");
  hs->GetHistogram()->SetLabelSize(0.05,"y");  
  hs->GetHistogram()->SetTitleOffset(1.1,"x");
  hs->GetHistogram()->SetTitleOffset(1.1,"y"); 
  hs->GetHistogram()->SetLabelSize(0.,"x");

  Float_t hist_max = histos[0]->GetMaximum();
  hs->SetMaximum(hist_max*1.5);
  hs->SetMinimum(0.);

  if(debug) cout<<"\tCreating pads"<<endl;

  //lower pad for ratio
  TPad *pad2 = new TPad("pad2","",0,0,1,0.3);
  setsubPadStyle(pad2);
  pad2->SetGrid();
  pad2->Draw();
  pad2->cd();
  
  TH1F* h_ratio = (TH1F*) histos[0]->Clone();
  //h_ratio->Sumw2();
  h_ratio->Divide(histos[1]);
  setHistoHSG3Style(h_ratio);
  h_ratio->SetTitleSize(0.15,"x");
  h_ratio->SetTitleSize(0.15,"y");
  h_ratio->SetTitleOffset(0.45,"y");
  h_ratio->SetLabelSize(0.12,"x");
  h_ratio->SetLabelSize(0.12,"y");
  h_ratio->SetNdivisions(505,"y");
  h_ratio->SetMaximum(1.5);
  h_ratio->SetMinimum(0.5);
  h_ratio->SetTickLength(0.04,"y");
  h_ratio->SetTickLength(0.15,"x");
  h_ratio->GetXaxis()->SetTitle(xtitle);
  
  h_ratio->GetYaxis()->SetLabelSize(.1);
  h_ratio->Draw("E");
  gStyle->SetOptStat("");
  h_ratio->SetTitle("");
  c1->cd();

  //upper pad for actual plot
  TPad *pad1 = new TPad("pad1","",0,0.3,1,1);
  setPadStyle(pad1);
  pad1->Draw();
  pad1->cd();
  hs->Draw("eNOSTACK");  

  legend->Draw();

//KS test
  if(nhyp==2 && doKStest) {
    Double_t KS_value = histos[0]->KolmogorovTest(histos[1],"O");
    //if(isnan(KS_value)) KS_value = -999;
    TLatex *KS = new TLatex();
    KS->SetNDC();
    KS->SetTextFont(42);
    KS->SetTextSize(0.05);
    KS->SetTextColor(1);
    KS->DrawLatex(0.27, 0.2, Form("KS-test: %E",KS_value));
    cout<<KS_value<<endl;
  }


  if(debug) {
    cout<<"Saving png"<<endl;
    hs->GetHists()->Print();
  }
  
  c1->Print("./plots/"+variable+".png");
  
  myfile.close();
  //f_input->Close();
  //delete c1;
  //delete hs;
  //delete h_ratio;
  //delete legend;
  //delete *histos;
  //delete f_input;
  
  cout<<"."<<endl;
}


Int_t Cut()
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 

  //return 1;

  bool goodEvent = true;

  int emu = lepplusID*lepminID;
  //emu 143
  //ee 121
  //mumu 169
  //taue 165
  //taumu 195
  //tautau 225
  goodEvent = goodEvent && (emu==-143);// || emu==-195 || emu==-225);

  goodEvent = goodEvent && leadlepPt>25;
  goodEvent = goodEvent && subleadlepPt>15;
      //goodEvent = goodEvent && Ptll>20;
  //goodEvent = goodEvent && METRel>20;
      //goodEvent = goodEvent && Mt>60 && Mt<130;
  //goodEvent = goodEvent && Mll>10 && Mll<90;

  if(goodEvent)  return 1;
  else return -1;
}
