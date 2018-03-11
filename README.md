# gridRegionSignals
SDP Mar, 2018

Use C++ to calculate subregions from a 2D array (cell grid) of integers (signal strengths)

Project developed and tested on Ubuntu 16.04 LTS linux using the Qt Creator IDE

Project name: ioproj, over 700 lines of C++ code for 1st cut

This is a project for a potential employer. The requirements are listed in a PDF
file I received from the client. 

Also see files:

  - problemDescription.pdf This is the PDF that has a description of the requirements

  When coding these modules, I used a technique to allow some documentation to be extracted
  later by using grep. The files are a little sloppy as I havent edited the raw output,
  but the comments are there and can be read with a little effort.

  - commentsByModule.out Has *my* additional requirements, assumptions, test plan, and todos by module. Snapshot line counts too.
  - commentsByType.out Same as above sorted by type
  - build-output Raw output from a compiler run. Useful to see compiler switches

Build notes

  - enable C++11 features of gcc 4.6.3
  g++ -std=c++0x

  This project can be built at the command line using the linux make utility. Begin
  in the project home directory: ioproj. I am checking in the QT creator generated
  files, which might be overkill, but I wish anyone to be able so use make to build
  from the command line.

Testing

  - I made heavy use of data files. See the dot dat files in top directory.
  - Data file format: text file length = (width of grid * 2) + 2
    so given an 8x8 grid:

8 // first line - grid width
200 // 2nd line here. Signal strength limit
XXX // 3rd line here. First integer, x,y coords = 0,0
XXX // 4th line here. Second integer, x,y coords = 1,0
...

66 lines of text in all for a 8x8 grid

Thanks!

