// Info.h is a part of the PYTHIA event generator.
// Copyright (C) 2011 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// This file contains a class that keep track of generic event info.
// Info: contains information on the generation process and errors.

#ifndef Pythia8_Info_H
#define Pythia8_Info_H

#include "PythiaStdlib.h"

namespace Pythia8 {
 
//==========================================================================

// The Info class contains a mixed bag of information on the event
// generation activity, especially on the current subprocess properties,
// and on the number of errors encountered. This is used by the 
// generation machinery, but can also be read by the user.
// Note: some methods that maybe should not be accessible to the user
// are still public, to work also for user-written FSR/ISR classes.

class Info {

public:

  // Constructor. 
  Info() : lowPTmin(false), a0MISave(0.) {
    for (int i = 0; i < 40; ++i) counters[i] = 0;} 

  // Listing of most available information on current event.
  void   list(ostream& os = cout) const;
  
  // Beam particles (in rest frame). CM energy of event.
  int    idA()            const {return idASave;}
  int    idB()            const {return idBSave;}
  double pzA()            const {return pzASave;}
  double pzB()            const {return pzBSave;}
  double eA()             const {return eASave;}
  double eB()             const {return eBSave;}
  double mA()             const {return mASave;}
  double mB()             const {return mBSave;}
  double eCM()            const {return eCMSave;}
  double s()              const {return sSave;}

  // Warnings from initialization.
  bool   tooLowPTmin()    const {return lowPTmin;}

  // Process name and code, and the number of final-state particles.
  string name()           const {return nameSave;}
  int    code()           const {return codeSave;}    
  int    nFinal()         const {return nFinalSave;}

  // Are beam particles resolved, with pdf's? Are they diffractive? 
  bool   isResolved()     const {return isRes;}
  bool   isDiffractiveA() const {return isDiffA;} 
  bool   isDiffractiveB() const {return isDiffB;} 
  bool   isMinBias()      const {return isMB;}

  // Information for Les Houches Accord and reading files.
  bool   isLHA()          const {return isLH;}
  bool   atEndOfFile()    const {return atEOF;}

  // For minbias and Les Houches Accord identify hardest subprocess.
  bool   hasSub()         const {return hasSubSave;}
  string nameSub()        const {return nameSubSave;}
  int    codeSub()        const {return codeSubSave;}    
  int    nFinalSub()      const {return nFinalSubSave;}

  // Incoming parton flavours and x values.
  int    id1()            const {return id1Save;}
  int    id2()            const {return id2Save;}
  double x1()             const {return x1Save;}
  double x2()             const {return x2Save;}
  double y()              const {return 0.5 * log( x1Save / x2Save );}
  double tau()            const {return x1Save * x2Save;}

  // Incoming parton densities, hard process couplings, Q2 scales.
  double pdf1()           const {return pdf1Save;}
  double pdf2()           const {return pdf2Save;}
  double QFac()           const {return sqrtpos(Q2FacSave);}
  double Q2Fac()          const {return Q2FacSave;}
  bool   isValence1()     const {return isVal1;}
  bool   isValence2()     const {return isVal2;}
  double alphaS()         const {return alphaSSave;}
  double alphaEM()        const {return alphaEMSave;}
  double QRen()           const {return sqrtpos(Q2RenSave);}
  double Q2Ren()          const {return Q2RenSave;}

  // Mandelstam variables (notation as if subcollision).
  double mHat()           const {return sqrt(sH);}   
  double sHat()           const {return sH;}   
  double tHat()           const {return tH;}   
  double uHat()           const {return uH;}   
  double pTHat()          const {return pTH;} 
  double pT2Hat()         const {return pTH*pTH;} 
  double m3Hat()          const {return m3H;}   
  double m4Hat()          const {return m4H;} 
  double thetaHat()       const {return thetaH;}   
  double phiHat()         const {return phiH;}   

  // Weight of current event; normally 1, but used for Les Houches events
  // or when reweighting phase space selection. Also cumulative sum.
  double weight()         const {return weightSave;}   
  double weightSum()      const {return wtAccSum;}

  // Number of times other steps have been carried out.
  int    nISR()           const {return nISRSave;}
  int    nFSRinProc()     const {return nFSRinProcSave;}
  int    nFSRinRes()      const {return nFSRinResSave;}

  // Maximum pT scales for MI, ISR and FSR (in hard process).
  double pTmaxMI()        const {return pTmaxMISave;}
  double pTmaxISR()       const {return pTmaxISRSave;}
  double pTmaxFSR()       const {return pTmaxFSRSave;}

  // Current evolution scale (for UserHooks).
  double pTnow()          const {return pTnowSave;}

  // Impact parameter picture, global information
  double a0MI()           const {return a0MISave;}

  // Impact parameter picture, as set by hardest interaction.
  double bMI()            const {return (bIsSet) ? bMISave : 1.;}
  double enhanceMI()      const {return (bIsSet) ? enhanceMISave : 1.;}
  double eMI(int i)       const {return (bIsSet) ? eMISave[i] : 1.;}

