#include "../SFrameTools/include/TTbarGen.h"
#include "include/cutflowHists.h"
#include "../SFrameTools/include/EventCalc.h"
#include <iostream>
#include "../SFrameTools/include/Utils.h"
#include <TH2.h>
#include <TGraph.h> 
#include <TVectorT.h>
#include <TLorentzVector.h>

using namespace std;


// cutflowHists::cutflowHists(const char* name) : BaseHists(name){
//   // named default constructor 
// }


cutflowHists::cutflowHists(const char* name, TString mode,TString filename) : BaseHists(name){
  // named default constructor 
  topJetConeSize = 1.5;
  runWith4Jets = true;
  m_BTaggingMode = mode;
  m_BTagEffiFilenameMC=filename;
}



cutflowHists::~cutflowHists(){
  // default destructor, does nothing
}

void cutflowHists::Init()
{
  Book( TH1F( "numberEvents", "", 1, 0, 1));
  Book( TH1F( "nTopJets", "n jets", 10, 0, 10));
  Book( TH1F( "nJets", "n jets", 20, 0, 20));
  Book( TH1F( "nTopTags", "n top-tags", 10, 0, 10));
  Book( TH1F( "nSubJetBTagsL", "n subjet b-tags", 10, 0, 10));
  Book( TH1F( "nSubJetBTagsM", "n subjet b-tags", 10, 0, 10));
  Book( TH1F( "nSubJetBTagsT", "n subjet b-tags", 10, 0, 10));
  Book( TH1F( "nTopTagsWithSubBTagL", "n top-tags + b-tagged subjet", 10, 0, 10));
  Book( TH1F( "nTopTagsWithSubBTagM", "n top-tags + b-tagged subjet", 10, 0, 10));
  Book( TH1F( "nTopTagsWithSubBTagT", "n top-tags + b-tagged subjet", 10, 0, 10));
  Book( TH1F( "nHiggsTagsLL", "n Higgs-tags", 10, 0, 10));
  Book( TH1F( "nHiggsTagsLM", "n Higgs-tags", 10, 0, 10));
  Book( TH1F( "nHiggsTagsMM", "n Higgs-tags", 10, 0, 10));
  Book( TH1F( "nHiggsTagsMT", "n Higgs-tags", 10, 0, 10));
  Book( TH1F( "nHiggsTagsTT", "n Higgs-tags", 10, 0, 10));
  
  Book( TH1F( "HTJets", "HT (GeV)", 50, 0, 3000));
  Book( TH1F( "HTJetsLept", "HT (GeV)", 50, 0, 3000));
  Book( TH1F( "HTSubJets", "HT (GeV)", 50, 0, 3000));
  
  Book( TH1F( "HTJetsSingleHiggsTagBin", "HT (GeV)", 50, 0, 3000));
  Book( TH1F( "HTJetsLeptSingleHiggsTagBin", "HT (GeV)", 50, 0, 3000));
  Book( TH1F( "HTSubJetsSingleHiggsTagBin", "HT (GeV)", 50, 0, 3000));
 
  Book( TH1F( "HTJetsMultiHiggsTagBin", "HT (GeV)", 50, 0, 3000));
  Book( TH1F( "HTJetsLeptMultiHiggsTagBin", "HT (GeV)", 50, 0, 3000));
  Book( TH1F( "HTSubJetsMultiHiggsTagBin", "HT (GeV)", 50, 0, 3000));

  Book( TH1F( "HTJetsSingleTopTagBin", "HT (GeV)", 50, 0, 3000));
  Book( TH1F( "HTJetsLeptSingleTopTagBin", "HT (GeV)", 50, 0, 3000));
  Book( TH1F( "HTSubJetsSingleTopTagBin", "HT (GeV)", 50, 0, 3000));

  Book( TH1F( "HTJetsMultiTopTagBin", "HT (GeV)", 50, 0, 3000));
  Book( TH1F( "HTJetsLeptMultiTopTagBin", "HT (GeV)", 50, 0, 3000));
  Book( TH1F( "HTSubJetsMultiTopTagBin", "HT (GeV)", 50, 0, 3000));


  Book( TH1F( "HTJetsSingleHiggsSingleTopTagBin", "HT (GeV)", 50, 0, 3000));
  Book( TH1F( "HTJetsLeptSingleHiggsSingleTopTagBin", "HT (GeV)", 50, 0, 3000));
  Book( TH1F( "HTSubJetsSingleHiggsSingleTopTagBin", "HT (GeV)", 50, 0, 3000));

  Book( TH1F( "HTJetsSingleHiggsMultiTopTagBin", "HT (GeV)", 50, 0, 3000));
  Book( TH1F( "HTJetsLeptSingleHiggsMultiTopTagBin", "HT (GeV)", 50, 0, 3000));
  Book( TH1F( "HTSubJetsSingleHiggsMultiTopTagBin", "HT (GeV)", 50, 0, 3000));
 
 
  Book( TH1F( "HTJetsMultiHiggsSingleTopTagBin", "HT (GeV)", 50, 0, 3000));
  Book( TH1F( "HTJetsLeptMultiHiggsSingleTopTagBin", "HT (GeV)", 50, 0, 3000));
  Book( TH1F( "HTSubJetsMultiHiggsSingleTopTagBin", "HT (GeV)", 50, 0, 3000));

  Book( TH1F( "HTJetsMultiHiggsMultiTopTagBin", "HT (GeV)", 50, 0, 3000));
  Book( TH1F( "HTJetsLeptMultiHiggsMultiTopTagBin", "HT (GeV)", 50, 0, 3000));
  Book( TH1F( "HTSubJetsMultiHiggsMultiTopTagBin", "HT (GeV)", 50, 0, 3000));

  Book( TH1F( "HTJetsHighPt", "HT (GeV)", 50, 0, 3000));
  Book( TH1F( "HTTopJets", "HT (GeV)", 50, 0, 3000));
  Book( TH1F( "HiggsCandidateMass", "mass of Higgs candidate (GeV)", 25, 0, 300));
  Book( TH1F( "HiggsCandidateMassFromSubjets", "mass of Higgs candidate (GeV)", 25, 0, 300));
  Book( TH1F( "HiggsCandidateMassFromBTaggedSubjets", "mass of Higgs candidate (GeV)", 25, 0, 300));

  Book( TH1F( "HiggsCandidateMassFromBTaggedSubjetsSingleHiggsTagBin", "mass of Higgs candidate (GeV)", 25, 0, 300));
  Book( TH1F( "HiggsCandidateMassFromBTaggedSubjetsMultiHiggsTagBin", "mass of Higgs candidate (GeV)", 25, 0, 300));
  Book( TH1F( "HiggsCandidateMassFromBTaggedSubjetsSingleTopTagBin", "mass of Higgs candidate (GeV)", 25, 0, 300));
  Book( TH1F( "HiggsCandidateMassFromBTaggedSubjetsMultiTopTagBin", "mass of Higgs candidate (GeV)", 25, 0, 300));
  Book( TH1F( "HiggsCandidateMassFromBTaggedSubjetsSingleHiggsSingleTopTagBin", "mass of Higgs candidate (GeV)", 25, 0, 300));
  Book( TH1F( "HiggsCandidateMassFromBTaggedSubjetsSingleHiggsMultiTopTagBin", "mass of Higgs candidate (GeV)", 25, 0, 300));
  Book( TH1F( "HiggsCandidateMassFromBTaggedSubjetsMultiHiggsSingleTopTagBin", "mass of Higgs candidate (GeV)", 25, 0, 300));
  Book( TH1F( "HiggsCandidateMassFromBTaggedSubjetsMultiHiggsMultiTopTagBin", "mass of Higgs candidate (GeV)", 25, 0, 300));

  Book( TH1F( "InvMassCandidates", "m_{reco}(T') (GeV)", 50, 0, 2000));

}


