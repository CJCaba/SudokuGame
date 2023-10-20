project(GameLib)

set(SOURCE_FILES
        MainFrame.h
        MainFrame.cpp
        pch.h
        Item.h
        Item.cpp
        Item.h
        GameView.cpp
        GameView.h
        Game.cpp
        Game.h
        ids.h
        Clock.cpp
        Clock.h
        Container.cpp
        Container.h
        GivenNumber.cpp
        GivenNumber.h
        InteractNumber.cpp
        InteractNumber.h
        Sparty.cpp
        Sparty.h
        Number.cpp
        Number.h
        Declaration.cpp
        Declaration.h
        DeclarationNumber.cpp
        DeclarationNumber.h
        Solution.cpp
        Solution.h
)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)
include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})