  // Number of multiple interactions, with code and pT for them.
  int    nMI()            const {return nMISave;}
  int    codeMI(int i)    const {return codeMISave[i];} 
  double pTMI(int i)      const {return pTMISave[i];} 
  int    iAMI(int i)      const {return iAMISave[i];} 
  int    iBMI(int i)      const {return iBMISave[i];} 

  // Cross section estimate.
  long   nTried()         const {return nTry;}
  long   nSelected()      const {return nSel;}
  long   nAccepted()      const {return nAcc;}
  double sigmaGen()       const {return sigGen;}
  double sigmaErr()       const {return sigErr;}

  // Counters for number of loops in various places.
  int    getCounter( int i)  const {return counters[i];}    

  // Set or increase the value stored in a counter.
  void   setCounter( int i, int value = 0) {counters[i]  = value;}
  void   addCounter( int i, int value = 1) {counters[i] += value;}

  // Reset to empty map of error messages.
  void   errorReset() {messages.clear();}
  
  // Print a message the first few times. Insert in database.
  void   errorMsg(string messageIn, string extraIn = " ", 
    bool showAlways = false, ostream& os = cout);

  // Provide total number of errors/aborts/warnings experienced to date.
  int    errorTotalNumber();

  // Print statistics on errors/aborts/warnings.
  void   errorStatistics(ostream& os = cout);

  // Set initialization warning flag when too low pTmin in ISR/FSR/MI.
  void   setTooLowPTmin(bool lowPTminIn) {lowPTmin = lowPTminIn;} 

  // Set info on valence character of hard collision partons.
  void setValence( bool isVal1In, bool isVal2In) {isVal1 = isVal1In; 
    isVal2 = isVal2In;}

  // Set and get some MI/ISR/FSR properties needed for matching,
  // i.e. mainly of internal relevance.
  void   hasHistory( bool hasHistoryIn) {hasHistorySave = hasHistoryIn;}
  bool   hasHistory() {return hasHistorySave;}
  void   zNowISR( double zNowIn) {zNowISRSave = zNowIn;}
  double zNowISR() {return zNowISRSave;}
  void   pT2NowISR( double pT2NowIn) {pT2NowISRSave = pT2NowIn;}
  double pT2NowISR() {return pT2NowISRSave;}

private:

  // Number of times the same error message is repeated, unless overridden.
  static const int TIMESTOPRINT;

  // Store common beam quantities. 
  int    idASave, idBSave;
  double pzASave, eASave,mASave, pzBSave, eBSave, mBSave, eCMSave, sSave;

  // Store initialization information.
  bool   lowPTmin;

  // Store common integrated cross section quantities.
  long   nTry, nSel, nAcc;
  double sigGen, sigErr, wtAccSum;

  // Store common MPI information
  double a0MISave;

  // Store current-event quantities.
  bool   isRes, isDiffA, isDiffB, isMB, isLH, hasSubSave, bIsSet, evolIsSet,
         atEOF, isVal1, isVal2, hasHistorySave;  
  int    codeSave, codeSubSave, nFinalSave, nFinalSubSave, nTotal, 
         id1Save, id2Save, nMISave, nISRSave, nFSRinProcSave, nFSRinResSave;
  double x1Save, x2Save, pdf1Save, pdf2Save, Q2FacSave, alphaEMSave, 
         alphaSSave, Q2RenSave, sH, tH, uH, pTH, m3H, m4H, thetaH, phiH, 
         weightSave, bMISave, enhanceMISave, pTmaxMISave, pTmaxISRSave, 
         pTmaxFSRSave, pTnowSave, zNowISRSave, pT2NowISRSave;
  string nameSave, nameSubSave;
  vector<int>    codeMISave, iAMISave, iBMISave;
  vector<double> pTMISave, eMISave;

  // Vector of various loop counters.
  int    counters[50];

  // Map for all error messages.
  map<string, int> messages;

  // Friend classes allowed to set info.
  friend class Pythia;
  friend class ProcessLevel;
  friend class ProcessContainer;
  friend class PartonLevel;
  friend class MultipleInteractions;

  // Set info on the two incoming beams: only from Pythia class.
  void setBeamA( int idAin, double pzAin, double eAin, double mAin) {
    idASave = idAin; pzASave = pzAin; eASave = eAin; mASave = mAin;}
  void setBeamB( int idBin, double pzBin, double eBin, double mBin) {
    idBSave = idBin; pzBSave = pzBin; eBSave = eBin; mBSave = mBin;}
  void setECM( double eCMin) {eCMSave = eCMin; sSave = eCMSave * eCMSave;}

