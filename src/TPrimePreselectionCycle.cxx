
// $Id: TPrimePreselectionCycle.cxx,v 1.1 2013/03/26 12:50:16 hoeing Exp $

#include <iostream>

using namespace std;

// Local include(s):
#include "include/TPrimePreselectionCycle.h"
#include "../SFrameAnalysis/include/SelectionModules.h"
#include "include/cutflowHists.h"

ClassImp( TPrimePreselectionCycle );

TPrimePreselectionCycle::TPrimePreselectionCycle()
  : AnalysisCycle() {

  // constructor, declare additional variables that should be 
  // obtained from the steering-xml file

  // set the integrated luminosity per bin for the lumi-yield control plots
  SetIntLumiPerBin(25.);
 
}

TPrimePreselectionCycle::~TPrimePreselectionCycle() 
{
  // destructor
}

void TPrimePreselectionCycle::BeginCycle() throw( SError ) 
{
  // Start of the job, general set-up and definition of 
  // objects are done here

  // Important: first call BeginCycle of base class
  AnalysisCycle::BeginCycle();

  return;




}

void TPrimePreselectionCycle::EndCycle() throw( SError ) 
{
  // clean-up, info messages and final calculations after the analysis

  
  // call the base cycle class for all standard methods
  AnalysisCycle::EndCycle();

  return;

}

void TPrimePreselectionCycle::BeginInputData( const SInputData& id ) throw( SError ) 
{
  // declaration of histograms and selections

  // Important: first call BeginInputData of base class
  AnalysisCycle::BeginInputData( id );
  
 


  // -------------------- set up the selections ---------------------------


 
  Selection* trigger = new Selection("HLT_HT750");
  Selection* nJets = new Selection("nJets");
  Selection* HT1000 = new Selection("HT1000");
 


  //DO NOT use trigger selection in PROOF mode at the moment
  trigger->addSelectionModule(new TriggerSelection("HLT_HT750"));
  nJets->addSelectionModule(new NTopJetSelection(2, 99, 0., 99.));
  HT1000->addSelectionModule(new HTCut(1000.));
  

  RegisterSelection(trigger);
  RegisterSelection(nJets);
  RegisterSelection(HT1000);
 

 
  // ---------------- set up the histogram collections --------------------

  // histograms without any cuts
  RegisterHistCollection( new cutflowHists("NoCuts") );
  // histograms after the top selection
  RegisterHistCollection( new cutflowHists("cutflow1") );
  RegisterHistCollection( new cutflowHists("cutflow2") );
  RegisterHistCollection( new cutflowHists("cutflow3") );
 

  // RegisterHistCollection( new BTagEffHistsTPrime("BTagEff") );

  
  // important: initialise histogram collections after their definition
  InitHistos();

  return;

}

void TPrimePreselectionCycle::EndInputData( const SInputData& id ) throw( SError ) 
{
  AnalysisCycle::EndInputData( id );
  return;

}

void TPrimePreselectionCycle::BeginInputFile( const SInputData& id ) throw( SError ) 
{
  // Connect all variables from the Ntuple file with the ones needed for the analysis
  // The variables are commonly stored in the BaseCycleContaincer

  // important: call to base function to connect all variables to Ntuples from the input tree
  AnalysisCycle::BeginInputFile( id );

  return;

}

void TPrimePreselectionCycle::ExecuteEvent( const SInputData& id, Double_t weight) throw( SError ) 
{
  // this is the most important part: here the full analysis happens
  // user should implement selections, filling of histograms and results

  // first step: call Execute event of base class to perform basic consistency checks
  // also, the good-run selection is performed there and the calculator is reset
  AnalysisCycle::ExecuteEvent( id, weight);
   


  // get the selections
  static Selection* trigger = GetSelection("HLT_HT750");
  static Selection* nJets = GetSelection("nJets");
  static Selection* HT1000 = GetSelection("HT1000");
 

  // get the histogram collections
  BaseHists* HistsNoCuts = GetHistCollection("NoCuts");
  BaseHists* Histscutflow1 = GetHistCollection("cutflow1");
  BaseHists* Histscutflow2 = GetHistCollection("cutflow2");
  BaseHists* Histscutflow3 = GetHistCollection("cutflow3");
 


  // start the analysis
  HistsNoCuts->Fill();

  EventCalc* calc = EventCalc::Instance();
  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();

  if(trigger->passSelection(bcc)) Histscutflow1->Fill();
  else throw SError( SError::SkipEvent );
  if(nJets->passSelection(bcc)) Histscutflow2->Fill();
  else throw SError( SError::SkipEvent );
  if(HT1000->passSelection(bcc)) Histscutflow3->Fill();
  else throw SError( SError::SkipEvent );
  WriteOutputTree();
  return;
  
}

