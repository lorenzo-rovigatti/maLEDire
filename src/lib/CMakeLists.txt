SET(mldr_lib_SOURCES
	Game.cpp
	LEDDisplay.cpp
	TextDisplay.cpp
)

ADD_LIBRARY(_maLEDire SHARED ${mldr_lib_SOURCES})

SET_TARGET_PROPERTIES(_maLEDire PROPERTIES PREFIX "")

# by default, libraries have extension ".dylib" on Mac OS X, but these are
# not recognized by python as modules
IF(APPLE)
    SET_TARGET_PROPERTIES(_baggianalysis PROPERTIES SUFFIX ".so")
ENDIF(APPLE)
