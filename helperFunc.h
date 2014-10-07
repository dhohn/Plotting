#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <math.h>
#include "TH2F.h"  
#include "TColor.h"
#include "TStyle.h"

void setStyle()
{

  gStyle->SetOptStat(0);

  gStyle->SetCanvasBorderMode(0); //frame color of canvas
  gStyle->SetCanvasColor(0);  //bkrd color of canvas
  gStyle->SetStatBorderSize(0); //frame style of stat-box 1

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleFillColor(0);
  gStyle->SetPadColor(0);
  gStyle->SetPadBorderMode(0);

  gStyle->SetLineWidth(3); // width of ticks
  gStyle->SetPadTickX(0); //1:ticks on upper,2: ticks+labels on upper xaxis
  gStyle->SetPadTickY(0);

  gStyle->SetPadLeftMargin(0.12); // 0.18
  gStyle->SetPadRightMargin(0.08);
  gStyle->SetPadTopMargin(0.07);
  gStyle->SetPadBottomMargin(0.17);
  gStyle->SetFrameLineWidth(2);
  gStyle->SetFrameFillColor(0);
  gStyle->SetPaintTextFormat(".2f");
  
  gStyle->SetTitleOffset(1.1,"X");
  gStyle->SetTitleOffset(1.1,"Y");
  gStyle->SetTextFont(42); 

}

void setHSG3Style()
{

  gStyle->SetOptStat(0);

  gStyle->SetFillColor(10);           
  gStyle->SetFrameFillColor(10);      
  gStyle->SetCanvasColor(10);         
  gStyle->SetPadColor(10);            
  gStyle->SetTitleFillColor(0);       
  gStyle->SetStatColor(10);   
    
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetFrameBorderMode(0); 
  gStyle->SetPadBorderMode(0);   
  gStyle->SetDrawBorder(0);      
  gStyle->SetTitleBorderSize(0);
    
  gStyle->SetFuncWidth(2);
  gStyle->SetHistLineWidth(2);
  gStyle->SetFuncColor(2);

  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadBottomMargin(0.16);
  gStyle->SetPadLeftMargin(0.16);
  gStyle->SetPadRightMargin(0.05);

  gStyle->SetPadTickX(1);        
  gStyle->SetPadTickY(1); 

  gStyle->SetFrameLineWidth(1);
  gStyle->SetLineWidth(1); // width of ticks

}
void setHistoStyle(TH1F* histo)
{
  
  histo->SetTitle("");
  histo->SetLineWidth(3);
  histo->SetTitleSize(0.07,"x");
  histo->SetTitleSize(0.07,"y");
  histo->SetNdivisions(505,"x"); 
  histo->SetNdivisions(505,"y"); 
  histo->SetLabelSize(0.07,"x"); 
  histo->SetLabelSize(0.07,"y");
  histo->SetTitleOffset(1.,"x"); 
  histo->SetTitleOffset(1.,"y");
}

void setHistoHSG3Style(TH1F* histo)
{
  
  histo->SetTitle("");
  //histo->SetLineWidth(0);
  histo->SetLineWidth(3);
  histo->SetTitleSize(0.07,"x");
  histo->SetTitleSize(0.07,"y");
  histo->SetNdivisions(510,"x");
  histo->SetNdivisions(510,"y");
  histo->SetLabelSize(0.05,"x");
  histo->SetLabelSize(0.05,"y");
  histo->SetTitleOffset(1.1,"x"); 
  histo->SetTitleOffset(1.1,"y");
}

void drawNorm(TString normtxt)
{
  TLatex *normbox = new TLatex();
  normbox->SetNDC();
  normbox->SetTextSize(0.04);
  normbox->SetTextAngle(90);
  normbox->DrawLatex(0.975,0.18,normtxt);
  normbox->Draw();
}

void drawOverflow(TH1 *h){
  Int_t nx1  = h->GetNbinsX()+1;
  Int_t nx  = h->GetNbinsX();
  Double_t x = h->GetBinContent(nx);
  Double_t x1 = h->GetBinContent(nx1);
  h->SetBinContent(nx,x+x1);
  h->SetBinContent(nx1,0);
  Double_t ex = h->GetBinError(nx);
  Double_t ex1 = h->GetBinError(nx1);  
  h->SetBinError(nx,ex+ex1);
  h->SetBinError(nx1,0);  
}

void setPadStyle(TPad *pad)
{
  pad->SetTopMargin(0.07);
  pad->SetBottomMargin(0.05);
  pad->SetFrameLineWidth(2);
  pad->SetLeftMargin(0.16);

}

void setsubPadStyle(TPad *pad)
{
  pad->SetBottomMargin(0.4);
  pad->SetFrameLineWidth(2);
  pad->SetLeftMargin(0.16);
}

