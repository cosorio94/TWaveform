// File: TWaveform.h
// Carlos Osorio, July 2016
// Waveform class used to read and process data from CVS file 

#ifndef ROOT_TWaveform
#define ROOT_TWaveform
#include "TNamed.h"
#include "TH2.h"
#include <string>
#include <vector>
#include "TTree.h" 
#include "TChain.h"
#include "TWaveformConstants.h"


// namespace TWaveform
// {

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                          ///////////////////////////////////                                         
                                                          ////// Srtucture Declarations /////                                         
                                                          ///////////////////////////////////                                         
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  struct fitParam
  {
    int bestOffset;
    double bestScale;
    double chiSquared;
  };

  struct chiParam
  {
    std::vector<std::string> bestTemp;
    std::vector<int> bestOffset;
    std::vector<double> bestScale;
    double chiNor;
    bool operator==(const chiParam& par2)
    {
      if (this->bestTemp == par2.bestTemp && this->bestScale == par2.bestScale && this->bestOffset == par2.bestOffset && this->chiNor == par2.chiNor)
        return true;
      else
        return false;
    };
  };

  struct treeData
  {
    std::vector<double> pulseStrength, signalStrength, heightUnc, bestTemplateScale;
    std::vector<int> peakPos, risePos, timeUnc, bestTemplateOffset;
    float stDev, tBinSize;
    double area, chiSquared;
    int waveformNum, directoryNum, nSamples;
    bool noise;
    std::vector<std::string> bestTemplates;
  };

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                          //////////////////////////////
                                                          ////// Class Declaration /////
                                                          //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  class TWaveform : public TNamed
  {
  public:

    //_____________________________________________________________________________________________________________________________________
    // CONSTRUCTORS
    TWaveform();
    TWaveform(std::string dirAddress, std::string fName, std::string fType);
    TWaveform(const char *name,const char *title);
    TWaveform(const char *name,const char *title, std::string dirAddress, std::string fName, std::string fType);

    //_____________________________________________________________________________________________________________________________________
    // DESTRUCTORS
    ~TWaveform();
    // Clears all the member variables of the current waveform and assigns them their initial values
    virtual void Clear();

    //_____________________________________________________________________________________________________________________________________
    // OVERLOADED OPERATORS
    // Returns a TWaveform that has vA values that are the sum of the TWaveforms performed on
    TWaveform operator+(TWaveform &obj);
    // Returns a TWaveform that has vA values that are the result of subtracting the second TWaveform from the first
    TWaveform operator-(TWaveform &obj);

    //_____________________________________________________________________________________________________________________________________
    // COPY MEMEBER FUNCTIONS
    // Copies the current TWaveform into the TWaveform obj
    virtual void Copy(TWaveform &obj); //const;
    // Copies only the signal of the current TWaveform into the TWaveform obj
    void CopySignal(TWaveform &obj);
    // Copies only the setup parameters of the current TWaveform into the TWaveform obj
    void CopySetup(TWaveform &obj);

    //_____________________________________________________________________________________________________________________________________
    // READ MEMBER FUNCTIONS
    bool ReadCSV(std::string fName1);
    bool ReadTXT(std::string fName1, bool debug = false);
    bool ReadFile(std::string fName);
    // Reads the TWaveform template "temp" in the file "tempFile" and copies it to the current TWveform
    void ReadTemp(const char *tempName, const char *tempFile = TWaveformConstants::templateFile);
    // Returns the best fit template TWaveform for the current TWaveform
    TWaveform ReadBestTemp(const char *tempFile, int pulseNum = 0);
  

    //_____________________________________________________________________________________________________________________________________
    // DRAW & PLOT MEMBER FUNCTIONS
    void Draw(std::string histName = "Waveform", Option_t* option = "C hist", Color_t color = kBlue+2);
    void PlotArea(Option_t* option = "C hist");
    void PlotIntegral(Option_t* option = "C hist");
    void DrawComp(TWaveform &temp, int tOffset = 0, double scale = 1);
    void DrawFitPar(TWaveform &temp, int tLim = TWaveformConstants::timeFittingLim, double scaleLim = TWaveformConstants::scaleFittingLim);
    void DrawBestFit(const char *tempFile = TWaveformConstants::templateFile);

    //_____________________________________________________________________________________________________________________________________
    // FIND MEMBER FUNCTIONS
    float FindAvg(int pos, std::string data = "Waveform", int nPoints = 5);
    void FindArea();
    void FindIntegral();
    void FindOffset(/*std::string data = "Integral"*/);
    float FindSlope(int pos, std::string data = "Waveform", int nPoints = 5);
    int FindPeak(int start = 26, int nPoints = 25);
    void FindPeaks();
    void Find1stPulse(int step = 40, float sigma = TWaveformConstants::slopeSigma, int nPoints = 5);              //******* MAKE PRIVATE! ******* 
    void FindStdev();
    fitParam FindFitPar(TWaveform &temp, int tLim = TWaveformConstants::timeFittingLim, double scaleLim = TWaveformConstants::scaleFittingLim);
    fitParam FindFitParMultiple(TWaveform &temp, TWaveform multWave, int tLim = TWaveformConstants::timeFittingLim, double scaleLim = TWaveformConstants::scaleFittingLim);
    void FindPeaksTemp(const char *tempFile = TWaveformConstants::templateFile);
    void FindRiseTemp(const char *tempFile = TWaveformConstants::templateFile);
    chiParam FindFirstBestTemplateParameters(const char *tempFile = TWaveformConstants::templateFile, const char *tempName = TWaveformConstants::templateNames, int tempNum = TWaveformConstants::numberOfTemplates, int tLim = TWaveformConstants::timeFittingLim, double scaleLim = TWaveformConstants::scaleFittingLim);
    chiParam FindMultipleBestTemplateParameters(TWaveform multipleWave, const char *tempFile = TWaveformConstants::templateFile, const char *tempName = TWaveformConstants::templateNames, int tempNum = TWaveformConstants::numberOfTemplates, int tLim = TWaveformConstants::timeFittingLim, double scaleLim = TWaveformConstants::scaleFittingLim);
    chiParam FindBestTemplatesFit(const char *tempFile = TWaveformConstants::templateFile, const char *tempName = TWaveformConstants::templateNames, int tempNum = TWaveformConstants::numberOfTemplates, int maxPulses = TWaveformConstants::maxPulses, int tLim = TWaveformConstants::timeFittingLim, double scaleLim = TWaveformConstants::scaleFittingLim);

    //_____________________________________________________________________________________________________________________________________
    // GET MEMBER FUNCTIONS
    double GetLowestChi2(TWaveform &temp, int tLim = TWaveformConstants::timeFittingLim, double scaleLim = TWaveformConstants::scaleFittingLim);
    double GetChi2Norm(double chiSq, double constraints = 0);
    double GetChiMultiple(const char *tempFile, chiParam tempChi);
    double GetChiMultiple(TWaveform temp, TWaveform multWave, double tempScale, int tempOffset);
    std::vector<int> GetTimeUncertainty(int tStep = TWaveformConstants::timeResolution, const char *tempFile = TWaveformConstants::templateFile);
    std::vector<double> GetPulseHeightUncertainty(double scaleStep = TWaveformConstants::scaleResolution, const char *tempFile = TWaveformConstants::templateFile);
    char* GetBestTempName(int pulseNum = 0);
    std::vector<TWaveform> GetBestTemplates(const char *tempFile = TWaveformConstants::templateFile);
    TWaveform GetBestFitWave(const char *tempFile = TWaveformConstants::templateFile);
    TWaveform GetBestFitWaveShifted(int pulseToBeShifted, int tOffset, double scale, const char *tempFile = TWaveformConstants::templateFile);
    std::string GetCSVFilename(int waveNum, int dirNum = 20);
    std::string GetTXTFilename(int waveNum, int dirNum = 125);
    std::string GetFilename(int waveNum, int dirNum = 20);
    double GetPulseHeight(int pulseNum, const char *tempFile = TWaveformConstants::templateFile);
    int Get1stRisePosition(int start = 6, int iterations = 8, std::string data = "Waveform", int step = 40); 
    double GetChiSquare(TWaveform &temp, int tOffset = 0, double scale = 1);

    //_____________________________________________________________________________________________________________________________________
    // SET MEMBER FUNCTIONS
    bool SetBestTemplateParameters(const char *tempFile = TWaveformConstants::templateFile, const char *tempName = TWaveformConstants::templateNames, int tempNum = TWaveformConstants::numberOfTemplates, int maxPulses = TWaveformConstants::maxPulses, int tLim = TWaveformConstants::timeFittingLim, double scaleLim = TWaveformConstants::scaleFittingLim);
    bool SetSignalPositive();
    void SetFileName(std::string dirAddress, std::string fName, std::string fType);


    //_____________________________________________________________________________________________________________________________________
    // OTHER MEMBER FUNCTIONS
    bool IsIncreasing(int start, int end, std::string data = "Waveform", int nPoints = 5);
    void ApplyOffset(/*std::string data = "Integral"*/);
    void MarkRise();
    void PreDataProcessing(/*std::string data = "Integral"*/);
    TH2F* Chi2Hist(TWaveform &temp, int inTOff, double inScale, int tLim = TWaveformConstants::timeFittingLim, double scaleLim = TWaveformConstants::scaleFittingLim, int tStep = 1, double scaleStep = 0.01);
    TH2F* Chi2HistMultiple(TWaveform &temp, TWaveform multWave, int inTOff, double inScale, int tLim = TWaveformConstants::timeFittingLim, double scaleLim = TWaveformConstants::scaleFittingLim, int tStep = 1, double scaleStep = 0.01);
    void NoiseFilter();
    void NoiseFilterAvg(double maxAvgForNoise = TWaveformConstants::maxAvgForNoise);
    void NoiseFilterArea(double maxAreaForNoise = TWaveformConstants::maxAreaForNoise);
    TWaveform AddBestTemps(const char *tempFile);
    void Shift(int offset, double scale = 1);
    TWaveform Add(TWaveform &temp2, double temp2Scale = 1, int temp2Offset = 0, double tempScale = 1, int tempOffset = 0);
    TWaveform Subtract(TWaveform &temp2, double temp2Scale = 1, int temp2Offset = 0, double tempScale = 1, int tempOffset = 0);
    void SmoothOut(int nPoints);
    bool SortPulses();
    bool AnalyzeWave(const char *tempFile = TWaveformConstants::templateFile, const char *tempName = TWaveformConstants::templateNames, int tempNum = TWaveformConstants::numberOfTemplates, int maxPulses = TWaveformConstants::maxPulses, double maxChi = TWaveformConstants::maxChiNorm, int tLim = TWaveformConstants::timeFittingLim, double scaleLim = TWaveformConstants::scaleFittingLim, double minHeight = TWaveformConstants::minimumPulseHeight);
    bool IsGoodFit(double maxChi = TWaveformConstants::maxChiNorm);
    bool FilterPulseHeight(double minHeight = TWaveformConstants::minimumPulseHeight, const char *tempFile = TWaveformConstants::templateFile);
    void ChangeSignalSign();


    //_____________________________________________________________________________________________________________________________________
    // DATA MEMBERS
    std::string directoryAddress;               // Address of the directory where waveform files will be read from
    std::string genericFileName;                // Generic name for the waveform files that will be read
    std::string fileType;                       // File type of the waveform files that will be read
    int nSamples;                               // Number of samples (time bins), up to 8192
    float t[8192];                              // The time of each sample, in seconds
    float vA[8192];                             // The voltage value for each sample in the waveform
    float tBinSize;                             // Size of each time bin
    double vAreaA[8192];                        // The waveform's area between each sample
    double vIAreaA[8192];                       // The waveform's integral value up to each sample in the waveform
    float vOffsetA;                             // The voltage offset applied to the waveform
    float stDevA;                               // The waveform's standard deviation
    int risePosA[4096];                         // Position of each pulse's start in the waveform
    int peaksA[4096];                           // Position of all the peaks in the waveform
    int nPeaksA;                                // Number of peaks in the waveform
    // int nPulses;                             // Number of pulses in the waveform (each pulse represents a template fitted)
    bool noiseA;                                // True if the waveform is composed of some kind of periodic noise
    std::vector<std::string> bestTemp;          // Vector of strings containing the name of the templates that fit the waveform the best
    std::vector<int> bestTempOffset;            // Vector containing the tOffset parameters for the templates to give the best fit
    std::vector<double> bestTempScale;          // Vector containing the vScale parameters for the templates to give the best fit
    double bestTempChi;                         // Records the value of the normalized chi^2 of the waveform with its recorded best templates


    ClassDef(TWaveform,0)

  };

