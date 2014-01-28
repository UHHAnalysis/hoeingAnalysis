// $Id: cutflowCycle.cxx,v 1.2 2013/06/12 12:35:42 peiffer Exp $

#include <iostream>

using namespace std;

// Local include(s):
#include "include/cutflowCycle.h"
#include "../SFrameAnalysis/include/SelectionModules.h"
#include "../SFrameAnalysis/include/LikelihoodHists.h"
#include "include/cutflowHists.h"
#include "../SFrameTools/include/Utils.h"

ClassImp( cutflowCycle );

cutflowCycle::cutflowCycle()
  : AnalysisCycle() {

  // constructor, declare additional variables that should be 
  // obtained from the steering-xml file

  // set the integrated luminosity per bin for the lumi-yield control plots
  SetIntLumiPerBin(25.);
  DeclareProperty( "BTagEffi_Filename_MC", m_BTagEffiFilenameMC );
  DeclareProperty( "BTaggingMode", m_BTaggingMode);
  DeclareProperty( "Thetafile", m_thetainput);
 
}

cutflowCycle::~cutflowCycle() 
{
  // destructor
}

void cutflowCycle::BeginCycle() throw( SError ) 
{
  // Start of the job, general set-up and definition of 
  // objects are done here

  // Important: first call BeginCycle of base class
  AnalysisCycle::BeginCycle();

  return;




}

void cutflowCycle::EndCycle() throw( SError ) 
{
  // clean-up, info messages and final calculations after the analysis

  
  // call the base cycle class for all standard methods
  AnalysisCycle::EndCycle();

  return;

}

void cutflowCycle::BeginInputData( const SInputData& id ) throw( SError ) 
{
  // declaration of histograms and selections

  if(m_BTagEffiFilenameMC.size()>0)
    {
      m_BTagEffiFilenameMC += ".";
      m_BTagEffiFilenameMC += id.GetType();
      m_BTagEffiFilenameMC += ".";
      m_BTagEffiFilenameMC += id.GetVersion();
      m_BTagEffiFilenameMC += ".root";
    }
  else{
    m_BTagEffiFilenameMC="";
  }

  if(!(m_BTaggingMode.size()>0))  m_BTaggingMode="default";

  // Important: first call BeginInputData of base class
  AnalysisCycle::BeginInputData( id );
  
 


  // -------------------- set up the selections ---------------------------


 
  Selection* trigger = new Selection("HLT_HT750");
  Selection* nJets = new Selection("nJets");
  Selection* topTag = new Selection("topTag");
  Selection* topAndSubBTag = new Selection("topAndSubBTag");
  Selection* topAndSubBTagPlusHiggsTag = new Selection("topAndSubBTagPlusHiggsTag");
  Selection* HT1000 = new Selection("HT1000");
  Selection* HTSubJets720 = new Selection("HTSubJets720");
  

  //for QCD Estimation

  Selection* invertedTopTag = new Selection("invertedTopTag");
  Selection* fullyInvertedHiggsTag = new Selection("fullyInvertedHiggsTag");
  Selection* fullyInvertedTopAndHiggsTag = new Selection("fullyInvertedTopAndHiggsTag");


  //DO NOT use trigger selection in PROOF mode at the moment
  trigger->addSelectionModule(new TriggerSelection("HLT_HT750"));
  nJets->addSelectionModule(new NTopJetSelection(2, 99, 0., 99.));
  topTag->addSelectionModule(new NHEPTopTagSelection(1, 99));
  topAndSubBTag->addSelectionModule(new NHEPTopAndSubBTagSelection(1, 99, e_CSVM, m_BTaggingMode, m_BTagEffiFilenameMC));
  topAndSubBTagPlusHiggsTag->addSelectionModule(new HEPTopAndSubBTagPlusOtherHiggsTag(e_CSVM, e_CSVM, e_CSVM, m_BTaggingMode, m_BTagEffiFilenameMC, 60.));
  HT1000->addSelectionModule(new HTCut(1380.));
 HTSubJets720->addSelectionModule(new HTSubJetsCut(720.));
 
  invertedTopTag->addSelectionModule(new InvertedTopTagRegularBTagRegularHiggsTag(e_CSVM, e_CSVM, e_CSVM, m_BTaggingMode, m_BTagEffiFilenameMC, 60.));
  fullyInvertedHiggsTag->addSelectionModule(new RegularTopTagRegularBTagFullyInvertedHiggsTag(e_CSVM, e_CSVL, e_CSVL, m_BTaggingMode, m_BTagEffiFilenameMC));
  fullyInvertedTopAndHiggsTag->addSelectionModule(new InvertedTopTagRegularBTagFullyInvertedHiggsTag(e_CSVM, e_CSVL, e_CSVL, m_BTaggingMode, m_BTagEffiFilenameMC));


  
  RegisterSelection(trigger);
  RegisterSelection(nJets);
  RegisterSelection(topTag);
  RegisterSelection(topAndSubBTag);
  RegisterSelection(topAndSubBTagPlusHiggsTag);
  RegisterSelection(HT1000);
  RegisterSelection(HTSubJets720);
  RegisterSelection(invertedTopTag);
  RegisterSelection(fullyInvertedHiggsTag);
  RegisterSelection(fullyInvertedTopAndHiggsTag);




  // ---------------- set up the histogram collections --------------------

 RegisterHistCollection( new cutflowHists("NoCuts", m_BTaggingMode, m_BTagEffiFilenameMC) );
  // histograms after the top selection
  RegisterHistCollection( new cutflowHists("cutflow1", m_BTaggingMode, m_BTagEffiFilenameMC) );
  RegisterHistCollection( new cutflowHists("cutflow2", m_BTaggingMode, m_BTagEffiFilenameMC) );
  RegisterHistCollection( new cutflowHists("cutflow3", m_BTaggingMode, m_BTagEffiFilenameMC) );
  RegisterHistCollection( new cutflowHists("cutflow4", m_BTaggingMode, m_BTagEffiFilenameMC) );
  RegisterHistCollection( new cutflowHists("cutflow5", m_BTaggingMode, m_BTagEffiFilenameMC) );
  RegisterHistCollection( new cutflowHists("cutflow6", m_BTaggingMode, m_BTagEffiFilenameMC) ); 
  RegisterHistCollection( new cutflowHists("cutflow6HT720", m_BTaggingMode, m_BTagEffiFilenameMC) ); 
  RegisterHistCollection( new BTagEffHistsTPrime("BTagEff") );
  RegisterHistCollection( new LikelihoodHists("like500", m_thetainput, "500", m_BTaggingMode, m_BTagEffiFilenameMC) );
  RegisterHistCollection( new LikelihoodHists("like600", m_thetainput, "600", m_BTaggingMode, m_BTagEffiFilenameMC) );
  RegisterHistCollection( new LikelihoodHists("like700", m_thetainput, "700", m_BTaggingMode, m_BTagEffiFilenameMC) );
  RegisterHistCollection( new LikelihoodHists("like800", m_thetainput, "800", m_BTaggingMode, m_BTagEffiFilenameMC) );
  RegisterHistCollection( new LikelihoodHists("like900", m_thetainput, "900", m_BTaggingMode, m_BTagEffiFilenameMC) );
  RegisterHistCollection( new LikelihoodHists("like1000", m_thetainput, "1000", m_BTaggingMode, m_BTagEffiFilenameMC) );
  
  // important: initialise histogram collections after their definition
  InitHistos();

  return;

}

