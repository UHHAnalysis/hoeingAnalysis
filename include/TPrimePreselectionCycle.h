// Dear emacs, this is -*- c++ -*-
// $Id: TPrimePreselectionCycle.h,v 1.1 2013/03/26 13:01:44 hoeing Exp $
#ifndef TPrimePreselectionCycle_H
#define TPrimePreselectionCycle_H

// SFrame include(s):
#include "../SFrameAnalysis/include/AnalysisCycle.h"
#include "../SFrameAnalysis/include/BTagEffHistsTPrime.h"
#include "../SFrameAnalysis/include/Cleaner.h"
//#include "include/Scaling.h"
/**
 *   @short Example of an analysis cycle
 *
 *          This is an example of an analysis cycle. It can be used
 *          as a template for writing your own analysis. Also should
 *          be used for quick cross checks of the system setup.
 *
 *  @author Roman Kogler
 *  @version $Revision: 1.1 $
 */

class TPrimePreselectionCycle : public AnalysisCycle {

public:
  /// Default constructor
  TPrimePreselectionCycle();
  /// Default destructor
  ~TPrimePreselectionCycle();

  /// Function called at the beginning of the cycle
  void BeginCycle() throw( SError );
  /// Function called at the end of the cycle
  void EndCycle() throw( SError );

  /// Function called at the beginning of a new input data
  void BeginInputData( const SInputData& ) throw( SError );
  /// Function called after finishing to process an input data
  void EndInputData  ( const SInputData& ) throw( SError );

  /// Function called after opening each new input file
  void BeginInputFile( const SInputData& ) throw( SError );

  /// Function called for every event
  void ExecuteEvent( const SInputData&, Double_t ) throw( SError );

private:
  //
  // Put all your private variables here
  //
   std::string m_BTagEffiFilenameMC;
   std::string m_BTaggingMode;
//   BTaggingRoutine* m_bsf;
  
  // Macro adding the functions for dictionary generation
  ClassDef( TPrimePreselectionCycle, 0 );

}; // class TPrimePreselectionCycle

#endif // TPrimePreselectionCycle_H