void plot(TH1F* h_vbf, TH1F* h_ggf, TH1F* h_ggf_spin0, TH1F* h_ggf_spin2, TH1F* h_wh, TH1F* h_zh,  TH1F* h_top, TH1F* h_stop, TH1F* h_wjets, TH1F* h_ww, TH1F* h_wz, TH1F* h_zjets, TH1F* h_data,  TH1F* reldiff_sum_up, TH1F* reldiff_sum_dw, Int_t scale, TString mH, TString channel, TString jet_bin, TString cut_name, TString variable_name, TString variable_nameX, TString variable_nameY, TString histo_name, TString outputdir, bool doSys, Int_t doAnalysis){

  Bool_t doLog = false;
  Bool_t doPrelim = false;
  Bool_t doRatio = true;
  Bool_t doScaleBin = false;
  Bool_t plot_data = true;
  Bool_t doMVA = false; // do the default rate measurement plots
  Bool_t doVBF = false; // do the VBF analysis plotting
  Bool_t doSpin = false; // do properties analysis plotting
  Bool_t doSpinAgainstSpin = false; // do spin vs spin analysis

  if(doAnalysis==0) {
    doMVA=true;
    h_ggf_spin0=0;
    h_ggf_spin2=0;
  }
  else if(doAnalysis==1) doVBF=true;
  else if(doAnalysis==2){
    doSpin=true;
    h_ggf=0;
  }
  else if(doAnalysis==3) {
    doSpin=true;
    doSpinAgainstSpin=true;
    h_ggf=0;
  }
  else{
		std::cout << "#code/include/helperFunc.h:: plot(): Fatal error when choosing analysis." << std::endl;
    return;
  }
  
  if(doMVA){
    h_ggf->Add(h_vbf);
    h_ggf->Add(h_wh);
    h_ggf->Add(h_zh);
  }
  else if(doVBF) {
    h_vbf->Add(h_wh);
    h_vbf->Add(h_zh); 
  }
  // if we're performing spin analysis we ignore VBF/ZH/WH production
  
  Int_t canvX = 0;
  Int_t canvY = 0;
  if(doRatio) {canvX=800; canvY=800;}
  else  {canvX=800; canvY=600;}
  TString Lumi = "13";
	setHSG3Style();
	//define canvas
	TCanvas *canvas = new TCanvas(histo_name,"",canvX,canvY);
	THStack *h_stacked = new THStack(histo_name,"");
          
	h_top->SetFillColor(219);
	h_stop->SetFillColor(218);
	h_wjets->SetFillColor(227);
	h_ww->SetFillColor(kBlue-6);
	h_wz->SetFillColor(222);
	h_zjets->SetFillColor(210);

	h_data->SetLineColor(kBlack);
	h_top->SetLineColor(kBlack); 
	h_stop->SetLineColor(kBlack); 
	h_wjets->SetLineColor(kBlack);
	h_ww->SetLineColor(kBlack);
	h_wz->SetLineColor(kBlack);
	h_zjets->SetLineColor(kBlack);
	h_data->SetMarkerStyle(20);
	if(plot_data) h_data->SetMarkerSize(0.9); //1.2
	else h_data->SetMarkerSize(0);
	h_data->SetMarkerColor(kBlack);
	if(doVBF) {
	  h_vbf->SetLineColor(kRed);
	  h_ggf->SetLineColor(kBlue);
	} 
	else if(doMVA) h_ggf->SetLineColor(kRed);
	else if(doSpin){
	  h_ggf_spin0->SetLineColor(kRed);
	  h_ggf_spin2->SetLineColor(kBlue);
	}
	if(doScaleBin){
		h_data->SetBinContent(1,h_data->GetBinContent(1)/10);
		h_data->SetBinError(1,h_data->GetBinError(1)/10);
		h_top->SetBinContent(1,h_top->GetBinContent(1)/10);
		h_top->SetBinError(1,h_top->GetBinError(1)/10);
		h_stop->SetBinContent(1,h_stop->GetBinContent(1)/10);
		h_stop->SetBinError(1,h_stop->GetBinError(1)/10);
		h_wjets->SetBinContent(1,h_wjets->GetBinContent(1)/10);
		h_wjets->SetBinError(1,h_wjets->GetBinError(1)/10);
		h_ww->SetBinContent(1,h_ww->GetBinContent(1)/10);
		h_ww->SetBinError(1,h_ww->GetBinError(1)/10);
		h_wz->SetBinContent(1,h_wz->GetBinContent(1)/10);
		h_wz->SetBinError(1,h_wz->GetBinError(1)/10);
		h_zjets->SetBinContent(1,h_zjets->GetBinContent(1)/10);
		h_zjets->SetBinError(1,h_zjets->GetBinError(1)/10);
		if(h_vbf) h_vbf->SetBinContent(1,h_vbf->GetBinContent(1)/10);
		if(h_vbf) h_vbf->SetBinError(1,h_vbf->GetBinError(1)/10);
		if(h_ggf) h_ggf->SetBinContent(1,h_ggf->GetBinContent(1)/10);
		if(h_ggf) h_ggf->SetBinError(1,h_ggf->GetBinError(1)/10);
		if(h_ggf_spin0) h_ggf_spin0->SetBinContent(1,h_ggf_spin0->GetBinContent(1)/10);
		if(h_ggf_spin0) h_ggf_spin0->SetBinError(1,h_ggf_spin0->GetBinError(1)/10);
		if(h_ggf_spin2) h_ggf_spin2->SetBinContent(1,h_ggf_spin2->GetBinContent(1)/10);
		if(h_ggf_spin2) h_ggf_spin2->SetBinError(1,h_ggf_spin2->GetBinError(1)/10);
		if(h_wh) h_wh->SetBinContent(1,h_wh->GetBinContent(1)/10);
		if(h_wh) h_wh->SetBinError(1,h_wh->GetBinError(1)/10);
		if(h_zh) h_zh->SetBinContent(1,h_zh->GetBinContent(1)/10);
		if(h_zh) h_zh->SetBinError(1,h_zh->GetBinError(1)/10);

		if(reldiff_sum_up) reldiff_sum_up->SetBinContent(1,reldiff_sum_up->GetBinContent(1)/10);
		if(reldiff_sum_up) reldiff_sum_up->SetBinError(1,reldiff_sum_up->GetBinError(1)/10);
		if(reldiff_sum_dw) reldiff_sum_dw->SetBinContent(1,reldiff_sum_dw->GetBinContent(1)/10);
		if(reldiff_sum_dw) reldiff_sum_dw->SetBinError(1,reldiff_sum_dw->GetBinError(1)/10);

	}
	//overflow bins
	drawOverflow(h_top);
	drawOverflow(h_stop);
	drawOverflow(h_wjets);
	drawOverflow(h_ww);
	drawOverflow(h_wz);
	drawOverflow(h_zjets);
	drawOverflow(h_data);
	if(h_vbf) drawOverflow(h_vbf);  
 	if(h_ggf) drawOverflow(h_ggf);           
	if(h_ggf_spin0) drawOverflow(h_ggf_spin0);
	if(h_ggf_spin2) drawOverflow(h_ggf_spin2);

	TH1F* h_ratio =(TH1F*) h_data->Clone();
	TH1F* h_sum =(TH1F*) h_top->Clone();
	//set histo style
	setHistoHSG3Style(h_top);
	setHistoHSG3Style(h_stop);
	setHistoHSG3Style(h_wjets);
	setHistoHSG3Style(h_ww);
	setHistoHSG3Style(h_wz);
	setHistoHSG3Style(h_zjets);
	setHistoHSG3Style(h_data);
	if(h_vbf) setHistoHSG3Style(h_vbf);
	if(h_ggf) setHistoHSG3Style(h_ggf);
	if(h_ggf_spin0) setHistoHSG3Style(h_ggf_spin0);
	if(h_ggf_spin2) setHistoHSG3Style(h_ggf_spin2);
	if(h_vbf) h_vbf->SetLineWidth(3);
	if(h_vbf) h_vbf->SetLineStyle(2);
	if(h_ggf) h_ggf->SetLineWidth(3);
	if(h_ggf) h_ggf->SetLineStyle(2);
	if(h_ggf_spin0) h_ggf_spin0->SetLineWidth(3);
	if(h_ggf_spin0) h_ggf_spin0->SetLineStyle(2);
	if(h_ggf_spin2) h_ggf_spin2->SetLineWidth(3);
	if(h_ggf_spin2) h_ggf_spin2->SetLineStyle(2);
	setHistoHSG3Style(h_ratio);

	//
	h_ratio->SetMarkerStyle(20);
	h_ratio->SetMarkerColor(kBlack);
	h_ratio->SetMarkerSize(0.8); //1.2
	
	//stack bgd histos
	h_stacked->Add(h_wjets);
	h_stacked->Add(h_zjets);
	h_stacked->Add(h_stop);
	h_stacked->Add(h_top);
	h_stacked->Add(h_wz);
	h_stacked->Add(h_ww);

	//add bgr histos
	h_sum->Add(h_stop);
	h_sum->Add(h_wjets);
	h_sum->Add(h_ww);
	h_sum->Add(h_wz);
	h_sum->Add(h_zjets);
	h_sum->SetFillColor(kWhite);
	h_sum->SetLineColor(kWhite);

	Float_t hist_max = h_data->GetMaximum();
	if(hist_max<h_stacked->GetMaximum()) hist_max=h_stacked->GetMaximum();
	if(doLog) h_data->SetMaximum(hist_max*10.0);
	else h_data->SetMaximum(hist_max*1.8);
	h_stacked->SetMaximum(1.8*hist_max);
 	h_stacked->SetMinimum(0);         
	//New ratio plot
	h_ratio->Divide(h_sum);
	h_ratio->SetTitleSize(0.15,"x");
	h_ratio->SetTitleSize(0.15,"y");
	h_ratio->SetTitleOffset(0.45,"y");
	h_ratio->SetLabelSize(0.12,"x");
	h_ratio->SetLabelSize(0.12,"y");
	h_ratio->SetNdivisions(505,"y"); 
	//draw error
	TH1F* h_sum_err = (TH1F*) h_sum->Clone();
	for(int iBin=0;iBin<=h_sum_err->GetNbinsX()+1;iBin++){
	  Double_t err_up = 0;
	  Double_t err_dw = 0;
	  if(reldiff_sum_up) err_up = reldiff_sum_up->GetBinContent(iBin);
	  if(reldiff_sum_dw) err_dw = reldiff_sum_dw->GetBinContent(iBin);
	  Double_t err_add = err_up/4+err_dw/4+0.039*0.039;
	  //std::cout << "err_up = " << err_up << std::endl;
	  //std::cout << "err_dw = " << err_dw << std::endl;
	  //std::cout << "stat only = " << h_sum->GetBinError(iBin) << std::endl;
	  h_sum_err->SetBinError(iBin,h_sum->GetBinError(iBin)+sqrt(err_add));
	  //std::cout << "all = " << h_sum_err->GetBinError(iBin) << std::endl;
	}		
	h_sum_err->SetMarkerSize(0);
	h_sum_err->SetFillColor(14);
	h_sum_err->SetLineColor(kBlack);
	h_sum_err->SetFillStyle(3254);            
	h_sum_err->SetLineWidth(0);
	
	//scale signal
 	if(h_vbf) h_vbf->Scale(scale);
 	if(h_ggf) h_ggf->Scale(scale);
 	if(h_ggf_spin0) h_ggf_spin0->Scale(scale);
 	if(h_ggf_spin2) h_ggf_spin2->Scale(scale);
	
	if(doRatio){
	  TPad *pad2 = new TPad("pad2","",0,0,1,0.3);
	  setsubPadStyle(pad2);
	  pad2->SetGrid();
	  pad2->Draw();
	  pad2->cd();
	  h_ratio->SetMaximum(2);
	  h_ratio->SetMinimum(0.);            
	  h_ratio->Draw("E");
	  h_ratio->GetYaxis()->SetTitle("Data/Bkg");
	  h_ratio->GetXaxis()->SetTitle(variable_nameX);
	  h_ratio->SetTickLength(0.04,"y");
	  h_ratio->SetTickLength(0.15,"x");
	  canvas->cd();
	  
	  TPad *pad1 = new TPad("pad1","",0,0.3,1,1);
	  setPadStyle(pad1);
	  pad1->Draw();
	  pad1->cd();
	  h_data->SetMinimum(0.); 
	  h_data->Draw("E");
	  h_data->SetLabelSize(0.,"x");
	  h_data->GetYaxis()->SetTitle(variable_nameY);
	  h_stacked->Draw("hist same"); 
	  h_sum_err->Draw("E2 same");
	  if(doVBF){
	    h_vbf->Draw("hist same");
	    h_ggf->Draw("hist same");
	  } 
	  else if(doMVA) h_ggf->Draw("hist same");
	  else if(doSpin) {
	    h_ggf_spin0->Draw("hist same");
	    h_ggf_spin2->Draw("hist same");
	  }
	  
	  //draw data
	  if(plot_data) h_data->Draw("E same");
	  if(doLog) pad1->SetLogy();
	} else {
	  if(plot_data) {
	    h_data->Draw("E");
	    h_stacked->Draw("hist same");
	  } else {
	    h_stacked->Draw("hist");
	  }
	  h_sum_err->Draw("E2 same");
	  if(doVBF){
	    h_ggf->Draw("hist same");
	    h_vbf->Draw("hist same");
	  }
	  else if(doMVA) h_ggf->Draw("hist same");
	  else if(doSpin){
	    h_ggf_spin0->Draw("hist same");
	    h_ggf_spin2->Draw("hist same");
	  }
	 	  
	  h_data->GetXaxis()->SetTitle(variable_nameX);
	  h_data->GetYaxis()->SetTitle(variable_nameY);
	  
	  h_stacked->GetXaxis()->SetTitle(variable_nameX);
	  h_stacked->GetYaxis()->SetTitle(variable_nameY);  
	  h_stacked->GetHistogram()->SetTitleSize(0.05,"x");
	  h_stacked->GetHistogram()->SetTitleSize(0.05,"y"); 
	  h_stacked->GetHistogram()->SetLabelSize(0.06,"x");
	  h_stacked->GetHistogram()->SetLabelSize(0.06,"y");    
	  h_stacked->GetHistogram()->SetTitleOffset(1.1,"X");
	  h_stacked->GetHistogram()->SetTitleOffset(1.1,"Y"); 
	  if(plot_data) h_data->Draw("E same");
	  
	  if(doLog) canvas->SetLogy();
	}
	
	//draw legend
	TLegend *leg = new TLegend(0.60, 0.70, 0.94, 0.90);
	leg->SetBorderSize(0);
	leg->SetTextFont(42);
	leg->SetTextSize(0.032);
	leg->SetFillColor(0);
	leg->SetNColumns(2);
	if(plot_data) leg->AddEntry(h_data," Data","lep");
	if(doSys) leg->AddEntry(h_sum_err, "SM (sys #oplus stat)", "lf");
	else leg->AddEntry(h_sum_err, "SM (stat)", "lf");
	leg->AddEntry(h_ww," WW","f");
	leg->AddEntry(h_wz," WZ/ZZ/W#gamma ","f");
	leg->AddEntry(h_top," t#bar{t}","f");
	leg->AddEntry(h_stop," Single Top","f");
	leg->AddEntry(h_zjets," Z+jets","f");
	leg->AddEntry(h_wjets," W+jets","f");
	leg->AddEntry(h_sum," ","f");
	if(doVBF){
	  if(scale != 1) leg->AddEntry(h_vbf,"VBF/VH ["+mH+"]x"+Form("%d",scale),"f");
	  else leg->AddEntry(h_vbf,"VBF/VH ["+mH+"]","f");
	  if(scale != 1) leg->AddEntry(h_ggf,"ggF ["+mH+"]x"+Form("%d",scale),"f");
	  else leg->AddEntry(h_ggf,"ggF ["+mH+"]","f");
	} else if(doMVA) {
	  if(scale != 1) leg->AddEntry(h_ggf,"H ["+mH+"]x"+Form("%d",scale),"f");
	  else leg->AddEntry(h_ggf,"H ["+mH+"]","f");
	}
	else if(doSpin){
	  if(scale != 1) {
	    leg->AddEntry(h_ggf_spin0,"H 0^{+}["+mH+"]x"+Form("%d",scale),"f");
	    leg->AddEntry(h_ggf_spin2,"H 2^{+}["+mH+"]x"+Form("%d",scale),"f");

	  }
	  else {
	    leg->AddEntry(h_ggf_spin0,"H 0^{+}["+mH+"]","f");
	    leg->AddEntry(h_ggf_spin2,"H 2^{+}["+mH+"]","f");
	 
	  }
	}

	leg->Draw();
	if(doPrelim){
	  TLatex * prelim = new TLatex();
	  prelim->SetNDC();
	  prelim->SetTextFont(42);
	  prelim->SetTextColor(1);
	  prelim->SetTextSize(0.06);
	  prelim->DrawLatex(0.22, 0.86, "#font[72]{ATLAS} Preliminary"); //0.26
	} else {
	  TLatex * prelim = new TLatex();
	  prelim->SetNDC();
	  prelim->SetTextFont(42);
	  prelim->SetTextColor(1);
	  prelim->SetTextSize(0.06);
	  prelim->DrawLatex(0.22, 0.86, "#font[72]{ATLAS} Internal"); //0.26
	}
	// TString normtxt="MC normalized to SM prediction";
	// drawNorm(normtxt);
	TLatex * lumi = new TLatex();
	lumi->SetNDC();
	lumi->SetTextFont(42);
	lumi->SetTextSize(0.04);
	lumi->SetTextColor(1);
	lumi->DrawLatex(0.2, 0.79, "#sqrt{s} = 8 TeV,  #int L dt = "+Lumi+" fb^{-1}"); //0.25
	TLatex * chan = new TLatex();
	chan->SetNDC();
	chan->SetTextFont(42);
	chan->SetTextSize(0.04);
	chan->SetTextColor(1);
	if( jet_bin == "0jet" ) {
	  if( channel=="ee" ) chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow e#nue#nu + 0 jet");
	  else if(channel=="emu" )  chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow e#nu#mu#nu + 0 jet");
	  else if(channel=="mue" )  chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow #mu#nue#nu + 0 jet");
	  else if(channel=="mumu" )  chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow #mu#nu#mu#nu + 0 jet");   
	  else if(channel=="all" )  chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow l#nul#nu + 0 jet"); 
	  else if(channel=="emu_all" )  chan->DrawLatex(0.19, 0.71, "H #rightarrow WW^{(*)} #rightarrow e#nu#mu#nu+#mu#nue#nu + 0 jet");                
	} else if( jet_bin == "1jet" ) {
	  if( channel=="ee" ) chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow e#nue#nu + 1 jet");
	  else if(channel=="emu" )  chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow e#nu#mu#nu + 1 jet");
	  else if(channel=="mue" )  chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow #mu#nue#nu + 1 jet");
	  else if(channel=="mumu" )  chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow #mu#nu#mu#nu + 1 jet");   
	  else if(channel=="all" )  chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow l#nul#nu + 1 jet"); 
	  else if(channel=="emu_all" )  chan->DrawLatex(0.19, 0.71, "H #rightarrow WW^{(*)} #rightarrow e#nu#mu#nu+#mu#nue#nu + 1 jet"); 
	} else if( jet_bin == "2jet" ) {
	  if( channel=="ee" ) chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow e#nue#nu + 2 jet");
	  else if(channel=="emu" )  chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow e#nu#mu#nu + 2 jet");
	  else if(channel=="mue" )  chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow #mu#nue#nu + 2 jet");
	  else if(channel=="mumu" )  chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow #mu#nu#mu#nu + 2 jet");   
	  else if(channel=="all" )  chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow l#nul#nu + 2 jet"); 
	  else if(channel=="emu_all" )  chan->DrawLatex(0.19, 0.71, "H #rightarrow WW^{(*)} #rightarrow e#nu#mu#nu+#mu#nue#nu + 2 jet"); 
	}
	
	canvas->cd();
	
	if(doLog) {
	  if(doRatio) canvas->Print(outputdir+mH+"_"+variable_name+jet_bin+"_"+channel+"_ratiolog.eps");
	  else canvas->Print(outputdir+mH+"_"+variable_name+jet_bin+"_"+channel+"_log.eps");
	  if(doRatio) canvas->Print(outputdir+mH+"_"+variable_name+jet_bin+"_"+channel+"_ratiolog.pdf");
	  else canvas->Print(outputdir+mH+"_"+variable_name+jet_bin+"_"+channel+"_log.pdf");
	} else if(doScaleBin) {
	  TLatex * leg_scale = new TLatex();
	  leg_scale->SetNDC();
	  leg_scale->SetTextFont(42);
	  leg_scale->SetTextSize(0.032);
	  leg_scale->SetTextColor(1);
	  leg_scale->DrawLatex(0.22, 0.63, "bin 1 scaled by 0.1");
	  if(cut_name!="") cut_name = cut_name+"_";
	  if(doRatio) canvas->Print(outputdir+mH+"_"+cut_name+variable_name+jet_bin+"_"+channel+"_ratioScaleBin.eps");
	  else canvas->Print(outputdir+mH+"_"+cut_name+variable_name+jet_bin+"_"+channel+"_ScaleBin.eps");
	  if(doRatio) canvas->Print(outputdir+mH+"_"+cut_name+variable_name+jet_bin+"_"+channel+"_ratioScaleBin.pdf");
	  else canvas->Print(outputdir+mH+"_"+cut_name+variable_name+jet_bin+"_"+channel+"_ScaleBin.pdf");
	  
	} else {  
	  
	  if(doRatio)  canvas->Print(outputdir+mH+"_"+cut_name+variable_name+jet_bin+"_"+channel+"_ratio.eps");
	  else canvas->Print(outputdir+mH+"_"+cut_name+variable_name+jet_bin+"_"+channel+".eps");
	  if(doRatio) canvas->Print(outputdir+mH+"_"+cut_name+variable_name+jet_bin+"_"+channel+"_ratio.pdf");
	  else canvas->Print(outputdir+mH+"_"+cut_name+variable_name+jet_bin+"_"+channel+".pdf");
	}
	
	
	delete canvas;
	delete h_stacked;
	delete h_ratio;
	delete h_sum;
	delete lumi; 
	delete chan;
	delete leg;
}
void print_cutflow(TH1F* h_signal, TH1F* h_signal2, TH1F* h_top, TH1F* h_stop, TH1F* h_wjets, TH1F* h_ww, TH1F* h_wz, TH1F* h_zjets, TH1F* h_data, TString cut_name, Int_t doAnalysis){

	Double_t err_signal;
	Double_t n_signal = h_signal->IntegralAndError(0,h_signal->GetNbinsX()+1,err_signal);

	Double_t err_signal2, n_signal2=0.;
	if(h_signal2)  n_signal2 = h_signal2->IntegralAndError(0,h_signal2->GetNbinsX()+1,err_signal2);

	Double_t err_top;
	Double_t n_top = h_top->IntegralAndError(0,h_top->GetNbinsX()+1,err_top);  
	Double_t err_stop;
	Double_t n_stop = h_stop->IntegralAndError(0,h_stop->GetNbinsX()+1,err_stop);  
	Double_t err_wjets;
	Double_t n_wjets = h_wjets->IntegralAndError(0,h_wjets->GetNbinsX()+1,err_wjets);  
	Double_t err_zjets;
	Double_t n_zjets = h_zjets->IntegralAndError(0,h_zjets->GetNbinsX()+1,err_zjets);
	Double_t err_ww;
	Double_t n_ww = h_ww->IntegralAndError(0,h_ww->GetNbinsX()+1,err_ww);  
	Double_t err_wz;
	Double_t n_wz = h_wz->IntegralAndError(0,h_wz->GetNbinsX()+1,err_wz); 
	Double_t err_data;
	Double_t n_data = h_data->IntegralAndError(0,h_data->GetNbinsX()+1,err_data);  
	TH1F* h_total_bkd(0); 
	h_total_bkd = (TH1F*)h_top->Clone();
	h_total_bkd->Add(h_stop);	
	h_total_bkd->Add(h_wjets);
	h_total_bkd->Add(h_ww);
	h_total_bkd->Add(h_wz);
	h_total_bkd->Add(h_zjets);
	Double_t err_total_bkd;
	Double_t n_total_bkd = h_total_bkd->IntegralAndError(0,h_total_bkd->GetNbinsX()+1,err_total_bkd);
	Double_t err_ratio = sqrt(pow(err_data/n_total_bkd,2) + pow(err_total_bkd*n_data/(n_total_bkd*n_total_bkd),2));
	if(doAnalysis==0){
	  std::cout << cut_name << std::setiosflags(std::ios::fixed) << std::setprecision(2) << " & " << n_signal << " $\\pm$ " << err_signal << 
	    " & " << n_ww << " $\\pm$ " << err_ww <<
	  " & " << n_wz << " $\\pm$ " << err_wz <<
	  " & " << n_top << " $\\pm$ " << err_top <<
	  " & " << n_stop << " $\\pm$ " << err_stop <<
	  " & " << n_zjets << " $\\pm$ " << err_zjets <<
	  " & " << n_wjets << " $\\pm$ " << err_wjets <<
	  " & " << n_total_bkd << " $\\pm$ " << err_total_bkd <<
	  " & " << n_data << " $\\pm$ " << err_data <<
		" & " << n_data/n_total_bkd << " $\\pm$ " << err_ratio << "\\\\"	<< std::endl;

	} else if(doAnalysis ==1){

	  std::cout << cut_name << std::setiosflags(std::ios::fixed) << std::setprecision(2) << " & " << n_signal << " $\\pm$ " << err_signal << 
	   " & " << n_signal2 << " $\\pm$ " << err_signal2 <<
	    " & " << n_ww << " $\\pm$ " << err_ww <<
	  " & " << n_wz << " $\\pm$& " << err_wz <<
	  " & " << n_top << " $\\pm$ " << err_top <<
	  " & " << n_stop << " $\\pm$ " << err_stop <<
	  " & " << n_zjets << " $\\pm$ " << err_zjets <<
	  " & " << n_wjets << " $\\pm$ " << err_wjets <<
	  " & " << n_total_bkd << " $\\pm$ " << err_total_bkd <<
	  " & " << n_data << " $\\pm$ " << err_data <<
		" & " << n_data/n_total_bkd << " $\\pm$ " << err_ratio << "\\\\"	<< std::endl;
	}
	else if(doAnalysis == 2){
	  std::cout << cut_name << std::setiosflags(std::ios::fixed) << std::setprecision(2) << " & " << n_signal << " $\\pm$ " << err_signal << 
	    " & " << n_signal2 << " $\\pm$ " << err_signal2 <<  
	    " & " << n_ww << " $\\pm$ " << err_ww <<
	  " & " << n_wz << " $\\pm$ " << err_wz <<
	  " & " << n_top << " $\\pm$ " << err_top <<
	  " & " << n_stop << " $\\pm$ " << err_stop <<
	  " & " << n_zjets << " $\\pm$ " << err_zjets <<
	  " & " << n_wjets << " $\\pm$ " << err_wjets <<
	  " & " << n_total_bkd << " $\\pm$ " << err_total_bkd <<
	  " & " << n_data << " $\\pm$ " << err_data <<
		" & " << n_data/n_total_bkd << " $\\pm$ " << err_ratio << "\\\\"	<< std::endl;
	}
	
}

