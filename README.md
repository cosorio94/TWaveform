# TWaveform
A C++ utility library used to read, process, and analyze massive sets of waveform data.
![alt text](https://github.com/cosorio94/TWaveform/blob/master/Plots/wave5439_Fit.png "Waveform data fitted with TWaveform")

## Developer
- [Carlos Osorio](https://github.com/cosorio94)

## User Manual
View a detailed description of TWaveform's capabilities and how to use it in the user manual [here](https://github.com/cosorio94/TWaveform/blob/master/UserManual.pdf).

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