void cutflowCycle::EndInputData( const SInputData& id ) throw( SError ) 
{
  AnalysisCycle::EndInputData( id );
  return;

}

void cutflowCycle::BeginInputFile( const SInputData& id ) throw( SError ) 
{
  // Connect all variables from the Ntuple file with the ones needed for the analysis
  // The variables are commonly stored in the BaseCycleContaincer

  // important: call to base function to connect all variables to Ntuples from the input tree
  AnalysisCycle::BeginInputFile( id );

  return;

}

void cutflowCycle::ExecuteEvent( const SInputData& id, Double_t weight) throw( SError ) 
{
  // this is the most important part: here the full analysis happens
  // user should implement selections, filling of histograms and results

  // first step: call Execute event of base class to perform basic consistency checks
  // also, the good-run selection is performed there and the calculator is reset
  AnalysisCycle::ExecuteEvent( id, weight);
  Cleaner cleaner;
  


  // get the selections
  static Selection* trigger = GetSelection("HLT_HT750");
  static Selection* nJets = GetSelection("nJets");
  static Selection* topTag = GetSelection("topTag");
  static Selection* topAndSubBTag = GetSelection("topAndSubBTag");
  static Selection* topAndSubBTagPlusHiggsTag = GetSelection("topAndSubBTagPlusHiggsTag");
  static Selection* HT1000 = GetSelection("HT1000");
 static Selection* HTSubJets720 = GetSelection("HTSubJets720");
  static Selection* invertedTopTag = GetSelection("invertedTopTag");
  static Selection* fullyInvertedHiggsTag = GetSelection("fullyInvertedHiggsTag");
  static Selection* fullyInvertedTopAndHiggsTag = GetSelection("fullyInvertedTopAndHiggsTag");
  
  // get the histogram collections
  BaseHists* HistsNoCuts = GetHistCollection("NoCuts");
  BaseHists* Histscutflow1 = GetHistCollection("cutflow1");
  BaseHists* Histscutflow2 = GetHistCollection("cutflow2");
  BaseHists* Histscutflow3 = GetHistCollection("cutflow3");
  BaseHists* Histscutflow4 = GetHistCollection("cutflow4");
  BaseHists* Histscutflow5 = GetHistCollection("cutflow5");
  BaseHists* Histscutflow6 = GetHistCollection("cutflow6");
  BaseHists* Histscutflow6HT720 = GetHistCollection("cutflow6HT720");
  BaseHists* BTagEff_Hists = GetHistCollection("BTagEff");
  BaseHists* like500 = GetHistCollection("like500");
  BaseHists* like600 = GetHistCollection("like600");
  BaseHists* like700 = GetHistCollection("like700");
  BaseHists* like800 = GetHistCollection("like800");
  BaseHists* like900 = GetHistCollection("like900");
  BaseHists* like1000 = GetHistCollection("like1000");

  // start the analysis
 

  EventCalc* calc = EventCalc::Instance();
  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
  bool IsRealData = calc->IsRealData();

  bool invertTopTag = 0;
  bool invertHiggsTag = 0;
  bool invertTopAndHiggsTag = 0;
  bool regularSelection = 1;
  bool FillBTagEfficiency = 0;

  if (m_sys_unc==e_JER){
    if (m_sys_var==e_Up) cleaner.ApplyJERVariationUp();
    if (m_sys_var==e_Down) cleaner.ApplyJERVariationDown();
  }

  if (!bcc->isRealData && bcc->jets) cleaner.JetEnergyResolutionShifter();
  // HistsNoCuts->Fill();

  if(trigger->passSelection(bcc)) Histscutflow1->Fill();
  else throw SError( SError::SkipEvent );
  if(HTSubJets720->passSelection(bcc)) Histscutflow2->Fill();
  else throw SError( SError::SkipEvent );  
  if(nJets->passSelection(bcc)) Histscutflow3->Fill();
  else throw SError( SError::SkipEvent );

  // if(!trigger->passSelection(bcc)) throw SError( SError::SkipEvent );
  //  if(!nJets->passSelection(bcc))throw SError( SError::SkipEvent );
  
  // if(!HT1000->passSelection(bcc))  throw SError( SError::SkipEvent );
  if(invertTopTag){
    if (!invertedTopTag->passSelection(bcc)) throw SError( SError::SkipEvent );
    //   Histscutflow5->Fill();
    // else throw SError( SError::SkipEvent );
  }
  if (invertHiggsTag){
    if (fullyInvertedHiggsTag->passSelection(bcc))Histscutflow5->Fill();
    else throw SError( SError::SkipEvent );
  }
  if (invertTopAndHiggsTag){
    if (fullyInvertedTopAndHiggsTag->passSelection(bcc))Histscutflow5->Fill();
    else throw SError( SError::SkipEvent );
  }

  if (regularSelection){
    
    if(topTag->passSelection(bcc)) Histscutflow4->Fill();
    else throw SError( SError::SkipEvent );
     if (IsRealData == false)BTagEff_Hists->Fill(); 
   
    if(topAndSubBTag->passSelection(bcc))Histscutflow5->Fill();
    else throw SError( SError::SkipEvent );
    if(topAndSubBTagPlusHiggsTag->passSelection(bcc))Histscutflow6->Fill();
    else throw SError( SError::SkipEvent );

    // if(!topTag->passSelection(bcc)) throw SError( SError::SkipEvent );
    // if(!topAndSubBTag->passSelection(bcc))throw SError( SError::SkipEvent );
    // if(!topAndSubBTagPlusHiggsTag->passSelection(bcc)) throw SError( SError::SkipEvent );
  }

  if (FillBTagEfficiency){
    if(topTag->passSelection(bcc)) BTagEff_Hists->Fill(); 
    else throw SError( SError::SkipEvent );
  }
  // if(HT1000->passSelection(bcc)) Histscutflow6->Fill();
  // else throw SError( SError::SkipEvent );

   // if(HTSubJets720->passSelection(bcc)) Histscutflow6HT720->Fill();
   // else throw SError( SError::SkipEvent );  

   // if(!HTSubJets720->passSelection(bcc)) throw SError( SError::SkipEvent );  

  // like500->Fill();
  // like600->Fill();
  // like700->Fill();
  // like800->Fill();
  // like900->Fill();
  // like1000->Fill();

  // WriteOutputTree();

  return;
  
}

