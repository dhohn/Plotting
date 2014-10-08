#include "plotHistos.C"
#include "TFile.h"
#include "TCollection.h" //TIter
#include "TKey.h"
#include "TH1.h"

int main(int argc, char** argv)
{
  TFile* in1 = TFile::Open("169888_hist.root");
  TFile* in2 = TFile::Open("169888_weight_hist.root");
  TH1F* histos[2];
  TString legends[2];
  
  TIter next(in1->GetListOfKeys());
  TKey *key;
  while((key=(TKey*)next())) {
    histos[0] = (TH1F*)in1->Get(key->GetName());
    histos[1] = (TH1F*)in2->Get(key->GetName());
    legends[0] = "v4";
    legends[1] = "sys5";
    plotHistos(2,histos,legends);
  }
}
