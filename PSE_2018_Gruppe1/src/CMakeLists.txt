######################################################################################
# Praktikum Example Application
######################################################################################



link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)

SET(SOURCE_FILES
	AbstractModeController.cpp
	AutoModeController.cpp
	DriveCommandHandler.cpp
	DriveCommandPublisher.cpp
	FindMarkerModule.cpp
	FollowMarkerModule.cpp
	main.cpp
	ManualDriveCommandModule.cpp
	ManualModeController.cpp
	ObstacleAvoidanceModule.cpp
	PIDController.cpp
	TerminalHandler.cpp
	Logging.cpp
)

SET(H_FILES
	AbstractModeController.hpp
	AutoModeController.hpp
	DataProcessModule.hpp
	DriveCommand.hpp
	DriveCommandHandler.hpp
	DriveCommandPublisher.hpp
	DriveCommandPublisherType.hpp
	DriveCommandSubscriber.hpp
	FindMarkerModule.hpp
	FollowMarkerModule.hpp
	ManualDriveCommandModule.hpp
	ManualModeController.hpp
	ObstacleAvoidanceModule.hpp
	PIDController.hpp
	TerminalHandler.hpp
	Logging.hpp
	FileLogger.hpp
)

IF(NOT WIN32)
 
	add_executable(pse_2018_gruppe1 ${SOURCE_FILES} ${H_FILES})
	target_link_libraries(pse_2018_gruppe1 tivseg_ctrl freenect usb-1.0 SDL asound pulse-simple pulse X11 Xext caca pthread dl m rt)
	target_include_directories(pse_2018_gruppe1 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")

ENDIF(NOT WIN32)

add_subdirectory(test)
