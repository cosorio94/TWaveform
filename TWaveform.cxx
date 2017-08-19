// TWaveform.cxx
// Carlos Osorio, July 2016
// Utility library used to read, process and analyze massive sets of waveform data 
// See User Guide for documentation

#include <iostream>
#include <cstdlib>
#include <string> 
#include <stdio.h>
#include <cmath>
#include <fstream>
#include "TWaveform.h"
#include "TROOT.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TPaveLabel.h"
#include "TH1.h"
#include "TH2.h"
#include "TAxis.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TBRIK.h"
#include "TKey.h"
#include "TBox.h"
#include "TNode.h"
#include "TRotMatrix.h"
#include "TPaveText.h"
#include "TArrow.h"
#include "TMarker.h"
#include "TText.h"
#include "TPad.h"
#include "TControlBar.h"
#include "TPostScript.h"
#include "TFile.h"
#include "TStyle.h"
#include "TMath.h"
#include "TLorentzVector.h"
#include "TVector.h"
#include "THStack.h"
#include "TAttMarker.h"
#include "TBenchmark.h"
#include "TClass.h"
#include "TObject.h"
#include "TNamed.h"
#include <Math.h>
#include "TClass.h"
#include <vector>
#include <sstream>
#include <stdlib.h>
#include "TLegend.h"
#include "TTree.h"
#include "TChain.h"
#include <algorithm>
#include "TWaveformConstants.h"



ClassImp(TWaveform)

