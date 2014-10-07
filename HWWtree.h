//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Oct 25 14:23:14 2012 by ROOT version 5.32/00
// from TTree tree/event Tree
// found on file: spin2.root
//////////////////////////////////////////////////////////

#ifndef HWWtree_h
#define HWWtree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <math.h>
#include "TLorentzVector.h"
#include <iostream>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class HWWtree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Float_t         lepplusPt;
   Float_t         lepminPt;
   Float_t         lepplusPhi;
   Float_t         lepminPhi;
   Float_t         lepplusEta;
   Float_t         lepminEta;
   Float_t         lepplusID;
   Float_t         lepminID;
   Float_t         lepplusE;
   Float_t         lepminE;
   Float_t         nuplusPt;
   Float_t         numinPt;
   Float_t         nuplusPhi;
   Float_t         numinPhi;
   Float_t         nuplusEta;
   Float_t         numinEta;
   Float_t         nuplusE;
   Float_t         numinE;
   Float_t         WplusPt;
   Float_t         WminPt;
   Float_t         WplusPhi;
   Float_t         WminPhi;
   Float_t         WplusEta;
   Float_t         WminEta;
   Float_t         WplusE;
   Float_t         WminE;
   Float_t         yPt;
   Float_t         yPhi;
   Float_t         yEta;
   Float_t         yE;
   Float_t         yID;
   Float_t         Mll;
   Float_t         DPhill;
   Float_t         MET;
   Float_t         yM;

   //vars to cut
   Float_t LeadLepPt, SubLeadLepPt, Ptll, Mt, METRel, WplusM, WminM, phi3, theta1, theta3, cosThetaStar, Phi, Phi1, WoffShellM, WonShellM, cosTheta1, cosTheta2;
   TLorentzVector lepplus, lepmin, dilep, nuplus, numin, met;
   Float_t pie;

   Float_t Mnunu, resyPt, resyPhi, resyEta, resyE, BDPhill, DPsill, BDPsill, DEtall;
   Float_t DPhiLeadLepMET, DPhiSubLeadLepMET, DLepPt, ESum;
   Float_t DPhiLepPlusMET, DPhiLepMinMET, DPtcharge, BLepPlusPhi, BLepMinPhi;

   // List of branches
   TBranch        *b_lepplusPt;   //!
   TBranch        *b_lepminPt;   //!
   TBranch        *b_lepplusPhi;   //!
   TBranch        *b_lepminPhi;   //!
   TBranch        *b_lepplusEta;   //!
   TBranch        *b_lepminEta;   //!
   TBranch        *b_lepplusID;   //!
   TBranch        *b_lepminID;   //!
   TBranch        *b_lepplusE;   //!
   TBranch        *b_lepminE;   //!
   TBranch        *b_nuplusPt;   //!
   TBranch        *b_numinPt;   //!
   TBranch        *b_nuplusPhi;   //!
   TBranch        *b_numinPhi;   //!
   TBranch        *b_nuplusEta;   //!
   TBranch        *b_numinEta;   //!
   TBranch        *b_nuplusE;   //!
   TBranch        *b_numinE;   //!
   TBranch        *b_WplusPt;   //!
   TBranch        *b_WminPt;   //!
   TBranch        *b_WplusPhi;   //!
   TBranch        *b_WminPhi;   //!
   TBranch        *b_WplusEta;   //!
   TBranch        *b_WminEta;   //!
   TBranch        *b_WplusE;   //!
   TBranch        *b_WminE;   //!
   TBranch        *b_yPt;   //!
   TBranch        *b_yPhi;   //!
   TBranch        *b_yEta;   //!
   TBranch        *b_yE;   //!
   TBranch        *b_yID;   //!
   TBranch        *b_Mll;   //!
   TBranch        *b_DPhill;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_yM;   //!

   HWWtree(TTree *HWWtree=0, TString file="");
   virtual ~HWWtree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *HWWtree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual void CalcVars(Long64_t);
   virtual void NewTree(TString);

   TString fname;
};

#endif

#ifdef HWWtree_cxx
HWWtree::HWWtree(TTree *HWWtree , TString file) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
  if(file=="") fname = "ggF0";
  else fname = file;
  pie  = 3.14159265359;

   if (HWWtree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(fname);
      if (!f || !f->IsOpen()) {
         f = new TFile(fname);
      }
      f->GetObject("tree",HWWtree);

   }
   Init(HWWtree);
}