void plot_shapes(TH1F* h_vbf, TH1F* h_ggf, TH1F* h_ggf_spin0, TH1F* h_ggf_spin2, TH1F* h_wh, TH1F* h_zh, TH1F* h_top, TH1F* h_stop, TH1F* h_wjets, TH1F* h_ww, TH1F* h_wz, TH1F* h_zjets, TString mH, TString channel, TString jet_bin, TString cut_name, TString variable_name, TString variable_nameX, TString variable_nameY, TString histo_name, TString outputdir, Int_t doAnalysis){


  Bool_t doPrelim = false;
  Bool_t doMVA = false; // do the default rate measurement plots
  Bool_t doVBF = false; // do the VBF analysis plotting
  Bool_t doSpin = false; // do properties analysis plotting
  Bool_t doSpinAgainstSpin = false; // do spin vs spin analysis


  if(doAnalysis==0) {
    doMVA=true;
    h_ggf_spin0=0;
    h_ggf_spin2=0;
  }
  else if(doAnalysis==1){
    doVBF=true;
  }
  else if(doAnalysis==2){
    doSpin=true;
    h_ggf=0;
  }
  else if(doAnalysis==3) {
    doSpin=true;
    doSpinAgainstSpin=true;
    h_ggf=0;
  }
  else{
		std::cout << "#code/include/helperFunc.h::plot_shapes() : Fatal error when choosing analysis." << std::endl;
    return;
  }


  Int_t canvX = 800;
  Int_t canvY = 600;
  TString Lumi = "13";
  setHSG3Style();
  
  if(doVBF) {
    h_vbf->Add(h_wh);
    h_vbf->Add(h_zh);
  } 
  else if(doMVA){
    h_ggf->Add(h_vbf);
    h_ggf->Add(h_wh);
    h_ggf->Add(h_zh);
  }
  if(doSpin){
		h_ww->Add(h_wz);
		h_top->Add(h_stop);
	}

  //define canvas
  TCanvas *canvas = new TCanvas(histo_name,"",canvX,canvY);
  
  h_top->SetLineColor(219); 
  h_stop->SetLineColor(218); 
  h_wjets->SetLineColor(227);
  h_ww->SetLineColor(kBlue-6);
  h_wz->SetLineColor(222);
  h_zjets->SetLineColor(210);
  if(doVBF){
    h_vbf->SetLineColor(kRed);
    h_ggf->SetLineColor(kBlue);	
  } else if(doMVA) h_ggf->SetLineColor(kRed);
  else if(doSpin){
    h_ggf_spin0->SetLineColor(kRed);
    h_ggf_spin2->SetLineColor(kBlue);
  }
  
  
  h_top->SetFillColor(0); 
  h_stop->SetFillColor(0); 
  h_wjets->SetFillColor(0);
  h_ww->SetFillColor(0);
  h_wz->SetFillColor(0);
  h_zjets->SetFillColor(0);
  h_vbf->SetFillColor(0);
  if(h_ggf) h_ggf->SetFillColor(0);
  if(h_ggf_spin0) h_ggf_spin0->SetFillColor(0);
  if(h_ggf_spin2) h_ggf_spin2->SetFillColor(0);
  

  //set histo style
  setHistoHSG3Style(h_top);
  setHistoHSG3Style(h_stop);
  setHistoHSG3Style(h_wjets);
  setHistoHSG3Style(h_ww);
  setHistoHSG3Style(h_wz);
  setHistoHSG3Style(h_zjets);
  setHistoHSG3Style(h_vbf);
  if(h_ggf) setHistoHSG3Style(h_ggf);
  if(h_ggf_spin0) setHistoHSG3Style(h_ggf_spin0);
  if(h_ggf_spin2) setHistoHSG3Style(h_ggf_spin2);
   std::cout << "TP3" << std::endl; 
  h_top->SetLineWidth(3); 
  h_stop->SetLineWidth(3); 
  h_wjets->SetLineWidth(3);
  h_ww->SetLineWidth(3);
  h_wz->SetLineWidth(3);
  h_zjets->SetLineWidth(3);
  h_vbf->SetLineWidth(3);
  if(h_ggf) h_ggf->SetLineWidth(3);
  if(h_ggf_spin0) h_ggf_spin0->SetLineWidth(3);
  if(h_ggf_spin2) h_ggf_spin2->SetLineWidth(3);
  
  drawOverflow(h_top);
  drawOverflow(h_stop);
  drawOverflow(h_wjets);
  drawOverflow(h_ww);
  drawOverflow(h_wz);
  drawOverflow(h_zjets);
  drawOverflow(h_vbf);            
  if(h_ggf) drawOverflow(h_ggf);  
  if(h_ggf_spin0) drawOverflow(h_ggf_spin0);  
  if(h_ggf_spin2) drawOverflow(h_ggf_spin2);  
  
  h_top->Scale(1/h_top->Integral(0,h_top->GetNbinsX()+1)); 
  h_stop->Scale(1/h_stop->Integral(0,h_stop->GetNbinsX()+1)); 
  h_wjets->Scale(1/h_wjets->Integral(0,h_wjets->GetNbinsX()+1));
  h_ww->Scale(1/h_ww->Integral(0,h_ww->GetNbinsX()+1));
  h_wz->Scale(1/h_wz->Integral(0,h_wz->GetNbinsX()+1));
  h_zjets->Scale(1/h_zjets->Integral(0,h_zjets->GetNbinsX()+1));
  h_vbf->Scale(1/h_vbf->Integral(0,h_vbf->GetNbinsX()+1));
  if(h_ggf) h_ggf->Scale(1/h_ggf->Integral(0,h_ggf->GetNbinsX()+1));
  if(h_ggf_spin0) h_ggf_spin0->Scale(1/h_ggf_spin0->Integral(0,h_ggf_spin0->GetNbinsX()+1));
  if(h_ggf_spin2) h_ggf_spin2->Scale(1/h_ggf_spin2->Integral(0,h_ggf_spin2->GetNbinsX()+1));
  
  Float_t hist_max = h_top->GetMaximum();
  if(hist_max<h_stop->GetMaximum()) hist_max=h_stop->GetMaximum();
  if(hist_max<h_wjets->GetMaximum()) hist_max=h_wjets->GetMaximum();
  if(hist_max<h_ww->GetMaximum()) hist_max=h_ww->GetMaximum();
  if(hist_max<h_wz->GetMaximum()) hist_max=h_wz->GetMaximum();
  if(hist_max<h_zjets->GetMaximum()) hist_max=h_zjets->GetMaximum();
  if(hist_max<h_vbf->GetMaximum()) hist_max=h_vbf->GetMaximum();
  if(h_ggf) if(hist_max<h_ggf->GetMaximum()) hist_max=h_ggf->GetMaximum();
  if(h_ggf_spin0) if(hist_max<h_ggf_spin0->GetMaximum()) hist_max=h_ggf_spin0->GetMaximum();
  if(h_ggf_spin2) if(hist_max<h_ggf_spin2->GetMaximum()) hist_max=h_ggf_spin2->GetMaximum();
  h_top->SetMaximum(1.6*hist_max);   
  h_top->SetMinimum(0);         
  
  h_top->Draw("hist"); 
  if(!doSpin) h_stop->Draw("hist same"); 
  h_wjets->Draw("hist same");
  h_ww->Draw("hist same");
  if(!doSpin) h_wz->Draw("hist same");
  h_zjets->Draw("hist same");
  if(doVBF){
    h_vbf->Draw("hist same");
		h_ggf->Draw("hist same");
	} else if(doMVA){
		h_ggf->Draw("hist same");
	}
	else if(doSpin){
	  h_ggf_spin0->Draw("hist same");
	  h_ggf_spin2->Draw("hist same");
	}
	h_top->GetXaxis()->SetTitle(variable_nameX);
	h_top->GetYaxis()->SetTitle(variable_nameY); 
	h_top->SetTitleSize(0.05,"x");
	h_top->SetTitleSize(0.05,"y"); 
	h_top->SetLabelSize(0.06,"x");
	h_top->SetLabelSize(0.06,"y");     
	h_top->SetTitleOffset(1.1,"x"); 
	
	
	//draw legend
	TLegend *leg = new TLegend(0.60, 0.70, 0.94, 0.90);
	leg->SetBorderSize(0);
	leg->SetTextFont(42);
	leg->SetTextSize(0.032);
	leg->SetFillColor(0);
	leg->SetNColumns(2);
	if(doSpin){
		leg->AddEntry(h_ww," diboson","f");
		leg->AddEntry(h_top," top","f");
	}
	else {
	leg->AddEntry(h_ww," WW","f");
	leg->AddEntry(h_wz," WZ/ZZ/W#gamma ","f");
	leg->AddEntry(h_top," t#bar{t}","f");
	leg->AddEntry(h_stop," Single Top","f");
	}
	leg->AddEntry(h_zjets," Z+jets","f");
	leg->AddEntry(h_wjets," W+jets","f");
	if(doVBF){
	  leg->AddEntry(h_vbf,"VBF/VH ["+mH+"]","f");
	  leg->AddEntry(h_ggf,"ggF ["+mH+"]","f");
	} else if(doMVA) leg->AddEntry(h_ggf,"H ["+mH+"]","f");
	else if(doSpin){
	  leg->AddEntry(h_ggf_spin0,"H 0^{+}["+mH+"]","f");
	  leg->AddEntry(h_ggf_spin2,"H 2^{+}["+mH+"]","f");
	}

	leg->Draw();
	if(doPrelim){
	  TLatex * prelim = new TLatex();
	  prelim->SetNDC();
	  prelim->SetTextFont(42);
	  prelim->SetTextColor(1);
	  prelim->SetTextSize(0.06);
	  prelim->DrawLatex(0.22, 0.86, "#font[72]{ATLAS} Preliminary"); //0.26
	} else {
	  TLatex * prelim = new TLatex();
	  prelim->SetNDC();
	  prelim->SetTextFont(42);
	  prelim->SetTextColor(1);
	  prelim->SetTextSize(0.06);
	  prelim->DrawLatex(0.22, 0.86, "#font[72]{ATLAS} Internal"); //0.26
	}
	// TString normtxt="MC normalized to SM prediction";
	// drawNorm(normtxt);
	TLatex * lumi = new TLatex();
	lumi->SetNDC();
	lumi->SetTextFont(42);
	lumi->SetTextSize(0.04);
	lumi->SetTextColor(1);
	lumi->DrawLatex(0.2, 0.79, "#sqrt{s} = 8 TeV,  #int L dt = "+Lumi+" fb^{-1}"); //0.25
	TLatex * chan = new TLatex();
	chan->SetNDC();
	chan->SetTextFont(42);
	chan->SetTextSize(0.04);
	chan->SetTextColor(1);
	if( jet_bin == "0jet" ) {
	  if( channel=="ee" ) chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow e#nue#nu + 0 jet");
	  else if(channel=="emu" )  chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow e#nu#mu#nu + 0 jet");
	  else if(channel=="mue" )  chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow #mu#nue#nu + 0 jet");
	  else if(channel=="mumu" )  chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow #mu#nu#mu#nu + 0 jet");   
	  else if(channel=="all" )  chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow l#nul#nu + 0 jet"); 
	  else if(channel=="emu_all" )  chan->DrawLatex(0.19, 0.71, "H #rightarrow WW^{(*)} #rightarrow e#nu#mu#nu+#mu#nue#nu + 0 jet");                
	} else if( jet_bin == "1jet" ) {
	  if( channel=="ee" ) chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow e#nue#nu + 1 jet");
	  else if(channel=="emu" )  chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow e#nu#mu#nu + 1 jet");
	  else if(channel=="mue" )  chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow #mu#nue#nu + 1 jet");
	  else if(channel=="mumu" )  chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow #mu#nu#mu#nu + 1 jet");   
	  else if(channel=="all" )  chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow l#nul#nu + 1 jet"); 
	  else if(channel=="emu_all" )  chan->DrawLatex(0.19, 0.71, "H #rightarrow WW^{(*)} #rightarrow e#nu#mu#nu+#mu#nue#nu + 1 jet"); 
	} else if( jet_bin == "2jet" ) {
	  if( channel=="ee" ) chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow e#nue#nu + 2 jet");
	  else if(channel=="emu" )  chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow e#nu#mu#nu + 2 jet");
	  else if(channel=="mue" )  chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow #mu#nue#nu + 2 jet");
	  else if(channel=="mumu" )  chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow #mu#nu#mu#nu + 2 jet");   
	  else if(channel=="all" )  chan->DrawLatex(0.21, 0.71, "H #rightarrow WW^{(*)} #rightarrow l#nul#nu + 2 jet"); 
	  else if(channel=="emu_all" )  chan->DrawLatex(0.19, 0.71, "H #rightarrow WW^{(*)} #rightarrow e#nu#mu#nu+#mu#nue#nu + 2 jet"); 
	}
	
	canvas->cd();
	canvas->Print(outputdir+mH+"_"+cut_name+variable_name+jet_bin+"_"+channel+"_shape.pdf");
	canvas->Print(outputdir+mH+"_"+cut_name+variable_name+jet_bin+"_"+channel+"_shape.eps");
	
	
	
	delete canvas;
	delete lumi; 
	delete chan;
	delete leg;
}

