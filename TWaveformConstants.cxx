// TWaveformConstants.cxx
// Carlos Osorio, April 2017
// File that contains the adresses and name extensions of files to be read and used for the TWaveform class. 

#include <string>
#include "TWaveformConstants.h"

namespace TWaveformConstants
{
  //_____________________________________________________________________________________________________________________________________
  // File Address Parameters
  extern const std::string directoryAddress = "./Waveforms/Run";                    //CSV: "./Waveforms/SiPM_"
  extern const std::string fileType = ".txt";                                       //".CSV", ".txt"
  extern const std::string fileName = "/data/C2wave";                               //CSV: "/DS", txt: "/data/C1wave" or "/data/C2wave"
  
  //_____________________________________________________________________________________________________________________________________
  // Template Generation Parameters
  extern const char *templateFile = "./Templates/TemplateTXT.root";                 //CSV: "Templates/TempSmooth.root"
  extern const char *templateNames = "Template";
  extern const int numberOfTemplates = 4;                                           //CSV: 7, txt: 4
  
  //_____________________________________________________________________________________________________________________________________
  // Fitting Parameters
  extern const double scaleResolution = 0.01;
  extern const int timeResolution = 1;
  extern const double minimumScale = 0;
  extern const int timeStepDivider = 8;
  extern const double scaleStepDivider = 8;
  extern const int timeFittingLim = 2000;                                           //CSV: 2000
  extern const double scaleFittingLim = 5;                                          //CSV: 3, txt: 5
  extern const int maxPulses = 4;                                                   //CSV: 4
  extern const double maxChiNorm = 200;

  
  //_____________________________________________________________________________________________________________________________________
  // Other Processing Parameters
  extern const float slopeSigma = 3.7e-13;                                          //CSV: 3.7e-11, txt: 3.7e-13
  extern const double minimumPulseHeight = 0;                                       //CSV: 0.005

  //_____________________________________________________________________________________________________________________________________
  // Noise Filter Parameters
  extern const double maxAvgForNoise = 1e-3;                                        //CSV: 1e-3, txt = 0
  extern const double maxAreaForNoise = 3e-12;                                      // txt: 3e-12
  extern const std::string noiseFilterMethod = "Area";                              // "Avg" or "Area"

  //_____________________________________________________________________________________________________________________________________
  // Tree and Chain Generation Parameters
  extern const int treeSaveStep = 400;
  extern const std::string treeDirectoryAddress = "./WaveTrees/WaveTree";
  extern const std::string treeName = "WaveTree";
  extern const std::string chainDirectoryAddress = "./WaveChains";
  extern const std::string chainName = "WaveChain";

  //_____________________________________________________________________________________________________________________________________
  // Tree and Chain Histogram Generation Parameters
  // All Time Distribution Parameters:
  extern const int nPulse = 2;                                                      // Pulse whose time distribution will be analyzed
  extern const int nTimeBins = 100;
  extern const double timeLowLim = 0;
  extern const double timeUpLim = 4e-7;                                             //CSV: 1e-6, txt: 4e-7
  // PulseHeight() Parameters:
  extern const int nPulseHeightBins = 100;
  extern const double pulseHeightLowLim = 0;
  extern const double pulseHeightUpLim = 0.012;                                     //CSV: 0.8, txt: 0.012
  // AreaDist() Parameters:
  extern const int nAreaBins = 100;
  extern const double areaLowLim = 0;
  extern const double areaUpLim = 6e-10;                                            //CSV: 5e-7, txt: 6e-10
  // PulseAreaDist() Parameters:
  extern const int nPulseAreaBins = 100;
  extern const double pulseAreaLowLim = 0;
  extern const double pulseAreaUpLim = 2e-10;                                       //CSV: 2e-7, txt: 2e-10
  // ChiSquaredHist() Parameters:
  extern const int nChiSquaredBins = 100;
  extern const float chiSquaredLowLim = 0;
  extern const float chiSquaredUpLim = 15;
  // ChiSquaredProbHist() Parameters:
  extern const int nChiProbBins = 100;
  extern const float chiProbLowLim = 0;
  extern const float chiProbUpLim = 1e-7;
}