HWWtree::~HWWtree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t HWWtree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t HWWtree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void HWWtree::Init(TTree *HWWtree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!HWWtree) return;
   fChain = HWWtree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("lepplusPt", &lepplusPt, &b_lepplusPt);
   fChain->SetBranchAddress("lepminPt", &lepminPt, &b_lepminPt);
   fChain->SetBranchAddress("lepplusPhi", &lepplusPhi, &b_lepplusPhi);
   fChain->SetBranchAddress("lepminPhi", &lepminPhi, &b_lepminPhi);
   fChain->SetBranchAddress("lepplusEta", &lepplusEta, &b_lepplusEta);
   fChain->SetBranchAddress("lepminEta", &lepminEta, &b_lepminEta);
   fChain->SetBranchAddress("lepplusID", &lepplusID, &b_lepplusID);
   fChain->SetBranchAddress("lepminID", &lepminID, &b_lepminID);
   fChain->SetBranchAddress("lepplusE", &lepplusE, &b_lepplusE);
   fChain->SetBranchAddress("lepminE", &lepminE, &b_lepminE);
   fChain->SetBranchAddress("nuplusPt", &nuplusPt, &b_nuplusPt);
   fChain->SetBranchAddress("numinPt", &numinPt, &b_numinPt);
   fChain->SetBranchAddress("nuplusPhi", &nuplusPhi, &b_nuplusPhi);
   fChain->SetBranchAddress("numinPhi", &numinPhi, &b_numinPhi);
   fChain->SetBranchAddress("nuplusEta", &nuplusEta, &b_nuplusEta);
   fChain->SetBranchAddress("numinEta", &numinEta, &b_numinEta);
   fChain->SetBranchAddress("nuplusE", &nuplusE, &b_nuplusEta);
   fChain->SetBranchAddress("numinE", &numinE, &b_numinE);
   fChain->SetBranchAddress("WplusPt", &WplusPt, &b_WplusPt);
   fChain->SetBranchAddress("WminPt", &WminPt, &b_WminPt);
   fChain->SetBranchAddress("WplusPhi", &WplusPhi, &b_WplusPhi);
   fChain->SetBranchAddress("WminPhi", &WminPhi, &b_WminPhi);
   fChain->SetBranchAddress("WplusEta", &WplusEta, &b_WplusEta);
   fChain->SetBranchAddress("WminEta", &WminEta, &b_WminEta);
   fChain->SetBranchAddress("WplusE", &WplusE, &b_WplusEta);
   fChain->SetBranchAddress("WminE", &WminE, &b_WminE);
   fChain->SetBranchAddress("yPt", &yPt, &b_yPt);
   fChain->SetBranchAddress("yPhi", &yPhi, &b_yPhi);
   fChain->SetBranchAddress("yEta", &yEta, &b_yEta);
   fChain->SetBranchAddress("yE", &yE, &b_yE);
   fChain->SetBranchAddress("yID", &yID, &b_yID);
   fChain->SetBranchAddress("Mll", &Mll, &b_Mll);
   fChain->SetBranchAddress("DPhill", &DPhill, &b_DPhill);
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   fChain->SetBranchAddress("yM", &yM, &b_yM);
   Notify();
}

Bool_t HWWtree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void HWWtree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}


