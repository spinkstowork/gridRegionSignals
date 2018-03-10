# gridRegionSignals
SDP Mar, 2018

Use C++ to calculate subregions from a 2D array (grid) of integers (signal strengths)

Project developed and tested on Ubuntu 16.04 LTS linux using the Qt Creator IDE

Project name: ioproj

This is a project for a potential employer. The requirements are listed in a PDF
file I received from the client. 

Also see files:

  - problemDescription.pdf This is the PDF that has a description of the requirements

  When coding these modules, I used a technique to allow some documentation to be extracted
  later by using grep. The files are a little sloppy as I havent edited the raw output,
  but the comments are there and can be read with a little effort.

  - commentsByModule.out Has requirements, assumptions, test plan, and todos by module. Snapshot line counts too.
  - commentsByType.out Same as above sorted by type
  - build-output Raw output from a compiler run. Useful to see compiler switches

Build notes

  - enable C++11 features of gcc 4.6.3
  g++ -std=c++0x

  This project can be built at the command line using the linux make utility. Begin
  in the project home directory: ioproj. I am checking in the QT creator generated
  files, which might be overkill, but I wish anyone to be able so use make to build
  from the command line.

Thanks!

