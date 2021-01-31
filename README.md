![Preview](https://github.com/joshuakarp/side-scrolling-animation/blob/master/assets/preview.gif?raw=true)

A side-scrolling animation, created in Qt Creator 4.8.2 (Qt version 5.12.1) and compiled with Microsoft Visual C++ Compiler 15.0 (amd64). Utilises an abstract factory and builder to encapsulate the potential animation versions (differing stickman and background objects).

* **P:** pause/play animation
* **Q:** quit animation

Config file
-----------
The config file is composed of 4 JSON objects:
* **stage:** the animation version number (i.e. Stage1Stickman vs. Stage2Stickman)
* **world:** spatial dimensions for the dialog window (width and height, in pixels)
* **stickman:** parameters and properties of the stickman object. Specifically, it is expected to contain the following key-value pairs:
  * sourceFolder: directory location of stickman size folders, using the reference from the `resources.qrc` file (default: `://assets/stickman/`)
  * sourceFilename: filename of all stickman sprites, without appended number or filetype (default: `sprite`)
  * sourceFiletype: filetype extension of all stickman sprites (default: `.png`)
  * numberOfSprites: number of sprite images for each stickman size (used for animation purposes; default: 6)
  * size: categorial size of stickman (either tiny, normal, large, or giant)
  * heights: a JSON object containing the pixel heights of all stickman sizes (ie. in the form heights:{tiny:<height>, normal:<height>, etc})
  * position: initial x-coordinate of stickman (referring to the left-most side of its sprite image)
  * velocity: initial speed (in pixels per frame update) of stickman (and thus, the background layers too)
* **backgrounds:** array of background layers (for purposes of parallax scrolling effect), with each index containing:
  * source: location of the background layer image, using the reference from the `resources.qrc` file (for example, `://assets/background/clouds.png`)
  * width: pixel width of background image
  * velocityScaling: the scaling factor applied to the background layer's velocity (ie. each background layer moves at (stickmanVelocity * its velocityScaling value) )

Coding style
------------
The coding style is based on the [C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md) outlined by Bjarne Stroustrup and Herb Sutter. Most notably:
* use camelCase for naming variables and functions, and UpperCamelCase for class names (global constants should be in capitals with underscore separators)
* prepend member variables with an `m_` prefix
* base indentation is set at 4 spaces
* attempt to keep lines of code to a maximum of roughly 100 characters
* local header includes appear before system headers (and in alphabetical order for both sections)
* use standard header guards (`#ifndef`) in all header files
* method parameters should be passed by value for cheaply-copied types (like `int`, `std::string`), with all others being passed as a `const` reference where possible
* any non-pure virtual methods within an abstract class should have their implementation within the header file (as opposed to an additional implementation file)
* throw an exception to signal when a function can't perform it's assigned task (in order to safely return and quit application)
* code comments and documentation should be Doxygen-esque (see [here](https://developer.lsst.io/cpp/api-docs.html))

Acknowledgements
----------------
Graphical and audio assets were used and adapted from [ansimuz - Games & Pixel Art](https://ansimuz.itch.io/): specifically [SunnyLand Woods](https://ansimuz.itch.io/sunnyland-woods) and [SunnyLand](https://ansimuz.itch.io/sunny-land-pixel-game-art).