void plot_comp(TH1F* histo1, TH1F* histo2, TString channel, TString jet_bin, TString cut_name, TString sample, TString var_nameX, TString var_nameY, TString outputdir) {
  
  setHSG3Style();
  
  Bool_t doPrelim = false;
  Bool_t doRatio = true;
  Bool_t doNorm = true;
  TString Lumi = "13";
  Int_t canvX = 0;
  Int_t canvY = 0;
  if(doRatio) {canvX=800; canvY=800;}
  else  {canvX=800; canvY=600;}

	if(doNorm) {
		histo1->Scale(1/histo1->Integral());
		histo2->Scale(1/histo2->Integral());
	}
	setHistoStyle(histo1); 
	setHistoStyle(histo2); 
	histo1->SetLineColor(kBlack);
	histo2->SetLineColor(kRed-2);

	//sys histo
	TCanvas *canvas = new TCanvas(sample+"_"+histo1->GetName(),sample+"_"+histo1->GetName(),canvX,canvY);
	//find max 
	Float_t max = histo1->GetMaximum();
	if(histo2->GetMaximum() > max) max =  histo2->GetMaximum();
	histo1->SetMaximum(2*max);
	histo1->SetMinimum(0.);
	if(doRatio){
		TPad *pad2 = new TPad("pad2","",0,0,1,0.3);
		setsubPadStyle(pad2);
		pad2->SetGrid();
		pad2->Draw();
		pad2->cd();
		TH1F *h_ratio = (TH1F*) histo1->Clone();
		h_ratio->Divide(histo2);

	  h_ratio->SetMarkerStyle(20);
	  h_ratio->SetMarkerColor(kBlack);
	  h_ratio->SetMarkerSize(0.8); //1.2
		h_ratio->SetTitleSize(0.15,"x");
		h_ratio->SetTitleSize(0.12,"y");
		h_ratio->SetTitleOffset(0.45,"y");
		h_ratio->SetLabelSize(0.17,"x");
		h_ratio->SetLabelSize(0.17,"y");
		h_ratio->SetMaximum(1.5);
		h_ratio->SetMinimum(0.5);            
		h_ratio->Draw("E");
		h_ratio->GetYaxis()->SetTitle("fullsim/AFII");
		h_ratio->GetXaxis()->SetTitle(var_nameX);
		h_ratio->SetTickLength(0.04,"y");
		h_ratio->SetTickLength(0.15,"x");
		canvas->cd();
		TPad *pad1 = new TPad("pad1","",0,0.3,1,1);
		setPadStyle(pad1);
		pad1->Draw();
		pad1->cd();
	  histo1->Draw("histo E"); 
	  histo2->Draw("histo same E"); 
	  histo1->SetLabelSize(0.,"x");
	  histo1->GetXaxis()->SetTitle(var_nameX);
	  histo1->GetYaxis()->SetTitle(var_nameY);
	} else {

	  histo1->Draw("histo E"); 
	  histo2->Draw("histo same E");
	  histo1->GetXaxis()->SetTitle(var_nameX);
	  histo1->GetYaxis()->SetTitle(var_nameY);
	}
	//draw legend
	TLegend *leg = new TLegend(0.6,0.65,0.9,0.9);
	leg->SetBorderSize(0);
	leg->SetTextSize(0.032);
	leg->SetFillColor(0);
	leg->AddEntry(histo1," fullsim, "+sample,"l");
	leg->AddEntry(histo2," AFII, "+sample,"l");
	leg->Draw();
	TLatex * lumi = new TLatex();
	lumi->SetNDC();
	lumi->SetTextFont(42);
	lumi->SetTextSize(0.032);
	lumi->SetTextColor(1);
	lumi->DrawLatex(0.27, 0.8, "#sqrt{s} = 8 TeV,  #int L dt = "+Lumi+" fb^{-1}");
	TLatex * chan = new TLatex();
	chan->SetNDC();
	chan->SetTextFont(42);
	chan->SetTextSize(0.05);
	chan->SetTextColor(1);
	if(channel=="ee") chan->DrawLatex(0.27, 0.74, "ee-channel, "+jet_bin);
	else if(channel=="mumu") chan->DrawLatex(0.27, 0.74, "#mu#mu-channel, "+jet_bin);
	else if(channel=="emu") chan->DrawLatex(0.27, 0.74, "e#mu-channel, "+jet_bin);
	else if(channel=="mue") chan->DrawLatex(0.27, 0.74, "#mue-channel, "+jet_bin);
	else if(channel=="all") chan->DrawLatex(0.23, 0.74, "ee+#mu#mu+e#mu-channel, "+jet_bin);
	else if(channel=="emu_all") chan->DrawLatex(0.23, 0.74, "e#mu+#mue-channel, "+jet_bin);
	//KS test
	double KS_value = histo1->KolmogorovTest(histo2);
	//if(isnan(KS_value)) KS_value = -999;
	TLatex *KS = new TLatex();
	KS->SetNDC();
	KS->SetTextFont(42);
	KS->SetTextSize(0.05);
	KS->SetTextColor(1);
  KS->DrawLatex(0.27, 0.64, Form("KS-test: %.2f",KS_value));

	if(doPrelim){
		TLatex * prelim = new TLatex();
		prelim->SetNDC();
		prelim->SetTextFont(42);
		prelim->SetTextColor(1);
		prelim->DrawLatex(0.27, 0.88, "#font[72]{ATLAS} Preliminary");
	}
	canvas->Print(outputdir+sample+"_"+histo1->GetName()+"_comp.eps");
	canvas->Print(outputdir+sample+"_"+histo1->GetName()+"_comp.pdf"); 

}