namespace TWaveformSpace
{

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                      ///////////////////////////////////////////
                                                      ////// Nonmember Function Declarations ////
                                                      ///////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //_____________________________________________________________________________________________________________________________________
  // NONMEMBER FUNCTIONS
  std::string TempName(int n, const char *tempName = "");
  std::vector<TWaveform> GetTempWaves(int tempNum = TWaveformConstants::numberOfTemplates, const char *tempFile = TWaveformConstants::templateFile, const char *tempName = TWaveformConstants::templateNames);
  std::vector<TWaveform> GetTempWavesAnalyzed(int tempNum = TWaveformConstants::numberOfTemplates, const char *tempFile = TWaveformConstants::templateFile, const char *tempName = TWaveformConstants::templateNames);
  std::vector<double> GetTempAreas(std::vector<TWaveform> tempWaves);
  double GetPulseArea(double pulseStrength, std::string waveBestTemp, std::vector<TWaveform> tempWaves, std::vector<double> tempAreas);
  TWaveform AddWaveforms(std::vector<TWaveform> waves);
  std::vector<double> GetIntegralLimits(int waveDir, int firstWave = 0);
  char *GetTreeFileName(int dirNum, int treeNum, std::string dirAddress, std::string treeName);
  treeData GetTreeData(int entry, TChain* chain);

