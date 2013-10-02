#ifndef hoeingHists_H
#define hoeingHists_H

#include "SFrameTools/include/BaseHists.h"

/**
 *   hoeing class for booking and filling histograms
 *
 *   This class books and fills a collection of histograms.
 *   It should have a unique name, such that the histograms
 *   of multiple instances of this class are ordered in the
 *   output file. 
 *   Always sort your histograms and used methods topically.
 *   This example collection can be used for data and reconstructed
 *   MC events.
 *   
 *   @version $Revision: 1.2 $
 */

class hoeingHists : public BaseHists {

public:
   /// Named constructor
   hoeingHists(const char* name);

   /// Default destructor
   ~hoeingHists();

   void Init();

   void Fill();

   void Finish();

private:

}; // class hoeingHists


#endif // hoeingHists_H
