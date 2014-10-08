#include <iostream>
#include <fstream>
#include "TCanvas.h"
#include "TLegend.h"
#include "TH1.h"
#include "THStack.h"
#include "TString.h"
#include "TLatex.h"
#include "helperFunc.h"


using namespace std;

void normalise(TH1F* h){
  Double_t scale = 1./h->Integral("width");
  h->Scale(scale); 
  
}


void plotHistos(int nhyp, TH1F** histos, TString legends[], TString options=""){
  bool debug = false;
  
  setHSG3Style();

  bool fDoKStest  = options.Contains("KS");
  bool fNormalise = options.Contains("Norm");

  ofstream yieldfile;
  yieldfile.open("./plots/nevents");

  TString variable = histos[0]->GetTitle();

  TString xtitle = histos[0]->GetXaxis()->GetTitle();
  TString ytitle = histos[0]->GetYaxis()->GetTitle();

  //  TH1F** p_histos = new TH1F*[nhyp];
  
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
    if(fNormalise) normalise(histos[h]);
    setHistoHSG3Style(histos[h]);
    //colours are 0white, 1black, 2red, 3green, 4blue, 5yellow, ...
    histos[h]->SetLineColor(h+1);
    legend->AddEntry(histos[h],legends[h]);
    hs->Add(histos[h]);
    yieldfile<<legends[h]<<" "<<histos[h]->GetEntries()<<endl;
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
  hs->SetMaximum(hist_max*1.55);
  hs->SetMinimum(0.);

  if(nhyp==2) {

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

  }

  legend->Draw();

  //KS test
  if(nhyp==2 && fDoKStest) {
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
    //only works in CINT
    //hs->GetHists()->Print();
  }
  
  c1->Print("./plots/"+variable+".png");
  
  yieldfile.close();
  delete c1;
  delete hs;
  //delete h_ratio;
  delete legend;

}
