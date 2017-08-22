# TWaveform
A C++ utility library used to read, process, and analyze massive sets of waveform data.

## Developer
- [Carlos Osorio](https://github.com/cosorio94)

## Table of Contents
1. [User Manual](#user-manual)
1. [Examples](#examples)
1. [Installation](#installation)
1. [Usage](#usage)
1. [More Examples](#more-examples)
    1. [Waveforms with high-noise](#waveforms-with-high-noise-being-fitted-by-twaveform)
    1. [Waveforms with two pulses](#waveforms-with-two-pulses)

## User Manual
View a detailed description of TWaveform's capabilities and how to use it in the user manual [here](https://github.com/cosorio94/TWaveform/blob/master/UserManual.pdf).

## Examples
- The graph below was plotted, fitted and analyzed using TWaveform. The blue curve represents the waveform's signal, while the red curve represents the calculated best fit. The red asterisks represent the peak and rise positions of the pulses contained within the waveform, as calculated by TWaveform.

![alt text](https://github.com/cosorio94/TWaveform/blob/master/Plots/Screen%20Shot%202017-08-21%20at%205.32.41%20PM.png "Waveform data fitted with TWaveform")

- The plot below shows a template waveform created by TWaveform from a set of waveforms similar to the one on top.

![alt text](https://github.com/cosorio94/TWaveform/blob/master/Plots/Screen%20Shot%202017-08-21%20at%205.39.51%20PM.png "Template waveform created with TWaveform")

- The following histograms were created with TWaveform from data collected from a massive set of waveforms. The data was analyzed using TWaveform's TTree and TChain generating methods to analyze large sets of waveform data.

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

## More Examples

### Waveforms with high-noise being fitted by TWaveform:
![alt text](https://github.com/cosorio94/TWaveform/blob/master/Plots/Screen%20Shot%202017-08-21%20at%205.24.16%20PM.png "Waveform with noise being fitted by TWaveform")

![alt text](https://github.com/cosorio94/TWaveform/blob/master/Plots/Screen%20Shot%202017-08-21%20at%205.30.09%20PM.png "Waveform with noise being fitted by TWaveform")

### Waveforms with two pulses:
![alt text](https://github.com/cosorio94/TWaveform/blob/master/Plots/Screen%20Shot%202017-08-21%20at%205.31.15%20PM.png "Waveform with two pulses")

![alt text](https://github.com/cosorio94/TWaveform/blob/master/Plots/Screen%20Shot%202017-08-21%20at%205.31.38%20PM.png "Waveform with two pulses and high noise")

#### Waveforms with large first pulse and minor second pulse:
![alt text](https://github.com/cosorio94/TWaveform/blob/master/Plots/wave5439_Fit.png "Waveform with large first pulse and minor second pulse")

![alt text](https://github.com/cosorio94/TWaveform/blob/master/Plots/wave3434.png "Waveform with large first pulse and minor second pulse")
