target_include_directories(sparkly-fx PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/sdk/
    ${CMAKE_CURRENT_SOURCE_DIR}/util/
    ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_sources(sparkly-fx PRIVATE
    Base.cpp
    CDraw.cpp
    CMat.cpp
    Controls.cpp
    "Dev tools.cpp"
    DLLMain.cpp
    DrawModelExecute.cpp
    FrameStageNotify.cpp
    KeyValues.cpp
    Menu.cpp
    Netvars.cpp
    Panels.cpp
    Styles.cpp
    Visuals.cpp
    Clipboard.cpp
)

add_subdirectory(util)