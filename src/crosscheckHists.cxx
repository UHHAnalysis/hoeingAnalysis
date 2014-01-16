#include "../SFrameTools/include/TTbarGen.h"
#include "include/crosscheckHists.h"
#include "../SFrameTools/include/EventCalc.h"
#include <iostream>
#include "../SFrameTools/include/Utils.h"
#include <TH2.h>
#include <TGraph.h> 
#include <TVectorT.h>
#include <TLorentzVector.h>

using namespace std;


// crosscheckHists::crosscheckHists(const char* name) : BaseHists(name){
//   // named default constructor
 
//   topJetConeSize = 1.5;
//   runWith4Jets = true;

 
// }


crosscheckHists::crosscheckHists(const char* name, TString mode,TString filename) : BaseHists(name){
  // named default constructor
 
 
  m_BTaggingMode = mode;
  m_BTagEffiFilenameMC=filename;
 
}



crosscheckHists::~crosscheckHists(){
  // default destructor, does nothing
}

void crosscheckHists::Init()
{
  Book( TH1F( "HTJets", "HT (GeV)", 50, 0, 3000));
  Book( TH1F( "nTopTags", "n top-tags", 10, 0, 10));
  Book( TH1F( "HTJetsSingleHiggsTagBin", "HT (GeV)", 50, 0, 3000));
  Book( TH1F( "HTJetsMultiHiggsTagBin", "HT (GeV)", 50, 0, 3000));

}


void crosscheckHists::Fill()
{ 
  // fill the histograms

  
  
  //for jet collection
  double ptcutjets=10;

  EventCalc* calc = EventCalc::Instance();
  bool IsRealData = calc->IsRealData();
  LuminosityHandler* lumih = calc->GetLumiHandler();
  // important: get the event weight
  double weight = calc->GetWeight();

  //bool IsRealData = calc->IsRealData();

  if(!IsRealData){
    weight=weight*HiggsBRweight();
  }

  std::vector<Jet>* jets = calc->GetJets();
  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
 
  double HTJets = 0.;
  int nhiggstag = 0;
  int nTopTags = 0;
  for(int i =0; i<bcc->topjets->size(); i++ ){
    if(bcc->topjets->at(i).pt()<150) continue;
    TopJet myJet = bcc->topjets->at(i); 
    if (HepTopTagWithMatch(myJet)) nTopTags+= 1;
    if (HiggsTag(myJet, e_CSVM, e_CSVM, m_BTaggingMode, m_BTagEffiFilenameMC)) nhiggstag++;
  }
 
  for (unsigned int itj=0;itj<bcc->jets->size();itj++){
    if(bcc->jets->at(itj).pt()<ptcutjets) continue;
    HTJets += jets->at(itj).pt();
  }

  Hist("HTJets")-> Fill(HTJets, weight);
  if (nhiggstag == 1) Hist("HTJetsSingleHiggsTagBin")-> Fill(HTJets, weight);
  if (nhiggstag > 1) Hist("HTJetsMultiHiggsTagBin")-> Fill(HTJets, weight);
  Hist("nTopTags") -> Fill(nTopTags, weight);
  

}
void crosscheckHists::Finish()
{
  // final calculations, like division and addition of certain histograms
  EventCalc* calc = EventCalc::Instance(); 
}