void plot_comp3(TH1F* histo1, TH1F* histo2, TH1F* histo3, TString channel, TString jet_bin, TString cut_name, TString sample, TString var_nameX, TString var_nameY, TString outputdir) {
  
  setHSG3Style();
  
  Bool_t doPrelim = false;
  Bool_t doRatio = true;
  Bool_t doNorm = true;
  TString Lumi = "13";
  Int_t canvX = 0;
  Int_t canvY = 0;
  if(doRatio) {canvX=800; canvY=800;}
  else  {canvX=800; canvY=600;}

	if(doNorm) {
		histo1->Scale(1/histo1->Integral());
		histo2->Scale(1/histo2->Integral());
		histo3->Scale(1/histo3->Integral());
	}
	setHistoStyle(histo1); 
	setHistoStyle(histo2); 
	setHistoStyle(histo3);
	histo1->SetLineColor(kBlack);
	histo2->SetLineColor(kRed-2);
	histo3->SetLineColor(kBlue-2);

	//sys histo
	TCanvas *canvas = new TCanvas(sample+"_"+histo1->GetName(),sample+"_"+histo1->GetName(),canvX,canvY);
	//find max 
	Float_t max = histo1->GetMaximum();
	if(histo2->GetMaximum() > max) max =  histo2->GetMaximum();
	if(histo3->GetMaximum() > max) max =  histo3->GetMaximum();
	histo1->SetMaximum(2*max);
	histo1->SetMinimum(0.);
	if(doRatio){
		TPad *pad2 = new TPad("pad2","",0,0,1,0.3);
		setsubPadStyle(pad2);
		pad2->SetGrid();
		pad2->Draw();
		pad2->cd();
		TH1F *h_ratio = (TH1F*) histo2->Clone();
		h_ratio->Divide(histo1);
		TH1F *h_ratio2 = (TH1F*) histo3->Clone();
		h_ratio2->Divide(histo1);

	  //h_ratio->SetMarkerStyle(20);
	  //h_ratio->SetMarkerColor(kBlack);
	  //h_ratio->SetMarkerSize(0.8); //1.2
		h_ratio->SetTitleSize(0.15,"x");
		h_ratio->SetTitleSize(0.12,"y");
		h_ratio->SetTitleOffset(0.45,"y");
		h_ratio->SetLabelSize(0.17,"x");
		h_ratio->SetLabelSize(0.17,"y");
		h_ratio->SetMaximum(1.5);
		h_ratio->SetMinimum(0.5);            
		h_ratio->Draw("E");
		h_ratio2->Draw("E same");

		h_ratio->GetYaxis()->SetTitle("other/powheg");
		h_ratio->GetXaxis()->SetTitle(var_nameX);
		h_ratio->SetTickLength(0.04,"y");
		h_ratio->SetTickLength(0.15,"x");
		canvas->cd();
		TPad *pad1 = new TPad("pad1","",0,0.3,1,1);
		setPadStyle(pad1);
		pad1->Draw();
		pad1->cd();
	  histo1->Draw("histo E"); 
	  histo2->Draw("histo same E"); 
	  histo3->Draw("histo same E"); 
	  histo1->SetLabelSize(0.,"x");
	  histo1->GetXaxis()->SetTitle(var_nameX);
	  histo1->GetYaxis()->SetTitle(var_nameY);
	} else {

	  histo1->Draw("histo E"); 
	  histo2->Draw("histo same E");
	  histo1->GetXaxis()->SetTitle(var_nameX);
	  histo1->GetYaxis()->SetTitle(var_nameY);
	}
	//draw legend
	TLegend *leg = new TLegend(0.6,0.65,0.9,0.9);
	leg->SetBorderSize(0);
	leg->SetTextSize(0.032);
	leg->SetFillColor(0);
	leg->AddEntry(histo1," powheg, "+sample,"l");
	leg->AddEntry(histo2," mcatnlo, "+sample,"l");
	leg->AddEntry(histo3," sherpa, "+sample,"l");
	leg->Draw();
	TLatex * lumi = new TLatex();
	lumi->SetNDC();
	lumi->SetTextFont(42);
	lumi->SetTextSize(0.032);
	lumi->SetTextColor(1);
	lumi->DrawLatex(0.27, 0.8, "#sqrt{s} = 8 TeV,  #int L dt = "+Lumi+" fb^{-1}");
	TLatex * chan = new TLatex();
	chan->SetNDC();
	chan->SetTextFont(42);
	chan->SetTextSize(0.05);
	chan->SetTextColor(1);
	if(channel=="ee") chan->DrawLatex(0.27, 0.74, "ee-channel, "+jet_bin);
	else if(channel=="mumu") chan->DrawLatex(0.27, 0.74, "#mu#mu-channel, "+jet_bin);
	else if(channel=="emu") chan->DrawLatex(0.27, 0.74, "e#mu-channel, "+jet_bin);
	else if(channel=="mue") chan->DrawLatex(0.27, 0.74, "#mue-channel, "+jet_bin);
	else if(channel=="all") chan->DrawLatex(0.23, 0.74, "ee+#mu#mu+e#mu-channel, "+jet_bin);
	else if(channel=="emu_all") chan->DrawLatex(0.23, 0.74, "e#mu+#mue-channel, "+jet_bin);
	//KS test
	/* double KS_value = histo1->KolmogorovTest(histo2); */

	//if(isnan(KS_value)) KS_value = -999;
	/* TLatex *KS = new TLatex(); */
	/* KS->SetNDC(); */
	/* KS->SetTextFont(42); */
	/* KS->SetTextSize(0.05); */
	/* KS->SetTextColor(1); */
  /* KS->DrawLatex(0.27, 0.64, Form("KS-test: %.2f",KS_value)); */

	if(doPrelim){
		TLatex * prelim = new TLatex();
		prelim->SetNDC();
		prelim->SetTextFont(42);
		prelim->SetTextColor(1);
		prelim->DrawLatex(0.27, 0.88, "#font[72]{ATLAS} Preliminary");
	}
	canvas->Print(outputdir+sample+"_"+histo1->GetName()+"_comp2.eps");
	canvas->Print(outputdir+sample+"_"+histo1->GetName()+"_comp2.pdf"); 

}

