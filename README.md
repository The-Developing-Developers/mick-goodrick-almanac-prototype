<!-- omit in toc -->
# Mick Goodrick's Almanac Prototype

<p style="color:red;">NOTE: this document is still work in progress.</p>

A rough prototype of an application based on Mick Goodrick's Almanac. This is just a proof of concept: the final application will be developed in JUCE.

- [Implementation](#implementation)
- [How To Build](#how-to-build)
- [To Do List](#to-do-list)


# Implementation

<p style="color:red;">This chapter will describe how the application is implemented from a software architecture point of view.</p>

# How To Build

1. Clone this repository.
2. Install Qt 6.6.x (or later version) using the web installer. Required packages:
    - C++ compiler (at least C++14, such as MinGW 11.2.0 64-bit)
    - Qt Creator 12.0.2 (or later version)
    - CMake 3.27.7 (or later version)
    - Ninja 1.10.2 (or later version)
3. Open Qt Creator.
4. Open `CMakeLists.txt` in Qt Creator.
5. Select *Release* configuration.
6. Run.


# To Do List

- Pentatonic and hexatonal scales have not been implemented yet.
- Fix the widgets alignment in Qt Designer (some labels are a bit misaligned).
- If a functional note is selected in one of the "desired sequence" combo boxes, that note should be made unavailable in the other combo boxes. This requires a constant recreation / modification of the content of the "desired sequence" combo boxes every time the user selects an entry in a combo box.