void cutflowHists::Fill()
{ 
  // fill the histograms

  //for topjet copllection
  double ptcut=150;
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

  int run = calc->GetRunNum();
  int lumiblock = calc->GetLumiBlock();
  int Npvs = calc->GetPrimaryVertices()->size();
  std::vector<Jet>* jets = calc->GetJets();
  int Njets = 0;
  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
  for (unsigned int itj=0;itj<bcc->jets->size();itj++){
    if(bcc->jets->at(itj).pt()<ptcutjets) continue;
    Njets=Njets+1;
  }
 
  if (IsRealData == false)TTbarGen* Decay = calc->GetTTbarGen();

  // Hist("NPrimaryVertices")-> Fill(Npvs, weight);
  Hist("numberEvents") -> Fill(.5, weight);
  Hist("nJets") -> Fill(Njets, weight);
  int Ntopjets=0;

 //  for (unsigned int itj=0;itj<bcc->topjets->size();itj++){
//     if(bcc->topjets->at(itj).pt()<ptcut) continue;
//     Ntopjets=Ntopjets+1;
//     //  Hist("ptJets") -> Fill( bcc->topjets->at(itj).pt(), weight);
//     if(Ntopjets==1){
//       Hist("ptJet1") -> Fill( bcc->topjets->at(itj).pt(), weight);
//     }
//     if(Ntopjets==2){
//       Hist("ptJet2") -> Fill( bcc->topjets->at(itj).pt(), weight);
//     }
//     if(Ntopjets==3){
//       Hist("ptJet3") -> Fill( bcc->topjets->at(itj).pt(), weight);
//     }
//     if(Ntopjets==4){
//       Hist("ptJet4") -> Fill( bcc->topjets->at(itj).pt(), weight);
//     }
//     if(Ntopjets>4) break;
//   }
  Hist("nTopJets") -> Fill(Ntopjets, weight);

  int nTopTags = 0;
  int indexFirstTopJet = -99;
  int indexTopJet1 = -99;
  int indexTopJet2 = -99;
  int indexHiggs1= -99;
  int indexHiggs2= -99;
  int nSubTagsFirstTopTaggedJet = 0;
  int nSubTagsL = 0;
  int nSubTagsM = 0;
  int nSubTagsT = 0;
  int countTopTagPlusSubBTagL =0;
  int countTopTagPlusSubBTagM =0;
  int countTopTagPlusSubBTagT =0;
  int countHiggsTagLL = 0;
  int countHiggsTagLM = 0;
  int countHiggsTagMM = 0;
  int countHiggsTagMT = 0;
  int countHiggsTagTT = 0;
  int finallySelected = 1;
  int indexTopCandidate = -99;
  int indexHiggsCandidate = -99;
  int nheptoptag=0;
  int nhiggstag=0;
 int nhiggstagWithCut=0;
  std::vector<int> topTaggedJets;
  std::vector<int> HiggsTaggedJets;

  //find top and higgs candidate used in the selection
  for(unsigned int i=0; i< bcc->topjets->size(); ++i){
    TopJet topjet =  bcc->topjets->at(i);

    if(HepTopTagWithMatch(topjet) && subJetBTagTop(topjet, e_CSVM, m_BTaggingMode, m_BTagEffiFilenameMC)>=1){
      nheptoptag++;
      topTaggedJets.push_back(i);
    }
    if (HiggsTag(topjet, e_CSVM, e_CSVM, m_BTaggingMode, m_BTagEffiFilenameMC)){
      nhiggstag++;
      if (HiggsMassFromBTaggedSubjets(topjet, e_CSVM, m_BTaggingMode, m_BTagEffiFilenameMC)>60.){
	nhiggstagWithCut ++;
	HiggsTaggedJets.push_back(i);
      }
    }
  }
  if (nheptoptag == 0){
    finallySelected = 0;
    if (nhiggstagWithCut != 0){
      indexHiggsCandidate = HiggsTaggedJets[0];
    }
  }
  if (nhiggstagWithCut == 0){
    finallySelected = 0; 
    if(nheptoptag != 0){
      indexTopCandidate = topTaggedJets[0];
    }
  }
  if(nheptoptag == 1 && nhiggstagWithCut == 1 && topTaggedJets[0] == HiggsTaggedJets[0]){
    finallySelected = 0;
    indexTopCandidate = topTaggedJets[0];
  } 
  if (finallySelected == 1){
    if (topTaggedJets[0] != HiggsTaggedJets[0]){
      indexTopCandidate = topTaggedJets[0];
      indexHiggsCandidate = HiggsTaggedJets[0];
    }
    if (topTaggedJets[0] == HiggsTaggedJets[0]){
      if (HiggsTaggedJets.size()>1){
	indexTopCandidate = topTaggedJets[0];
	indexHiggsCandidate = HiggsTaggedJets[1];
      }
      if(topTaggedJets.size()>1){
	indexTopCandidate = topTaggedJets[1];
	indexHiggsCandidate = HiggsTaggedJets[0];
      }     
    }
  }


  double HTJets = 0.;
  double HTJetsLept = 0.;
  double HTSubJets = 0.;
  std::vector<Particle> subjets_top;
  double HTJetsHighPt = 0.;
  double pairwiseMassCrit1 = -99;
  double pairwiseMassCrit2 = -99;
  double WMassHEP = -99;

  for (unsigned int itj=0;itj<bcc->jets->size();itj++){
    if(bcc->jets->at(itj).pt()<ptcutjets) continue;
    HTJets += jets->at(itj).pt();
  }

  HTJetsLept = calc->GetHT();
 

 for (unsigned int itj = 0; itj < bcc->topjets->size(); itj++){
    TopJet topjet = bcc->topjets->at(itj);
    subjets_top=topjet.subjets();
    for (unsigned int subj = 0; subj < subjets_top.size(); subj++){
      HTSubJets += subjets_top.at(subj).pt();
    }
  }
  
  
  int HTTopJets = 0.;

  for(int i =0; i<bcc->topjets->size(); i++ ){
    TopJet myJet = bcc->topjets->at(i);
    HTTopJets += myJet.pt();
    pairwiseMassCrit1 = HepTopTagPairwiseMassWithMatch1(myJet);
    pairwiseMassCrit2 = HepTopTagPairwiseMassWithMatch2(myJet);
    WMassHEP = WMassWithMatch(myJet);
   //  Hist("pairwiseMassCriterium1AllJets") -> Fill(pairwiseMassCrit1, weight);
   // Hist("pairwiseMassCriterium2AllJets") -> Fill(pairwiseMassCrit2, weight);
    //Hist("WMass")-> Fill(WMassHEP, weight);   
 
  //   if (i == indexTopCandidate){
//       Hist("topCandidatePt") -> Fill(HepTopTagMatchPt(myJet), weight);
//       Hist("topCandidateMass") -> Fill(HepTopTagMatchMass(myJet), weight);
//     }
    
     if (HepTopTagWithMatch(myJet)){
//       nTopTags+= 1;
//       Hist("pairwiseMassCriterium1AfterTag") -> Fill(pairwiseMassCrit1, weight);
//       Hist("pairwiseMassCriterium2AfterTag") -> Fill(pairwiseMassCrit2, weight);
//       Hist("WMassAfterTag") -> Fill(WMassHEP, weight);

      if( nTopTags == 1 && indexTopJet1 == -99) indexTopJet1 = i;
      if( nTopTags == 2 && indexTopJet2 == -99) indexTopJet2 = i;

      nSubTagsL = subJetBTagTop(myJet, e_CSVL,m_BTaggingMode, m_BTagEffiFilenameMC);
      nSubTagsM = subJetBTagTop(myJet, e_CSVM,m_BTaggingMode, m_BTagEffiFilenameMC);
      nSubTagsT = subJetBTagTop(myJet, e_CSVT,m_BTaggingMode, m_BTagEffiFilenameMC);      
      Hist("nSubJetBTagsL") -> Fill(nSubTagsL, weight);//how many loose wp subjet b-tags do we have on a top tagged jet (any top tagged jet)
      Hist("nSubJetBTagsM") -> Fill(nSubTagsM, weight);
      Hist("nSubJetBTagsT") -> Fill(nSubTagsT, weight);

      if (nSubTagsL > 0) countTopTagPlusSubBTagL++;
      if (nSubTagsM > 0) countTopTagPlusSubBTagM++;  
      if (nSubTagsT > 0) countTopTagPlusSubBTagT++;
      if (countTopTagPlusSubBTagM == 1 && indexFirstTopJet == -99)indexFirstTopJet = i;
    }

    if(i != indexTopCandidate){
      if (HiggsTag(myJet, e_CSVL, e_CSVL,m_BTaggingMode, m_BTagEffiFilenameMC)) countHiggsTagLL++;  
      if (HiggsTag(myJet, e_CSVL, e_CSVM,m_BTaggingMode, m_BTagEffiFilenameMC)) countHiggsTagLM++; 
      if (HiggsTag(myJet, e_CSVM, e_CSVM,m_BTaggingMode, m_BTagEffiFilenameMC)) countHiggsTagMM++;
      if (HiggsTag(myJet, e_CSVM, e_CSVT,m_BTaggingMode, m_BTagEffiFilenameMC)) countHiggsTagMT++; 
      if (HiggsTag(myJet, e_CSVT, e_CSVT,m_BTaggingMode, m_BTagEffiFilenameMC)) countHiggsTagTT++;
      if (countHiggsTagLL == 1 && indexHiggs1 == -99) indexHiggs1 = i;
      if (countHiggsTagLL == 2 && indexHiggs2 == -99) indexHiggs2 = i;     
    }
  }
  
 

  Hist("HTTopJets")-> Fill(HTTopJets, weight);
  Hist("nTopTags") -> Fill(nTopTags, weight);
  Hist("nTopTagsWithSubBTagL") -> Fill(countTopTagPlusSubBTagL, weight);
  Hist("nTopTagsWithSubBTagM") -> Fill(countTopTagPlusSubBTagM, weight);
  Hist("nTopTagsWithSubBTagT") -> Fill(countTopTagPlusSubBTagT, weight);
  Hist("nHiggsTagsLL") -> Fill(countHiggsTagLL, weight);
  Hist("nHiggsTagsLM") -> Fill(countHiggsTagLM, weight);
  Hist("nHiggsTagsMM") -> Fill(countHiggsTagMM, weight);
  Hist("nHiggsTagsMT") -> Fill(countHiggsTagMT, weight);
  Hist("nHiggsTagsTT") -> Fill(countHiggsTagTT, weight);
  TopJet higgsCandidateJet;
  if (indexHiggsCandidate != -99){

    higgsCandidateJet = bcc->topjets->at(indexHiggsCandidate);
    // Hist("HiggsCandidatePt") -> Fill(higgsCandidateJet.pt(), weight);
    Hist("HiggsCandidateMass") -> Fill(higgsCandidateJet.v4().M(), weight);
    Hist("HiggsCandidateMassFromSubjets") -> Fill( HiggsMassFromSubjets(higgsCandidateJet),weight);
    Hist("HiggsCandidateMassFromBTaggedSubjets") -> Fill( HiggsMassFromBTaggedSubjets(higgsCandidateJet, e_CSVM, m_BTaggingMode, m_BTagEffiFilenameMC),weight);
  }

  Hist("HTJets")-> Fill(HTJets, weight);
  Hist("HTJetsLept")-> Fill(HTJetsLept, weight);
  Hist("HTSubJets")-> Fill(HTSubJets, weight);

  if (nhiggstag == 1){
    Hist("HTJetsSingleHiggsTagBin")-> Fill(HTJets, weight);
    Hist("HTJetsLeptSingleHiggsTagBin")-> Fill(HTJetsLept, weight);
    Hist("HTSubJetsSingleHiggsTagBin")-> Fill(HTSubJets, weight);
    if (indexHiggsCandidate != -99) Hist("HiggsCandidateMassFromBTaggedSubjetsSingleHiggsTagBin") -> Fill( HiggsMassFromBTaggedSubjets(higgsCandidateJet, e_CSVM, m_BTaggingMode, m_BTagEffiFilenameMC),weight);
    if (nheptoptag == 1){
      Hist("HTJetsSingleHiggsSingleTopTagBin")-> Fill(HTJets, weight);
      Hist("HTJetsLeptSingleHiggsSingleTopTagBin")-> Fill(HTJetsLept, weight);
      Hist("HTSubJetsSingleHiggsSingleTopTagBin")-> Fill(HTSubJets, weight);
       if (indexHiggsCandidate != -99) Hist("HiggsCandidateMassFromBTaggedSubjetsSingleHiggsSingleTopTagBin") -> Fill( HiggsMassFromBTaggedSubjets(higgsCandidateJet, e_CSVM, m_BTaggingMode, m_BTagEffiFilenameMC),weight);

      if (nheptoptag >= 2){
	Hist("HTJetsSingleHiggsMultiTopTagBin")-> Fill(HTJets, weight);
	Hist("HTJetsLeptSingleHiggsMultiTopTagBin")-> Fill(HTJetsLept, weight);
	Hist("HTSubJetsSingleHiggsMultiTopTagBin")-> Fill(HTSubJets, weight);
	 if (indexHiggsCandidate != -99)Hist("HiggsCandidateMassFromBTaggedSubjetsSingleHiggsMultiTopTagBin") -> Fill( HiggsMassFromBTaggedSubjets(higgsCandidateJet, e_CSVM, m_BTaggingMode, m_BTagEffiFilenameMC),weight);
      }
    }
  }

  if (nhiggstag >= 2){
    Hist("HTJetsMultiHiggsTagBin")-> Fill(HTJets, weight);
    Hist("HTJetsLeptMultiHiggsTagBin")-> Fill(HTJetsLept, weight);
    Hist("HTSubJetsMultiHiggsTagBin")-> Fill(HTSubJets, weight);
     if (indexHiggsCandidate != -99)Hist("HiggsCandidateMassFromBTaggedSubjetsMultiHiggsTagBin") -> Fill( HiggsMassFromBTaggedSubjets(higgsCandidateJet, e_CSVM, m_BTaggingMode, m_BTagEffiFilenameMC),weight);

    if (nheptoptag == 1){
      Hist("HTJetsMultiHiggsSingleTopTagBin")-> Fill(HTJets, weight);
      Hist("HTJetsLeptMultiHiggsSingleTopTagBin")-> Fill(HTJetsLept, weight);
      Hist("HTSubJetsMultiHiggsSingleTopTagBin")-> Fill(HTSubJets, weight);
       if (indexHiggsCandidate != -99)Hist("HiggsCandidateMassFromBTaggedSubjetsMultiHiggsSingleTopTagBin") -> Fill( HiggsMassFromBTaggedSubjets(higgsCandidateJet, e_CSVM, m_BTaggingMode, m_BTagEffiFilenameMC),weight);
    }
    if (nheptoptag >= 2){
      Hist("HTJetsMultiHiggsMultiTopTagBin")-> Fill(HTJets, weight);
      Hist("HTJetsLeptMultiHiggsMultiTopTagBin")-> Fill(HTJetsLept, weight);
      Hist("HTSubJetsMultiHiggsMultiTopTagBin")-> Fill(HTSubJets, weight);
       if (indexHiggsCandidate != -99)Hist("HiggsCandidateMassFromBTaggedSubjetsMultiHiggsMultiTopTagBin") -> Fill( HiggsMassFromBTaggedSubjets(higgsCandidateJet, e_CSVM, m_BTaggingMode, m_BTagEffiFilenameMC),weight);
    }
  }

  if (nheptoptag == 1){
    Hist("HTJetsSingleTopTagBin")-> Fill(HTJets, weight);
    Hist("HTJetsLeptSingleTopTagBin")-> Fill(HTJetsLept, weight);
    Hist("HTSubJetsSingleTopTagBin")-> Fill(HTSubJets, weight);
     if (indexHiggsCandidate != -99)Hist("HiggsCandidateMassFromBTaggedSubjetsSingleTopTagBin") -> Fill( HiggsMassFromBTaggedSubjets(higgsCandidateJet, e_CSVM, m_BTaggingMode, m_BTagEffiFilenameMC),weight);
  }
  if (nheptoptag >= 2){
    Hist("HTJetsMultiTopTagBin")-> Fill(HTJets, weight);
    Hist("HTJetsLeptMultiTopTagBin")-> Fill(HTJetsLept, weight);
    Hist("HTSubJetsMultiTopTagBin")-> Fill(HTSubJets, weight);
     if (indexHiggsCandidate != -99)Hist("HiggsCandidateMassFromBTaggedSubjetsMultiTopTagBin") -> Fill( HiggsMassFromBTaggedSubjets(higgsCandidateJet, e_CSVM, m_BTaggingMode, m_BTagEffiFilenameMC),weight);
  }
  


  TopJet combinationJet1;
  TLorentzVector jet1Vec;
  TopJet combinationJet2;
  TLorentzVector jet2Vec;
  TLorentzVector newVector;
  TopJet topCandidateJet;
  TopJet HiggsCandidateJet;
  double InvMassCandidates = -99;

  if(indexTopCandidate != -99 && indexHiggsCandidate != -99){
    topCandidateJet = bcc->topjets->at(indexTopCandidate);
    HiggsCandidateJet = bcc->topjets->at(indexHiggsCandidate);
    jet1Vec.SetPtEtaPhiE(topCandidateJet.pt(), topCandidateJet.eta(), topCandidateJet.phi(), topCandidateJet.energy());
    jet2Vec.SetPtEtaPhiE(HiggsCandidateJet.pt(), HiggsCandidateJet.eta(), HiggsCandidateJet.phi(), HiggsCandidateJet.energy());
    newVector = jet1Vec+jet2Vec;
    InvMassCandidates = newVector.M();    
  }
  Hist("InvMassCandidates") -> Fill(InvMassCandidates, weight);



     
 //  if(IsRealData == false){
//     bool secondTPrime = false;
//     GenParticle TPrime1;
//     GenParticle TPrime2;

//     for( int i=0; i<bcc->genparticles->size(); ++i){
 
//       GenParticle genp = bcc->genparticles->at(i); 

//       if (abs(genp.pdgId()) > 15000){//selects the Tprime
// 	if(secondTPrime == false) TPrime1 = genp;
// 	if(secondTPrime == true)  TPrime2 = genp;
// 	int indexDaughter1 = genp.daughter(bcc->genparticles,1)->index();
// 	int indexDaughter2 = genp.daughter(bcc->genparticles,2)->index();
// 	double deltaRDaughters = bcc->genparticles->at(indexDaughter1).deltaR(bcc->genparticles->at(indexDaughter2));
// 	double deltaPhiDaughters = bcc->genparticles->at(indexDaughter1).deltaPhi(bcc->genparticles->at(indexDaughter2));
// 	Hist("deltaRDaughters") ->  Fill(deltaRDaughters);
// 	Hist("deltaPhiDaughters") ->  Fill(deltaPhiDaughters);
// 	secondTPrime = true;
//       }
//     }
  
//     double deltaPhiMothers = TPrime1.deltaPhi(TPrime2);
//     Hist("deltaPhiMothers") -> Fill(deltaPhiMothers);
//   }
}
void cutflowHists::Finish()
{
  // final calculations, like division and addition of certain histograms
  EventCalc* calc = EventCalc::Instance(); 
}