void plot2D(TH2F* h_signal0, TH2F* h_signal2, TH2F* h_background, TH2F* h_data, TString mH, TString channel, TString jet_bin, TString cut_name, TString variable_name, TString variable_nameX, TString variable_nameY, TString histo_name, TString outputdir) 

{

  gStyle->SetOptStat(0);

  gStyle->SetCanvasBorderMode(0); //frame color of canvas
  gStyle->SetCanvasColor(0);  //bkrd color of canvas
  gStyle->SetStatBorderSize(0); //frame style of stat-box 1

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleFillColor(0);
  gStyle->SetPadColor(0);
  gStyle->SetPadBorderMode(0);

  gStyle->SetLineWidth(3); // width of ticks
  gStyle->SetPadTickX(0); //1:ticks on upper,2: ticks+labels on upper xaxis
  gStyle->SetPadTickY(0);

  gStyle->SetPadLeftMargin(0.14); // 0.18
  gStyle->SetPadRightMargin(0.14);
  gStyle->SetPadTopMargin(0.07);
  gStyle->SetPadBottomMargin(0.14);
  gStyle->SetFrameLineWidth(2);
  gStyle->SetFrameFillColor(0);
  gStyle->SetPaintTextFormat(".1f");
  
  gStyle->SetTextFont(42); 


	const Int_t NRGBs = 5;
	const Int_t NCont = 255;

	Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
	Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
	Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
	Double_t blue[NRGBs]  = { 0.85, 1.00, 0.12, 0.00, 0.00 };
	TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
	gStyle->SetNumberContours(NCont);

	gStyle->SetFrameFillColor(kWhite);


	//signal
	TCanvas *canvas_signal0 = new TCanvas("signal0_"+histo_name,"",800,800);
	canvas_signal0->SetFillColor(kWhite);

	h_signal0->SetXTitle(variable_nameX);
	h_signal0->SetYTitle(variable_nameY);
	h_signal0->SetNdivisions(505,"x"); 
	h_signal0->SetNdivisions(505,"y"); 
  h_signal0->SetTitleOffset(1.,"x"); 
  h_signal0->SetTitleOffset(1.2,"y");
	h_signal0->Draw("colz");
	h_signal0->SetTitle("");

	h_signal0->SetMarkerColor(kWhite);
	h_signal0->Draw("text,same");

	canvas_signal0->Print(outputdir+"signal0_"+h_signal0->GetName()+".pdf");

	//signal
	TCanvas *canvas_signal2 = new TCanvas("signal2_"+histo_name,"",800,800);
	canvas_signal2->SetFillColor(kWhite);

	h_signal2->SetXTitle(variable_nameX);
	h_signal2->SetYTitle(variable_nameY);
	h_signal2->SetNdivisions(505,"x"); 
	h_signal2->SetNdivisions(505,"y"); 
  h_signal2->SetTitleOffset(1.,"x"); 
  h_signal2->SetTitleOffset(1.2,"y");
	h_signal2->Draw("colz");
	h_signal2->SetTitle("");

	h_signal2->SetMarkerColor(kWhite);
	h_signal2->Draw("text,same");

	canvas_signal2->Print(outputdir+"signal2_"+h_signal0->GetName()+".pdf");

	//background
	TCanvas *canvas_bgr = new TCanvas("bgr_"+histo_name,"",800,800);
	canvas_bgr->SetFillColor(kWhite);

	h_background->SetXTitle(variable_nameX);
	h_background->SetYTitle(variable_nameY);
	h_background->SetNdivisions(505,"x"); 
	h_background->SetNdivisions(505,"y"); 
  h_background->SetTitleOffset(1.,"x"); 
  h_background->SetTitleOffset(1.2,"y");
	h_background->Draw("colz");
	h_background->SetTitle("");

	h_background->SetMarkerColor(kWhite);
	h_background->Draw("text,same");

	canvas_bgr->Print(outputdir+"bgr_"+h_signal0->GetName()+".pdf");

	//data
	TCanvas *canvas_data = new TCanvas("data_"+histo_name,"",800,800);
	canvas_data->SetFillColor(kWhite);

	h_data->SetXTitle(variable_nameX);
	h_data->SetYTitle(variable_nameY);
	h_data->SetNdivisions(505,"x"); 
	h_data->SetNdivisions(505,"y"); 
  h_data->SetTitleOffset(1.,"x"); 
  h_data->SetTitleOffset(1.2,"y");
	h_data->Draw("colz");
	h_data->SetTitle("");

	h_data->SetMarkerColor(kWhite);
	h_data->Draw("text,same");
	std::cout << "Correlation: histo " << histo_name << " data " << h_data->GetCorrelationFactor() << std::endl;
	canvas_data->Print(outputdir+"data_"+h_signal0->GetName()+".pdf");

	//background + signal
	TCanvas *canvas_bgr_plus_sig0 = new TCanvas("bgr_plus_sig0_"+histo_name,"",800,800);
	canvas_bgr_plus_sig0->SetFillColor(kWhite);

  h_signal0->Scale(1.45);
	h_background->Add(h_signal0);
	
	h_background->SetXTitle(variable_nameX);
	h_background->SetYTitle(variable_nameY);
	h_background->SetNdivisions(505,"x"); 
	h_background->SetNdivisions(505,"y"); 
  h_background->SetTitleOffset(1.,"x"); 
  h_background->SetTitleOffset(1.2,"y");
	h_background->Draw("colz");
	h_background->SetTitle("");

	h_background->SetMarkerColor(kWhite);
	h_background->Draw("text,same");

	std::cout << "Correlation: histo " << histo_name << " bgr+spin0 " << h_background->GetCorrelationFactor() << std::endl;
	canvas_bgr_plus_sig0->Print(outputdir+"bgr_plus_sig0_"+h_signal0->GetName()+".pdf");


}