void HWWtree::CalcVars(Long64_t entry)
{

  TLorentzVector LeadLep, SubLeadLep;
  
  if(lepplusPt>=lepminPt) {
    LeadLepPt = lepplusPt; SubLeadLepPt = lepminPt;
    LeadLep.SetPtEtaPhiE(lepplusPt,lepplusEta,lepplusPhi,lepplusE);
    SubLeadLep.SetPtEtaPhiE(lepminPt,lepminEta,lepminPhi,lepminE);
  }
  else {
    LeadLepPt = lepminPt; SubLeadLepPt = lepplusPt;
    SubLeadLep.SetPtEtaPhiE(lepplusPt,lepplusEta,lepplusPhi,lepplusE);
    LeadLep.SetPtEtaPhiE(lepminPt,lepminEta,lepminPhi,lepminE);
  }

  lepplus.SetPtEtaPhiE(lepplusPt,lepplusEta,lepplusPhi,lepplusE);
  lepmin.SetPtEtaPhiE(lepminPt,lepminEta,lepminPhi,lepminE);
  dilep = lepplus+lepmin;
  Ptll = dilep.Pt();

  nuplus.SetPtEtaPhiE(nuplusPt,nuplusEta,nuplusPhi,nuplusE);
  numin.SetPtEtaPhiE(numinPt,numinEta,numinPhi,numinE);
  met = nuplus + numin;

  DPsill = fabs(lepmin.Angle(lepplus.Vect()));

  //ANGLES
  TLorentzVector H, Hr = dilep+met;
  H.SetPtEtaPhiE(yPt,yEta,yPhi,yE);

  TVector3 h_boost = -Hr.BoostVector();
  TLorentzVector Wmin = lepmin+numin;
  TLorentzVector Wplus = lepplus+nuplus;

  TLorentzVector Wmin_Hrest = Wmin;
  Wmin_Hrest.Boost(h_boost);
  TLorentzVector Wplus_Hrest = Wplus;
  Wplus_Hrest.Boost(h_boost);

  TLorentzVector lepplus_Hrest = lepplus;
  lepplus_Hrest.Boost(h_boost);
  TLorentzVector nuplus_Hrest = nuplus;
  nuplus_Hrest.Boost(h_boost);

  TLorentzVector lepmin_Hrest = lepmin;
  lepmin_Hrest.Boost(h_boost);
  TLorentzVector numin_Hrest = numin;
  numin_Hrest.Boost(h_boost);

  BDPhill = fabs(lepmin_Hrest.DeltaPhi(lepplus_Hrest));
  BDPsill = fabs(lepmin_Hrest.Angle(lepplus_Hrest.Vect()));


  TVector3 Wp_boost = -Wplus.BoostVector();
  TVector3 Wm_boost = -Wmin.BoostVector();
  //  Wp_boost = Wm_boost = h_boost;

  /**
  TLorentzVector Wmin_Wprest = Wmin;
  Wmin_Wprest.Boost(Wp_boost);
  TLorentzVector Wplus_Wmrest = Wplus;
  Wplus_Wmrest.Boost(Wm_boost);

  TLorentzVector lepplus_Wprest = lepplus;
  lepplus_Wprest.Boost(Wp_boost);
  TLorentzVector nuplus_Wprest = nuplus;
  nuplus_Wprest.Boost(Wp_boost);

  TLorentzVector lepmin_Wmrest = lepmin;
  lepmin_Wmrest.Boost(Wm_boost);
  TLorentzVector numin_Wmrest = numin;
  numin_Wmrest.Boost(Wm_boost);
  **/


  TVector3 zaxis(0,0,1);

  DEtall = fabs(lepminEta-lepplusEta);

  theta1 = nuplus_Hrest.Angle(Wplus_Hrest.Vect());
  theta3 = lepmin_Hrest.Angle(Wmin_Hrest.Vect());

  //theta1 = cos(theta1);
  //theta3 = cos(theta3);

  TVector3 planeplus = lepplus_Hrest.Vect().Cross(nuplus_Hrest.Vect());
  TVector3 planemin = lepmin_Hrest.Vect().Cross(numin_Hrest.Vect());

  phi3 = planemin.Angle(planeplus);
  phi3 = fabs(phi3);
  
  TLorentzVector q1,q2,q11,q12,q21,q22;
  TVector3 n1,n2,nsc;

  if(Wplus.M()>Wmin.M()) {
    //if(true) {
    q1 = Wplus;
    q2 = Wmin;
    q11= nuplus;
    q12= lepplus;
    q21= lepmin;
    q22= numin;
  
  }
  else {
    q1 = Wmin;
    q2 = Wplus;
    q11= lepmin;
    q12= numin;
    q21= nuplus;
    q22= lepplus;
  }

  WonShellM = q1.M();
  WoffShellM = q2.M();

  q1 = Wplus;
  q2 = Wmin;
  q11= nuplus;
  q12= lepplus;
  q21= lepmin;
  q22= numin;
  

   

  TVector3 q1_boost = -q1.BoostVector() ,q2_boost=-q2.BoostVector();

  TLorentzVector q1_Wr = q1, q2_Wr = q2, q11_Wr = q11, q21_Wr=q21;


  q1.Boost(h_boost);
  q2.Boost(h_boost);
  q11.Boost(h_boost);
  q12.Boost(h_boost);
  q21.Boost(h_boost);
  q22.Boost(h_boost);
  

  theta1=q11.Vect().Angle(q1.Vect());
  theta3=q21.Vect().Angle(q2.Vect());

  TVector3 q1hat(q1.Vect());
  //q1hat.SetMag(1);

  cosThetaStar = q1hat.Unit().CosTheta();
  
  //planes
  n1 = q11.Vect().Cross(q12.Vect());
  //  n1.SetMag(1);
  n1 = n1.Unit();
  n2= q21.Vect().Cross(q22.Vect());
  //  n2.SetMag(1);
  n2 = n2.Unit();
  nsc = zaxis.Cross(q1.Vect());
  //nsc.SetMag(1);
  nsc = nsc.Unit();

  Phi = q1.Vect().Dot(n1.Cross(n2));
  Phi = Phi/fabs(Phi);
  Phi = Phi*acos(-n1.Dot(n2));

  Phi1 = q1.Vect().Dot(n1.Cross(nsc));
  Phi1 = Phi1/fabs(Phi1);
  Phi1 = Phi1*acos(n1.Dot(nsc));
  

  //TVector3 q1_boost, q2_boost;
  //q1_boost = -q1.BoostVector();
  //q2_boost = -q2.BoostVector();

  q2_Wr.Boost(q1_boost);
  q11_Wr.Boost(q1_boost);

  q1_Wr.Boost(q2_boost);
  q21_Wr.Boost(q2_boost);

  cosTheta1 = -(q2_Wr.Vect().Dot(q11_Wr.Vect()));
  cosTheta1 = cosTheta1/(q2_Wr.Vect().Mag()*q11_Wr.Vect().Mag());
  //theta1 = acos(theta1);

  cosTheta2 = -(q1_Wr.Vect().Dot(q21_Wr.Vect()));
  cosTheta2 = cosTheta2/(q1_Wr.Vect().Mag()*q21_Wr.Vect().Mag());
  //theta3 = acos(theta3);

  //ANGLES


  TVector3 tmp=dilep.Vect() +met.Vect();
  Mt = sqrt( pow(dilep.Pt()+met.Pt(),2) - tmp.Mag2()  );


  Float_t dphimin = fabs(lepmin.DeltaPhi(met));
  if(fabs(lepplus.DeltaPhi(met))<dphimin) dphimin = fabs(lepplus.DeltaPhi(met));
  
  

  METRel = MET;
  if(dphimin<(pie/2.)) METRel = MET*sin(dphimin);

  WplusM = (lepplus+nuplus).M();
  WminM = (lepmin+numin).M();

  Mnunu = met.M();

  resyPt = H.Pt()-Hr.Pt();
  resyPhi = H.Phi()-Hr.Phi();
  resyEta = H.Eta()-Hr.Eta();
  resyE = H.E()-Hr.E();


  DPhiLeadLepMET = fabs(LeadLep.DeltaPhi(met));
  DPhiSubLeadLepMET = fabs(SubLeadLep.DeltaPhi(met));

  DLepPt = LeadLepPt-SubLeadLepPt;

  DPtcharge = lepplus.Pt() - lepmin.Pt();
  DPhiLepPlusMET = fabs(lepplus.DeltaPhi(met));
  DPhiLepMinMET = fabs(lepmin.DeltaPhi(met));
  BLepPlusPhi = lepplus_Hrest.Phi();
  BLepMinPhi = lepmin_Hrest.Phi();
  
  

}

