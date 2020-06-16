

SET(SOURCE_FILES
        ../PIDController.cpp
        ../AbstractModeController.cpp
        ../DriveCommandHandler.cpp
        ../DriveCommandPublisher.cpp
        ../TerminalHandler.cpp
        ../FindMarkerModule.cpp
		../FollowMarkerModule.cpp
        ../ObstacleAvoidanceModule.cpp
        ../ManualDriveCommandModule.cpp
        ../ManualModeController.cpp
        ../AutoModeController.cpp
        ../Logging.cpp
        )

SET(H_FILES
        ../PIDController.hpp
        ../AbstractModeController.hpp
        ../DataProcessModule.hpp
        ../DriveCommand.hpp
        ../DriveCommandHandler.hpp
        ../DriveCommandPublisher.hpp
        ../DriveCommandPublisherType.hpp
        ../DriveCommandSubscriber.hpp
        ../PIDController.hpp
        ../MathFunctions.hpp
        ../FindMarkerModule.hpp
        ../ObstacleAvoidanceModule.hpp
        ../ManualDriveCommandModule.hpp
		../FollowMarkerModule.hpp
        ../AutoModeController.hpp
        ../Logging.hpp
        ../FileLogger.hpp
        mocks/SensorManager.hpp
        mocks/DriveController.hpp
        mocks/DriveCommandSubscriberMock.hpp
        mocks/BoundingBox.hpp
        mocks/TerminalHandler.hpp
)

SET(TEST_FILES
        PIDControllerTest.cpp
        DriveCommandHandlerTest.cpp
        MathFunctionsTest.cpp
        TerminalHandlerTest.cpp
        FindMarkerModuleTest.cpp
        ObstacleAvoidanceModuleTest.cpp
        FollowMarkerModuleTest.cpp
        ManualDriveCommandModuleTest.cpp
)

IF (WIN32)

    SET(SOURCE_FILES
            ${SOURCE_FILES}
            mocks/Diagnostics.cpp
            ObstacleAvoidanceModuleTest.cpp
    )
    add_executable(pse_2018_gruppe1_test test.cpp ${SOURCE_FILES} ${H_FILES} ${TEST_FILES})
    target_link_libraries(pse_2018_gruppe1_test gtest)
    target_include_directories(pse_2018_gruppe1_test PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/mocks" "${CMAKE_CURRENT_SOURCE_DIR}/../../include")

    MESSAGE("BUILDING TESTS FOR WIN32")
else ()
    add_executable(pse_2018_gruppe1_test test.cpp ${SOURCE_FILES} ${H_FILES} ${TEST_FILES})
    target_link_libraries(pse_2018_gruppe1_test gtest tivseg_ctrl freenect usb-1.0 SDL asound pulse-simple pulse X11 Xext caca pthread dl m rt)
    target_include_directories(pse_2018_gruppe1_test PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/mocks" "${CMAKE_CURRENT_SOURCE_DIR}/../../include")
ENDIF (WIN32)