  //_____________________________________________________________________________________________________________________________________
  // TEMPLATE CREATION FUNCTIONS
  std::vector<TWaveform> AvgAreaTemplates(int waveDir, const char *fName, double minArea, double maxArea, int numTemps = TWaveformConstants::numberOfTemplates, const char *tempName = TWaveformConstants::templateNames, int numWaves = 0, bool smooth = true);
  std::vector<TWaveform> AvgAreaTemplates(int firstWave, int waveDir, const char *fName, double minArea, double maxArea, int numTemps = TWaveformConstants::numberOfTemplates, const char *tempName = TWaveformConstants::templateNames, int numWaves = 0, bool smooth = true);
  std::vector<TWaveform> AvgAreaTemplates(int waveDir, const char *fName, double *areaRange, int numTemps = TWaveformConstants::numberOfTemplates, const char *tempName = TWaveformConstants::templateNames, int numWaves = 0, bool smooth = true);
  void SaveTemplates(const std::vector<TWaveform> &tempWaves, const char *fName, const char *tempName = TWaveformConstants::templateNames, bool smooth = true, int nPoints = 4);

  //_____________________________________________________________________________________________________________________________________
  // TTREE AND TCHAIN CREATION FUNCTIONS
  void CreateTree(int fileNum, const char* fName = "WaveTree.root", const char* treeName = TWaveformConstants::treeName.c_str(), const char* treeTitle = "Waveform Tree", const char *tempFile = TWaveformConstants::templateFile, const char *tempName = TWaveformConstants::templateNames, int tempNum = TWaveformConstants::numberOfTemplates, int maxPulses = TWaveformConstants::maxPulses, double maxChi = TWaveformConstants::maxChiNorm, int tLim = TWaveformConstants::timeFittingLim, double scaleLim = TWaveformConstants::scaleFittingLim);
  bool CreateTree(int start, int end, int fileNum, const char* fName = "WaveTree.root", const char* treeName = TWaveformConstants::treeName.c_str(), Option_t* fileOption = "Recreate", const char* treeTitle = "Waveform Tree", const char *tempFile = TWaveformConstants::templateFile, const char *tempName = TWaveformConstants::templateNames, int tempNum = TWaveformConstants::numberOfTemplates, int maxPulses = TWaveformConstants::maxPulses, double maxChi = TWaveformConstants::maxChiNorm, int tLim = TWaveformConstants::timeFittingLim, double scaleLim = TWaveformConstants::scaleFittingLim);
  bool CreateTree(std::vector<int> waveformNums, int fileNum, const char* fName = "WaveTree.root", const char* treeName = TWaveformConstants::treeName.c_str(), Option_t* fileOption = "Recreate", const char* treeTitle = "Waveform Tree", const char *tempFile = TWaveformConstants::templateFile, const char *tempName = TWaveformConstants::templateNames, int tempNum = TWaveformConstants::numberOfTemplates, int maxPulses = TWaveformConstants::maxPulses, double maxChi = TWaveformConstants::maxChiNorm, int tLim = TWaveformConstants::timeFittingLim, double scaleLim = TWaveformConstants::scaleFittingLim);
  void CreateTrees(int dirNum, std::string dirAddress = TWaveformConstants::treeDirectoryAddress, std::string treeName = TWaveformConstants::treeName, const char* treeTitle = "Waveform Tree", const char *tempFile = TWaveformConstants::templateFile, const char *tempName = TWaveformConstants::templateNames, int tempNum = TWaveformConstants::numberOfTemplates, int maxPulses = TWaveformConstants::maxPulses, double maxChi = TWaveformConstants::maxChiNorm, int tLim = TWaveformConstants::timeFittingLim, double scaleLim = TWaveformConstants::scaleFittingLim);
  void CreateTrees(int dirNum, int firstWave, int treeNum, std::string dirAddress = TWaveformConstants::treeDirectoryAddress, std::string treeName = TWaveformConstants::treeName, const char* treeTitle = "Waveform Tree", const char *tempFile = TWaveformConstants::templateFile, const char *tempName = TWaveformConstants::templateNames, int tempNum = TWaveformConstants::numberOfTemplates, int maxPulses = TWaveformConstants::maxPulses, double maxChi = TWaveformConstants::maxChiNorm, int tLim = TWaveformConstants::timeFittingLim, double scaleLim = TWaveformConstants::scaleFittingLim);
  void CreateChain(int dirNum, std::string treeDirAddress = TWaveformConstants::treeDirectoryAddress, const char *chainName = TWaveformConstants::chainName.c_str(), const char *chainFile = "WaveChain.root", std::string treeName = TWaveformConstants::treeName, const char *chainTitle = "A Waveform Chain");
  void CreateTreeChain(int dirNum, std::string treeDirAddress = TWaveformConstants::treeDirectoryAddress, std::string treeName = TWaveformConstants::treeName, std::string chainName = TWaveformConstants::chainName, std::string chainDirAddress = TWaveformConstants::chainDirectoryAddress, const char* treeTitle = "Waveform Tree", const char *chainTitle = "A Waveform Chain", const char *tempFile = TWaveformConstants::templateFile, const char *tempName = TWaveformConstants::templateNames, int tempNum = TWaveformConstants::numberOfTemplates, int maxPulses = TWaveformConstants::maxPulses, double maxChi = TWaveformConstants::maxChiNorm, int tLim = TWaveformConstants::timeFittingLim, double scaleLim = TWaveformConstants::scaleFittingLim);
  void CreateTreeChain(int dirNum, int firstWave, int treeNum, std::string treeDirAddress = TWaveformConstants::treeDirectoryAddress, std::string treeName = TWaveformConstants::treeName, std::string chainName = TWaveformConstants::chainName, std::string chainDirAddress = TWaveformConstants::chainDirectoryAddress, const char* treeTitle = "Waveform Tree", const char *chainTitle = "A Waveform Chain", const char *tempFile = TWaveformConstants::templateFile, const char *tempName = TWaveformConstants::templateNames, int tempNum = TWaveformConstants::numberOfTemplates, int maxPulses = TWaveformConstants::maxPulses, double maxChi = TWaveformConstants::maxChiNorm, int tLim = TWaveformConstants::timeFittingLim, double scaleLim = TWaveformConstants::scaleFittingLim);
  void LinkChain(const char *chainFile1, const char *chainFile2, const char *fName, const char *chainName1 = TWaveformConstants::chainName.c_str(), const char *chainName2 = TWaveformConstants::chainName.c_str(), const char *newChainName = TWaveformConstants::chainName.c_str());

