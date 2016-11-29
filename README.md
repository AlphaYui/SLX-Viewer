# SLX-Viewer
The SLX Viewer is an application to open and view Simulink model files with with the DOM-based .slx file format.
Currently planned is the following functionality:

- The ability to load any .slx file including blocks, wires and parameters
- The ability to view those parameters in an intuitive GUI
- The ability to compare the parameters of subsequent versions of the same model
- The ability to also enter, view and compare all subsequent subsystems

Further functionality requests may be added in the future as soon as the first prototypes are finished.

<h2>Current state of development</h2>

<h3>The first prototype of the .slx-parser is complete and ready to use.</h3>
Further optimization is to be made but not necessary (86ms loading time for 15000 lines of XML)
Systems, blocks and wires are seemingly all loading and initializing as intended.

<h3>A very early rendering prototype has been completed</h3>
The current prototypes renders blocks as rectangles and wires as lines into a QPixmap.
However, Qts QPainter::drawText(...) method is horrendeously inefficient, causing the rendering time per frame to drop from a very comfortable 0.5ms to ~140ms (for the 15000 line model), and is therefore no option for live GUI rendering.
Switching to Qt's GraphicsView library seems to be the most straight-forward fix.
However the early prototype has proven the file parser to work correctly.

<h2>Current objective</h2>

Currently finishing the first usable rendering prototype has highest priority.
This has to be done prior to working on the GUI functionality.
Rendering time should probably be less than 5ms to support older machines and larger models