void HWWtree::NewTree(TString spin="") {

  std::cout<<"Creating new root file."<<std::endl;
  TString hypname = fname.Remove(fname.Length()-5,fname.Length());


  TFile *newfile = new TFile("./"+hypname+spin+"new.root","recreate");
  TTree *newtree = fChain->CloneTree();
  

  TBranch *newbranch = newtree->Branch("leadlepPt",&LeadLepPt,"leadlepPt/F");
  TBranch *newbranch2 = newtree->Branch("subleadlepPt",&SubLeadLepPt,"subleadlepPt/F");
  TBranch *newbranch3 = newtree->Branch("Ptll",&Ptll,"Ptll/F");
  TBranch *newbranch4 = newtree->Branch("Mt",&Mt,"Mt/F");
  TBranch *newbranch5 = newtree->Branch("METRel",&METRel,"METRel/F");
  TBranch *newbranch6 = newtree->Branch("WminM",&WminM,"WminM/F");
  TBranch *newbranch7 = newtree->Branch("WplusM",&WplusM,"WplusM/F");
  TBranch *newbranch8 = newtree->Branch("phi3",&phi3,"phi3/F");
  TBranch *newbranch9 = newtree->Branch("theta3",&theta3,"theta3/F");
  TBranch *newbranch10 = newtree->Branch("theta1",&theta1,"theta1/F");
  TBranch *newbranch11 = newtree->Branch("cosThetaStar",&cosThetaStar,"cosThetaStar/F");
  TBranch *newbranch12 = newtree->Branch("Phi",&Phi,"Phi/F");
  TBranch *newbranch13 = newtree->Branch("Phi1",&Phi1,"Phi1/F");
  TBranch *newbranch14 = newtree->Branch("WonShellM",&WonShellM,"WonShellM/F");
  TBranch *newbranch15 = newtree->Branch("WoffShellM",&WoffShellM,"WoffShellM/F");
  TBranch *newbranch16 = newtree->Branch("cosTheta1",&cosTheta1,"cosTheta1/F");
  TBranch *newbranch17 = newtree->Branch("cosTheta2",&cosTheta2,"cosTheta2/F");
  TBranch *newbranch18 = newtree->Branch("Mnunu",&Mnunu,"Mnunu/F");
  TBranch *newbranch19 = newtree->Branch("resyPt",&resyPt,"resyPt/F");
  TBranch *newbranch20 = newtree->Branch("resyPhi",&resyPhi,"resyPhi/F");
  TBranch *newbranch21 = newtree->Branch("resyEta",&resyEta,"resyEta/F");
  TBranch *newbranch22 = newtree->Branch("resyE",&resyE,"resyE/F");
  TBranch *newbranch23 = newtree->Branch("BDPhill",&BDPhill,"BDPhill/F");
  TBranch *newbranch24 = newtree->Branch("DPsill",&DPsill,"DPsill/F");
  TBranch *newbranch25 = newtree->Branch("BDPsill",&BDPsill,"BDPsill/F");
  TBranch *newbranch26 = newtree->Branch("DEtall",&DEtall,"DEtall/F");
  TBranch *newbranch27 = newtree->Branch("DPhiLeadLepMET",&DPhiLeadLepMET,"DPhiLeadLepMET/F");
  TBranch *newbranch28 = newtree->Branch("DPhiSubLeadLepMET",&DPhiSubLeadLepMET,"DPhiSubLeadLepMET/F");
  TBranch *newbranch29 = newtree->Branch("DLepPt",&DLepPt,"DLepPt/F");
  TBranch *newbranch30 = newtree->Branch("DPtcharge",&DPtcharge,"DPtcharge/F");
  TBranch *newbranch31 = newtree->Branch("DPhiLepPlusMET",&DPhiLepPlusMET,"DPhiLepPlusMET/F");
  TBranch *newbranch32 = newtree->Branch("DPhiLepMinMET",&DPhiLepMinMET,"DPhiLepMinMET/F");
  TBranch *newbranch33 = newtree->Branch("BLepMinPhi",&BLepMinPhi,"BLepMinPhi/F");
  TBranch *newbranch34 = newtree->Branch("BLepPlusPhi",&BLepPlusPhi,"BLepPlusPhi/F");

  

  Long64_t nentries = fChain->GetEntriesFast();
  
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    fChain->GetEntry(jentry);
    //if (Cut(ientry) < 0) continue;
    if(ientry%1000==0) std::cout<<"Events: "<<ientry<<std::flush<<"\r";
    CalcVars(ientry);
    newbranch->Fill();
    newbranch2->Fill();
    newbranch3->Fill();
    newbranch4->Fill();
    newbranch5->Fill();
    newbranch6->Fill();
    newbranch7->Fill();
    newbranch8->Fill();
    newbranch9->Fill();
    newbranch10->Fill();
    newbranch11->Fill();
    newbranch12->Fill();
    newbranch13->Fill();
    newbranch14->Fill();
    newbranch15->Fill();
    newbranch16->Fill();
    newbranch17->Fill();
    newbranch18->Fill();
    newbranch19->Fill();
    newbranch20->Fill();
    newbranch21->Fill();
    newbranch22->Fill();
    newbranch23->Fill();
    newbranch24->Fill();
    newbranch25->Fill();
    newbranch26->Fill();
    newbranch27->Fill();
    newbranch28->Fill();    
    newbranch29->Fill();
    newbranch30->Fill();
    newbranch31->Fill();
    newbranch32->Fill();
    newbranch33->Fill();
    newbranch34->Fill();


  }

  newtree->Write();
  newfile->Write();
}

Int_t HWWtree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.


  CalcVars(entry);
  bool goodEvent = true;

  int emu = lepplusID*lepminID;
  goodEvent = goodEvent && fabs(emu)==143;

  goodEvent = goodEvent && LeadLepPt>25 && SubLeadLepPt>15;
  goodEvent = goodEvent && Ptll>20;
  goodEvent = goodEvent && METRel>20;
  //goodEvent = goodEvent && Mt>60 && Mt<130;
  goodEvent = goodEvent && Mll<80;// && Mll<90;
  goodEvent = goodEvent && DPhill<2.8;

  if(goodEvent)  return 1;
  else return -1;
}
#endif // #ifdef HWWtree_cxx
