#ifndef cutflowHists_H
#define cutflowHists_H

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

class cutflowHists : public BaseHists {

public:


   /// Named constructor
  // cutflowHists(const char* name);

  cutflowHists(const char* name,TString mode="default", TString filename="");
  // named default constructor

   /// Default destructor
   ~cutflowHists();

   void Init();

   void Fill();

   void Finish();

private:

   double m_ptMin;

   double m_ptMax;

   std::vector<float>* m_test123;

   bool runWith4Jets;
 std::string m_BTagEffiFilenameMC;
   std::string m_BTaggingMode;

float topJetConeSize;
float rangeMmin[2];
float rangeMjet[2];
float nDivisions;
int nDivisionsInt;
std::vector<float> mminLowerVector;
std::vector<float> mjetLowerVector;
std::vector<float> mjetUpperVector;
std::vector<float> vectorLengthNDivisions;
float mminLowerTemp;
float mjetLowerTemp;
float mjetUpperTemp;
std::vector<float> pTIntervalsVector;
int fillCounter;
int initCounter;
int finishCounter;
int currentPtBin;

std::vector<float> effDenominatorsPtBinsVaryMmin;
std::vector<float> misDenominatorsPtBinsVarMmin;
std::vector< std::vector<float> > effEnumeratorsPtBinsVaryMmin;
std::vector< std::vector<float> > misEnumeratorsPtBinsVaryMmin;

std::vector<float> effDenominatorsPtBinsVaryMjet;
std::vector<float> misDenominatorsPtBinsVarMjet;
std::vector< std::vector<float> > effEnumeratorsPtBinsVaryMjet;
std::vector< std::vector<float> > misEnumeratorsPtBinsVaryMjet;

 std::vector<TopJet*> allMatchedJets;

bool matchedJetIsTagged;
bool useHepTopTagger;
 bool jetWasMatched;
 bool isolatedTops;
bool checkDaughtersInCone;


}; // class cutflowHists


#endif // cutflowHists_H
