include_directories (${GPSI_SOURCE_DIR}/zabbr ${SDL_INCLUDE_DIR})

set(ZABBR_SOURCES 
               ./resources/resource.cpp
               ./resources/fontresource.cpp
               ./resources/resourcemanager.cpp
               ./resources/sdlsurfaceresource.cpp
               ./resources/imageresource.cpp
               ./sdlwindow.cpp
               ./widgets/label.cpp
               ./widgets/button.cpp
               ./widgets/widget.cpp
               ./widgets/textinput.cpp
               ./widgets/box.cpp
               ./widgets/vbox.cpp
               ./widgets/hbox.cpp
               ./widgets/table.cpp
               ./widgets/checkbox.cpp
               ./misc/stopwatch.cpp
               ./misc/fpscounter.cpp
               ./misc/fontprefetcher.cpp
               ./misc/audiomanager.cpp
               ./panels/splashpanel.cpp
               ./panels/widgetpanel.cpp
               ./panels/menupanel.cpp
               ./panels/sdlpanel.cpp
               ./panels/dialogpanel.cpp)

if(SDLMIXER_FOUND)
	set(ZABBR_SOURCES ${ZABBR_SOURCES} "./resources/soundresource.cpp")
	set(ZABBR_SOURCES ${ZABBR_SOURCES} "./misc/soundprefetcher.cpp")
endif()

add_library (zabbr SHARED ${ZABBR_SOURCES})

install(TARGETS zabbr
        LIBRARY DESTINATION lib)
