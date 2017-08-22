# TWaveform
A C++ utility library used to read, process, fit and analyze massive sets of waveform data through CERN's ROOT framework.

## Team
### UCSB High Energy Physics Group
#### Developer
- [Carlos Osorio](https://github.com/cosorio94)

#### Supervisor
- Dr. David Stuart


## Table of Contents
1. [Capabilities](#capabilities)
1. [User Manual](#user-manual)
1. [Examples](#examples)
    1. [Template Fitting and Waveform Analysis](#template-fitting-and-waveform-analysis)
    1. [Pulse Templates](#pulse-templates)
    1. [TTree and TChain Histograms](#ttree-and-tchain-histograms)
1. [Installation](#installation)
1. [Usage](#usage)
1. [More Template Fitting Examples](#more-template-fitting-examples)
    1. [Single-pulse Waveforms](#single-pulse-waveforms)
    1. [Waveforms with high-noise](#waveforms-with-high-noise)
    1. [Waveforms with multiple pulses](#waveforms-with-multiple-pulses)

## Capabilities
-  Read and plot waveforms from CSV and txt files. It can also be easily adjusted to read data from other file formats.
-  Find the integral and slope of a waveform. 
-  Find a waveform’s standard deviation when there is noise.
-  Compare waveforms to each other. It can determine if two waveforms have similar shapes and plots the fit between them.
-  Create templates for different shaped pulses within a waveform set. It does so by analyzing a large number of waveforms and getting an average of the pulses with similar shape and/or size.
-  Find a waveform’s best fitting template. It is also capable of fitting multiple templates to a single waveform.  This allows TWaveform to do the following processes:
    - Recognize if a waveform has multiple pulses
    - Record the position and height of each pulses’ peak.
    - Record the rise position of the separate pulses.
    - Find the relative strength of distinct pulses within a waveform.
-  Create TTrees and TChains with information on the properties of a large set of waveforms, such as:
    - Rise and peak positions.
    - Peak heights.
    - Best fitting templates.
    - Area under waveform.
    - Signal’s standard deviation.
    - Uncertainty values.
-  Create and plot 1D and 2D histograms of the time distribution of pulses and their peak heights.

## User Manual
View a detailed description of TWaveform's capabilities and how to use it in the user manual [here](https://github.com/cosorio94/TWaveform/blob/master/UserManual.pdf).

## Examples

### Template Fitting and Waveform Analysis
The graph below was plotted, fitted and analyzed using TWaveform. The blue curve represents the waveform's signal, while the red curve represents the calculated best fit. The red asterisks represent the peak and rise positions of the pulses contained within the waveform, as calculated by TWaveform.

![alt text](https://github.com/cosorio94/TWaveform/blob/master/Plots/Screen%20Shot%202017-08-21%20at%205.32.41%20PM.png "Waveform data fitted with TWaveform")

### Pulse Templates
The plot below shows a pulse template created by TWaveform from a set of waveforms similar to the one on top.

![alt text](https://github.com/cosorio94/TWaveform/blob/master/Plots/Screen%20Shot%202017-08-21%20at%205.39.51%20PM.png "Pulse template created with TWaveform")

### TTree and TChain Histograms
The following histograms were created from a massive collection of waveform data using TWaveform. The data was analyzed using TWaveform's TTree and TChain generating methods that analyze large sets of waveform data.

![alt text](https://github.com/cosorio94/TWaveform/blob/master/Plots/Screen%20Shot%202017-08-21%20at%205.40.12%20PM.png "after-pulse height distribution of set of waveforms")

![alt text](https://github.com/cosorio94/TWaveform/blob/master/Plots/Screen%20Shot%202017-08-21%20at%205.41.02%20PM.png "first-pulse height and chi-squared distribution")

## Installation
In the command line, go to the directory where you want to have TWaveform, and run these commands in order:
```
git clone https://github.com/cosorio94/TWaveform.git
cd TWaveform
make all
```

## Usage
For this step, you will need to have CERN's ROOT framework installed. For instructions on how to install it go [here](https://root.cern.ch/root/htmldoc/guides/users-guide/ROOTUsersGuide.html).
Now, to use and initialize a TWaveform instance using ROOT's command line, run the following commands on the terminal:
```
root -l
gSystem->Load("TWaveform.so");
TWaveform wave;
```
Check the [user manual](https://github.com/cosorio94/TWaveform/blob/master/UserManual.pdf) for more instructions on how to use TWaveform's methods.

## More Template Fitting Examples

### Single-pulse Waveforms:
![alt text](https://github.com/cosorio94/TWaveform/blob/master/Plots/Screen%20Shot%202017-08-21%20at%206.37.28%20PM.png "Waveform with single pulse being fitted by TWaveform")

![alt text](https://github.com/cosorio94/TWaveform/blob/master/Plots/Screen%20Shot%202017-08-21%20at%206.37.52%20PM.png "Waveform with single pulse being fitted by TWaveform")

### Waveforms with high-noise:
![alt text](https://github.com/cosorio94/TWaveform/blob/master/Plots/Screen%20Shot%202017-08-21%20at%205.24.16%20PM.png "Waveform with noise being fitted by TWaveform")

![alt text](https://github.com/cosorio94/TWaveform/blob/master/Plots/Screen%20Shot%202017-08-21%20at%205.30.09%20PM.png "Waveform with noise being fitted by TWaveform")

### Waveforms with multiple pulses:
![alt text](https://github.com/cosorio94/TWaveform/blob/master/Plots/Screen%20Shot%202017-08-21%20at%205.31.15%20PM.png "Waveform with two pulses")

![alt text](https://github.com/cosorio94/TWaveform/blob/master/Plots/Screen%20Shot%202017-08-21%20at%205.31.38%20PM.png "Waveform with two pulses and high noise")

#### Waveforms with slight second pulse:
![alt text](https://github.com/cosorio94/TWaveform/blob/master/Plots/wave5439_Fit.png "Waveform with large first pulse and minor second pulse")

![alt text](https://github.com/cosorio94/TWaveform/blob/master/Plots/wave3434.png "Waveform with large first pulse and minor second pulse")
