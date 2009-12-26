include_directories (${GPSI_SOURCE_DIR}/zabbr ${SDL_INCLUDE_DIR})

add_library (zabbr SHARED
               ./resources/resource.cpp
               ./resources/stringfontresource.cpp
               ./resources/fontresource.cpp
               ./resources/resourcemanager.cpp
               ./resources/sdlsurfaceresource.cpp
               ./resources/imageresource.cpp
               ./sdlwindow.cpp
               ./widgets/label.cpp
               ./widgets/button.cpp
               ./widgets/widget.cpp
               ./widgets/textinput.cpp
               ./misc/stopwatch.cpp
               ./misc/fpscounter.cpp
               ./misc/fontprefetcher.cpp
               ./panels/splashpanel.cpp
               ./panels/menupanel.cpp
               ./panels/sdlpanel.cpp
               ./panels/dialogpanel.cpp
)