  //_____________________________________________________________________________________________________________________________________
  // DATA ANALYSIS FUNCTIONS
  TH1F *TimeDist(const char* treeName = TWaveformConstants::treeName.c_str(), const char* fName = "WaveTree.root", int nBins = TWaveformConstants::nTimeBins, float xLow = TWaveformConstants::timeLowLim, float xUp = TWaveformConstants::timeUpLim, int nPeaks = TWaveformConstants::nPulse, double minSig = TWaveformConstants::minimumPulseHeight);
  TH1F *TimeDistChain(const char* fName ="WaveChain.root", const char* chainName = TWaveformConstants::chainName.c_str(), int nBins = TWaveformConstants::nTimeBins, float xLow = TWaveformConstants::timeLowLim, float xUp = TWaveformConstants::timeUpLim, int nPeaks = TWaveformConstants::nPulse, double minSig = TWaveformConstants::minimumPulseHeight);
  TH2F *AfterPulseHeightAndTime(const char* fName = "WaveChain.root", const char* chainName = TWaveformConstants::chainName.c_str(), int nBinsX = TWaveformConstants::nTimeBins, int nBinsY = TWaveformConstants::nPulseHeightBins, float xLow = TWaveformConstants::timeLowLim, float xUp = TWaveformConstants::timeUpLim, float yLow = TWaveformConstants::pulseHeightLowLim, float yUp = TWaveformConstants::pulseHeightUpLim, int nPeaks = TWaveformConstants::nPulse, double minSig = TWaveformConstants::minimumPulseHeight);
  TH1F *FirstPulseHeight(const char* fName ="WaveChain.root", const char* chainName = TWaveformConstants::chainName.c_str(), int nBins = TWaveformConstants::nPulseHeightBins, float xLow = TWaveformConstants::pulseHeightLowLim, float xUp = TWaveformConstants::pulseHeightUpLim);
  TH2F *FirstPulseHeightAndTime(const char* fName = "WaveChain.root", const char* chainName = TWaveformConstants::chainName.c_str(), int nBinsX = TWaveformConstants::nTimeBins, int nBinsY = TWaveformConstants::nPulseHeightBins, float xLow = TWaveformConstants::timeLowLim, float xUp = TWaveformConstants::timeUpLim, float yLow = TWaveformConstants::pulseHeightLowLim, float yUp = TWaveformConstants::pulseHeightUpLim, int nPeaks = TWaveformConstants::nPulse, double minSig = TWaveformConstants::minimumPulseHeight);
  TH2F *FirstAndSecondPulseHeights(const char* fName = "WaveChain.root", const char* chainName = TWaveformConstants::chainName.c_str(), int nBinsX = TWaveformConstants::nPulseHeightBins, int nBinsY = TWaveformConstants::nPulseHeightBins, float xLow = TWaveformConstants::pulseHeightLowLim, float xUp = TWaveformConstants::pulseHeightUpLim, float yLow = TWaveformConstants::pulseHeightLowLim, float yUp = TWaveformConstants::pulseHeightUpLim, int nPeaks = TWaveformConstants::nPulse, double minSig = TWaveformConstants::minimumPulseHeight);
  TH2F *AreaDist(const char* fName = "WaveChain.root", const char* chainName = TWaveformConstants::chainName.c_str(), int nBinsX = TWaveformConstants::nTimeBins, int nBinsY = TWaveformConstants::nAreaBins, float xLow = TWaveformConstants::timeLowLim, float xUp = TWaveformConstants::timeUpLim, float yLow = TWaveformConstants::areaLowLim, float yUp = TWaveformConstants::areaUpLim, int nPeaks = TWaveformConstants::nPulse, double minSig = TWaveformConstants::minimumPulseHeight);
  TH2F *PulseAreaDist(const char* fName = "WaveChain.root", const char* chainName = TWaveformConstants::chainName.c_str(), int nBinsX = TWaveformConstants::nTimeBins, int nBinsY = TWaveformConstants::nPulseAreaBins, float xLow = TWaveformConstants::timeLowLim, float xUp = TWaveformConstants::timeUpLim, float yLow = TWaveformConstants::pulseAreaLowLim, float yUp = TWaveformConstants::pulseAreaUpLim, int tempNum = TWaveformConstants::numberOfTemplates, const char *tempFile = TWaveformConstants::templateFile, const char *tempName = TWaveformConstants::templateNames, int nPeaks = TWaveformConstants::nPulse, double minSig = TWaveformConstants::minimumPulseHeight);
  TH1F *ChiSquaredHist(const char* fName ="WaveChain.root", const char* chainName = TWaveformConstants::chainName.c_str(), int nBins = TWaveformConstants::nChiSquaredBins, float xLow = TWaveformConstants::chiSquaredLowLim, float xUp = TWaveformConstants::chiSquaredUpLim);
  TH2F *ChiSquaredHist2(const char* fName = "WaveChain.root", const char* chainName = TWaveformConstants::chainName.c_str(), int nBinsX = TWaveformConstants::nTimeBins, int nBinsY = TWaveformConstants::nChiSquaredBins, float xLow = TWaveformConstants::timeLowLim, float xUp = TWaveformConstants::timeUpLim, float yLow = TWaveformConstants::chiSquaredLowLim, float yUp = TWaveformConstants::chiSquaredUpLim, int nPeaks = TWaveformConstants::nPulse, double minSig = TWaveformConstants::minimumPulseHeight);
  TH2F *ChiSquaredProbHist(const char* fName = "WaveChain.root", const char* chainName = TWaveformConstants::chainName.c_str(), int nBinsX = TWaveformConstants::nTimeBins, int nBinsY = TWaveformConstants::nChiProbBins, float xLow = TWaveformConstants::timeLowLim, float xUp = TWaveformConstants::timeUpLim, float yLow = TWaveformConstants::chiProbLowLim, float yUp = TWaveformConstants::chiProbUpLim, int nPeaks = TWaveformConstants::nPulse, double minSig = TWaveformConstants::minimumPulseHeight);
  TH2F *ChiSquaredProbAndPulseHeightHist(const char* fName = "WaveChain.root", const char* chainName = TWaveformConstants::chainName.c_str(), int nBinsX = TWaveformConstants::nPulseHeightBins, int nBinsY = TWaveformConstants::nChiProbBins, float xLow = TWaveformConstants::pulseHeightLowLim, float xUp = TWaveformConstants::pulseHeightUpLim, float yLow = TWaveformConstants::chiProbLowLim, float yUp = TWaveformConstants::chiProbUpLim);
  TH2F *ChiSquaredAndPulseHeightHist(const char* fName = "WaveChain.root", const char* chainName = TWaveformConstants::chainName.c_str(), int nBinsX = TWaveformConstants::nPulseHeightBins, int nBinsY = TWaveformConstants::nChiSquaredBins, float xLow = TWaveformConstants::pulseHeightLowLim, float xUp = TWaveformConstants::pulseHeightUpLim, float yLow = TWaveformConstants::chiSquaredLowLim, float yUp = TWaveformConstants::chiSquaredUpLim);
}


#endif