  // Reset info for current event: only from Pythia class.
  void clear() { isRes = isDiffA = isDiffB = isMB = isLH = hasSubSave 
    = bIsSet = evolIsSet = atEOF = isVal1 =isVal2 = hasHistorySave = false; 
    codeSave = codeSubSave = nFinalSave = nFinalSubSave = nTotal = id1Save 
    = id2Save = nMISave = nISRSave = nFSRinProcSave = nFSRinResSave = 0; 
    x1Save = x2Save = pdf1Save = pdf2Save = Q2FacSave = alphaEMSave 
    = alphaSSave = Q2RenSave = sH = tH = uH = pTH = m3H = m4H = thetaH 
    = phiH = 0.; weightSave = bMISave = enhanceMISave = 1.; 
    pTmaxMISave = pTmaxISRSave = pTmaxFSRSave = pTnowSave = zNowISRSave 
    = pT2NowISRSave = 0.; nameSave = nameSubSave = " "; 
    codeMISave.resize(0); iAMISave.resize(0); iBMISave.resize(0);  
    pTMISave.resize(0); eMISave.resize(0); }

  // Set info on the (sub)process: from ProcessLevel, ProcessContainer or 
  // MultipleInteractions classes.
  void setType( string nameIn, int codeIn, int nFinalIn,  
    bool isMinBiasIn = false, bool isResolvedIn = true, 
    bool isDiffractiveAin = false, bool isDiffractiveBin = false,
    bool isLHAin = false) {nameSave = nameIn; codeSave = codeIn; 
    nFinalSave = nFinalIn; isMB = isMinBiasIn; isRes = isResolvedIn; 
    isDiffA = isDiffractiveAin; isDiffB = isDiffractiveBin; isLH = isLHAin;
    nTotal = 2 + nFinalSave; bIsSet = false; hasSubSave = false; 
    nameSubSave = " "; codeSubSave = 0; nFinalSubSave = 0; evolIsSet = false;}
  void setSubType( string nameSubIn, int codeSubIn, int nFinalSubIn) {  
    hasSubSave = true; nameSubSave = nameSubIn; codeSubSave = codeSubIn; 
    nFinalSubSave = nFinalSubIn;}
  void setPDFalpha( int id1In, int id2In,  double pdf1In, double pdf2In, 
    double Q2FacIn, double alphaEMIn, double alphaSIn, double Q2RenIn) 
    {id1Save = id1In; id2Save = id2In; pdf1Save = pdf1In; pdf2Save = pdf2In; 
    Q2FacSave = Q2FacIn; alphaEMSave = alphaEMIn; alphaSSave = alphaSIn; 
    Q2RenSave = Q2RenIn;}
  void setKin( double x1In, double x2In, double sHatIn, double tHatIn, 
    double uHatIn, double pTHatIn, double m3HatIn, double m4HatIn, 
    double thetaHatIn, double phiHatIn) {x1Save = x1In; x2Save = x2In; 
    sH = sHatIn; tH = tHatIn; uH = uHatIn; pTH = pTHatIn; m3H = m3HatIn; 
    m4H = m4HatIn; thetaH = thetaHatIn; phiH = phiHatIn;}
  void setTypeMI( int codeMIIn, double pTMIIn, int iAMIIn = 0, 
    int iBMIIn = 0, double eMIIn = 1.) {codeMISave.push_back(codeMIIn); 
    pTMISave.push_back(pTMIIn); iAMISave.push_back(iAMIIn); 
    iBMISave.push_back(iBMIIn); eMISave.push_back(eMIIn); }

  // Set info on cross section: from ProcessLevel.
  void setSigma( long nTryIn, long nSelIn, long nAccIn, double sigGenIn, 
    double sigErrIn, double wtAccSumIn) { nTry = nTryIn; nSel = nSelIn; 
    nAcc = nAccIn; sigGen = sigGenIn; sigErr = sigErrIn; 
    wtAccSum = wtAccSumIn;} 

  // Set info on impact parameter: from PartonLevel.
  void setImpact( double bMIIn, double enhanceMIIn) {bMISave = bMIIn;
    enhanceMISave = eMISave[0] = enhanceMIIn, bIsSet = true;} 

  // Set info on pTmax scales and number of evolution steps: from PartonLevel.
  void setPartEvolved( int nMIIn, int nISRIn) {
    nMISave = nMIIn; nISRSave = nISRIn;} 
  void setEvolution( double pTmaxMIIn, double pTmaxISRIn, double pTmaxFSRIn, 
    int nMIIn, int nISRIn, int nFSRinProcIn, int nFSRinResIn) { 
    pTmaxMISave = pTmaxMIIn; pTmaxISRSave = pTmaxISRIn; 
    pTmaxFSRSave = pTmaxFSRIn; nMISave = nMIIn; nISRSave = nISRIn; 
    nFSRinProcSave = nFSRinProcIn; nFSRinResSave = nFSRinResIn; 
    evolIsSet = true;}

  // Set current pT evolution scale for MI/ISR/FSR; from PartonLevel.
  void setPTnow( double pTnowIn) {pTnowSave = pTnowIn;}

  // Set a0 from MultipleInteractions.
  void a0MI(double a0MIin) {a0MISave = a0MIin;}

  // Set info whether reading of Les Houches Accord file at end.
  void setEndOfFile( bool atEOFin) {atEOF = atEOFin;}

  // Set event weight; currently only for Les Houches description.
  void setWeight( double weightIn) {weightSave = weightIn;}

};
 
//==========================================================================

} // end namespace Pythia8

#endif // Pythia8_Info_H
