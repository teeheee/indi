# ###################################################################################################
#
# Component   : LX200 Library
# Dependencies: pthreads
# Supported OS: Linux, BSD, MacOS, Cygwin
#
# ################################################################################################

add_library(indilx200 SHARED
    lx200driver.cpp
    lx200telescope.cpp)

if(NOT WIN32)
    set_target_properties(indilx200 PROPERTIES COMPILE_FLAGS "-fPIC")
endif(NOT WIN32)

target_compile_definitions(indilx200 PRIVATE _XOPEN_SOURCE=700 HAVE_LIBNOVA)
set_target_properties(indilx200 PROPERTIES VERSION ${CMAKE_INDI_VERSION_STRING} SOVERSION ${INDI_SOVERSION} OUTPUT_NAME indilx200)

target_link_libraries(indilx200 indidevice $<$<PLATFORM_ID:CYGWIN>:indidriver>)

install(TARGETS indilx200 LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES
    lx200telescope.h
    lx200driver.h
    DESTINATION ${INCLUDE_INSTALL_DIR}/libindi/mounts
    COMPONENT Devel)

# ################################################################################

########### LX200 Onstep ###############
add_executable(indi_lx200_OnStep
    lx200driver.cpp
    lx200autostar.cpp
    lx200_16.cpp
    lx200gps.cpp
    lx200generic.cpp
    lx200telescope.cpp
    lx200classic.cpp
    lx200gemini.cpp
    lx200zeq25.cpp
    lx200am5.cpp
    lx200gotonova.cpp
    lx200pulsar2.cpp
    lx200apdriver.cpp
    lx200ap.cpp
    lx200ap_v2.cpp
    lx200ap_gtocp2.cpp
    lx200fs2.cpp
    lx200ss2000pc.cpp
    lx200_OnStep.cpp
    lx200_OpenAstroTech.cpp
    lx200_pegasus_nyx101.cpp
    lx200_10micron.cpp
    ioptronHC8406.cpp
    eq500x.cpp
    lx200_OnStep_focuser.cpp
    )

target_compile_definitions(indi_lx200_OnStep PRIVATE _XOPEN_SOURCE=700)
target_link_libraries(indi_lx200_OnStep indidriver)

install(TARGETS indi_lx200_OnStep RUNTIME DESTINATION bin)
# ################################################################################

