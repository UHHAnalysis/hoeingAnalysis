// $Id: cutflowCycle.cxx,v 1.2 2013/06/12 12:35:42 peiffer Exp $

#include <iostream>

using namespace std;

// Local include(s):
#include "include/crosscheckCycle.h"
#include "../SFrameAnalysis/include/SelectionModules.h"
#include "include/crosscheckHists.h"
#include "../SFrameTools/include/Utils.h"

ClassImp( crosscheckCycle );

crosscheckCycle::crosscheckCycle()
  : AnalysisCycle() {

  // constructor, declare additional variables that should be 
  // obtained from the steering-xml file

  // set the integrated luminosity per bin for the lumi-yield control plots
  SetIntLumiPerBin(25.);
  DeclareProperty( "BTagEffi_Filename_MC", m_BTagEffiFilenameMC );
  DeclareProperty( "BTaggingMode", m_BTaggingMode);
 
}

crosscheckCycle::~crosscheckCycle() 
{
  // destructor
}

void crosscheckCycle::BeginCycle() throw( SError ) 
{
  // Start of the job, general set-up and definition of 
  // objects are done here

  // Important: first call BeginCycle of base class
  AnalysisCycle::BeginCycle();

  return;




}

void crosscheckCycle::EndCycle() throw( SError ) 
{
  // clean-up, info messages and final calculations after the analysis

  
  // call the base cycle class for all standard methods
  AnalysisCycle::EndCycle();

  return;

}

void crosscheckCycle::BeginInputData( const SInputData& id ) throw( SError ) 
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

 


  //DO NOT use trigger selection in PROOF mode at the moment
  trigger->addSelectionModule(new TriggerSelection("HLT_HT750"));
  nJets->addSelectionModule(new NTopJetSelection(2, 99, 200., 2.4));
  topTag->addSelectionModule(new NHEPTopTagSelection(1, 99));
  topAndSubBTag->addSelectionModule(new NHEPTopAndSubBTagSelection(1, 99, e_CSVM, m_BTaggingMode, m_BTagEffiFilenameMC));
  topAndSubBTagPlusHiggsTag->addSelectionModule(new HEPTopAndSubBTagPlusOtherHiggsTag(e_CSVM, e_CSVM, e_CSVM, m_BTaggingMode, m_BTagEffiFilenameMC));
  HT1000->addSelectionModule(new HTCut(1000.));
 
  
  RegisterSelection(trigger);
  RegisterSelection(nJets);
  RegisterSelection(topTag);
  RegisterSelection(topAndSubBTag);
  RegisterSelection(topAndSubBTagPlusHiggsTag);
  RegisterSelection(HT1000);
 




  // ---------------- set up the histogram collections --------------------


  RegisterHistCollection( new crosscheckHists("crosscheck3",m_BTaggingMode,m_BTagEffiFilenameMC) );
  RegisterHistCollection( new crosscheckHists("crosscheck4",m_BTaggingMode,m_BTagEffiFilenameMC) );
  RegisterHistCollection( new crosscheckHists("crosscheck5",m_BTaggingMode,m_BTagEffiFilenameMC) );
  RegisterHistCollection( new crosscheckHists("crosscheck6",m_BTaggingMode,m_BTagEffiFilenameMC) );

  // histograms without any cuts
  // RegisterHistCollection( new crosscheckHists("NoCuts") );
//   // histograms after the top selection
//   RegisterHistCollection( new crosscheckHists("crosscheck1") );
//   RegisterHistCollection( new crosscheckHists("crosscheck2") );
//   RegisterHistCollection( new crosscheckHists("crosscheck3") );
//   RegisterHistCollection( new crosscheckHists("crosscheck4") );
//   RegisterHistCollection( new crosscheckHists("crosscheck5") );
//   RegisterHistCollection( new crosscheckHists("crosscheck6") );
 

  
  // important: initialise histogram collections after their definition
  InitHistos();

  return;

}

void crosscheckCycle::EndInputData( const SInputData& id ) throw( SError ) 
{
  AnalysisCycle::EndInputData( id );
  return;

}

void crosscheckCycle::BeginInputFile( const SInputData& id ) throw( SError ) 
{
  // Connect all variables from the Ntuple file with the ones needed for the analysis
  // The variables are commonly stored in the BaseCycleContaincer

  // important: call to base function to connect all variables to Ntuples from the input tree
  AnalysisCycle::BeginInputFile( id );

  return;

}

void crosscheckCycle::ExecuteEvent( const SInputData& id, Double_t weight) throw( SError ) 
{
  // this is the most important part: here the full analysis happens
  // user should implement selections, filling of histograms and results

  // first step: call Execute event of base class to perform basic consistency checks
  // also, the good-run selection is performed there and the calculator is reset
  AnalysisCycle::ExecuteEvent( id, weight);
   


  // get the selections
  static Selection* trigger = GetSelection("HLT_HT750");
  static Selection* nJets = GetSelection("nJets");
  static Selection* topTag = GetSelection("topTag");
  static Selection* topAndSubBTag = GetSelection("topAndSubBTag");
  static Selection* topAndSubBTagPlusHiggsTag = GetSelection("topAndSubBTagPlusHiggsTag");
  static Selection* HT1000 = GetSelection("HT1000");
 
  
  // get the histogram collections
 
  // BaseHists* Histscrosscheck3 = GetHistCollection("crosscheck3");
//   BaseHists* Histscrosscheck4 = GetHistCollection("crosscheck4");
//   BaseHists* Histscrosscheck5 = GetHistCollection("crosscheck5");
  BaseHists* Histscrosscheck6 = GetHistCollection("crosscheck6");
  // BaseHists* BTagEff_Hists = GetHistCollection("BTagEff");


  // start the analysis
 



  EventCalc* calc = EventCalc::Instance();
  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
  bool IsRealData = calc->IsRealData();





  if(!trigger->passSelection(bcc))  throw SError( SError::SkipEvent );
  if(!nJets->passSelection(bcc)) throw SError( SError::SkipEvent );
  if(!HT1000->passSelection(bcc)) throw SError( SError::SkipEvent );
  if(!topTag->passSelection(bcc)) throw SError( SError::SkipEvent );
  //  if (IsRealData == false)BTagEff_Hists->Fill(); 
  if(!topAndSubBTag->passSelection(bcc)) throw SError( SError::SkipEvent );
  if(topAndSubBTagPlusHiggsTag->passSelection(bcc))Histscrosscheck6->Fill();
  else throw SError( SError::SkipEvent);
  

  return;
  
}

