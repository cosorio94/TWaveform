// File: TWaveformConstants.h
// Carlos Osorio, April 2017
// Waveform class used to read and process data from CVS file 

#ifndef ROOT_TWaveform_Constants
#define ROOT_TWaveform_Constants

#include <string>

namespace TWaveformConstants
{
  //_____________________________________________________________________________________________________________________________________
  // File Address Parameters
  extern const std::string directoryAddress;
  extern const std::string fileType;
  extern const std::string fileName;
  
  //_____________________________________________________________________________________________________________________________________
  // Template Generation Parameters
  extern const char *templateFile;
  extern const char *templateNames;
  extern const int numberOfTemplates;

  //_____________________________________________________________________________________________________________________________________
  // Fitting Parameters
  extern const double scaleResolution;
  extern const int timeResolution;
  extern const double minimumScale;
  extern const int timeStepDivider;
  extern const double scaleStepDivider;
  extern const int timeFittingLim;
  extern const double scaleFittingLim;
  extern const int maxPulses;
  extern const double maxChiNorm;
  
  //_____________________________________________________________________________________________________________________________________
  // Other Processing Parameters
  extern const float slopeSigma;
  extern const double minimumPulseHeight;

  //_____________________________________________________________________________________________________________________________________
  // Noise Filter Parameters
  extern const double maxAvgForNoise;
  extern const double maxAreaForNoise; 
  extern const std::string noiseFilterMethod;

  //_____________________________________________________________________________________________________________________________________
  // TTree and TChain Generation Parameters
  extern const int treeSaveStep;
  extern const std::string treeDirectoryAddress;
  extern const std::string treeName;
  extern const std::string chainDirectoryAddress;
  extern const std::string chainName;

  //_____________________________________________________________________________________________________________________________________
  // Tree and Chain Histogram Generation Parameters
  // All Time Distribution Parameters:
  extern const int nPulse;
  extern const int nTimeBins;
  extern const double timeLowLim;
  extern const double timeUpLim;
  // PulseHeight() Parameters:
  extern const int nPulseHeightBins;
  extern const double pulseHeightLowLim;
  extern const double pulseHeightUpLim;
  // AreaDist() Parameters:
  extern const int nAreaBins;
  extern const double areaLowLim;
  extern const double areaUpLim;
  // PulseAreaDist() Parameters:
  extern const int nPulseAreaBins;
  extern const double pulseAreaLowLim;
  extern const double pulseAreaUpLim;
  // ChiSquaredHist() Parameters:
  extern const int nChiSquaredBins;
  extern const float chiSquaredLowLim;
  extern const float chiSquaredUpLim;
  // ChiSquaredProbHist() Parameters:
  extern const int nChiProbBins;
  extern const float chiProbLowLim;
  extern const float chiProbUpLim;
}

#endif