#ifndef crosscheckHists_H
#define crosscheckHists_H

// ROOT include(s):
#include <TObject.h>
#include <TString.h>


// Local include(s):
#include "../SFrameTools/include/BaseHists.h"
#include "../SFrameTools/include/BaseCycleContainer.h"


/**
 *   Example class for booking and filling histograms
 *
 *   This class books and fills a collection of histograms.
 *   It should have a unique name, such that the histograms
 *   of multiple instances of this class are ordered in the
 *   output file. 
 *   Always sort your histograms and used methods topically.
 *   This example collection can be used for data and reconstructed
 *   MC events.
 *   
 *   @version $Revision: 1.1 $
 */

class crosscheckHists : public BaseHists {

public:


   /// Named constructor
  // crosscheckHists(const char* name);

  crosscheckHists(const char* name,TString mode="default", TString filename="");
  // named default constructor

   /// Default destructor
   ~crosscheckHists();

   void Init();

   void Fill();

   void Finish();

private:

   
 std::string m_BTagEffiFilenameMC;
   std::string m_BTaggingMode;






}; // class crosscheckHists


#endif // crosscheckHists_H
