# BEGIN TO COMPILE STUFF
SET(exe_name test_feature)

SET(mldr_SOURCES
	test_feature.cpp
)

INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/lib )

ADD_EXECUTABLE(${exe_name} ${mldr_SOURCES})
TARGET_LINK_LIBRARIES(${exe_name} _maLEDire)