// namespace TWaveform
// {

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                               /////////////////////////////////////////
                                               ////// CONSTRUCTORS & DESTRUCTOR ////////
                                               /////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //_____________________________________________________________________________________________________________________________________
  TWaveform::TWaveform(): TNamed()
  {
    this->nSamples=0;
    memset(this->risePosA, 0 , sizeof(this->risePosA));
    memset(this->vAreaA, 0 , sizeof(this->vAreaA));
    memset(this->peaksA, 0 , sizeof(this->peaksA));
    memset(this->t, 0 , sizeof(this->t));
    memset(this->vA, 0 , sizeof(this->vA));
    memset(this->vIAreaA, 0 , sizeof(this->vIAreaA));
    this->vOffsetA=0;
    this->nPeaksA=0;
    this->tBinSize=0;
    this->stDevA=0;
    this->noiseA = false;
    this->bestTemp.reserve(10);
    this->bestTemp.assign(1,"");
    this->bestTempScale.reserve(10);
    this->bestTempScale.assign(1,1);
    this->bestTempOffset.reserve(10);
    this->bestTempOffset.assign(1,0);
    this->bestTempChi = 0;
    this->directoryAddress = TWaveformConstants::directoryAddress;
    this->genericFileName = TWaveformConstants::fileName;
    this->fileType = TWaveformConstants::fileType;
  }

  //_____________________________________________________________________________________________________________________________________
  TWaveform::TWaveform(std::string dirAddress, std::string fName, std::string fType): TNamed()
  {
    this->nSamples=0;
    memset(this->risePosA, 0 , sizeof(this->risePosA));
    memset(this->vAreaA, 0 , sizeof(this->vAreaA));
    memset(this->peaksA, 0 , sizeof(this->peaksA));
    memset(this->t, 0 , sizeof(this->t));
    memset(this->vA, 0 , sizeof(this->vA));
    memset(this->vIAreaA, 0 , sizeof(this->vIAreaA));
    this->vOffsetA=0;
    this->nPeaksA=0;
    this->tBinSize=0;
    this->stDevA=0;
    this->noiseA = false;
    this->bestTemp.reserve(10);
    this->bestTemp.assign(1,"");
    this->bestTempScale.reserve(10);
    this->bestTempScale.assign(1,1);
    this->bestTempOffset.reserve(10);
    this->bestTempOffset.assign(1,0);
    this->bestTempChi = 0;
    this->directoryAddress = dirAddress;
    this->genericFileName = fName;
    this->fileType = fType;
  }

  //_____________________________________________________________________________________________________________________________________
  TWaveform::TWaveform(const char *name,const char *title): TNamed(name, title)
  {
    this->nSamples=0;
    memset(this->risePosA, 0 , sizeof(this->risePosA));
    memset(this->vAreaA, 0 , sizeof(this->vAreaA));
    memset(this->peaksA, 0 , sizeof(this->peaksA));
    memset(this->t, 0 , sizeof(this->t));
    memset(this->vA, 0 , sizeof(this->vA));
    memset(this->vIAreaA, 0 , sizeof(this->vIAreaA));
    this->vOffsetA=0;
    this->nPeaksA=0;
    this->tBinSize=0;
    this->stDevA=0;
    this->noiseA = false;
    this->bestTemp.reserve(10);
    this->bestTemp.assign(1,"");
    this->bestTempScale.reserve(10);
    this->bestTempScale.assign(1,1);
    this->bestTempOffset.reserve(10);
    this->bestTempOffset.assign(1,0);
    this->bestTempChi = 0;
    this->directoryAddress = TWaveformConstants::directoryAddress;
    this->genericFileName = TWaveformConstants::fileName;
    this->fileType = TWaveformConstants::fileType;
  }

  //_____________________________________________________________________________________________________________________________________
  TWaveform::TWaveform(const char *name,const char *title, std::string dirAddress, std::string fName, std::string fType): TNamed(name, title)
  {
    this->nSamples=0;
    memset(this->risePosA, 0 , sizeof(this->risePosA));
    memset(this->vAreaA, 0 , sizeof(this->vAreaA));
    memset(this->peaksA, 0 , sizeof(this->peaksA));
    memset(this->t, 0 , sizeof(this->t));
    memset(this->vA, 0 , sizeof(this->vA));
    memset(this->vIAreaA, 0 , sizeof(this->vIAreaA));
    this->vOffsetA=0;
    this->nPeaksA=0;
    this->tBinSize=0;
    this->stDevA=0;
    this->noiseA = false;
    this->bestTemp.reserve(10);
    this->bestTemp.assign(1,"");
    this->bestTempScale.reserve(10);
    this->bestTempScale.assign(1,1);
    this->bestTempOffset.reserve(10);
    this->bestTempOffset.assign(1,0);
    this->bestTempChi = 0;
    this->directoryAddress = dirAddress;
    this->genericFileName = fName;
    this->fileType = fType;
  }

  //_____________________________________________________________________________________________________________________________________
  TWaveform::~TWaveform()
  {}

  //_____________________________________________________________________________________________________________________________________
  // Clears all the information in the TWaveform's data members.
  void TWaveform::Clear()
  {
    TNamed::Clear();
    this->nSamples=0;
    memset(this->risePosA, 0 , sizeof(this->risePosA));
    memset(this->vAreaA, 0 , sizeof(this->vAreaA));
    memset(this->peaksA, 0 , sizeof(this->peaksA));
    memset(this->t, 0 , sizeof(this->t));
    memset(this->vA, 0 , sizeof(this->vA));
    memset(this->vIAreaA, 0 , sizeof(this->vIAreaA));
    this->vOffsetA=0;
    this->nPeaksA=0;
    this->tBinSize=0;
    this->stDevA=0;
    this->noiseA = false;
    this->bestTemp.reserve(10);
    this->bestTemp.assign(1,"");
    this->bestTempScale.reserve(10);
    this->bestTempScale.assign(1,1);
    this->bestTempOffset.reserve(10);
    this->bestTempOffset.assign(1,0);
    this->bestTempChi = 0;
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                             /////////////////////////////////////////
                                             ///////// OVERLOADED OPERATORS //////////
                                             /////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //_____________________________________________________________________________________________________________________________________
  // + operator adds vA values and returns a pre-processed TWaveform
  TWaveform TWaveform::operator+(TWaveform &obj)
  {
    TWaveform tolo;
    std::copy(std::begin(this->t), std::end(this->t), std::begin(tolo.t));
    ((TWaveform&)tolo).tBinSize = this->tBinSize;
    int iMax;
    if (obj.nSamples > tolo.nSamples)
    {
      iMax = obj.nSamples;
    }
    else
    {
      iMax = tolo.nSamples;
    }
    ((TWaveform&)tolo).nSamples = iMax;
    for (int i = 0; i < iMax; ++i)
    {
      tolo.vA[i] = this->vA[i] + obj.vA[i];
    }
    tolo.PreDataProcessing();
    return tolo;
  }

  //_____________________________________________________________________________________________________________________________________
  // + operator subtracts vA values and returns a pre-processed TWaveform
  TWaveform TWaveform::operator-(TWaveform &obj)
  {
    TWaveform tolo;
    std::copy(std::begin(this->t), std::end(this->t), std::begin(tolo.t));
    ((TWaveform&)tolo).nSamples = nSamples;
    ((TWaveform&)tolo).tBinSize = tBinSize;
    int iMax;
    if (obj.nSamples > tolo.nSamples)
    {
      iMax = obj.nSamples;
    }
    else
    {
      iMax = tolo.nSamples;
    }
    for (int i = 0; i < iMax; ++i)
    {
      tolo.vA[i] = this->vA[i] - obj.vA[i];
    }
    tolo.PreDataProcessing();
    return tolo;
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                               /////////////////////////////////////////
                                               ///////// COPY MEMBER FUNCTIONS /////////
                                               /////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  //_____________________________________________________________________________________________________________________________________
  // Copies the current TWaveform into the TWaveform obj
  void TWaveform::Copy(TWaveform &obj)
  {
    TNamed::Copy(obj);
    std::copy(std::begin(this->t), std::end(this->t), std::begin(obj.t));
    std::copy(std::begin(this->vA), std::end(this->vA), std::begin(obj.vA));
    std::copy(std::begin(this->risePosA), std::end(this->risePosA), std::begin(obj.risePosA));
    std::copy(std::begin(this->vAreaA), std::end(this->vAreaA), std::begin(obj.vAreaA));
    std::copy(std::begin(this->vIAreaA), std::end(this->vIAreaA), std::begin(obj.vIAreaA));
    std::copy(std::begin(this->peaksA), std::end(this->peaksA), std::begin(obj.peaksA));
    ((TWaveform&)obj).nPeaksA = this->nPeaksA;
    ((TWaveform&)obj).nSamples = this->nSamples;
    ((TWaveform&)obj).tBinSize = this->tBinSize;
    ((TWaveform&)obj).vOffsetA = this->vOffsetA;
    ((TWaveform&)obj).stDevA = this->stDevA;
    ((TWaveform&)obj).noiseA = this->noiseA;
    ((TWaveform&)obj).bestTemp = this->bestTemp;
    ((TWaveform&)obj).bestTempOffset = this->bestTempOffset;
    ((TWaveform&)obj).bestTempScale = this->bestTempScale;
    ((TWaveform&)obj).directoryAddress = this->directoryAddress;
    ((TWaveform&)obj).genericFileName = this->genericFileName;
    ((TWaveform&)obj).fileType = this->fileType;
    return;
  }

  //_____________________________________________________________________________________________________________________________________
  // Copies only the signal of the current TWaveform into the TWaveform obj
  void TWaveform::CopySignal(TWaveform &obj)
  {
    TNamed::Copy(obj);
    std::copy(std::begin(this->t), std::end(this->t), std::begin(obj.t));
    std::copy(std::begin(this->vA), std::end(this->vA), std::begin(obj.vA));
    ((TWaveform&)obj).nSamples = this->nSamples;
    ((TWaveform&)obj).tBinSize = this->tBinSize;
    ((TWaveform&)obj).noiseA = this->noiseA;
    ((TWaveform&)obj).directoryAddress = this->directoryAddress;
    ((TWaveform&)obj).genericFileName = this->genericFileName;
    ((TWaveform&)obj).fileType = this->fileType;
    return;
  }

  //_____________________________________________________________________________________________________________________________________
  // Copies only the setup parameters of the current TWaveform into the TWaveform obj
  void TWaveform::CopySetup(TWaveform &obj)
  {
    TNamed::Copy(obj);
    std::copy(std::begin(this->t), std::end(this->t), std::begin(obj.t));
    ((TWaveform&)obj).nSamples = this->nSamples;
    ((TWaveform&)obj).tBinSize = this->tBinSize;
    ((TWaveform&)obj).noiseA = this->noiseA;
    ((TWaveform&)obj).directoryAddress = this->directoryAddress;
    ((TWaveform&)obj).genericFileName = this->genericFileName;
    ((TWaveform&)obj).fileType = this->fileType;
    return;
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                               /////////////////////////////////////////
                                               ///////// READ MEMBER FUNCTIONS /////////
                                               /////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  //_____________________________________________________________________________________________________________________________________
  // Reads CSV and saves the data inside of the current TWaveform.
  // Read file method: 1
  bool TWaveform::ReadCSV(std::string fName1)
  {
   // The format from the GDS scope is as follows:
   //Memory Length,4000,
   //Trigger Level,-2.40000e+01,
   //Source,CH2,
   //Probe,1.0X,
   //Vertical Units,V,
   //Vertical Scale,5.00000e-02,
   //Vertical Position,1.04000e-01,
   //Horizontal Units,S,
   //Horizontal Scale,1.00000e-03,
   //Horizontal Position,4.0000000e-05,
   //Horizontal Mode,Main,
   //Sampling Period,4.00000e-06,
   //Firmware,V1.09,
   //Time, ,
   //Mode,Detail or Fast,
   //Waveform Data,
   //   What follows depends on whether it is detail mode or fast mode.
   //   For detail mode it is
   //time[1],v[1],
   //time[2],v[2],
   //time[3],v[3],
   //...
   //time[n],v[n],
   //   For fast mode it is
   //v[1],
   //v[2],
   //v[3],
   //...
   //v[n],
   //   Where v is in ADC counts rather than in volts. (?)
    
   // The format from the tektronics scope is as follows:
   //"Record Length",500,"Points",-6.24000008e-008,-0.00800000069
   //"Sample Interval",1.60000002e-009,s,-6.08000008e-008,-0.00800000069
   //"Trigger Point",39,"Samples",-5.92000008e-008,-0.00800000069
   //"Trigger Time",1.5990174e-009,s,-5.76000008e-008,-0.0160000006
   //"",,,Time[0],Voltage[0]
   //,,,Time[1],Voltage[1]
   //...
   //,,,Time[n],Voltage[n]

    int scopemodel = 0;                             // Which type of scope did this come from: 0=GDS, 1=Tek
    std::string temp;
    bool fastMode = true;                         // True if scope was in fast mode
    bool detailMode = false;                      // True if scope was in detail mode
    int nchar=1;                                  // Number of characters read
    int memLength = 0;                            // Number of samples in the waveform
    float vScale = 1.;                            // Vertical scale
    float vPosition = 1.;                         // Vertical Position
    float hScale = 1.;                            // Vertical scale
    float samplePeriod = 1.;                      // time between samples in seconds
    float tIn, vIn;                               // input time and voltage variables used to pass information into waveform object
    bool Channel1 = true;                         // True if csv file corresponds to the scope's channel 1 and false if it corresponds to channel 2
    bool debug = false;

    FILE* f;
    f = fopen(fName1.c_str(),"r");                          //Opens first csv file

    if (!f)
    {
      // std::cout<<"File was not found.\n";       // Outputs text when file is not found.
      return false;
    }
    else
    {
      char line[200];                             // The current line of input in character format
      std::string Line;                           // The current line of input in string format
      
      // This part will read the header information of the file
      nchar=fscanf(f,"%s",line);                    // Should be "Memory" if GDS scope and ""Record" if Tek
      Line=line;

      if(Line!="Memory")                          // Determine what scope model does the csv file correspond to (GDS or Tektronic)
      {
        temp=Line.erase(0,1);
        if (temp=="Record")
          scopemodel=1;
        if (scopemodel==0)
          std::cerr << "Parsing error. Expected Memory Length on first line, but instead got "<<Line<<"\n";
      }
      // Parse GDS scope waveforms
      if (scopemodel==0)
      {
        //Memory Length
        nchar = fscanf(f,"%s",line);                  // Should be "Length,XXXX,"
        Line=line;
        Line.erase(0,7);
        Line.erase(Line.length()-1,1);
        sscanf(Line.c_str(),"%d",&memLength);             // Determines the Memory length given by the csv file
        if (debug) 
          std::cout << "Memory Length is "<<Line<<" " << memLength <<"\n";    // Prints out the Memory Length when on debug mode
        
        //Trigger Level
        nchar = fscanf(f,"%s",line); 
        Line = line;                          // Should be "Trigger"
        if (Line != "Trigger") 
          std::cerr << "Parsing error. Expected Trigger Level on second line, but instead got "<<Line<<"\n";
        nchar = fscanf(f,"%s",line); 
        Line = line;                            // Should be "Level,XXXX,"
        Line.erase(0,6);
        Line.erase(Line.length()-1,1); 

        //Source (Channel)
        nchar = fscanf(f,"%s",line); 
        Line = line;                            // Should be "Source,CHx,"
        temp=Line.substr(9,1);
        if (temp!="1")
          Channel1 = false;                     // Determines what Channel of the scope does the csv correspond to
        
        //Probe
        nchar = fscanf(f,"%s",line); 
        Line = line;                            // Should be "Probe,nX,"
          
        //Vertical Units
        nchar = fscanf(f,"%s",line); 
        Line = line;                          // Should be "Vertical"
        if (Line != "Vertical") 
          std::cerr << "Parsing error. Expected Vertical Units on fifth line, but instead got "<<Line<<"\n";
        nchar = fscanf(f,"%s",line); 
        Line = line;                            // Should be "Units,V,"
          
        //Vertical Scale
        nchar = fscanf(f,"%s",line); 
        Line = line;                          // Should be "Vertical"
        if (Line != "Vertical") 
          std::cerr << "Parsing error. Expected Vertical Scale on sixth line, but instead got "<<Line<<"\n";
        nchar = fscanf(f,"%s",line); 
        Line = line;                            // Should be "Scale,xxx,"
        Line.erase(0,6);
        Line.erase(Line.length()-1,1); 
        sscanf(Line.c_str(),"%f",&vScale);                // Determines the Vertical Scale given by the csv file
        if (debug) 
          std::cout <<"Vertical Scale is "<<Line<<" " << vScale <<"\n";

        //Vertical Position
        nchar = fscanf(f,"%s",line); 
        Line = line;                          // Should be "Vertical"
        if (Line != "Vertical") 
          std::cerr << "Parsing error. Expected Vertical Position on seventh line, but instead got "<<Line<<"\n";
        nchar = fscanf(f,"%s",line); 
        Line = line;                            // Should be "Position,xxx,"
        Line.erase(0,9);
        Line.erase(Line.length()-1,1);
        sscanf(Line.c_str(),"%f",&vPosition);             // Determines the Vertical Position given by the csv file 
        if (debug) 
          std::cout << "Vertical Position is " << Line<<" " << vPosition<<"\n";

        //Horizontal Units
        nchar = fscanf(f,"%s",line); 
        Line = line;                          // Should be "Horizontal"
        if (Line != "Horizontal") 
          std::cerr << "Parsing error. Expected Horizontal Units on eigth line, but instead got "<<Line<<"\n";
        nchar = fscanf(f,"%s",line); 
        Line = line;                            // Should be "Units,V,"

        //Horizontal Scale
        nchar = fscanf(f,"%s",line); 
        Line = line;                          // Should be "Horizontal"
        if (Line != "Horizontal") 
          std::cerr << "Parsing error. Expected Horizontal Scale on ninth line, but instead got "<<Line<<"\n";
        nchar = fscanf(f,"%s",line); 
        Line = line;                            // Should be "Scale,xxx,"
        Line.erase(0,6);
        Line.erase(Line.length()-1,1);  
        sscanf(Line.c_str(),"%f",&hScale);                // Determines the Horizontal Scale given by the csv file
        if (debug) 
          std::cout << "Horizontal Scale is "<<Line<<" " << hScale<<"\n";
        
        //Horizontal Position
        nchar = fscanf(f,"%s",line); 
        Line = line;                          // Should be "Horizontal"
        if (Line != "Horizontal") 
          std::cerr << "Parsing error. Expected Horizontal Position on tenth line, but instead got "<<Line<<"\n";
        nchar = fscanf(f,"%s",line); 
        Line = line;                            // Should be "Position,xxx,"
        Line.erase(0,9); 
        Line.erase(Line.length()-1,1);  

        //Horizontal Mode
        nchar = fscanf(f,"%s",line); 
        Line = line;                          // Should be "Horizontal"
        if (Line != "Horizontal") 
          std::cerr << "Parsing error. Expected Horizontal Position on eleventh line, but instead got "<<Line<<"\n";
        nchar = fscanf(f,"%s",line); 
        Line = line;                            // Should be "Mode,xxx,"
        
        //Sampling Period
        nchar = fscanf(f,"%s",line); 
        Line = line;                          // Should be "Sampling"
        if (Line != "Sampling") 
          std::cerr << "Parsing error. Expected Sampling Period on eleventh line, but instead got "<<Line<<"\n";
        nchar = fscanf(f,"%s",line); 
        Line = line;                            // Should be "Period,xxx,"
        Line.erase(0,7); 
        Line.erase(Line.length()-1,1);  
        sscanf(Line.c_str(),"%f",&samplePeriod);            // Determines the Sampling Period given by the csv file 
        if (debug) 
          std::cout << "The Sampling Period is " << Line<<" " << samplePeriod<<"\n";

        //Firmware and Time
        nchar = fscanf(f,"%s",line);                    // Should be "Firmware,XXX"
        nchar = fscanf(f,"%s",line);                    // Should be "Time,"
        nchar = fscanf(f,"%s",line);                    // Should be " ,"

        //Mode
        nchar = fscanf(f,"%s",line); 
        Line = line;                            // Should be "Mode,Detail"
        if (Line.compare("Mode,Fast,") == 0)              // Determines what mode the scope was running on (fast or detail)
          {
            fastMode = true; 
            detailMode = false;
          }
        if (debug) 
          std::cout << "The Mode is" << Line << ", so fastMode is " << fastMode << " and detailMode is " << detailMode << "\n";

        //Waveform Data
        nchar = fscanf(f,"%s",line); Line = line;             // Should be "Waveform"
        nchar = fscanf(f,"%s",line); Line = line;             // Should be "Data"

        //This part of the code will collect the raw data
        nSamples=0;
        while (nchar>0)                         // Read to end of file (where nchar=0)
        {
          nchar = fscanf(f,"%s",line);
          if (nchar>0)                        // Have a line?
          { 
            Line = line;

            // For scope in Detail Mode. Data parsed as "time,voltage,"
            if (detailMode)                     
            {
              std::string timestr = Line;
              std::string voltstr = Line;
              int i = Line.find(",");
              timestr = Line.substr(0,i);
              Line.erase(0,i+1);                  // Remove characters up to first ','
              i = Line.find(",");
              voltstr = Line.substr(0,i);
              // Convert from strings to floats
              sscanf(timestr.c_str(),"%f",&tIn);
              sscanf(voltstr.c_str(),"%f",&vIn);
              if (debug) 
                std::cout << "time: " << Line << " voltage: "<<tIn<<" "<<vIn<<"\n";
            } 

            // For scope in Fast Mode. Data parsed as "voltage,"
            else 
            { 
              int i = Line.find(",");
              Line.erase(i,1);                    // Remove the trailing comma
              // Set the time
              tIn = samplePeriod*(-memLength/2 + nSamples);
              
              // Read the voltage
              sscanf(Line.c_str(),"%f",&vIn);
              vIn *= vScale/25;                   // Correct for the scale and the ADC *ASK* 
              if (debug && nSamples == 0) 
                std::cout << Line << ": "<<tIn<<" "<<vIn<<"\n";
            }

            //Save information into the TWaveform object
            t[nSamples] = tIn;
            vA[nSamples] = vIn;
            nSamples++;
          } 
        }                                 
      }   // Parse GDS scope waveforms
  
      // Parse Tek scope waveform
      else if (scopemodel == 1) 
      { 
        nchar = fscanf(f,"%s",line); 
        Line = line;                              // Should be Length",500,"Points",-6.24000008e-008,-0.00800000069
        nchar = fscanf(f,"%s",line); 
        Line = line;                              // Should be "Sample
        nchar = fscanf(f,"%s",line); 
        Line = line;                              // Should be Interval",1.60000002e-009,s,-6.08000008e-008,-0.00800000069
        nchar = fscanf(f,"%s",line); 
        Line = line;                              // Should be "Trigger
        nchar = fscanf(f,"%s",line); 
        Line = line;                              // Should be Point",39,"Samples",-5.92000008e-008,-0.00800000069
        nchar = fscanf(f,"%s",line); 
        Line = line;                              // Should be "Trigger
        nchar = fscanf(f,"%s",line); 
        Line = line;                              // Should be Time",1.5990174e-009,s,-5.76000008e-008,-0.0160000006
          
        // What follows is the raw data in ",,,t,v," format
        nSamples = 0;
        while (nchar>0)                           // Read to end of file 
        {  
          nchar = fscanf(f,"%s",line);
          if (nchar>0) 
          {                                 // Have a line?
            Line = line;
            if (nSamples == 0) 
              Line.erase(0,5);                    // Remove the leading "",,, from the first line. Subsequent lines don't have the ""
            else
            Line.erase(0,3);                    // Remove the leading ,,,
    
            // Parse this as "time,voltage,"
            std::string timestr = Line;
            std::string voltstr = Line;
            int i = Line.find(",");
            timestr = Line.substr(0,i);
            voltstr = Line;
            voltstr.erase(0,i+1);                     // Remove characters up to first ','
            while (voltstr[0] == ' ') 
              voltstr.erase(0,1);                   // Remove any leading blanks
            while (timestr[0] == ' ')
              timestr.erase(0,1);                   // Remove any leading blanks
            
            // Convert from strings to floats
            sscanf(timestr.c_str(),"%f",&tIn);
            sscanf(voltstr.c_str(),"%f",&vIn);
              
            // Save the information into the waveform.
            t[nSamples] = tIn;
            vA[nSamples] = vIn;
            nSamples++;
          } // Have a line?
        } // Read to end of file
      } // Parse Tek scope waveform
      fclose(f);
      tBinSize = t[1]-t[0];
      return true;
    }
  }

  //_____________________________________________________________________________________________________________________________________
  // Reads .txt files and saves the data inside of the current TWaveform.
  // Read file method: 2
  bool TWaveform::ReadTXT(std::string fName1, bool debug)
  {
    // The format for the text files that this method reads from is:
    // LECROYWR104MXi-A©Ë 52137 Waveform
    // Segments 1 SegmentSize 5002
    // Segment TrigTime TimeSinceSegment1
    // #1 03-Apr-2017 14:53:22 0                 
    // Time Ampl
    // time[0] v[0]
    // time[1] v[1]
    // time[2] v[2]
    // ...
    // time[n] v[n]
    float tIn, vIn;                                            // Input time and voltage variables used to pass information into waveform object
    std::string line;
    int nChar(0);
    std::ifstream file(fName1.c_str(), std::ifstream::in);          //Opens first text file
    if (!file.good())
    {
      if(debug) std::cout<<"File was not found.\n";                      // Outputs text when file is not found.
      return false;
    }
    else
    {
      std::getline(file, line);                                // Should be something like "LECROYWR104MXi-A©Ë 52137 Waveform"
      if(debug) std::cout << line << std::endl;
      std::getline(file, line);                                // Should be something like "Segments 1 SegmentSize 5002"
      if(debug) std::cout << line << std::endl;
      std::getline(file, line);                                // Should be something like "Segment TrigTime TimeSinceSegment1"
      if(debug) std::cout << line << std::endl;
      std::getline(file, line);                                // Should be something like "#1 03-Apr-2017 14:53:22 0"
      if(debug) std::cout << line << std::endl;
      std::getline(file, line);                                // Should be "Time Ampl"
      if(debug) std::cout << line << std::endl;    
      int i(0);
      while(std::getline(file, line))
      {
        if(debug) std::cout << i << ": " << line << std::endl;
        nChar = sscanf(line.c_str(), "%f %f", &tIn, &vIn);
        if(debug) std::cout << "line scanned" << std::endl;
        this->vA[i] = vIn;
        if(debug) std::cout<< "v: " << vIn << std::endl;
        this->t[i] = tIn;
        if(debug) std::cout<< "t: " << tIn << std::endl;
        i++;
      }
      this->nSamples = i;
      this->tBinSize = t[1] - t[0];
    }
    file.close();
    return true;
  }

  //_____________________________________________________________________________________________________________________________________
  // Uses one of the Read File methods of TWaveform depending on the current waveform's fileType.
  bool TWaveform::ReadFile(std::string fName)
  {
    bool read;
    if(this->fileType == ".CSV")
    {
      read = this->ReadCSV(fName);
    }
    else if(this->fileType == ".txt")
    {
      read = this->ReadTXT(fName);
    }
    return read;
  }

  //_____________________________________________________________________________________________________________________________________
  // Reads a TWaveform template named temp in the root file tempFile and copies it to the current waveform
  // ********CHANGED ---- SEE IF IT WORKS******
  void TWaveform::ReadTemp(const char *tempName, const char *tempFile)
  {
    TFile *file = new TFile(tempFile, "Read");
    TWaveform *tempWave = (TWaveform*) gDirectory->Get(tempName);
    std::copy(std::begin(tempWave->t), std::end(tempWave->t), std::begin(this->t));
    std::copy(std::begin(tempWave->vA), std::end(tempWave->vA), std::begin(this->vA));
    std::copy(std::begin(tempWave->risePosA), std::end(tempWave->risePosA), std::begin(this->risePosA));
    std::copy(std::begin(tempWave->vAreaA), std::end(tempWave->vAreaA), std::begin(this->vAreaA));
    std::copy(std::begin(tempWave->vIAreaA), std::end(tempWave->vIAreaA), std::begin(this->vIAreaA));
    std::copy(std::begin(tempWave->peaksA), std::end(tempWave->peaksA), std::begin(this->peaksA));
    this->nPeaksA = tempWave->nPeaksA;
    this->nSamples = tempWave->nSamples;
    this->tBinSize = tempWave->tBinSize;
    this->vOffsetA = tempWave->vOffsetA;
    this->stDevA = tempWave->stDevA;
    this->noiseA = tempWave->noiseA;
    this->directoryAddress = tempWave->directoryAddress;
    this->genericFileName = tempWave->genericFileName;
    this->fileType = tempWave->fileType;
    delete tempWave;
    file->Close();
    delete file;
    return; 
  }

  //_____________________________________________________________________________________________________________________________________
  // Prerequisite: Call SetBestTemplateParameters() first. 
  // Returns the best fit template waveform for the current waveform
  // pulseNum = 0 represents the waveform's first pulse.
  TWaveform TWaveform::ReadBestTemp(const char *tempFile, int pulseNum)
  {
    TWaveform temp;
    if (this->bestTemp[pulseNum] == "" || this->bestTemp.size() < pulseNum)
    {
      std::cout << "Error: The current waveform has less than " << pulseNum << " pulses saved in its bestTemp data member." << std::endl;
      return temp;
    }
    temp.ReadTemp(this->bestTemp[pulseNum].c_str(), tempFile);
    return temp;
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                             /////////////////////////////////////////
                                             ////// DRAW & PLOT MEMBER FUNCTIONS /////
                                             /////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //_____________________________________________________________________________________________________________________________________
  // Plots the current TWaveform without creating a new TCanvas when option contains "SAME"
  void TWaveform::Draw(std::string histName, Option_t* option, Color_t color)
  {
    TH1F *hist = new TH1F(histName.c_str(),"Waveform Signal",nSamples,t[0],t[nSamples-1]);
    bool isCanv = gROOT->GetListOfCanvases()->Contains("ca1");
    bool optionSame;
    std::string str("SAME"), opt(option);
    std::transform(opt.begin(), opt.end(),opt.begin(), ::toupper);
    optionSame = opt.find(str) != std::string::npos;
    if (isCanv && !optionSame)
    {
      TCanvas *c1 = ((TCanvas *)(gROOT->FindObject("ca1")));
      delete c1;
      c1 = new TCanvas("ca1","c1",800,1000); 
    }
    if (!isCanv)
    {
       TCanvas *c1 =  new TCanvas("ca1","c1",800,1000);
    }
    float v;
    for (int i=0; i<nSamples; i++)
    {
      v=vA[i];
      hist->Fill(t[i],v);
    }
    hist->SetMarkerStyle(3);
    hist->GetXaxis()->SetTitle("time (s)");
    hist->GetYaxis()->SetTitle("Voltage (V)");
    hist->GetXaxis()->SetTitleOffset(1.1);
    hist->GetYaxis()->SetTitleOffset(1.4);
    hist->SetLineColor(color);  
    hist->Draw(option);
    return;
  }

  //_____________________________________________________________________________________________________________________________________
  // Plots the area between each sample point of the waveform (vAreaA)
  void TWaveform::PlotArea(Option_t* option)
  {
    if (vAreaA[0]==0)
      this->FindArea();
    TH1F *hist = ((TH1F *)(gROOT->FindObject("Waveform Area")));
    delete hist;
    hist = new TH1F("Waveform Area","SiPM Signal Area",nSamples,t[0],t[nSamples-1]);
    TCanvas *c1 = ((TCanvas *)(gROOT->FindObject("carea1")));
    delete c1;
    c1 = new TCanvas("carea1","carea1",800,1000);                                                 
    float v;
    for (int i=0; i<nSamples-1; i++)
    {
      v=vAreaA[i];
      hist->Fill(t[i]+tBinSize/2,v);
    }
    hist->SetMarkerStyle(3);
    hist->GetXaxis()->SetTitle("time (s)");
    hist->GetYaxis()->SetTitle("Area (V*s)");  
    hist->Draw(option);
    return;
  }

  //_____________________________________________________________________________________________________________________________________
  void TWaveform::PlotIntegral(Option_t* option)                                 
  {
    if (vAreaA[0]==0)
      this->FindIntegral();
    TH1F *hist = ((TH1F *)(gROOT->FindObject("Waveform Integral")));
    delete hist;
    hist = new TH1F("Waveform Area","Waveform Integral",nSamples,t[0],t[nSamples-1]);
    TCanvas *c1 = ((TCanvas *)(gROOT->FindObject("carea1")));
    delete c1;
    c1 = new TCanvas("carea1","carea1",800,1000);                                                            
    float v;
    for (int i=0; i<nSamples-1; i++)
    {
      v=vIAreaA[i];
      hist->Fill(t[i],v);
    }
    hist->SetMarkerStyle(3);
    hist->GetXaxis()->SetTitle("time (s)");
    hist->GetYaxis()->SetTitle("Area (V*s)");  
    hist->Draw(option);
    return;
  }

  //_____________________________________________________________________________________________________________________________________
  //Plots the current waveform along with the TWaveform temp after applying to it the inserted scale and tOffset
  void TWaveform::DrawComp(TWaveform &temp, int tOffset, double scale)
  {
    this->Draw();
    TH1F *hist = ((TH1F *)(gROOT->FindObject("Template")));
    delete hist;
    hist = new TH1F("Template","Template",temp.nSamples,temp.t[0],temp.t[temp.nSamples-1]);
    double v;
    for (int i=0; i<nSamples; i++)
    {
      if (i - tOffset < 0)
        v = 0;
      else
        v = scale * temp.vA[i - tOffset];                                                       //**** LATER *****// make temp.vA[i + tOffset]=0 when i + tOffset<0 
      hist->Fill(t[i],v);
    }
    hist->SetMarkerStyle(3);
    hist->SetLineColor(kRed); 
    hist->Draw("C HIST SAME");
    //TLegend *leg = new TLegend(0.1,0.7,0.48,0.9);
    //leg->AddEntry(hist, "Template","l");
    //leg->Draw();
    return;
  }

  //_____________________________________________________________________________________________________________________________________
  //Plots the waveform being analized along with a template using the scale and tOffset that gives the least chi^2
  void TWaveform::DrawFitPar(TWaveform &temp, int tLim, double scaleLim)
  {
    fitParam par;
    par = this->FindFitPar(temp, tLim, scaleLim);
    this->DrawComp(temp, par.bestOffset, par.bestScale);
    return;
  }

  //_____________________________________________________________________________________________________________________________________
  // Plots the current waveform along with its best fitting templates.
  // PreCondition: Need to call TWaveform::AnalyzeWave() first.
  void TWaveform::DrawBestFit(const char *tempFile)
  {
    TWaveform wave;
    wave = this->AddBestTemps(tempFile);
    this->Draw();
    TH1F *hist = ((TH1F *)(gROOT->FindObject("BestFit")));
    delete hist;
    hist = new TH1F("BestFit","Best Fit",wave.nSamples,wave.t[0],wave.t[wave.nSamples-1]);
    for (int i=0; i<wave.nSamples; i++)
    {
      hist->Fill(wave.t[i],wave.vA[i]);
    }
    hist->SetMarkerStyle(3);
    hist->SetLineColor(kRed); 
    hist->Draw("C hist SAME");
    return;
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                               /////////////////////////////////////////
                                               ///////// FIND MEMBER FUNCTIONS /////////
                                               /////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  //_____________________________________________________________________________________________________________________________________
  // Returns the average of the waveform from its position in the x-axis (pos) up to nPoints after that. If "Integral" is used instead of
  // "Waveform", the average will be calculated for the integral of the waveform
  float TWaveform::FindAvg(int pos, std::string data, int nPoints)
  {
    float avg=0.0;
    int n(0);
    if (data=="Waveform")
    {
      for (int i=0; i<nPoints; i++)
      {
        if ((pos+i) >= 0 && (pos+i) < this->nSamples)
        {
          avg += vA[pos+i];
          n++;
        }
      }
      avg = avg/nPoints;
    }
    if (data=="Integral")
    {
      for (int i=0; i<nPoints; i++)
      {
        if ((pos+i) >= 0 && (pos+i) < this->nSamples)
        {
          avg += vIAreaA[pos+i];
          n++;
        }
      }
      avg = avg/n;
    }
    return avg;
  }

  //_____________________________________________________________________________________________________________________________________
  // Finds the area under the waveform between each data point and assigns it to the data type: vArea.
  void TWaveform::FindArea()                                  
  {
    double trArea=0;
    double recArea=0;
    for (int i = 0; i<nSamples-1; i++)
    {
      trArea = ((vA[i+1] - vA[i]) * tBinSize)/2;
      recArea = vA[i] * tBinSize;
      vAreaA[i] = recArea + trArea;
    }
    vAreaA[nSamples-1]=0;
    return;
  }

  //_____________________________________________________________________________________________________________________________________
  // Calculates the integral of the waveform and and assigns it to the data type: vIArea.
  void TWaveform::FindIntegral()
  {
    double area=0;
    this->FindArea();
    for (int i = 0; i < nSamples; ++i)
    {
      vIAreaA[i]=area;
      area+=vAreaA[i];
    }
    return;
  }

  //_____________________________________________________________________________________________________________________________________
  //            ************ CHANGE posA & posB TO BE MORE GENERAL  ******************
  // Assigns to vOffsetA the value of the offset.
  void TWaveform::FindOffset(/*std::string data*/)
  {
    // int iterations=8;
    int posA;                                                                             // To get the avg signal before the waveform is affected by the small dip in signal right before a pulse
    // if (data=="Integral")                                                                       // When getting the rise of the integral uses 7 iterations instead
      // iterations=7;                                                                           
    if (risePosA[0]==0)               
      this->Find1stPulse();
    posA=risePosA[0]-250;               
    vOffsetA = this->FindAvg(0, "Waveform", posA);
    return;
  }

  //_____________________________________________________________________________________________________________________________________
  // Finds the waveform's slope at position pos
  float TWaveform::FindSlope(int pos, std::string data, int nPoints)
  {
    float point1, point2, slope;
    point1 = this->FindAvg(pos - nPoints, data, nPoints);
    point2 = this->FindAvg(pos, data, nPoints);
    slope = point2 - point1;
    return slope;
  }

  //_____________________________________________________________________________________________________________________________________
  // Finds the first peak after the start position given.
  int TWaveform::FindPeak(int start, int nPoints)
  {
    float slope = 0.0;
    for (int i=start; i<nSamples; i++)
    {
      slope = this->FindSlope(i, "Waveform", nPoints);
      if (slope < 0)
      {
        return i;
      }
    }
    return 0;
  }

  //_____________________________________________________________________________________________________________________________________
  // Prerequisite: Call ApplyOffset() first.
  // Finds the peaks of the waveform.
  void TWaveform::FindPeaks()                              
  {
    int start;
    start = risePosA[0];
    int i=0;
    while (start!=0)
    {
      peaksA[i] = this->FindPeak(start);
      if(peaksA[i] == 0)
      {
        break;
      }
      risePosA[i+1] = this->Get1stRisePosition(peaksA[i]);
      start = risePosA[i+1];
      if (start != 0)
      {
        start++;
      }
      i++;    
    }
    return;
  }

  //_____________________________________________________________________________________________________________________________________
  // Finds the waveform's 1st pulse
  void TWaveform::Find1stPulse(int step, float sigma, int nPoints)
  {
    float slopeStart(0.0), slope2(0.0), diff(0.0);
    int pos(0);
    slopeStart = this->FindSlope(20, "Integral" , nPoints);
    for (int i = nPoints; i < nSamples; i+=step)
    {
      slope2 = this->FindSlope(i, "Integral" , nPoints);
      diff = slope2 - slopeStart;
      if (diff > sigma)
      {
        pos = i;
        for (int n = pos-step; i<pos+1; n++)
        {
          slope2 = this->FindSlope(n, "Integral" , nPoints);
          diff = slope2 - slopeStart;
          if (diff > sigma)
          {
            pos = n;
            risePosA[0] = pos;
            return;
          }
        }
      }
    }
    return;
  }

  //_____________________________________________________________________________________________________________________________________
  // Calculates the standard deviation of Waveform      
  // Prerequisite: Need to call ApplyOffset first
  //                                ************ FIX nPoints W/ 250 BELOW *************
  void TWaveform::FindStdev()
  {
    if (vOffsetA == 0)
    {
      this->ApplyOffset(/*"Integral"*/);
    }
    float sum(0.0);
    int nPoints = risePosA[0]-250;
    for (int i = 0; i < nPoints; ++i)
    {
      sum += vA[i]*vA[i];
    }
    stDevA = sqrt(sum/nPoints);
    return;
  }

  //_____________________________________________________________________________________________________________________________________
  // Prerequisite: Call PreDataProcessing() first for every waveform
  // Finds the scale, tOffset and chi^2 for the best fit between the template temp and the waveform being analyzed
  // Change the TWaveformConstants::scaleResoltion and TWaveformConstants::timeResolution values to modify the resolution at which 
  // the parameters are calculated. 
  //    ************ TURN RESOLUTIONS INTO VARIABLES ***********
  //    ************ LOOK AT INTOFF FOR WAVEFORMS NOT CENTERED AT 0 *************
  fitParam TWaveform::FindFitPar(TWaveform &temp, int tLim, double scaleLim) 
  {
    const double SCALE_RESOLUTION(TWaveformConstants::scaleResolution);        
    const int TIME_RESOLUTION(TWaveformConstants::timeResolution);
    const double MIN_SCALE(TWaveformConstants::minimumScale);
    const int T_STEP_DIVIDER(TWaveformConstants::timeStepDivider);            // Refers to the time step division for the chi^2 hisograms (T_STEP_DIVIDER + 1 = number of x-bins in hist)
    const double SCALE_STEP_DIVIDER(TWaveformConstants::scaleStepDivider);    // Refers to the scale step division for each chi^2 histogram made (also the number of y-bins in hist)
    double inScale = MIN_SCALE;                                               // MinScale refers to the minimum scale value that is used for the template fitting
    fitParam par;
    int inTOff = 0;                                                           //inTOff is the initial t offset.
    int x,y,z;
    TH2F* chiSq;
    int tStep = tLim / T_STEP_DIVIDER;
    double scaleStep = scaleLim / (double)SCALE_STEP_DIVIDER;
    do
    {
      if(tStep == 0)
      {
        tStep = 1;
        tLim = 2;
      }
      chiSq = TWaveform::Chi2Hist(temp, inTOff, inScale, tLim, scaleLim, tStep, scaleStep);
      chiSq->GetBinXYZ(chiSq->GetMinimumBin(), x, y, z);
      par.bestOffset = ((x) * tStep) + inTOff - tLim;
      par.bestScale = (y - 1) * scaleStep + inScale;
      inTOff = par.bestOffset;
      if(par.bestScale == MIN_SCALE)
      {
        inScale = par.bestScale;
        scaleLim = inScale + scaleStep;
      }
      else
      {
        inScale = par.bestScale - scaleStep;
        scaleLim = scaleStep * 2;
      }
      tLim = tStep;
      tStep = tLim / 2;
      scaleStep = scaleLim / (double)4;
      par.chiSquared = chiSq->GetBinContent(chiSq->GetMinimumBin());
      delete chiSq;
    }while((scaleStep * 2 >= SCALE_RESOLUTION) && (tStep * 2 >= TIME_RESOLUTION));
    return par;
  }

  //_____________________________________________________________________________________________________________________________________
  // Prerequisite: Call PreDataProcessing() first for every waveform
  // Finds the scale, tOffset, and chi^2 for the best fit of template temp being added to multWave and then fitted to the current waveform.
  // Change the TWaveformConstants::scaleResoltion and TWaveformConstants::timeResolution values to modify the resolution at which 
  // the parameters are calculated. 
  fitParam TWaveform::FindFitParMultiple(TWaveform &temp, TWaveform multWave, int tLim, double scaleLim)                    
  {
    const double SCALE_RESOLUTION(TWaveformConstants::scaleResolution);        
    const int TIME_RESOLUTION(TWaveformConstants::timeResolution);
    const double MIN_SCALE(TWaveformConstants::minimumScale);
    const int T_STEP_DIVIDER(TWaveformConstants::timeStepDivider);              // Refers to the time step division for the chi^2 hisograms (T_STEP_DIVIDER + 1 = number of x-bins in hist)
    const double SCALE_STEP_DIVIDER(TWaveformConstants::scaleStepDivider);      // Refers to the scale step division for each chi^2 histogram made (also the number of y-bins in hist)
    double inScale = MIN_SCALE;                                                 // inScale refers to the minimum scale value that is used for the template fitting
    fitParam par;
    int x,y,z;
    TH2F *chiSq;
    int tStep = tLim / T_STEP_DIVIDER;
    double scaleStep = scaleLim / (double)SCALE_STEP_DIVIDER;
    int inTOff = 0;
    do
    {
      if(tStep == 0)
      {
        tStep = 1;
        tLim = 2;
      }
      chiSq = TWaveform::Chi2HistMultiple(temp, multWave, inTOff, inScale, tLim, scaleLim, tStep, scaleStep);
      chiSq->GetBinXYZ(chiSq->GetMinimumBin(), x, y, z);
      par.bestOffset = ((x) * tStep) + inTOff - tLim;
      par.bestScale = (y - 1) * scaleStep + inScale;
      par.chiSquared = chiSq->GetBinContent(chiSq->GetMinimumBin());
      inTOff = par.bestOffset;
      if(par.bestScale == MIN_SCALE)
      {
        inScale = par.bestScale;
        scaleLim = scaleStep;
      }
      else
      {
        inScale = par.bestScale - scaleStep;
        scaleLim = scaleStep * 2;
      }
      tLim = tStep;
      tStep = tLim / T_STEP_DIVIDER;
      scaleStep = scaleLim / (double)SCALE_STEP_DIVIDER;
      delete chiSq;
    }while((scaleStep * 2 >= SCALE_RESOLUTION) && (tStep * 2 >= TIME_RESOLUTION));
    return par;
  }

  //_____________________________________________________________________________________________________________________________________
  // Finds the position of the peaks in the waveform after it has been fitted by a template.
  // Does so by looking at the position of the bestTemps and their peaks.
  // Prerequisite: Use SetBestTemplateParameters() first
  void TWaveform::FindPeaksTemp(const char *tempFile)
  {
    memset(this->peaksA, 0 , sizeof(this->peaksA));
    std::vector<TWaveform> tempWaves(this->nPeaksA);
    for (int i = 0; i < this->nPeaksA; ++i)
    {
      tempWaves[i].ReadTemp(this->bestTemp[i].c_str(), tempFile);
      if (tempWaves[i].peaksA[0] == 0)
      {
        tempWaves[i].PreDataProcessing();
      }
      this->peaksA[i] = tempWaves[i].peaksA[0] + this->bestTempOffset[i];       
    }
    return;
  }

  //_____________________________________________________________________________________________________________________________________
  // Finds the position of the pulses' rise in the waveform after it has been fitted by a template.
  // Does so by looking at the position of the bestTemps and their rise positions.
  // Prerequisite: Use SetBestTemplateParameters() first
  void TWaveform::FindRiseTemp(const char *tempFile)
  {
    memset(this->risePosA, 0 , sizeof(this->risePosA));
    std::vector<TWaveform> tempWaves(this->nPeaksA);
    for (int i = 0; i < this->nPeaksA; ++i)
    {
      tempWaves[i].ReadTemp(this->bestTemp[i].c_str(), tempFile);
      if (tempWaves[i].peaksA[0] == 0)
      {
        tempWaves[i].PreDataProcessing();
      }
      this->risePosA[i] = tempWaves[i].risePosA[0] + this->bestTempOffset[i];
    }
    return;
  }

  //_____________________________________________________________________________________________________________________________________
  // Prerequisite: Call PreDataProcessing()
  // Returns a chiParam struct with the best fitting parameters (best template, best offset, best scale and best chi^2(normalized) 
  // of the waveform's main pulse.
  chiParam TWaveform::FindFirstBestTemplateParameters(const char *tempFile, const char *tempName, int tempNum, int tLim, double scaleLim)
  {
    std::vector<fitParam> par(tempNum);
    std::vector<TWaveform> temp = TWaveformSpace::GetTempWaves(tempNum, tempFile, tempName);
    std::vector<double> chiSquaredVector(tempNum);
    chiParam bestFitPar;
    double lowChi;
    int lowTemp(0);
    for (int i = 0; i < tempNum; ++i)
    {
      par[i] = this->FindFitPar(temp[i], tLim, scaleLim);
      chiSquaredVector[i] = par[i].chiSquared;
    }
    auto smallest = std::min_element(std::begin(chiSquaredVector), std::end(chiSquaredVector));
    int smallestPosition = std::distance(std::begin(chiSquaredVector), smallest);
    bestFitPar.bestTemp.push_back(TWaveformSpace::TempName(smallestPosition, tempName));
    bestFitPar.bestOffset.push_back(par[smallestPosition].bestOffset);
    bestFitPar.bestScale.push_back(par[smallestPosition].bestScale);
    bestFitPar.chiNor = this->GetChi2Norm(chiSquaredVector[smallestPosition]);
    return bestFitPar;
  }

  //_____________________________________________________________________________________________________________________________________
  // Prerequisite: Call PreDataProcessing()
  // Returns a chiParam struct with the best fitting parameters (best template, best offset, best scale and best chi^2(normalized)) 
  // of the template to be added to multipleWave to get the best fit with the current waveform.
  chiParam TWaveform::FindMultipleBestTemplateParameters(TWaveform multipleWave, const char *tempFile, const char *tempName, int tempNum, int tLim, double scaleLim)
  {
    std::vector<fitParam> par(tempNum);
    std::vector<TWaveform> temp(tempNum);
    std::vector<double> chiSq(tempNum);
    chiParam bestFitPar;
    double lowChi;
    int lowTemp(0);
    for (int i = 0; i < tempNum; ++i)
    {
      temp[i].ReadTemp(TWaveformSpace::TempName(i, tempName).c_str(), tempFile);
      temp[i].PreDataProcessing();
      par[i] = this->FindFitParMultiple(temp[i], multipleWave, tLim, scaleLim);
      chiSq[i] = par[i].chiSquared;
      if (i == 0)
      {
        lowChi = chiSq[0];
      }
      else if (chiSq[i] < lowChi)
      {
        lowChi = chiSq[i];
        lowTemp = i;
      }
    }
    bestFitPar.bestTemp.push_back(TWaveformSpace::TempName(lowTemp, tempName));
    bestFitPar.bestOffset.push_back(par[lowTemp].bestOffset);
    bestFitPar.bestScale.push_back(par[lowTemp].bestScale);
    bestFitPar.chiNor = this->GetChi2Norm(lowChi);
    return bestFitPar;
  }

  //_____________________________________________________________________________________________________________________________________
  // Prerequisite: Call PreDataProcessing()
  // Returns a chiParam struct that contains vectors of the best templates, best template offsets, best template scales,
  // and best normalized chi^2 that when added give the best fit for the current waveform. 
  // The templates with name tempName are found in root file tempFile.
  // maxPulses is the maximum number of pulses that will searched for in the waveform.
  chiParam TWaveform::FindBestTemplatesFit(const char *tempFile, const char *tempName, int tempNum, int maxPulses, int tLim, double scaleLim)
  {
    chiParam bestFitPar, temporaryPar;
    std::vector<double> chiSquaredVector;
    TWaveform multipleWave, templateWave;
    bestFitPar = this->FindFirstBestTemplateParameters(tempFile, tempName, tempNum, tLim, scaleLim);
    chiSquaredVector.push_back(bestFitPar.chiNor);
    multipleWave.ReadTemp(bestFitPar.bestTemp[0].c_str(), tempFile);
    multipleWave.Shift(bestFitPar.bestOffset[0], bestFitPar.bestScale[0]);
    for(int i = 1; i < maxPulses; i++)
    {
      temporaryPar = this->FindMultipleBestTemplateParameters(multipleWave, tempFile, tempName, tempNum, tLim, scaleLim);
      bestFitPar.bestTemp.push_back(temporaryPar.bestTemp[0]);
      bestFitPar.bestScale.push_back(temporaryPar.bestScale[0]);
      bestFitPar.bestOffset.push_back(temporaryPar.bestOffset[0]);
      chiSquaredVector.push_back(temporaryPar.chiNor);
      templateWave.Clear();
      templateWave.ReadTemp(temporaryPar.bestTemp[0].c_str(), tempFile);
      multipleWave = multipleWave.Add(templateWave, temporaryPar.bestScale[0], temporaryPar.bestOffset[0]);
    }
    auto smallest = std::min_element(std::begin(chiSquaredVector), std::end(chiSquaredVector));
    int smallestPosition = std::distance(std::begin(chiSquaredVector), smallest);
    bestFitPar.bestTemp.resize(smallestPosition + 1);
    bestFitPar.bestScale.resize(smallestPosition + 1);
    bestFitPar.bestOffset.resize(smallestPosition + 1);
    bestFitPar.chiNor = chiSquaredVector[smallestPosition];
    return bestFitPar;
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                               /////////////////////////////////////////
                                               ////////// GET MEMBER FUNCTIONS /////////
                                               /////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  //_____________________________________________________________________________________________________________________________________
  // Needs to call PreDataProcessing() first for every waveform
  // Calculates the lowest chi^2 of the waveform with the template selected
  double TWaveform::GetLowestChi2(TWaveform &temp, int tLim, double scaleLim)
  {
    fitParam par = this->FindFitPar(temp, tLim, scaleLim);
    double chiSq(0.0);
    chiSq = this->GetChiSquare(temp, par.bestOffset, par.bestScale);
    return chiSq;
  }

  // Returns the normalized chi^2 (chiSq) with degrees of freedom of nSamples - constraints 
  // If chiNorm = 1 it is a perfect fit, if chiNorm << 1 usually means the error is being over-estimated, and if chiNorm >> 1 it is a bad fit
  double TWaveform::GetChi2Norm(double chiSq, double constraints)
  {
    double chiNorm = chiSq/(this->nSamples - constraints);
    return chiNorm;
  }

  //_____________________________________________________________________________________________________________________________________
  // Returns the normalized chi square of the current waveform with the templates passed by tempChi.
  double TWaveform::GetChiMultiple(const char *tempFile, chiParam tempChi)
  {
    TWaveform add, tempWave;
    double chiSq;
    tempWave.ReadTemp(tempChi.bestTemp[0].c_str(), tempFile);
    tempWave.CopySetup(add);
    for (int i = 0; i < tempChi.bestTemp.size(); ++i)
    {
      tempWave.Clear();
      tempWave.ReadTemp(tempChi.bestTemp[i].c_str(), tempFile);
      add = add.Add(tempWave, tempChi.bestScale[i], tempChi.bestOffset[i]);
    }
    chiSq = this->GetChiSquare(add);
    chiSq = add.GetChi2Norm(chiSq);
    return chiSq;
  }

  //_____________________________________________________________________________________________________________________________________
  // Returns chi^2 for the sum of multWave and the shifted temp with the current waveform.
  double TWaveform::GetChiMultiple(TWaveform temp, TWaveform multWave, double tempScale, int tempOffset)
  {
    TWaveform temporaryWave = multWave.Add(temp, tempScale, tempOffset);
    return this->GetChiSquare(temporaryWave);
  }

  //_____________________________________________________________________________________________________________________________________
  // Returns a vector with the offset shifts from the bestTempOffset for the best template fit to have a chi square 
  // with the current waveform of one integer more than the bestTempChi. This is a measure of the unceratinty in time measurements.
  // If the time uncertainty couldn't be found within the waveform's range, the timeUnc element at that position will be set to 0.
  std::vector<int> TWaveform::GetTimeUncertainty(int tStep, const char *tempFile)
  {
    std::vector<double> chiSq(this->nPeaksA);
    std::vector<int> timeUnc(this->nPeaksA);
    std::vector<TWaveform> bestTemplates = this->GetBestTemplates(tempFile);
    int tShift;
    TWaveform waveShifted;
    for (int i = 0; i < this->nPeaksA; ++i)
    {
      tShift = 0;
      do
      {
        tShift += tStep;
        waveShifted = this->GetBestFitWaveShifted(i, tShift, 1, tempFile);
        chiSq.at(i) = this->GetChi2Norm(this->GetChiSquare(waveShifted));
      } while((chiSq.at(i) - this->bestTempChi) < 1 && tShift < this->nSamples);
      if(tShift >= this->nSamples)
      {
        timeUnc.at(i) = 0;
      }
      else
      {
        timeUnc.at(i) = tShift;
      }
    }
    return timeUnc;
  }

  //_____________________________________________________________________________________________________________________________________
  // Returns a vector with the scale shifts from the bestTempScale for the best template fit to have a chi square 
  // with the current waveform of one integer more than the bestTempChi. This is a measure of the unceratinty in pulse height measurements.
  std::vector<double> TWaveform::GetPulseHeightUncertainty(double scaleStep, const char *tempFile)
  {
    std::vector<double> chiSq(this->nPeaksA);
    std::vector<double> pulseUnc(this->nPeaksA);
    chiParam tempChi;
    for (int i = 0; i < this->nPeaksA; ++i)
    {
        tempChi.bestTemp.push_back(this->bestTemp[i]);
        tempChi.bestOffset.push_back(this->bestTempOffset[i]);
        tempChi.bestScale.push_back(this->bestTempScale[i]);
    }
    tempChi.chiNor = this->bestTempChi;
    double n;
    for (int i = 0; i < this->nPeaksA; ++i)
    {
      n = 0;
      do
      {
        n += scaleStep;
        tempChi.bestScale[i] = this->bestTempScale[i] + n;
        chiSq.at(i) = this->GetChiMultiple(tempFile, tempChi);
      }while((chiSq.at(i) - tempChi.chiNor) < 1);
      pulseUnc.at(i) = n;
    }
    return pulseUnc;
  }

  //_____________________________________________________________________________________________________________________________________
  // Returns pointer to char array containing the name of the best fit template
  char* TWaveform::GetBestTempName(int pulseNum)
  {
    char tempName[100];
    strncpy(tempName, bestTemp[pulseNum].c_str(), sizeof(tempName));
    tempName[sizeof(tempName) - 1] = '\0';
    char* tempNamePointer = tempName;
    return tempNamePointer;
  }

  //_____________________________________________________________________________________________________________________________________
  // Prerequisite: Call AnalyzeWave() first.
  // Returns a vector with all the waveform's best templates, shifted and scaled according to their best fit.
  std::vector<TWaveform> TWaveform::GetBestTemplates(const char *tempFile)
  {
    std::vector<TWaveform> bestTemplates(this->nPeaksA);
    char *tempName = 0;
    for (int i = 0; i < this->nPeaksA; ++i)
    {
      tempName = this->GetBestTempName(i);
      bestTemplates.at(i).ReadTemp(tempName, tempFile);
      bestTemplates.at(i).Shift(this->bestTempOffset[i], this->bestTempScale[i]);
    }
    return bestTemplates;
  }

  //_____________________________________________________________________________________________________________________________________
  // Prerequisite: Call AnalyzeWave() first.
  // Returns a TWaveform with the sum of the current waveform's best templates, shifted and scaled according to their best fit.
  TWaveform TWaveform::GetBestFitWave(const char *tempFile)
  {
    std::vector<TWaveform> bestTemplates = this->GetBestTemplates(tempFile);
    TWaveform bestFit = TWaveformSpace::AddWaveforms(bestTemplates);
    return bestFit;
  }


  //_____________________________________________________________________________________________________________________________________
  // Prerequisite: Call AnalyzeWave() first.
  // Returns a TWaveform with the sum of the current waveform's best templates, shifted and scaled according to their best fit.
  // In this version, the waveform's pulse number (pulseToBeShifted) is shifted by the given values while the other pulses remain
  // with their best fit position.
  TWaveform TWaveform::GetBestFitWaveShifted(int pulseToBeShifted, int tOffset, double scale, const char *tempFile)
  {
    std::vector<TWaveform> bestTemplates = this->GetBestTemplates(tempFile);
    bestTemplates.at(pulseToBeShifted).Shift(tOffset, scale);
    TWaveform waveShifted = TWaveformSpace::AddWaveforms(bestTemplates);
    return waveShifted;
  }

  //_____________________________________________________________________________________________________________________________________
  // Function that returns the string of the filename of waveform number waveNum in directory number dirNum
  // If dirNum = -1, no directory number will be added to the file address name
  // CSV Version filenames of form: [this->directoryAddress][dirNum][this->genericFileName][waveNum][this->fileType]
  std::string TWaveform::GetCSVFilename(int waveNum, int dirNum)
  {
    std::ostringstream sDir, sWave;
    sDir << dirNum;
    sWave << waveNum;
    std::string direc, fileName, dirNumStr(sDir.str()), waveNumStr(sWave.str());
    direc = this->directoryAddress;     /* Change if looking at waveforms in a different directory and/or with a different name */
    if(dirNum == -1)
    {
      dirNumStr = "";
    }
    fileName = direc + dirNumStr + this->genericFileName + waveNumStr + this->fileType;                                   /* Change if CSV files are saved under a different name */
    return fileName;
  }

  //_____________________________________________________________________________________________________________________________________
  // Function that returns the string of the filename of waveform number waveNum in directory number dirNum
  // If dirNum = -1, no directory number will be added to the file address name
  // TXT Version filenames of form: [this->directoryAddress][dirNum][this->genericFileName]00023[this->fileType] --- Where waveNum = 23.
  std::string TWaveform::GetTXTFilename(int waveNum, int dirNum)
  {
    std::ostringstream sDir, sWave;
    sDir << dirNum;
    sWave << waveNum;
    std::string direc, fileName, dirNumStr(sDir.str()), waveNumStr(sWave.str()), zeros;
    direc = this->directoryAddress;    
    for (int i = 0; i < 5 - waveNumStr.length(); ++i)
     {
       zeros += "0";
     } 
    if(dirNum == -1)
    {
      dirNumStr = "";
    }
    fileName = direc + dirNumStr + this->genericFileName + zeros + waveNumStr + this->fileType;
    return fileName;
  }

  //_____________________________________________________________________________________________________________________________________
  // Function that returns the string of the filename of waveform number waveNum in directory number dirNum
  // The method used to get the filename is determined by the current waveform's genericFileName.
  // If dirNum = -1, no directory number will be added to the file address name 
  std::string TWaveform::GetFilename(int waveNum, int dirNum)
  {
    std::string filename;
    if(this->genericFileName == "/DS")
    {
      filename = this->GetCSVFilename(waveNum, dirNum);
    }
    else if(this->genericFileName == "/data/C2wave" || this->genericFileName == "/data/C1wave")
    {
      filename = this->GetTXTFilename(waveNum, dirNum);
    }
    else
    {
      // std::cout << "Filename could not be generated: genericFileName not defined for this TWaveform object." << std::endl;
      filename = this->GetCSVFilename(waveNum, dirNum);
    }
    return filename;
  }

  //_____________________________________________________________________________________________________________________________________
  // Returns the voltage value of the peak of the pulse (best template) number pulseNum when best fitted
  // pulseNum = 0 is for the first pulse and so on
  double TWaveform::GetPulseHeight(int pulseNum, const char *tempFile)
  {
    TWaveform temp;
    double strength;
    temp.ReadTemp(this->bestTemp[pulseNum].c_str(), tempFile);
    if (temp.peaksA[0] == 0)
    {
      temp.PreDataProcessing();
    }
    strength = this->bestTempScale[pulseNum] * temp.vA[temp.peaksA[0]];
    return strength;
  }

  //_____________________________________________________________________________________________________________________________________
  // Returns the position of the first rise in the waveform after the start position. If data = "Integral", the rise position will be 
  // determined by the rise of the integral of the waveform. The input given by step represents the interval between points checked for 
  // rise. The function returns 0 if there is no rise in this section of the waveform.
  // Uses IsIncreasing to determine the rise position. 
  int TWaveform::Get1stRisePosition(int start, int iterations, std::string data, int step) 
  {
    int pos = 0;
    int end;
    for (int i=start; i<nSamples; i+=step)
    {
      end = i + iterations * 2;
      if(this->IsIncreasing(i, end, data))
      {
        pos = i;
        for (int n = pos-step; i<pos+1; n++)
        {
          end = n + iterations * 2;
          if (this->IsIncreasing(n, end, data) && n >= start)
          {
            pos = n;
            return pos;
          }
        }
      }
    }
    return pos;
  }

  //_____________________________________________________________________________________________________________________________________
  // Calculates and returns the chi^2 of the waveform temp with the current waveform
  // Works only if Waveforms are centered at V=0 (Offset has been applied)
  double TWaveform::GetChiSquare(TWaveform &temp, int tOffset, double scale)
  {
    double chiSq(0.0), sum(0.0);
    TWaveform tempShifted = temp;
    tempShifted.Shift(tOffset, scale);
    if (this->stDevA == 0)
    {
      this->FindStdev();
    }
    for (int i = 0; i < this->nSamples; ++i)
    {
      sum += (this->vA[i] - tempShifted.vA[i]) * (this->vA[i] - tempShifted.vA[i]);
    }
    chiSq = sum / (stDevA * stDevA);
    return chiSq;
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                               /////////////////////////////////////////
                                               ////////// SET MEMBER FUNCTIONS /////////
                                               /////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //_____________________________________________________________________________________________________________________________________
  // Prerequisite: Call PreDataProcessing() before using.
  // Saves the best template parameters (bestTemp, bestTempOffset, bestTempsScale, bestTempChi, and nPeaksA) into the current TWaveform.
  bool TWaveform::SetBestTemplateParameters(const char *tempFile, const char *tempName, int tempNum, int maxPulses, int tLim, double scaleLim)
  {
    chiParam bestFitPar = this->FindBestTemplatesFit(tempFile, tempName, tempNum, maxPulses, tLim, scaleLim);
    if(bestFitPar.bestTemp.size() > 0)
    {
      this->bestTemp = bestFitPar.bestTemp;
      this->bestTempOffset = bestFitPar.bestOffset;
      this->bestTempScale = bestFitPar.bestScale;
      this->nPeaksA = this->bestTemp.size();
      this->bestTempChi = bestFitPar.chiNor;
      return true;
    }
    else
    {
      return false;
    }
  }

  //_____________________________________________________________________________________________________________________________________
  // Prerequisite: Call FindIntegral() first. 
  // Changes the sign of all the Waveform's voltage values if the integral of the wave is negative
  bool TWaveform::SetSignalPositive()
  {
    if(this->vIAreaA[this->nSamples-1] == 0)
    {
      this->FindIntegral();
    }
    if(this->vIAreaA[this->nSamples-1] < 0)
    {
      this->ChangeSignalSign();
      return true;
    }
    return false;
  }

  //_____________________________________________________________________________________________________________________________________
  // Sets the TWaveform's directoryAddress, genericFileName, and fileType to the passed values.
  void TWaveform::SetFileName(std::string dirAddress, std::string fName, std::string fType)
  {
    this->directoryAddress = dirAddress;
    this->genericFileName = fName;
    this->fileType = fType;
    return;
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                               /////////////////////////////////////////
                                               ///////// OTHER MEMBER FUNCTIONS ////////
                                               /////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  //_____________________________________________________________________________________________________________________________________
  //                      ********* FIX FUNCTION - WHEN POS<2 THERE WILL BE A SEG. FAULT ******************
  // Function that returns true if the avg of a waveform is increasing from position start, up to position end.
  bool TWaveform::IsIncreasing(int start, int end, std::string data, int nPoints)
  {
    bool increase = false;
    int iterations = (end - start)/2;
    float * avg = new float[iterations];
    for (int i = 0; i < iterations; i++)
      avg[i] = this->FindAvg(start - nPoints/2 + 2 * i, data, nPoints);
    for (int i = 0; i < iterations-1; ++i)
    {
      if (avg[i]>=avg[i+1])
      {
        return increase;
      }
    }
    increase = true;
    delete[] avg;
    return increase;
  }

  //_____________________________________________________________________________________________________________________________________
  // Calls FindOffset and if the offset hasn't been applied, it applies it
  void TWaveform::ApplyOffset(/*std::string data*/)
  {
    // if (data=="Integral")
    // {
      this->FindIntegral();
    // }
    this->FindOffset();
    for (int i = 0; i < nSamples; ++i)
    {
      vA[i] -= vOffsetA;
    }
    // if (data=="Integral")
      this->FindIntegral();
    return;
  }
  
  //_____________________________________________________________________________________________________________________________________
  // Marks the points of the waveform's peaks and risepos values on the current canvas
  // Calls AnalyzeWave() when nPeaksA = 0.
  void TWaveform::MarkRise()
  {
    TGraph *rise = ((TGraph *)(gROOT->FindObject("Rise")));
    delete rise;
    rise = new TGraph();
    if (nPeaksA == 0)
      this->AnalyzeWave();
    for (int i = 0; i < nPeaksA; ++i)
    {
      rise->SetPoint(i+nPeaksA,t[peaksA[i]],vA[peaksA[i]]);
      rise->SetPoint(i,t[risePosA[i]],vA[risePosA[i]]);
    }
    rise->SetMarkerColor(kRed); 
    rise->Draw("*SAME");
    return;
  }

  //_____________________________________________________________________________________________________________________________________
  // Processess the waveform through the set of methods seen below.
  void TWaveform::PreDataProcessing()
  {
    this->ApplyOffset();
    if (this->SetSignalPositive())
      this->ApplyOffset();
    this->FindPeaks();
    this->NoiseFilter();
    return;
  }

  //_____________________________________________________________________________________________________________________________________
  // Prerequisite: Call PreDataProcessing() first for both waveforms
  // Creates a 2D histogram of the Chi^2 of the current waveform with temp with varying scales and tOffsets 
  // (x-axis = tOffset, y-axis = scale, z-axis/weight = Chi^2)
  // tStep refers to the time index difference between each temp offset probed. 
  // tLim and scaleLim are not inclusive.
  TH2F* TWaveform::Chi2Hist(TWaveform &temp, int inTOff, double inScale, int tLim, double scaleLim, int tStep, double scaleStep) 
  {
    int tOffset;
    double chiSq, scale;
    const double floatPrec = 1e-10;                                                               //**Temporary**// to deal with floating point precision 

    int tBins, scaleBins;
    tBins = 2 * tLim / tStep - 1;
    scaleBins = scaleLim / scaleStep;

    TH2F *hist2D  = new TH2F(Form("ChiSquared%f",scaleStep),"Chi Square", tBins, inTOff - tLim, inTOff + tLim, scaleBins, inScale, inScale + scaleLim);
    for (int i = -tLim + tStep; i < tLim; i+=tStep)
    {
      tOffset = inTOff + i;
      scale = inScale;
      for (int n = 0; n < scaleBins; n++)
      {
        chiSq = this->GetChiSquare(temp, tOffset, scale);
        hist2D->Fill(tOffset, scale + floatPrec, chiSq);
        scale+=scaleStep;
      }
    }
    return hist2D;
  }

  //_____________________________________________________________________________________________________________________________________
  // Prerequisite: Call PreDataProcessing() first for both waveforms
  // Creates a 2D histogram of the Chi^2 of the current waveform with the sum of multWave and temp with varying scales and tOffsets 
  // (x-axis = tOffset, y-axis = scale, z-axis/weight = Chi^2)
  // tStep refers to the t index difference between each temp offset probed. 
  // tLim and scaleLim are not inclusive.
  TH2F* TWaveform::Chi2HistMultiple(TWaveform &temp, TWaveform multWave, int inTOff, double inScale, int tLim, double scaleLim, int tStep, double scaleStep)                    // pulseNum is the number of the pulse being fitted, step is the step between parameter being tried to fit, tLim and scaleLim are the limits of the histogram, binNum is the number of bins being used
  {
    int tOffset;
    double chiSq, scale;
    const double floatPrec = 1e-10;                                                               //**Temporary**// to deal with floating point precision 
    TWaveform waveSum;

    int tBins, scaleBins;
    tBins = 2 * tLim / tStep - 1;
    scaleBins = scaleLim / scaleStep;

    TH2F *hist2D  = new TH2F(Form("ChiSquared-%f",scaleStep*tStep),"Chi Square", tBins, inTOff - tLim, inTOff + tLim, scaleBins, inScale, inScale + scaleLim);
    for (int i = -tLim + tStep; i < tLim; i+=tStep)
    {
      tOffset = inTOff + i;
      scale = inScale;
      for (int n = 0; n < scaleBins; n++)
      {
        waveSum = multWave.Add(temp, scale, tOffset);
        chiSq = this->GetChiSquare(waveSum);
        hist2D->Fill(tOffset, scale + floatPrec, chiSq);
        scale+=scaleStep;
      }
    }
    return hist2D;
  }

  //_____________________________________________________________________________________________________________________________________
  // Prerequisite: Call ApplyOffset() first.
  // Determines whether the wavefomr is composed of pure noise, and if so, sets the current waveforms noiseA data member to true.
  // If the waveform is not noise, then noiseA is set to false.
  // This version filters the noise by using the waveform's area
  void TWaveform::NoiseFilterAvg(double maxAvgForNoise)
  {
    float avg = this->FindAvg(0, "Waveform", this->nSamples);
    if (std::abs(avg) < maxAvgForNoise)
    {
      noiseA = true;
    }
    return;
  }

  //_____________________________________________________________________________________________________________________________________
  // Determines whether the wavefomr is composed of pure noise, and if so, sets the current waveforms noiseA data member to true.
  // If the waveform is not noise, then noiseA is set to false.
  // This version filters the noise by using the waveform's area
  void TWaveform::NoiseFilterArea(double maxAreaForNoise)
  {
    if(std::abs(this->vIAreaA[this->nSamples-1]) < maxAreaForNoise)
    {
      this->noiseA = true;
    }
    else
    {
      this->noiseA = false;
    }
    return;
  }

  //_____________________________________________________________________________________________________________________________________
  // Determines whether the wavefomr is composed of pure noise, and if so, sets the current waveforms noiseA data member to true.
  // If the waveform is not noise, then noiseA is set to false.
  void TWaveform::NoiseFilter()
  {
    if(TWaveformConstants::noiseFilterMethod == "Avg")
    {
      this->NoiseFilterAvg(TWaveformConstants::maxAvgForNoise);
    }
    else if(TWaveformConstants::noiseFilterMethod == "Area")
    {
      this->NoiseFilterArea(TWaveformConstants::maxAreaForNoise);
    }
    return;
  }

  //_____________________________________________________________________________________________________________________________________
  // Prerequisite: Must have called DataProcessing()
  // Returns a TWaveform that is the sum of its best fit templates, scaled and shifted respectively
  TWaveform TWaveform::AddBestTemps(const char *tempFile)                     //***Have to change to add more than 2**//
  {
    TWaveform add, tempWave;
    tempWave = this->ReadBestTemp(tempFile, 0);
    tempWave.CopySetup(add);
    for (int i = 0; i < this->bestTemp.size(); ++i)
    {
      tempWave.Clear();
      tempWave = this->ReadBestTemp(tempFile, i);
      add = add.Add(tempWave, this->bestTempScale[i], this->bestTempOffset[i]);
    }
    return add;
  }

  //_____________________________________________________________________________________________________________________________________
  // Shifts the Waveform by an offset and scales it by by scale
  void TWaveform::Shift(int offset, double scale)
  {
    TWaveform wave;
    this->CopySignal(wave);
    for (int i = 0; i < this->nSamples; ++i)
    {
      if (i - offset < 0)
      {
        this->vA[i] = 0;
      }
      else
      {
        this->vA[i] = scale * wave.vA[i - offset];
      }
    }
  }


  //_____________________________________________________________________________________________________________________________________
  // Returns a waveform which is an addition of the current waveform and temp2 with their respective scales and offsets
  TWaveform TWaveform::Add(TWaveform &temp2, double temp2Scale, int temp2Offset, double tempScale, int tempOffset)
  {
    TWaveform wave;
    this->CopySetup(wave);
    for (int i = 0; i < wave.nSamples; ++i)
    {
      if (i - tempOffset < 0)
      {
        if (i - temp2Offset < 0)
        {
          wave.vA[i] = 0;
        }
        else
        {
          wave.vA[i] = temp2Scale * temp2.vA[i - temp2Offset];
        }
      }
      else
      {
        if (i - temp2Offset < 0)
        {
          wave.vA[i] = tempScale * this->vA[i - tempOffset];
        }
        else
        {
          wave.vA[i] = tempScale * this->vA[i - tempOffset] + temp2Scale * temp2.vA[i - temp2Offset];
        }
      }
    }
    return wave;
  }

  //_____________________________________________________________________________________________________________________________________
  // Returns a waveform which is a subtraction of temp2 from the current waveform with their respective scales and offsets
  TWaveform TWaveform::Subtract(TWaveform &temp2, double temp2Scale, int temp2Offset, double tempScale, int tempOffset)  
  {
    TWaveform wave;
    this->CopySetup(wave);
    for (int i = 0; i < wave.nSamples; ++i)
    {
      if (i - tempOffset < 0)
      {
        if (i - temp2Offset < 0)
        {
          wave.vA[i] = 0;
        }
        else
        {
          wave.vA[i] = -temp2Scale * temp2.vA[i - temp2Offset];
        }
      }
      else
      {
        if (i - temp2Offset < 0)
        {
          wave.vA[i] = tempScale * this->vA[i - tempOffset];
        }
        else
        {
          wave.vA[i] = tempScale * this->vA[i - tempOffset] - temp2Scale * temp2.vA[i - temp2Offset];
        }
      }
    }
    return wave;
  }

  //_____________________________________________________________________________________________________________________________________
  // Smoothens out a waveform by averaging the signal at each point with nPoints surrounding it.
  void TWaveform::SmoothOut(int nPoints)
  {
    double avg;
    TWaveform wave;
    this->CopySetup(wave);
    for (int i = 0; i < this->nSamples; ++i)
    {
      avg = this->FindAvg(i - nPoints/2, "Waveform", nPoints);
      wave.vA[i] = avg; 
    }
    this->Clear();
    wave.Copy(*this);
    return;
  }

  //_____________________________________________________________________________________________________________________________________
  // Precondition: Must have called FindPeaksTemp()
  // Sorts the peaks, bestTemp and respective data members into ascending order of time.
  // Returns true if the pulses were sorted and false if there are no pulses inside the TWaveform to sort.
  bool TWaveform::SortPulses()
  {
    std::string tempTemp;
    int tempOffset;
    double tempScale, tempPeak, tempRise;
    if (this->bestTemp.size() == 0)
    {
      return false;
    }
    for (int i = 0; i < (this->bestTemp.size()-1) ; ++i)
    {
      for (int j = i+1; j < this->bestTemp.size(); ++j)
      {
        if (this->peaksA[j] < this->peaksA[i])
        {
          // Arranges peaksA
          tempPeak = this->peaksA[i];
          this->peaksA[i] = this->peaksA[j];
          this->peaksA[j] = tempPeak;
          // Arranges risePosA
          tempRise = this->risePosA[i];
          this->risePosA[i] = this->risePosA[j];
          this->risePosA[j] = tempRise;
          // Arranges bestTemp
          tempTemp = this->bestTemp[i];
          this->bestTemp[i] = this->bestTemp[j];
          this->bestTemp[j] = tempTemp;
          // Arrange bestTempOffset
          tempOffset = this->bestTempOffset[i];
          this->bestTempOffset[i] = this->bestTempOffset[j];
          this->bestTempOffset[j] = tempOffset;
          // Arranges bestTempScale
          tempScale = this->bestTempScale[i];
          this->bestTempScale[i] = this->bestTempScale[j];
          this->bestTempScale[j] = tempScale;
        }
      }
    }
    return true;
  }

  //_____________________________________________________________________________________________________________________________________
  // Analyzes the waveform and finds its best fitting templates, along with its pulses' rise and peak position. 
  // Uses FindBestTemps, FindPeaksTemp, and FindRiseTemp.
  // If minHeight = 0, minHeight will be set to 2 times the standard deviation (minHeight = 2 * stDevA)
  bool TWaveform::AnalyzeWave(const char *tempFile, const char *tempName, int tempNum, int maxPulses, double maxChi, int tLim, double scaleLim, double minHeight)
  {
    this->PreDataProcessing();
    this->SetBestTemplateParameters(tempFile, tempName, tempNum, maxPulses, tLim, scaleLim);
    bool hasGoodFit = this->IsGoodFit(maxChi);
    if (hasGoodFit)
    {
      if(minHeight == 0)
      {
        minHeight = 2 * this->stDevA;
      }
      this->FilterPulseHeight(minHeight, tempFile);
      if(this->nPeaksA > 0)
      {
        this->FindPeaksTemp(tempFile);
        this->FindRiseTemp(tempFile);
        this->SortPulses();
      }
    }
    return hasGoodFit;
  }

  //_____________________________________________________________________________________________________________________________________
  // Prerequisite: Call SetBestTemplateParameters() first.
  // Returns true if the waveform's bestTempChi is less than or equal to the maxChi passed.
  bool TWaveform::IsGoodFit(double maxChi)
  {
    return (this->bestTempChi <= maxChi);
  }

  //_____________________________________________________________________________________________________________________________________
  // Prerequisite: Call AnalyzeWave() first.
  // Filters the best template fits for the waveform by disposing of pulses with height less than minHeight.
  // Returns true if all the pulses fitted to the waveform are above minHeight, and false if otherwise.
  // ************* THINK OF TURNING minHeight INTO A MULTIPLE OF THE WAVE'S ST. DEV. **************
  // ************* WILL NOT WORK FOR NEGATIVE PULSES *************
  bool TWaveform::FilterPulseHeight(double minHeight, const char *tempFile)
  {
    bool allAboveMin = true;
    double pulseHeight;
    int pulseNumber(0);
    int numPulses = this->nPeaksA;
    for (int i = 0; i < numPulses; ++i)
    {
      pulseHeight = this->GetPulseHeight(pulseNumber, tempFile);
      if (pulseHeight < minHeight)
      {
        this->bestTemp.erase(this->bestTemp.begin() + pulseNumber);
        this->bestTempScale.erase(this->bestTempScale.begin() + pulseNumber);
        this->bestTempOffset.erase(this->bestTempOffset.begin() + pulseNumber);
        allAboveMin = false;
        pulseNumber--;
      }
      pulseNumber++;
    }
    this->nPeaksA = this->bestTemp.size();
    return allAboveMin;
  }

  //_____________________________________________________________________________________________________________________________________
  // Prerequisite: Call ReadFile() first. 
  // Changes the sign of all the Waveform's voltage values
  void TWaveform::ChangeSignalSign()
  {
    for (int i = 0; i < this->nSamples; ++i)
    {
      this->vA[i] *= (-1);
    }
    return;
  }

namespace TWaveformSpace
{

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                              ///////////////////////////////////////////
                                              ////// NONMEMBER FUNCTION DEFINITIONS /////
                                              ///////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  //_____________________________________________________________________________________________________________________________________
  // Returns a string of the form: [tempName][n]
  std::string TempName(int n, const char *tempName)
  {
    std::ostringstream num;
    std::string numStr, tName(tempName);
    num << n;
    numStr = num.str();
    tName = tName + numStr;
    return tName;
  }

  //_____________________________________________________________________________________________________________________________________
  // Returns a vector of the first (tempNum) TWaveforms saved in the root file tempFile with generic names tempName.
  std::vector<TWaveform> GetTempWaves(int tempNum, const char *tempFile, const char *tempName)
  {
    std::vector<TWaveform> tempWaves(tempNum);
    std::string tempFullName;
    for (int i = 0; i < tempNum; i++)
    {
      tempFullName = TWaveformSpace::TempName(i, tempName);
      tempWaves.at(i).ReadTemp(tempFullName.c_str(), tempFile);
      if (tempWaves.at(i).bestTemp[0] == "")
      {
        tempWaves.at(i).PreDataProcessing();
      }
    }
    return tempWaves;
  }


  //_____________________________________________________________________________________________________________________________________
  // Returns a vector of the first (tempNum) TWaveforms saved in the root file tempFile with generic names tempName.
  // In this version the templates have already been analyzed.
  std::vector<TWaveform> GetTempWavesAnalyzed(int tempNum, const char *tempFile, const char *tempName)
  {
    std::vector<TWaveform> tempWaves(tempNum);
    std::string tempFullName;
    for (int i = 0; i < tempNum; i++)
    {
      tempFullName = TWaveformSpace::TempName(i, tempName);
      tempWaves.at(i).ReadTemp(tempFullName.c_str(), tempFile);
      if (tempWaves.at(i).bestTemp[0] == "")
      {
        tempWaves.at(i).AnalyzeWave(tempFile, tempName, tempNum);
      }
    }
    return tempWaves;
  }

  //_____________________________________________________________________________________________________________________________________
  // Returns a vector with the area under the TWaveforms in tempWaves. 
  std::vector<double> GetTempAreas(std::vector<TWaveform> tempWaves)
  {
    std::vector<double> tempAreas;
    for (int i = 0; i < tempWaves.size(); ++i)
    {
      tempAreas.push_back(tempWaves.at(i).vIAreaA[tempWaves.at(i).nSamples-1]);
    }
    return tempAreas;
  }

  //_____________________________________________________________________________________________________________________________________
  // Returns the area under a pulse with height (pulseStrength), and fitted by the template waveBestTemp.
  double GetPulseArea(double pulseStrength, std::string waveBestTemp, std::vector<TWaveform> tempWaves, std::vector<double> tempAreas)
  {
    double pulseArea;
    double waveScale;
    for (int i = 0; i < tempWaves.size(); ++i)
    {
      if (waveBestTemp == tempWaves.at(i).bestTemp[0])
      {
        waveScale = pulseStrength / tempWaves.at(i).vA[tempWaves.at(i).peaksA[0]];
        pulseArea = tempAreas.at(i) * waveScale;
      }
    }
    return pulseArea;
  }

  //_____________________________________________________________________________________________________________________________________
  // Returns a sum of the waveforms inside the TWaveform vector: waves.
  TWaveform AddWaveforms(std::vector<TWaveform> waves)
  {
    TWaveform waveSum = waves[0];
    for (int i = 1; i < waves.size(); ++i)
    {
      waveSum = waveSum.Add(waves[i]);
    }
    return waveSum;
  }

  //_____________________________________________________________________________________________________________________________________
  // Returns a vector containing the minimum (integralLim[0]) and maximum (integralLim[1]) values of the integral for all the waveforms
  // in the directory number dirNum with genericFileName and fileType.
  std::vector<double> GetIntegralLimits(int waveDir, int firstWave)
  {
    std::vector<double> integralLim(2);
    TWaveform wave;
    bool fileRead = wave.ReadFile(wave.GetFilename(firstWave, waveDir));
    wave.SetSignalPositive();
    wave.FindIntegral();
    integralLim[0] = wave.vIAreaA[wave.nSamples-1];
    integralLim[1] = integralLim[0];
    while(fileRead)
    {
      wave.SetSignalPositive();
      wave.FindIntegral();
      if(wave.vIAreaA[wave.nSamples-1] < integralLim[0])
      {
        integralLim[0] = wave.vIAreaA[wave.nSamples-1];
      }
      if(wave.vIAreaA[wave.nSamples-1] > integralLim[1])
      {
        integralLim[1] = wave.vIAreaA[wave.nSamples-1];
      }
      wave.Clear();
      firstWave++;
      fileRead = wave.ReadFile(wave.GetFilename(firstWave, waveDir));
    }
    return integralLim; 
  }

  //_____________________________________________________________________________________________________________________________________
  // Returns a c-string with a generated address to save a tree root file
  // If dirNum = -1, then no directory number will be added to the c-string
  // Format of files generated: "[dirAddress][dirNum]/[treeName][treeNum].root"
  char* GetTreeFileName(int dirNum, int treeNum, std::string dirAddress, std::string treeName)
  {
    if(dirNum == -1)
    {
      char* treeFileName = Form("%s/%s%i.root", dirAddress.c_str(), treeName.c_str(), treeNum); 
      return treeFileName;
    }
    else
    {
      char* treeFileName = Form("%s%i/%s%i.root", dirAddress.c_str(), dirNum, treeName.c_str(), treeNum);
      return treeFileName;
    }
  }

  //_____________________________________________________________________________________________________________________________________
  // Returns a treeData object with all its data members set to the corresponding data saved in the TChain's (chain) entry #entry.
  treeData GetTreeData(int entry, TChain* chain)
  {
    treeData treeEntryData;
    std::vector<int> *peakPos = new std::vector<int>();
    std::vector<int> *risePos = new std::vector<int>();
    std::vector<int> *timeUnc = new std::vector<int>();
    std::vector<int> *bestTempOffset= new std::vector<int>();
    std::vector<std::string> *bestTemps = new std::vector<std::string>();
    std::vector<double> *pulseStrength = new std::vector<double>();
    std::vector<double> *signalStrength = new std::vector<double>();
    std::vector<double> *heightUnc = new std::vector<double>();
    std::vector<double> *bestTempScale = new std::vector<double>();
    chain->SetBranchAddress("Noise", &treeEntryData.noise);
    chain->SetBranchAddress("RisePosition", &risePos);
    chain->SetBranchAddress("StandardDeviation", &treeEntryData.stDev);
    chain->SetBranchAddress("Samples", &treeEntryData.nSamples);
    chain->SetBranchAddress("ChiSquared", &treeEntryData.chiSquared);
    chain->SetBranchAddress("Area", &treeEntryData.area);
    chain->SetBranchAddress("TimeBins", &treeEntryData.tBinSize);
    chain->SetBranchAddress("SignalStrength", &signalStrength);
    chain->SetBranchAddress("PulseStrength", &pulseStrength);
    chain->SetBranchAddress("PeakPosition", &peakPos);
    chain->SetBranchAddress("BestTemps", &bestTemps);
    chain->SetBranchAddress("WaveformNumber", &treeEntryData.waveformNum);
    chain->SetBranchAddress("DirectoryNumber", &treeEntryData.directoryNum);
    chain->SetBranchAddress("TimeUncertainty", &timeUnc);
    chain->SetBranchAddress("PulseHeightUncertainty", &heightUnc);
    chain->SetBranchAddress("BestTempScales", &bestTempScale);
    chain->SetBranchAddress("BestTempOffsets", &bestTempOffset);
    chain->GetEntry(entry);
    treeEntryData.pulseStrength = *pulseStrength;
    treeEntryData.signalStrength = *signalStrength;
    treeEntryData.peakPos = *peakPos;
    treeEntryData.risePos = *risePos;
    treeEntryData.timeUnc = *timeUnc;
    treeEntryData.bestTemplateOffset = *bestTempOffset;
    treeEntryData.bestTemplates = *bestTemps;
    treeEntryData.heightUnc = *heightUnc;
    treeEntryData.bestTemplateScale = *bestTempScale;

    delete pulseStrength;
    delete signalStrength;
    delete peakPos;
    delete risePos;
    delete bestTemps;
    delete timeUnc;
    delete bestTempOffset;
    delete heightUnc;
    delete bestTempScale;
    return treeEntryData;
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                              //////////////////////////////////////////////
                                              ///////// TEMPLATE CREATION FUNCTIONS ////////
                                              //////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //_____________________________________________________________________________________________________________________________________
  // Returns a vector of templates made from averaging waveforms in the same area range and saves them into a root file with name fName 
  // in the current directory.
  // waveDir corresponds to the directory number where the waveforms are, to be used for the GetFileName() method.
  // The area ranges are calculated by dividing (maxArea-minArea) by the number templates desired, numTemps.
  // ************ONLY WORKS WHEN FIRST WAVENUM IS 0 **************
  std::vector<TWaveform> AvgAreaTemplates(int waveDir, const char *fName, double minArea, double maxArea, int numTemps, const char *tempName, int numWaves, bool smooth)
  {
    double areaStep = (maxArea - minArea)/numTemps;
    std::vector<TWaveform> tempWaves(numTemps);
    std::vector<double> areaRange(numTemps+1);
    bool *firstTemp = new bool[numTemps];
    std::vector<int> count(numTemps,0);
    double scaler;
    bool fileRead;
    TWaveform wave;
    for (int k = 0; k < numTemps; ++k)
    {
      firstTemp[k] = false;
    }
    for (int i = 0; i < numTemps+1; ++i)
    {
      areaRange[i] = minArea + i * areaStep;
    }
    if (numWaves == 0)
    {
      int nWave = 0;
      fileRead = wave.ReadFile(wave.GetFilename(nWave, waveDir));
      do
      {
        wave.PreDataProcessing();
        for (int nTemp = 0; nTemp < numTemps; ++nTemp)
        {
          if (areaRange[nTemp] < wave.vIAreaA[wave.nSamples-1] && wave.vIAreaA[wave.nSamples-1] < areaRange[nTemp + 1] /*&& wave.noiseA == false*/)
          {
            if (firstTemp[nTemp] == false )
            {
              tempWaves.at(nTemp) = wave;
              firstTemp[nTemp] = true;
            }
            else
            {
              scaler = 1/(count.at(nTemp)+1.0);
              tempWaves.at(nTemp) = tempWaves.at(nTemp).Add(wave, scaler, 0, count.at(nTemp) * scaler);
            }
            count.at(nTemp)++;
          }
        }
        std::cout << "Wave #" << nWave << ": Added" << std::endl;
        nWave++;
        wave.Clear();
        fileRead = wave.ReadFile(wave.GetFilename(nWave, waveDir));
      } while (fileRead == true);
    }
    else
    {
      for (int nWave = 0; nWave < numWaves; ++nWave)
      {
        wave.Clear();
        fileRead = wave.ReadFile(wave.GetFilename(nWave, waveDir)); 
        if (fileRead == false)
        {
          std::cout<<"Last file read: #"<< nWave << std::endl;
          break;
        }
        wave.PreDataProcessing();
        for (int nTemp = 0; nTemp < numTemps; ++nTemp)
        {
          if (areaRange[nTemp] < wave.vIAreaA[wave.nSamples-1] && wave.vIAreaA[wave.nSamples-1] < areaRange[nTemp + 1] /*&& wave.noiseA == false*/) 
          {
            if (firstTemp[nTemp] == false )
            {
              tempWaves.at(nTemp) = wave;
              firstTemp[nTemp] = true;
              std::cout<<nTemp<<" "<<nWave<<std::endl;
            }
            else
            {
              scaler = 1/(count.at(nTemp)+1.0);
              tempWaves.at(nTemp) = tempWaves.at(nTemp).Add(wave, scaler, 0, count.at(nTemp) * scaler);
            }
            count.at(nTemp)++;
          }
        }
      } 
    }
    for (int p = 0; p < numTemps; ++p)
    {
      tempWaves[p].PreDataProcessing();  
    }
    TWaveformSpace::SaveTemplates(tempWaves, fName, tempName, smooth);
    delete [] firstTemp;
    return tempWaves;
  }

  //_____________________________________________________________________________________________________________________________________
  // Returns a vector of templates made from averaging waveforms in the same area range and saves them into a root file with name fName 
  // in the current directory.
  // waveDir corresponds to the directory number where the waveforms are, to be used for the GetFileName() method.
  // The area ranges are calculated by dividing (maxArea-minArea) by the number templates desired, numTemps.
  // ************ONLY WORKS WHEN FIRST WAVENUM IS 0 **************
  std::vector<TWaveform> AvgAreaTemplates(int firstWave, int waveDir, const char *fName, double minArea, double maxArea, int numTemps, const char *tempName, int numWaves, bool smooth)
  {
    double areaStep = (maxArea - minArea)/numTemps;
    std::vector<TWaveform> tempWaves(numTemps);
    std::vector<double> areaRange(numTemps+1);
    bool *firstTemp = new bool[numTemps];
    std::vector<int> count(numTemps,0);
    double scaler;
    bool fileRead;
    TWaveform wave;
    for (int k = 0; k < numTemps; ++k)
    {
      firstTemp[k] = false;
    }
    for (int i = 0; i < numTemps+1; ++i)
    {
      areaRange[i] = minArea + i * areaStep;
    }
    if (numWaves == 0)
    {
      int nWave = firstWave;
      fileRead = wave.ReadFile(wave.GetFilename(nWave, waveDir));
      do
      {
        wave.PreDataProcessing();
        for (int nTemp = 0; nTemp < numTemps; ++nTemp)
        {
          if (areaRange[nTemp] < wave.vIAreaA[wave.nSamples-1] && wave.vIAreaA[wave.nSamples-1] < areaRange[nTemp + 1] /*&& wave.noiseA == false*/)
          {
            if (firstTemp[nTemp] == false )
            {
              tempWaves.at(nTemp) = wave;
              firstTemp[nTemp] = true;
            }
            else
            {
              scaler = 1/(count.at(nTemp)+1.0);
              tempWaves.at(nTemp) = tempWaves.at(nTemp).Add(wave, scaler, 0, count.at(nTemp) * scaler);
            }
            count.at(nTemp)++;
          }
        }
        std::cout << "Wave #" << nWave << ": Added" << std::endl;
        nWave++;
        wave.Clear();
        fileRead = wave.ReadFile(wave.GetFilename(nWave, waveDir));
      } while (fileRead == true);
    }
    else
    {
      for (int nWave = firstWave; nWave < numWaves; ++nWave)
      {
        wave.Clear();
        fileRead = wave.ReadFile(wave.GetFilename(nWave, waveDir)); 
        if (fileRead == false)
        {
          std::cout<<"Last file read: #"<< nWave << std::endl;
          break;
        }
        wave.PreDataProcessing();
        for (int nTemp = 0; nTemp < numTemps; ++nTemp)
        {
          if (areaRange[nTemp] < wave.vIAreaA[wave.nSamples-1] && wave.vIAreaA[wave.nSamples-1] < areaRange[nTemp + 1] /*&& wave.noiseA == false*/) 
          {
            if (firstTemp[nTemp] == false )
            {
              tempWaves.at(nTemp) = wave;
              firstTemp[nTemp] = true;
              std::cout<<nTemp<<" "<<nWave<<std::endl;
            }
            else
            {
              scaler = 1/(count.at(nTemp)+1.0);
              tempWaves.at(nTemp) = tempWaves.at(nTemp).Add(wave, scaler, 0, count.at(nTemp) * scaler);
            }
            count.at(nTemp)++;
          }
        }
      } 
    }
    for (int p = 0; p < numTemps; ++p)
    {
      tempWaves[p].PreDataProcessing();  
    }
    TWaveformSpace::SaveTemplates(tempWaves, fName, tempName, smooth);
    delete [] firstTemp;
    return tempWaves;
  }

  //_____________________________________________________________________________________________________________________________________
  // Returns a vector of templates made from averaging waveforms in the same area range and saves them into a root file with name fName 
  // in the current directory.
  // waveDir corresponds to the directory number where the waveforms are, to be used for the GetFileName() method.
  // For this version, areaRange stands for an array of type double containing the limits of the range of areas for each template to be created.
  std::vector<TWaveform> AvgAreaTemplates(int waveDir, const char *fName, double *areaRange, int numTemps, const char *tempName, int numWaves, bool smooth)
  {
    std::vector<TWaveform> tempWaves(numTemps);
    bool *firstTemp = new bool[numTemps];
    std::vector<int> count(numTemps,0);
    double scaler;
    bool fileRead;
    TWaveform wave;
    for (int k = 0; k < numTemps; ++k)
    {
      firstTemp[k] = false;
    }
    if (numWaves == 0)
    {
      int nWave = 0;
      fileRead = wave.ReadFile(wave.GetFilename(nWave, waveDir)); 
      do
      {
        wave.PreDataProcessing();
        for (int nTemp = 0; nTemp < numTemps; ++nTemp)
        {
          if (areaRange[nTemp] < wave.vIAreaA[wave.nSamples-1] && wave.vIAreaA[wave.nSamples-1] < areaRange[nTemp + 1] /*&& wave.noiseA == false*/) 
          {
            if (firstTemp[nTemp] == false )
            {
              tempWaves.at(nTemp) = wave;
              firstTemp[nTemp] = true;
            }
            else
            {
              scaler = 1/(count.at(nTemp)+1.0);
              tempWaves.at(nTemp) = tempWaves.at(nTemp).Add(wave, scaler, 0, count.at(nTemp) * scaler);
            }
            count.at(nTemp)++;
          }
        }
        nWave++;
        wave.Clear();
        fileRead = wave.ReadFile(wave.GetFilename(nWave, waveDir));
      } while (fileRead == true);
    }
    else
    {
      for (int nWave = 0; nWave < numWaves; ++nWave)
      {
        wave.Clear();
        fileRead = wave.ReadFile(wave.GetFilename(nWave, waveDir));
        if (fileRead == false)
        {
          break;
        }
        wave.PreDataProcessing();
        for (int nTemp = 0; nTemp < numTemps; ++nTemp)
        {
          if (areaRange[nTemp] < wave.vIAreaA[wave.nSamples-1] && wave.vIAreaA[wave.nSamples-1] < areaRange[nTemp + 1] /*&& wave.noiseA == false*/)
          {
            if (firstTemp[nTemp] == false )
            {
              tempWaves.at(nTemp) = wave;
              firstTemp[nTemp] = true;
              std::cout<<nTemp<<" "<<nWave<<std::endl;
            }
            else
            {
              scaler = 1/(count.at(nTemp)+1.0);
              tempWaves.at(nTemp) = tempWaves.at(nTemp).Add(wave, scaler, 0, count.at(nTemp) * scaler);
            }
            count.at(nTemp)++;
          }
        }
      } 
    }
    for (int p = 0; p < numTemps; ++p)
    {
      tempWaves[p].PreDataProcessing(); 
    }
    TWaveformSpace::SaveTemplates(tempWaves, fName, tempName, smooth);
    delete [] firstTemp;
    return tempWaves;
  }

  //_____________________________________________________________________________________________________________________________________
  // Save the set of templates inside the vector tempWaves in to a root file of name fName. The templates are given a generic name tempName
  // with their respective iteration number attached at the end of the name. If smooth is true, the templates will be smoothen by using
  // the TWaveform::SmoothOut(nPoints) method.
  void SaveTemplates(const std::vector<TWaveform> &tempWaves, const char *fName, const char *tempName, bool smooth, int nPoints)
  {
    TFile *file = new TFile(fName, "Recreate");
    std::ostringstream num;
    std::string name, numStr, tName(tempName);
    std::vector<TWaveform> tempWaves2(tempWaves);
    for (int i = 0; i < tempWaves.size(); ++i)
    { 
      if (smooth)
      {
        tempWaves2[i].SmoothOut(nPoints);
        tempWaves2[i].PreDataProcessing();
      }
      num.str("");
      num.clear();
      name.clear();
      numStr.clear();  
      num << i;
      numStr = num.str();
      name = tName + numStr;
      tempWaves2[i].Write(name.c_str());
    }
    file->Close();
    return;
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                /////////////////////////////////////////
                                                //////  TTREE AND TCHAIN FUNCTIONS //////
                                                /////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //_____________________________________________________________________________________________________________________________________
  // Creates and saves a TTree of the noise, best templates, pulse strength, peak position, and signal strength of the waveforms
  // in the current directory's file number fileNum. The tree is given the name treeName and title treeTitle, and is saved on 
  // the root file fName. 
  void CreateTree(int fileNum, const char* fName, const char* treeName, const char* treeTitle, const char *tempFile, const char *tempName, int tempNum, int maxPulses, double maxChi, int tLim, double scaleLim)
  {
    TFile *file = new TFile(fName, "Update");
    TTree *tree = ((TTree *)(gROOT->FindObject(treeName)));
    delete tree;
    tree = new TTree(treeName, treeTitle);
    TWaveform wave;
    int waveformNum(0);
    bool fileRead = wave.ReadFile(wave.GetFilename(waveformNum, fileNum));
    std::vector<double> *pulseStrength = new std::vector<double>(); 
    std::vector<double> *signalStrength = new std::vector<double>(); 
    std::vector<int> *peakPos = new std::vector<int>();
    std::vector<int> *risePos = new std::vector<int>();
    double area(0);
    std::vector<int> *timeUnc = new std::vector<int>(); 
    std::vector<double> *heightUnc = new std::vector<double>();
    tree->Branch("Noise", &wave.noiseA, "noiseA/O");
    tree->Branch("RisePosition", &risePos);
    tree->Branch("StandardDeviation", &wave.stDevA, "stDevA/F");
    tree->Branch("ChiSquared", &wave.bestTempChi, "bestTempChi/D");
    tree->Branch("Samples", &wave.nSamples, "nSamples/I");
    tree->Branch("Area", &area, "area/D");
    tree->Branch("BestTemps", &wave.bestTemp);
    tree->Branch("PulseStrength", &pulseStrength);
    tree->Branch("PeakPosition", &peakPos);
    tree->Branch("SignalStrength", &signalStrength);
    tree->Branch("TimeBins", &wave.tBinSize, "tBinSize/F");
    tree->Branch("TimeUncertainty", &timeUnc);
    tree->Branch("PulseHeightUncertainty", &heightUnc);
    tree->Branch("WaveformNumber", &waveformNum, "waveformNum/I");
    tree->Branch("DirectoryNumber", &fileNum, "fileNum/I");
    tree->Branch("BestTempScales", &wave.bestTempScale);
    tree->Branch("BestTempOffsets", &wave.bestTempOffset);  
    while(fileRead == true)
    {
      wave.PreDataProcessing();
      std::cout << waveformNum << std::endl;
      pulseStrength->clear();
      peakPos->clear();
      signalStrength->clear();
      area = wave.vIAreaA[wave.nSamples-1];
      risePos->clear();
      if (wave.noiseA == false)
      {
        wave.AnalyzeWave(tempFile, tempName, tempNum, maxPulses, maxChi, tLim, scaleLim);
        for (int j = 0; j < wave.nPeaksA; ++j)
        {
          pulseStrength->push_back(wave.GetPulseHeight(j, tempFile));
          peakPos->push_back(wave.peaksA[j]);
          risePos->push_back(wave.risePosA[j]);
          signalStrength->push_back(wave.vA[wave.peaksA[j]]);
        }
        *timeUnc = wave.GetTimeUncertainty();
        *heightUnc = wave.GetPulseHeightUncertainty();
      }
      tree->Fill();
      if (waveformNum%400 == 1)
      {
        file->cd();
        tree->AutoSave();
      }
      std::cout<< "Wave: " << waveformNum << " - Done" << std::endl;
      waveformNum++;
      wave.Clear();
      fileRead = wave.ReadFile(wave.GetFilename(waveformNum, fileNum));
    }
    file->cd();
    tree->CloneTree()->Write();
    file->Close();
    delete file; 
    delete pulseStrength;
    delete signalStrength;
    delete peakPos; 
    delete risePos;
    return;
  }

  //_____________________________________________________________________________________________________________________________________
  // Creates and saves a TTree of the noise, best templates, pulse strength, peak position, and signal strength of the waveforms
  // in the current directory's file number fileNum. The tree is given the name treeName and title treeTitle, and is saved on 
  // the root file fName. 
  bool CreateTree(int start, int end, int fileNum, const char* fName, const char* treeName, Option_t* fileOption, const char* treeTitle, const char *tempFile, const char *tempName, int tempNum, int maxPulses, double maxChi, int tLim, double scaleLim)
  {
    TFile *file = new TFile(fName, fileOption);
    bool inFile = file->GetListOfKeys()->Contains(treeName); 
    TTree *tree = ((TTree *)(gROOT->FindObject(treeName)));
    bool fileRead;
    if (!(fileOption == "Update" && inFile))
    {
      delete tree;
      tree = new TTree(treeName, treeTitle);
    }
    TWaveform wave;
    double area(0);
    int waveformNum(0);
    std::vector<double> *pulseStrength = new std::vector<double>(); 
    std::vector<double> *signalStrength = new std::vector<double>(); 
    std::vector<int> *peakPos = new std::vector<int>();
    std::vector<int> *risePos = new std::vector<int>();
    std::vector<int> *timeUnc = new std::vector<int>(); 
    std::vector<double> *heightUnc = new std::vector<double>();
    tree->Branch("Noise", &wave.noiseA, "noiseA/O"); 
    tree->Branch("RisePosition", &risePos);
    tree->Branch("StandardDeviation", &wave.stDevA, "stDevA/F");
    tree->Branch("ChiSquared", &wave.bestTempChi, "bestTempChi/D");
    tree->Branch("Samples", &wave.nSamples, "nSamples/I");
    tree->Branch("Area", &area, "area/D");
    tree->Branch("BestTemps", &wave.bestTemp);
    tree->Branch("PulseStrength", &pulseStrength);
    tree->Branch("PeakPosition", &peakPos);
    tree->Branch("SignalStrength", &signalStrength);
    tree->Branch("TimeBins", &wave.tBinSize, "tBinSize/F");
    tree->Branch("TimeUncertainty", &timeUnc);
    tree->Branch("PulseHeightUncertainty", &heightUnc);
    tree->Branch("WaveformNumber", &waveformNum, "waveformNum/I");
    tree->Branch("DirectoryNumber", &fileNum, "fileNum/I"); 
    tree->Branch("BestTempScales", &wave.bestTempScale);
    tree->Branch("BestTempOffsets", &wave.bestTempOffset);  
    for (int i = start; i < end; ++i)
    {
      wave.Clear();
      fileRead = wave.ReadFile(wave.GetFilename(i, fileNum));
      if (fileRead == false)
      {
        break;
      }
      waveformNum = i;
      wave.PreDataProcessing();
      pulseStrength->clear();
      peakPos->clear();
      risePos->clear();
      signalStrength->clear();
      timeUnc->clear();
      heightUnc->clear();
      area = wave.vIAreaA[wave.nSamples-1];
      if (wave.noiseA == false)
      {
        wave.AnalyzeWave(tempFile, tempName, tempNum, maxPulses, maxChi, tLim, scaleLim);
        for (int j = 0; j < wave.nPeaksA; ++j)
        {
          pulseStrength->push_back(wave.GetPulseHeight(j, tempFile));
          peakPos->push_back(wave.peaksA[j]);
          risePos->push_back(wave.risePosA[j]);
          signalStrength->push_back(wave.vA[wave.peaksA[j]]);
        }
        *timeUnc = wave.GetTimeUncertainty();
        *heightUnc = wave.GetPulseHeightUncertainty();
      }
      tree->Fill();
      std::cout<< "Wave: " << waveformNum << " - Done" << std::endl;
      if (i%100 == 0)
      {
        file->cd();
        tree->AutoSave();
      }  
    }
    file->cd();
    tree->CloneTree()->Write();
    file->Close();
    delete pulseStrength;
    delete signalStrength;
    delete peakPos;
    delete risePos;
    delete file; 
    return fileRead;
  }

  //_____________________________________________________________________________________________________________________________________
  // Creates and saves a TTree of the noise, best templates, pulse strength, peak position, and signal strength of the waveforms
  // in the current directory's file number fileNum, and whose waveform number is contained in the vector: waveformNums. 
  // The tree is given the name treeName and title treeTitle, and is saved on the root file fName. 
  bool CreateTree(std::vector<int> waveformNums, int fileNum, const char* fName, const char* treeName, Option_t* fileOption, const char* treeTitle, const char *tempFile, const char *tempName, int tempNum, int maxPulses, double maxChi, int tLim, double scaleLim)
  {
    TFile *file = new TFile(fName, fileOption);
    bool inFile = file->GetListOfKeys()->Contains(treeName); 
    TTree *tree = ((TTree *)(gROOT->FindObject(treeName)));
    bool fileRead;
    if (!(fileOption == "Update" && inFile))
    {
      delete tree;
      tree = new TTree(treeName, treeTitle);
    }
    TWaveform wave;
    double area(0);
    int waveformNum(0);
    std::vector<double> *pulseStrength = new std::vector<double>(); 
    std::vector<double> *signalStrength = new std::vector<double>(); 
    std::vector<int> *peakPos = new std::vector<int>();
    std::vector<int> *risePos = new std::vector<int>();
    std::vector<int> *timeUnc = new std::vector<int>(); 
    std::vector<double> *heightUnc = new std::vector<double>();
    tree->Branch("Noise", &wave.noiseA, "noiseA/O"); 
    tree->Branch("RisePosition", &risePos);
    tree->Branch("StandardDeviation", &wave.stDevA, "stDevA/F");
    tree->Branch("ChiSquared", &wave.bestTempChi, "bestTempChi/D");
    tree->Branch("Samples", &wave.nSamples, "nSamples/I");
    tree->Branch("Area", &area, "area/D");
    tree->Branch("BestTemps", &wave.bestTemp);
    tree->Branch("PulseStrength", &pulseStrength);
    tree->Branch("PeakPosition", &peakPos);
    tree->Branch("SignalStrength", &signalStrength);
    tree->Branch("TimeBins", &wave.tBinSize, "tBinSize/F");
    tree->Branch("TimeUncertainty", &timeUnc);
    tree->Branch("PulseHeightUncertainty", &heightUnc);
    tree->Branch("WaveformNumber", &waveformNum, "waveformNum/I");
    tree->Branch("DirectoryNumber", &fileNum, "fileNum/I");
    tree->Branch("BestTempScales", &wave.bestTempScale);
    tree->Branch("BestTempOffsets", &wave.bestTempOffset);  
    for (int i = 0; i < waveformNums.size(); ++i)
    {
      wave.Clear();
      waveformNum = waveformNums.at(i);
      fileRead = wave.ReadFile(wave.GetFilename(waveformNum, fileNum));
      if (fileRead == false)
      {
        break;
      }
      wave.PreDataProcessing();
      std::cout << waveformNum << std::endl;
      pulseStrength->clear();
      peakPos->clear();
      risePos->clear();
      signalStrength->clear();
      area = wave.vIAreaA[wave.nSamples-1];
      if (wave.noiseA == false)
      {
        wave.AnalyzeWave(tempFile, tempName, tempNum, maxPulses, maxChi, tLim, scaleLim);
        for (int j = 0; j < wave.nPeaksA; ++j)
        {
          pulseStrength->push_back(wave.GetPulseHeight(j, tempFile));
          peakPos->push_back(wave.peaksA[j]);
          risePos->push_back(wave.risePosA[j]);
          signalStrength->push_back(wave.vA[wave.peaksA[j]]);
        }
        *timeUnc = wave.GetTimeUncertainty();
        *heightUnc = wave.GetPulseHeightUncertainty();
      }
      tree->Fill();
      if (i%100 == 0)
      {
        file->cd();
        tree->AutoSave();
      }  
    }
    file->cd();
    tree->CloneTree()->Write();
    file->Close();
    delete pulseStrength;
    delete signalStrength;
    delete peakPos;
    delete risePos;
    delete file; 
    return fileRead;
  }

  //_____________________________________________________________________________________________________________________________________
  // *********Fix Comment Below********
  // Creates and saves a set of TTrees of the noise, best templates, pulse strength, peak position, and signal strength (*****AND MORE*****) 
  // of the waveforms in the current directory's file number dirNum. The tree is given the name treeName and title treeTitle, and 
  // is saved on the root file fName. 
  void CreateTrees(int dirNum, std::string dirAddress, std::string treeName, const char* treeTitle, const char *tempFile, const char *tempName, int tempNum, int maxPulses, double maxChi, int tLim, double scaleLim)
  {
    int saveStep = TWaveformConstants::treeSaveStep;                               //Number of waveforms to be saved in each tree
    int i(0), n(0);
    bool isTree = true;
    char *treeFileName = TWaveformSpace::GetTreeFileName(dirNum, n, dirAddress, treeName);
    while(isTree == true)
    {
      isTree = TWaveformSpace::CreateTree(i, i+saveStep, dirNum, treeFileName, treeName.c_str(), "Recreate", treeTitle, tempFile, tempName, tempNum, maxPulses, maxChi, tLim , scaleLim);
      std::cout << "Tree number: " << n << " created" << std::endl;
      n++;
      i = i+saveStep;
      treeFileName = TWaveformSpace::GetTreeFileName(dirNum, n, dirAddress, treeName);
    }
    return;
  }

  //_____________________________________________________________________________________________________________________________________
  // *********Fix Comment Below********
  // Creates and saves a set of TTrees of the noise, best templates, pulse strength, peak position, and signal strength (*****AND MORE*****) 
  // of the waveforms in the current directory's file number dirNum. The tree is given the name treeName and title treeTitle, and 
  // is saved on the root file dirAddress. 
  // In this version, firstWave represents the index of the first wave that will be read, and treeNum will be the index given to the 
  // first tree created, such that it is saved as "[dirAddress][treeNum].root".
  void CreateTrees(int dirNum, int firstWave, int treeNum, std::string dirAddress, std::string treeName, const char* treeTitle, const char *tempFile, const char *tempName, int tempNum, int maxPulses, double maxChi, int tLim, double scaleLim)
  {
    int saveStep = TWaveformConstants::treeSaveStep;                               //Number of waveforms to be saved in each tree
    int i(firstWave), n(treeNum);
    bool isTree = true;
    char *treeFileName = TWaveformSpace::GetTreeFileName(dirNum, n, dirAddress, treeName);
    while(isTree == true)
    {
      isTree = TWaveformSpace::CreateTree(i, i+saveStep, dirNum, treeFileName, treeName.c_str(), "Recreate", treeTitle, tempFile, tempName, tempNum, maxPulses, maxChi, tLim , scaleLim);
      std::cout << "Tree number: " << n << " created" << std::endl;
      n++;
      i = i+saveStep;
      treeFileName = TWaveformSpace::GetTreeFileName(dirNum, n, dirAddress, treeName);
    }
    return;
  }

  //_____________________________________________________________________________________________________________________________________
  // *********Fix Comment Below********
  // Creates a TChain object of the trees with name [treeName] in root files with initial address [treeDirAddress]: 
  // ("[treeDirAddress][dirNum]/[treeName]0.root, [treeDirAddress][dirNum]/[treeName]1.root, [treeDirAddress][dirNum]/[treeName]2.root, ...") 
  // and saves it into the root file [chainFile] 
  void CreateChain(int dirNum, std::string treeDirAddress, const char *chainName, const char *chainFile, std::string treeName, const char *chainTitle)
  {
    TFile *chFile = new TFile(chainFile, "New");
    TChain *chain = new TChain(treeName.c_str(), chainTitle);
    std::string fileName;
    int i(0);
    bool isFile, isTree;
    char *treeFileName = TWaveformSpace::GetTreeFileName(dirNum, i, treeDirAddress, treeName);
    TFile *file = new TFile(treeFileName, "Read");
    isFile = file->IsOpen();
    isTree = file->GetListOfKeys()->Contains(treeName.c_str());
    while(isFile)
    {
      if (isTree)
      {
        chain->Add(treeFileName);
      }
      else
      {
        std::cout << "Tree with name " << treeName.c_str() << " does not exist in file " << treeFileName << std::endl;
      }
      i++;
      treeFileName = TWaveformSpace::GetTreeFileName(dirNum, i, treeDirAddress, treeName);
      file->Close();
      delete file;
      file = new TFile(treeFileName, "Read");
      isFile = file->IsOpen();
      isTree = file->GetListOfKeys()->Contains(treeName.c_str());
    }
    file->Close();
    delete file;
    chFile->cd();
    chain->Write(chainName);
    chFile->Close();
    delete chFile;
    // std::cout << "Last file to be added: " << treeDirAddress << i-1 << ".root" << std::endl;
    return;
  }

  //_____________________________________________________________________________________________________________________________________
  // Creates a set of TTrees with the noise, best templates, pulse strength, peak position, and signal strength (*****AND MORE*****) of 
  // the waveforms in the current directory's file number dirNum. The trees are given the name treeName and title treeTitle, and are 
  // saved on the root files "[dirAddress][dirNum]/[treeName][treeNum].root". A TChain with all the trees just constructed is created and given the name "chainName".
  // The TChain is then save in the rootFile "[chainDirAddress][dirNum].root"
  void CreateTreeChain(int dirNum, std::string treeDirAddress, std::string treeName, std::string chainName, std::string chainDirAddress, const char *treeTitle, const char *chainTitle, const char *tempFile, const char *tempName, int tempNum, int maxPulses, double maxChi, int tLim, double scaleLim)
  {
    TWaveformSpace::CreateTrees(dirNum, treeDirAddress, treeName, treeTitle, tempFile, tempName, tempNum, maxPulses, maxChi, tLim , scaleLim);
    char *chainFileName = TWaveformSpace::GetTreeFileName(-1, dirNum, chainDirAddress, chainName);
    CreateChain(dirNum, treeDirAddress, chainName.c_str(), chainFileName, treeName, chainTitle);
    return;
  } 

  //_____________________________________________________________________________________________________________________________________
  // *********Fix Comment Below********
  // Creates a set of TTrees with the noise, best templates, pulse strength, peak position, and signal strength (*****AND MORE*****) of 
  // the waveforms in the current directory's file number dirNum. The trees are given the name treeName and title treeTitle, and are 
  // saved on the root files "[dirAddress][dirNum]/[treeName][treeNum].root". A TChain with all the trees just constructed is created and given the name "chainName".
  // The TChain is then save in the rootFile "[chainDirAddress][dirNum].root"
  void CreateTreeChain(int dirNum, int firstWave, int treeNum, std::string treeDirAddress, std::string treeName, std::string chainName, std::string chainDirAddress, const char *treeTitle, const char *chainTitle, const char *tempFile, const char *tempName, int tempNum, int maxPulses, double maxChi, int tLim, double scaleLim)
  {
    TWaveformSpace::CreateTrees(dirNum, firstWave, treeNum, treeDirAddress, treeName, treeTitle, tempFile, tempName, tempNum, maxPulses, maxChi, tLim , scaleLim);
    char *chainFileName = TWaveformSpace::GetTreeFileName(-1, dirNum, chainDirAddress, chainName);
    CreateChain(dirNum, treeDirAddress, chainName.c_str(), chainFileName, treeName, chainTitle);
    return;
  } 

  //_____________________________________________________________________________________________________________________________________
  // Links the chain in root file chainFile2 to the chain in root file chainFile1 and saves it in root file fName. 
  // If fName doesn't exist, it creates it. If it does exist, it replaces its contents.
  void LinkChain(const char *chainFile1, const char *chainFile2, const char *fName, const char *chainName1, const char *chainName2, const char *newChainName)
  {
    TFile *file = new TFile(chainFile2, "Read");
    TChain *chain2 = ((TChain *)(gROOT->FindObject(chainName2)));
    file->Close();
    delete file;
    file = new TFile(chainFile1, "Read");
    TChain *chain1 = ((TChain *)(gROOT->FindObject(chainName1)));
    file->Close();
    delete file;
    chain1->Add(chain2);
    TFile *file2 = new TFile(fName, "Recreate");
    chain1->Write(newChainName);
    file2->Close();
    return;
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                /////////////////////////////////////////
                                                ////////  DATA ANALYSIS FUNCTIONS ///////
                                                /////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //_____________________________________________________________________________________________________________________________________
  // Create a histogram with the time distribution of the after-pulses of the waveforms whose properties were saved in the tree treeName
  // found in the root file fName. 
  // xLow and xUp represent the limits of the histogram in the x axis.
  TH1F *TimeDist(const char* treeName, const char* fName, int nBins, float xLow, float xUp, int nPeaks, double minSig)
  {
    TH1F *hist1D  = new TH1F("TimeDist","Time Distribution of After-Pulses", nBins, xLow, xUp);
    TFile *file = new TFile(fName, "Read");
    TTree *tree = ((TTree *)(gROOT->FindObject(treeName)));
    std::vector<int> sigPulses(0);
    double tSecPulse;
    std::vector<int> *peakPos = new std::vector<int>();
    std::vector<std::string> *bestTemps = new std::vector<std::string>();
    std::vector<double> *pulseStrength = new std::vector<double>();
    std::vector<double> *signalStrength = new std::vector<double>();
    bool noise;
    float tBinSize;
    int multPulses(0), goodWaves(0);
    Long64_t entries = tree->GetEntries();
    tree->SetBranchAddress("Noise", &noise);
    tree->SetBranchAddress("TimeBins", &tBinSize);
    tree->SetBranchAddress("SignalStrength", &signalStrength);
    tree->SetBranchAddress("PulseStrength", &pulseStrength);
    tree->SetBranchAddress("PeakPosition", &peakPos);
    tree->SetBranchAddress("BestTemps", &bestTemps);
    tree->GetEntry(0);
    for (int i = 0; i < entries; ++i)
    {
      tree->GetEntry(i);
      if (noise == false)
      {
        goodWaves++;
        if (peakPos->size() >= nPeaks)
        {
          sigPulses.clear();
          for (int n = 0; n < peakPos->size(); ++n)
          {
            if (pulseStrength->at(n) >= minSig)
            {
              sigPulses.push_back(n);
            }
          }
          if (sigPulses.size() >= nPeaks)
          {
            multPulses++;
            tSecPulse = peakPos->at(sigPulses.at(nPeaks - 1)) - peakPos->at(sigPulses.at(0));
            tSecPulse = tSecPulse * tBinSize;
            hist1D->Fill(tSecPulse);
            // hist1D->Fill(tSecPulse, 1/multPulses);                               //For percentage out of all waveforms with multiple pulses
            // hist1D->Fill(tSecPulse, 1/goodWaves);                                //For percentage out of all waveforms 
          }
        }
      }
    }
    hist1D->SetMarkerStyle(3);
    hist1D->GetXaxis()->SetTitle("time (s)");
    hist1D->GetYaxis()->SetTitle("Ocurrences");
    // hist1D->GetYaxis()->SetTitle("Percentage of Total After-Pulses (%)");        //For percentage out of all waveforms with multiple pulses
    // hist1D->GetYaxis()->SetTitle("Percentage of Total Waveforms (%)");           //For percentage out of all waveforms 
    file->Close();
    delete file;
    delete pulseStrength;
    delete signalStrength;
    delete peakPos;
    delete bestTemps;
    return hist1D;
  }

  //_____________________________________________________________________________________________________________________________________
  // Create a histogram with the time distribution of the after-pulses of the waveforms whose properties were saved in the TChain chainName
  // found in the root file fName. 
  // Same as Time Dist but gets info from a TChain of trees instead of a single tree
  // xLow and xUp represent the limits of the histogram in the x axis.
  TH1F *TimeDistChain(const char* fName, const char* chainName, int nBins, float xLow, float xUp, int nPeaks, double minSig)
  {
    TH1F *hist1D = new TH1F("TimeDist","Time Distribution of After-Pulses", nBins, xLow, xUp);
    TFile *file = new TFile(fName, "Read");
    TChain *chain = ((TChain *)(gROOT->FindObject(chainName)));
    std::vector<int> sigPulses(0);
    double tSecPulse;
    std::vector<int> *peakPos = new std::vector<int>();
    std::vector<int> *risePos = new std::vector<int>();
    std::vector<std::string> *bestTemps = new std::vector<std::string>();
    std::vector<double> *pulseStrength = new std::vector<double>();
    std::vector<double> *signalStrength = new std::vector<double>();
    bool noise;
    float tBinSize(0), stDevA(0);
    int multPulses(0), goodWaves(0);
    double area(0);
    int entries = chain->GetEntries();
    chain->SetBranchAddress("Noise", &noise);
    chain->SetBranchAddress("RisePosition", &risePos);
    chain->SetBranchAddress("StandardDeviation", &stDevA);
    chain->SetBranchAddress("Area", &area);
    chain->SetBranchAddress("TimeBins", &tBinSize);
    chain->SetBranchAddress("SignalStrength", &signalStrength);
    chain->SetBranchAddress("PulseStrength", &pulseStrength);
    chain->SetBranchAddress("PeakPosition", &peakPos);
    chain->SetBranchAddress("BestTemps", &bestTemps);
    for (int i = 0; i < entries; ++i)
    {
      chain->GetEntry(i);
      if (noise == false && area != 0)
      {
        goodWaves++;
        if (peakPos->size() >= nPeaks)
        {
          sigPulses.clear();
          for (int n = 0; n < peakPos->size(); ++n)
          {
            if (pulseStrength->at(n) >= minSig)
            {
              sigPulses.push_back(n);
            }
          }
          if (sigPulses.size() >= nPeaks)
          {
            multPulses++;
            tSecPulse = peakPos->at(sigPulses.at(nPeaks - 1)) - peakPos->at(sigPulses.at(0));
            tSecPulse = tSecPulse * tBinSize;
            hist1D->Fill(tSecPulse);
            // hist1D->Fill(tSecPulse, 1/multPulses);                               //For percentage out of all waveforms with multiple pulses
            // hist1D->Fill(tSecPulse, 1/goodWaves);                                //For percentage out of all waveforms 
          }
        }
      }
    }
    hist1D->SetMarkerStyle(3);
    hist1D->GetXaxis()->SetTitle("time (s)");
    hist1D->GetYaxis()->SetTitle("Ocurrences");
    // hist1D->GetYaxis()->SetTitle("Percentage of Total After-Pulses (%)");        //For percentage out of all waveforms with multiple pulses
    // hist1D->GetYaxis()->SetTitle("Percentage of Total Waveforms (%)");           //For percentage out of all waveforms 
    file->Close();
    delete pulseStrength;
    delete signalStrength;
    delete peakPos;
    delete risePos;
    delete bestTemps;
    return hist1D;
  }

  //_____________________________________________________________________________________________________________________________________
  // Create a 2D histogram with the time distribution of the after-pulses, and their signal height, of the waveforms whose properties 
  // were saved in the TChain chainName found in the root file fName. 
  // xLow and xUp represent the limits of the histogram in the x axis.
  // yLow and yUp represent the limits of the histogram in the y axis.
  TH2F *AfterPulseHeightAndTime(const char* fName, const char* chainName, int nBinsX, int nBinsY, float xLow, float xUp, float yLow, float yUp, int nPeaks, double minSig)
  {
    bool isFile, isChain;
    TH2F *hist  = new TH2F("PulseHeight","After-Pulse Height Time Distribution", nBinsX, xLow, xUp, nBinsY, yLow, yUp);
    TFile *file = new TFile(fName, "Read");
    isFile = file->IsOpen();
    isChain = file->GetListOfKeys()->Contains(chainName);
    if (isFile && isChain)
    {
      TChain *chain = ((TChain *)(gROOT->FindObject(chainName)));
      std::vector<int> sigPulses(0);
      double tSecPulse, pulseHeight;
      std::vector<int> *peakPos = new std::vector<int>();
      std::vector<int> *risePos = new std::vector<int>();
      std::vector<std::string> *bestTemps = new std::vector<std::string>();
      std::vector<double> *pulseStrength = new std::vector<double>();
      std::vector<double> *signalStrength = new std::vector<double>();
      bool noise;
      float tBinSize(0), stDevA(0);
      int multPulses(0), goodWaves(0);
      double area(0);
      Long64_t entries = chain->GetEntries();
      chain->SetBranchAddress("Noise", &noise);
      chain->SetBranchAddress("RisePosition", &risePos);
      chain->SetBranchAddress("StandardDeviation", &stDevA);
      chain->SetBranchAddress("Area", &area);
      chain->SetBranchAddress("TimeBins", &tBinSize);
      chain->SetBranchAddress("SignalStrength", &signalStrength);
      chain->SetBranchAddress("PulseStrength", &pulseStrength);
      chain->SetBranchAddress("PeakPosition", &peakPos);
      chain->SetBranchAddress("BestTemps", &bestTemps);
      for (int i = 0; i < entries; ++i)
      {
        chain->GetEntry(i);
        if (noise == false && risePos !=0)
        {
          goodWaves++;
          if (peakPos->size() >= nPeaks)
          {
            sigPulses.clear();
            for (int n = 0; n < peakPos->size(); ++n)
            {
              if (pulseStrength->at(n) >= minSig)
              {
                sigPulses.push_back(n);
              }
            }
            if (sigPulses.size() >= nPeaks)
            {
              multPulses++;
              tSecPulse = peakPos->at(sigPulses.at(nPeaks - 1)) - peakPos->at(sigPulses.at(0));
              tSecPulse = tSecPulse * tBinSize;
              pulseHeight = pulseStrength->at(sigPulses.at(nPeaks - 1));
              hist->Fill(tSecPulse, pulseHeight);
            }
          }
        }
      }
      delete pulseStrength;
      delete signalStrength;
      delete peakPos;
      delete risePos;
      delete bestTemps;
      std::cout << "Number of Waveforms with pulses: " << goodWaves << std::endl;
    }
    else
    {
      if (!isFile)
      {
        std::cout << "File named " << fName << " not found in current directory." << std::endl;
      }
      else if (!isChain)
      {
        std::cout << "Tree named " << chainName << " not found in file " << fName << std::endl;
      }
    }
    file->Close();
    delete file;
    hist->Scale(1/(hist->GetEntries()));
    hist->SetMarkerStyle(3);
    hist->GetXaxis()->SetTitleOffset(1.7);
    hist->GetYaxis()->SetTitleOffset(1.7);
    hist->GetZaxis()->SetTitleOffset(1.7);
    hist->GetXaxis()->SetTitle("time (s)");
    hist->GetYaxis()->SetTitle("After-Pulse Height (V)");
    hist->GetZaxis()->SetTitle("Normalized After-Pulses");
    return hist;
  }

  //_____________________________________________________________________________________________________________________________________
  // *********Fix Comment Below********
  // Create a 2D histogram with the time distribution of the after-pulses, and the first-pulse's height, of the waveforms whose properties 
  // were saved in the TChain chainName found in the root file fName. 
  // xLow and xUp represent the limits of the histogram in the x axis.
  // yLow and yUp represent the limits of the histogram in the y axis.
  TH1F *FirstPulseHeight(const char* fName, const char* chainName, int nBinsX, float xLow, float xUp)
  {
    bool isFile, isChain;
    TH1F *hist  = new TH1F("FirstPulseHeight","First Pulse Height Distribution", nBinsX, xLow, xUp);
    TFile *file = new TFile(fName, "Read");
    isFile = file->IsOpen();
    isChain = file->GetListOfKeys()->Contains(chainName);
    if (isFile && isChain)
    {
      TChain *chain = ((TChain *)(gROOT->FindObject(chainName)));
      std::vector<int> sigPulses(0);
      double tSecPulse, pulseHeight;
      int multPulses(0), goodWaves(0);
      Long64_t entries = chain->GetEntries();
      treeData treeEntry;
      for (int i = 0; i < entries; ++i)
      {
        treeEntry = TWaveformSpace::GetTreeData(i, chain);
        if (treeEntry.noise == false && treeEntry.pulseStrength.size() >= 1)
        {
          goodWaves++;
          pulseHeight = treeEntry.pulseStrength.at(0);
          hist->Fill(pulseHeight);
        }
      }
      std::cout << "Number of Waveforms with pulses: " << goodWaves << std::endl;
    }
    else
    {
      if (!isFile)
      {
        std::cout << "File named " << fName << " not found in current directory." << std::endl;
      }
      else if (!isChain)
      {
        std::cout << "Tree named " << chainName << " not found in file " << fName << std::endl;
      }
    }
    file->Close();
    delete file;
    hist->Scale(1/(hist->GetEntries()));
    hist->SetMarkerStyle(3);
    hist->GetXaxis()->SetTitleOffset(1.4);
    hist->GetYaxis()->SetTitleOffset(1.4);
    hist->GetXaxis()->SetTitle("First-Pulse Height (V)");
    hist->GetYaxis()->SetTitle("Normalized Pulses");
    return hist;
  }

  //_____________________________________________________________________________________________________________________________________
  // Create a 2D histogram with the time distribution of the after-pulses, and the first-pulse's height, of the waveforms whose properties 
  // were saved in the TChain chainName found in the root file fName. 
  // xLow and xUp represent the limits of the histogram in the x axis.
  // yLow and yUp represent the limits of the histogram in the y axis.
  TH2F *FirstPulseHeightAndTime(const char* fName, const char* chainName, int nBinsX, int nBinsY, float xLow, float xUp, float yLow, float yUp, int nPeaks, double minSig)
  {
    bool isFile, isChain;
    TH2F *hist  = new TH2F("PulseHeight","First-Pulse Height Time Distribution", nBinsX, xLow, xUp, nBinsY, yLow, yUp);
    TFile *file = new TFile(fName, "Read");
    isFile = file->IsOpen();
    isChain = file->GetListOfKeys()->Contains(chainName);
    if (isFile && isChain)
    {
      TChain *chain = ((TChain *)(gROOT->FindObject(chainName)));
      std::vector<int> sigPulses(0);
      double tSecPulse, pulseHeight;
      int multPulses(0), goodWaves(0);
      Long64_t entries = chain->GetEntries();
      treeData treeEntry;
      for (int i = 0; i < entries; ++i)
      {
        treeEntry = TWaveformSpace::GetTreeData(i, chain);
        if (treeEntry.noise == false)
        {
          goodWaves++;
          if (treeEntry.peakPos.size() >= nPeaks)
          {
            sigPulses.clear();
            for (int n = 0; n < treeEntry.peakPos.size(); ++n)
            {
              if (treeEntry.pulseStrength.at(n) >= minSig)
              {
                sigPulses.push_back(n);
              }
            }
            if (sigPulses.size() >= nPeaks)
            {
              multPulses++;
              tSecPulse = treeEntry.peakPos.at(sigPulses.at(nPeaks - 1)) - treeEntry.peakPos.at(sigPulses.at(0));
              tSecPulse = tSecPulse * treeEntry.tBinSize;
              pulseHeight = treeEntry.pulseStrength.at(sigPulses.at(0));
              hist->Fill(tSecPulse, pulseHeight);
            }
          }
        }
      }
      std::cout << "Number of Waveforms with pulses: " << goodWaves << std::endl;
    }
    else
    {
      if (!isFile)
      {
        std::cout << "File named " << fName << " not found in current directory." << std::endl;
      }
      else if (!isChain)
      {
        std::cout << "Tree named " << chainName << " not found in file " << fName << std::endl;
      }
    }
    file->Close();
    delete file;
    hist->Scale(1/(hist->GetEntries()));
    hist->SetMarkerStyle(3);
    hist->GetXaxis()->SetTitleOffset(1.7);
    hist->GetYaxis()->SetTitleOffset(1.7);
    hist->GetZaxis()->SetTitleOffset(1.7);
    hist->GetXaxis()->SetTitle("time (s)");
    hist->GetYaxis()->SetTitle("First-Pulse Height (V)");
    hist->GetZaxis()->SetTitle("Normalized After-Pulses");
    return hist;
  }

  //_____________________________________________________________________________________________________________________________________
  // *********Fix Comment Below********
  // Create a 2D histogram with the time distribution of the after-pulses, and the first-pulse's height, of the waveforms whose properties 
  // were saved in the TChain chainName found in the root file fName. 
  // xLow and xUp represent the limits of the histogram in the x axis.
  // yLow and yUp represent the limits of the histogram in the y axis.
  TH2F *FirstAndSecondPulseHeights(const char* fName, const char* chainName, int nBinsX, int nBinsY, float xLow, float xUp, float yLow, float yUp, int nPeaks, double minSig)
  {
    bool isFile, isChain;
    TH2F *hist  = new TH2F("PulseHeights","First and Secon Pulse Height Distribution", nBinsX, xLow, xUp, nBinsY, yLow, yUp);
    TFile *file = new TFile(fName, "Read");
    isFile = file->IsOpen();
    isChain = file->GetListOfKeys()->Contains(chainName);
    if (isFile && isChain)
    {
      TChain *chain = ((TChain *)(gROOT->FindObject(chainName)));
      std::vector<int> sigPulses(0);
      double tSecPulse, pulseHeight1, pulseHeight2;
      int multPulses(0), goodWaves(0);
      Long64_t entries = chain->GetEntries();
      treeData treeEntry;
      for (int i = 0; i < entries; ++i)
      {
        treeEntry = TWaveformSpace::GetTreeData(i, chain);
        if (treeEntry.noise == false)
        {
          goodWaves++;
          if (treeEntry.peakPos.size() >= nPeaks)
          {
            sigPulses.clear();
            for (int n = 0; n < treeEntry.peakPos.size(); ++n)
            {
              if (treeEntry.pulseStrength.at(n) >= minSig)
              {
                sigPulses.push_back(n);
              }
            }
            if (sigPulses.size() >= nPeaks)
            {
              multPulses++;
              tSecPulse = treeEntry.peakPos.at(sigPulses.at(nPeaks - 1)) - treeEntry.peakPos.at(sigPulses.at(0));
              tSecPulse = tSecPulse * treeEntry.tBinSize;
              pulseHeight1 = treeEntry.pulseStrength.at(sigPulses.at(0));
              pulseHeight2 = treeEntry.pulseStrength.at(sigPulses.at(nPeaks - 1));
              hist->Fill(pulseHeight1, pulseHeight2);
            }
          }
        }
      }
      std::cout << "Number of Waveforms with pulses: " << goodWaves << std::endl;
    }
    else
    {
      if (!isFile)
      {
        std::cout << "File named " << fName << " not found in current directory." << std::endl;
      }
      else if (!isChain)
      {
        std::cout << "Tree named " << chainName << " not found in file " << fName << std::endl;
      }
    }
    file->Close();
    delete file;
    hist->Scale(1/(hist->GetEntries()));
    hist->SetMarkerStyle(3);
    hist->GetXaxis()->SetTitleOffset(1.7);
    hist->GetYaxis()->SetTitleOffset(1.7);
    hist->GetZaxis()->SetTitleOffset(1.7);
    hist->GetXaxis()->SetTitle("After-Pulse Height (V)");
    hist->GetYaxis()->SetTitle("First-Pulse Height (V)");
    hist->GetZaxis()->SetTitle("Normalized After-Pulses");
    return hist;
  }

  //_____________________________________________________________________________________________________________________________________
  // Create a 2D histogram with the time distribution of the after-pulses, and the area under the waveform, of the waveforms whose properties 
  // were saved in the TChain chainName found in the root file fName. 
  // xLow and xUp represent the limits of the histogram in the x axis.
  // yLow and yUp represent the limits of the histogram in the y axis.
  TH2F *AreaDist(const char* fName, const char* chainName, int nBinsX, int nBinsY, float xLow, float xUp, float yLow, float yUp, int nPeaks, double minSig)
  {
    bool isFile, isChain;
    TH2F *hist  = new TH2F("AreaDist","After-Pulse Area and Time Distribution", nBinsX, xLow, xUp, nBinsY, yLow, yUp);
    TFile *file = new TFile(fName, "Read");
    isFile = file->IsOpen();
    isChain = file->GetListOfKeys()->Contains(chainName);
    if (isFile && isChain)
    {
      TChain *chain = ((TChain *)(gROOT->FindObject(chainName)));
      std::vector<int> sigPulses(0);
      double tSecPulse, pulseHeight;
      std::vector<int> *peakPos = new std::vector<int>();
      std::vector<int> *risePos = new std::vector<int>();
      std::vector<std::string> *bestTemps = new std::vector<std::string>();
      std::vector<double> *pulseStrength = new std::vector<double>();
      std::vector<double> *signalStrength = new std::vector<double>();
      bool noise;
      float tBinSize(0), stDevA(0);
      int multPulses(0), goodWaves(0);
      double area(0);
      Long64_t entries = chain->GetEntries();
      chain->SetBranchAddress("Noise", &noise);
      chain->SetBranchAddress("RisePosition", &risePos);
      chain->SetBranchAddress("StandardDeviation", &stDevA);
      chain->SetBranchAddress("Area", &area);
      chain->SetBranchAddress("TimeBins", &tBinSize);
      chain->SetBranchAddress("SignalStrength", &signalStrength);
      chain->SetBranchAddress("PulseStrength", &pulseStrength);
      chain->SetBranchAddress("PeakPosition", &peakPos);
      chain->SetBranchAddress("BestTemps", &bestTemps);
      for (int i = 0; i < entries; ++i)
      {
        chain->GetEntry(i);
        if (noise == false)
        {
          goodWaves++;
          if (peakPos->size() >= nPeaks)
          {
            sigPulses.clear();
            for (int n = 0; n < peakPos->size(); ++n)
            {
              if (pulseStrength->at(n) >= minSig)
              {
                sigPulses.push_back(n);
              }
            }
            if (sigPulses.size() >= nPeaks)
            {
              multPulses++;
              tSecPulse = peakPos->at(sigPulses.at(nPeaks - 1)) - peakPos->at(sigPulses.at(0));
              tSecPulse = tSecPulse * tBinSize;
              pulseHeight = pulseStrength->at(sigPulses.at(nPeaks - 1));
              hist->Fill(tSecPulse, area);
            }
          }
        }
      }
      delete pulseStrength;
      delete signalStrength;
      delete peakPos;
      delete risePos;
      delete bestTemps;
      std::cout << "Number of Waveforms with pulses: " << goodWaves << std::endl;
    }
    else
    {
      if (!isFile)
      {
        std::cout << "File named " << fName << " not found in current directory." << std::endl;
      }
      else if (!isChain)
      {
        std::cout << "Tree named " << chainName << " not found in file " << fName << std::endl;
      }
    }
    file->Close();
    delete file;
    hist->Scale(1/(hist->GetEntries()));
    hist->SetMarkerStyle(3);
    hist->GetXaxis()->SetTitleOffset(1.7);
    hist->GetYaxis()->SetTitleOffset(1.7);
    hist->GetZaxis()->SetTitleOffset(1.7);
    hist->GetXaxis()->SetTitle("time (s)");
    hist->GetYaxis()->SetTitle("Waveform Area (V*s)");
    hist->GetZaxis()->SetTitle("Normalized After-Pulses");
    return hist;
  }

  //_____________________________________________________________________________________________________________________________________
  // Create a 2D histogram with the time distribution of the after-pulses, and the area under the waveform, of the waveforms whose properties 
  // were saved in the TChain chainName found in the root file fName. 
  // xLow and xUp represent the limits of the histogram in the x axis.
  // yLow and yUp represent the limits of the histogram in the y axis.
  TH2F *PulseAreaDist(const char* fName, const char* chainName, int nBinsX, int nBinsY, float xLow, float xUp, float yLow, float yUp, int tempNum, const char *tempFile, const char *tempName, int nPeaks, double minSig)
  {
    bool isFile, isChain;
    std::vector<TWaveform> tempWaves;
    std::vector<double> tempAreas;
    double pulseArea;
    tempWaves = TWaveformSpace::GetTempWavesAnalyzed(tempNum, tempFile, tempName);
    tempAreas = TWaveformSpace::GetTempAreas(tempWaves);
    TH2F *hist  = new TH2F("PulseAreaDist","After-Pulse Area and Time Distribution", nBinsX, xLow, xUp, nBinsY, yLow, yUp);
    TFile *file = new TFile(fName, "Read");
    isFile = file->IsOpen();
    isChain = file->GetListOfKeys()->Contains(chainName);
    if (isFile && isChain)
    {
      TChain *chain = ((TChain *)(gROOT->FindObject(chainName)));
      std::vector<int> sigPulses(0);
      double tSecPulse, pulseHeight;
      int multPulses(0), goodWaves(0);
      Long64_t entries = chain->GetEntries();
      treeData treeEntry;
      for (int i = 0; i < entries; ++i)
      {
        treeEntry = TWaveformSpace::GetTreeData(i, chain);
        // std::cout << "Entry #" << i << " - Read" << std::endl;
        if (treeEntry.noise == false)
        {
          goodWaves++;
          if (treeEntry.peakPos.size() >= nPeaks)
          {
            sigPulses.clear();
            for (int n = 0; n < treeEntry.peakPos.size(); ++n)
            {
              if (treeEntry.pulseStrength.at(n) >= minSig)
              {
                sigPulses.push_back(n);
              }
            }
            if (sigPulses.size() >= nPeaks)
            {
              multPulses++;
              tSecPulse = treeEntry.peakPos.at(sigPulses.at(nPeaks - 1)) - treeEntry.peakPos.at(sigPulses.at(0));
              tSecPulse = tSecPulse * treeEntry.tBinSize;
              pulseHeight = treeEntry.pulseStrength.at(sigPulses.at(nPeaks - 1));
              pulseArea = TWaveformSpace::GetPulseArea(treeEntry.pulseStrength.at(sigPulses.at(nPeaks - 1)), treeEntry.bestTemplates.at(sigPulses.at(nPeaks - 1)), tempWaves, tempAreas);
              hist->Fill(tSecPulse, pulseArea);
            }
          }
        }
      }
      // std::cout << "Number of Waveforms with at least 1 pulse: " << goodWaves << std::endl;
      // std::cout << "Number of Waveforms with at least 2 pulses: " << multPulses << std::endl;
    }
    else
    {
      if (!isFile)
      {
        std::cout << "File named " << fName << " not found in current directory." << std::endl;
      }
      else if (!isChain)
      {
        std::cout << "Tree named " << chainName << " not found in file " << fName << std::endl;
      }
    }
    file->Close();
    delete file;
    hist->Scale(1/(hist->GetEntries()));
    hist->SetMarkerStyle(3);
    hist->GetXaxis()->SetTitleOffset(1.7);
    hist->GetYaxis()->SetTitleOffset(1.7);
    hist->GetZaxis()->SetTitleOffset(1.7);
    hist->GetXaxis()->SetTitle("time (s)");
    hist->GetYaxis()->SetTitle("Waveform Area (V*s)");
    hist->GetZaxis()->SetTitle("Normalized After-Pulses");
    return hist;
  }

  //_____________________________________________________________________________________________________________________________________
  // *********Fix Comment Below********
  // Create a 2D histogram with the time distribution of the after-pulses, and the first-pulse's height, of the waveforms whose properties 
  // were saved in the TChain chainName found in the root file fName. 
  // xLow and xUp represent the limits of the histogram in the x axis.
  // yLow and yUp represent the limits of the histogram in the y axis.
  TH1F *ChiSquaredHist(const char* fName, const char* chainName, int nBinsX, float xLow, float xUp)
  {
    bool isFile, isChain;
    TH1F *hist  = new TH1F("ChiSquaredDist","Chi Squared Distribution", nBinsX, xLow, xUp);
    TFile *file = new TFile(fName, "Read");
    isFile = file->IsOpen();
    isChain = file->GetListOfKeys()->Contains(chainName);
    if (isFile && isChain)
    {
      TChain *chain = ((TChain *)(gROOT->FindObject(chainName)));
      std::vector<int> sigPulses(0);
      double tSecPulse, pulseHeight;
      int multPulses(0), goodWaves(0);
      Long64_t entries = chain->GetEntries();
      treeData treeEntry;
      for (int i = 0; i < entries; ++i)
      {
        treeEntry = TWaveformSpace::GetTreeData(i, chain);
        if (treeEntry.noise == false)
        {
          goodWaves++;
          hist->Fill(treeEntry.chiSquared);
        }
      }
      std::cout << "Number of Waveforms with pulses: " << goodWaves << std::endl;
    }
    else
    {
      if (!isFile)
      {
        std::cout << "File named " << fName << " not found in current directory." << std::endl;
      }
      else if (!isChain)
      {
        std::cout << "Tree named " << chainName << " not found in file " << fName << std::endl;
      }
    }
    file->Close();
    delete file;
    hist->Scale(1/(hist->GetEntries()));
    hist->SetMarkerStyle(3);
    hist->GetXaxis()->SetTitleOffset(1.4);
    hist->GetYaxis()->SetTitleOffset(1.4);
    hist->GetXaxis()->SetTitle("Normalized Chi-Squared");
    hist->GetYaxis()->SetTitle("Normalized Pulses");
    return hist;
  }

  //_____________________________________________________________________________________________________________________________________
  // *********Fix Comment Below********
  // Create a 2D histogram with the time distribution of the after-pulses, and the first-pulse's height, of the waveforms whose properties 
  // were saved in the TChain chainName found in the root file fName. 
  // xLow and xUp represent the limits of the histogram in the x axis.
  // yLow and yUp represent the limits of the histogram in the y axis.
  TH2F *ChiSquaredHist2(const char* fName, const char* chainName, int nBinsX, int nBinsY, float xLow, float xUp, float yLow, float yUp, int nPeaks, double minSig)
  {
    bool isFile, isChain;
    TH2F *hist  = new TH2F("ChiSquaredDist","Chi Squared Distribution", nBinsX, xLow, xUp, nBinsY, yLow, yUp);
    TFile *file = new TFile(fName, "Read");
    isFile = file->IsOpen();
    isChain = file->GetListOfKeys()->Contains(chainName);
    if (isFile && isChain)
    {
      TChain *chain = ((TChain *)(gROOT->FindObject(chainName)));
      std::vector<int> sigPulses(0);
      double tSecPulse, pulseHeight;
      int multPulses(0), goodWaves(0);
      Long64_t entries = chain->GetEntries();
      treeData treeEntry;
      for (int i = 0; i < entries; ++i)
      {
        treeEntry = TWaveformSpace::GetTreeData(i, chain);
        if (treeEntry.noise == false)
        {
          goodWaves++;
          if (treeEntry.peakPos.size() >= nPeaks)
          {
            sigPulses.clear();
            for (int n = 0; n < treeEntry.peakPos.size(); ++n)
            {
              if (treeEntry.pulseStrength.at(n) >= minSig)
              {
                sigPulses.push_back(n);
              }
            }
            if (sigPulses.size() >= nPeaks)
            {
              multPulses++;
              tSecPulse = treeEntry.peakPos.at(sigPulses.at(nPeaks - 1)) - treeEntry.peakPos.at(sigPulses.at(0));
              tSecPulse = tSecPulse * treeEntry.tBinSize;
              pulseHeight = treeEntry.pulseStrength.at(sigPulses.at(0));
              hist->Fill(tSecPulse, treeEntry.chiSquared);
            }
          }
        }
      }
      std::cout << "Number of Waveforms with pulses: " << goodWaves << std::endl;
    }
    else
    {
      if (!isFile)
      {
        std::cout << "File named " << fName << " not found in current directory." << std::endl;
      }
      else if (!isChain)
      {
        std::cout << "Tree named " << chainName << " not found in file " << fName << std::endl;
      }
    }
    file->Close();
    delete file;
    hist->Scale(1/(hist->GetEntries()));
    hist->SetMarkerStyle(3);
    hist->GetXaxis()->SetTitleOffset(1.7);
    hist->GetYaxis()->SetTitleOffset(1.7);
    hist->GetZaxis()->SetTitleOffset(1.5);
    hist->GetXaxis()->SetTitle("Time Between First and Second Pulse (s)");
    hist->GetYaxis()->SetTitle("Normalized Chi-Squared");
    hist->GetZaxis()->SetTitle("Normalized After-Pulses");
    return hist;
  }

  //_____________________________________________________________________________________________________________________________________
  // *********Fix Comment Below********
  // Create a 2D histogram with the time distribution of the after-pulses, and the first-pulse's height, of the waveforms whose properties 
  // were saved in the TChain chainName found in the root file fName. 
  // xLow and xUp represent the limits of the histogram in the x axis.
  // yLow and yUp represent the limits of the histogram in the y axis.
  TH2F *ChiSquaredProbHist(const char* fName, const char* chainName, int nBinsX, int nBinsY, float xLow, float xUp, float yLow, float yUp, int nPeaks, double minSig)
  {
    bool isFile, isChain;
    TH2F *hist  = new TH2F("ChiSquaredDist","Chi Squared Distribution", nBinsX, xLow, xUp, nBinsY, yLow, yUp);
    TFile *file = new TFile(fName, "Read");
    isFile = file->IsOpen();
    isChain = file->GetListOfKeys()->Contains(chainName);
    if (isFile && isChain)
    {
      TChain *chain = ((TChain *)(gROOT->FindObject(chainName)));
      std::vector<int> sigPulses(0);
      double tSecPulse, pulseHeight;
      int multPulses(0), goodWaves(0);
      Long64_t entries = chain->GetEntries();
      treeData treeEntry;
      for (int i = 0; i < entries; ++i)
      {
        treeEntry = TWaveformSpace::GetTreeData(i, chain);
        if (treeEntry.noise == false)
        {
          goodWaves++;
          if (treeEntry.peakPos.size() >= nPeaks)
          {
            sigPulses.clear();
            for (int n = 0; n < treeEntry.peakPos.size(); ++n)
            {
              if (treeEntry.pulseStrength.at(n) >= minSig)
              {
                sigPulses.push_back(n);
              }
            }
            if (sigPulses.size() >= nPeaks)
            {
              multPulses++;
              tSecPulse = treeEntry.peakPos.at(sigPulses.at(nPeaks - 1)) - treeEntry.peakPos.at(sigPulses.at(0));
              tSecPulse = tSecPulse * treeEntry.tBinSize;
              pulseHeight = treeEntry.pulseStrength.at(sigPulses.at(0));
              hist->Fill(tSecPulse, TMath::Prob(treeEntry.chiSquared * (treeEntry.nSamples /*- treeEntry.peakPos.size()*/), treeEntry.nSamples - 2*treeEntry.peakPos.size()));
            }
          }
        }
      }
      std::cout << "Number of Waveforms with pulses: " << goodWaves << std::endl;
    }
    else
    {
      if (!isFile)
      {
        std::cout << "File named " << fName << " not found in current directory." << std::endl;
      }
      else if (!isChain)
      {
        std::cout << "Tree named " << chainName << " not found in file " << fName << std::endl;
      }
    }
    file->Close();
    delete file;
    hist->Scale(1/(hist->GetEntries()));
    hist->SetMarkerStyle(3);
    hist->GetXaxis()->SetTitleOffset(1.7);
    hist->GetYaxis()->SetTitleOffset(1.7);
    hist->GetZaxis()->SetTitleOffset(1.5);
    hist->GetXaxis()->SetTitle("time (s)");
    hist->GetYaxis()->SetTitle("Chi-Squared Probability");
    hist->GetZaxis()->SetTitle("Normalized After-Pulses");
    return hist;
  }

  //_____________________________________________________________________________________________________________________________________
  // *********Fix Comment Below********
  // Create a 2D histogram with the time distribution of the after-pulses, and the first-pulse's height, of the waveforms whose properties 
  // were saved in the TChain chainName found in the root file fName. 
  // xLow and xUp represent the limits of the histogram in the x axis.
  // yLow and yUp represent the limits of the histogram in the y axis.
  TH2F *ChiSquaredAndPulseHeightHist(const char* fName, const char* chainName, int nBinsX, int nBinsY, float xLow, float xUp, float yLow, float yUp)
  {
    bool isFile, isChain;
    TH2F *hist  = new TH2F("ChiSquaredDist","Chi Squared Distribution", nBinsX, xLow, xUp, nBinsY, yLow, yUp);
    TFile *file = new TFile(fName, "Read");
    isFile = file->IsOpen();
    isChain = file->GetListOfKeys()->Contains(chainName);
    if (isFile && isChain)
    {
      TChain *chain = ((TChain *)(gROOT->FindObject(chainName)));
      std::vector<int> sigPulses(0);
      double tSecPulse, pulseHeight;
      int multPulses(0), goodWaves(0);
      Long64_t entries = chain->GetEntries();
      treeData treeEntry;
      for (int i = 0; i < entries; ++i)
      {
        treeEntry = TWaveformSpace::GetTreeData(i, chain);
        if (treeEntry.noise == false && treeEntry.pulseStrength.size() >= 1)
        {
          goodWaves++;
          hist->Fill(treeEntry.pulseStrength.at(0), treeEntry.chiSquared);
        }
      }
      std::cout << "Number of Waveforms with pulses: " << goodWaves << std::endl;
    }
    else
    {
      if (!isFile)
      {
        std::cout << "File named " << fName << " not found in current directory." << std::endl;
      }
      else if (!isChain)
      {
        std::cout << "Tree named " << chainName << " not found in file " << fName << std::endl;
      }
    }
    file->Close();
    delete file;
    hist->Scale(1/(hist->GetEntries()));
    hist->SetMarkerStyle(3);
    hist->GetXaxis()->SetTitleOffset(1.7);
    hist->GetYaxis()->SetTitleOffset(1.7);
    hist->GetZaxis()->SetTitleOffset(1.5);
    hist->GetXaxis()->SetTitle("First Pulse Height (V)");
    hist->GetYaxis()->SetTitle("Normalized Chi-Squared");
    hist->GetZaxis()->SetTitle("Normalized After-Pulses");
    return hist;
  }

  //_____________________________________________________________________________________________________________________________________
  // *********Fix Comment Below********
  // Create a 2D histogram with the time distribution of the after-pulses, and the first-pulse's height, of the waveforms whose properties 
  // were saved in the TChain chainName found in the root file fName. 
  // xLow and xUp represent the limits of the histogram in the x axis.
  // yLow and yUp represent the limits of the histogram in the y axis.
  TH2F *ChiSquaredProbAndPulseHeightHist(const char* fName, const char* chainName, int nBinsX, int nBinsY, float xLow, float xUp, float yLow, float yUp)
  {
    bool isFile, isChain;
    TH2F *hist  = new TH2F("ChiSquaredDist","Chi Squared Distribution", nBinsX, xLow, xUp, nBinsY, yLow, yUp);
    TFile *file = new TFile(fName, "Read");
    isFile = file->IsOpen();
    isChain = file->GetListOfKeys()->Contains(chainName);
    if (isFile && isChain)
    {
      TChain *chain = ((TChain *)(gROOT->FindObject(chainName)));
      std::vector<int> sigPulses(0);
      double tSecPulse, pulseHeight;
      int multPulses(0), goodWaves(0);
      Long64_t entries = chain->GetEntries();
      treeData treeEntry;
      for (int i = 0; i < entries; ++i)
      {
        treeEntry = TWaveformSpace::GetTreeData(i, chain);
        if (treeEntry.noise == false && treeEntry.pulseStrength.size() >= 1)
        {
          goodWaves++;
          hist->Fill(treeEntry.pulseStrength.at(0), TMath::Prob(treeEntry.chiSquared * (treeEntry.nSamples /*- treeEntry.peakPos.size()*/), treeEntry.nSamples - 2*treeEntry.peakPos.size()));
        }
      }
      std::cout << "Number of Waveforms with pulses: " << goodWaves << std::endl;
    }
    else
    {
      if (!isFile)
      {
        std::cout << "File named " << fName << " not found in current directory." << std::endl;
      }
      else if (!isChain)
      {
        std::cout << "Tree named " << chainName << " not found in file " << fName << std::endl;
      }
    }
    file->Close();
    delete file;
    hist->Scale(1/(hist->GetEntries()));
    hist->SetMarkerStyle(3);
    hist->GetXaxis()->SetTitleOffset(1.7);
    hist->GetYaxis()->SetTitleOffset(1.7);
    hist->GetZaxis()->SetTitleOffset(1.5);
    hist->GetXaxis()->SetTitle("First Pulse Height (V)");
    hist->GetYaxis()->SetTitle("Chi-Squared Probability");
    hist->GetZaxis()->SetTitle("Normalized After-Pulses");
    return hist;
  }

}


