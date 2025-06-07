find_package(Qt6 REQUIRED COMPONENTS Quick Concurrent)
find_package(PkgConfig REQUIRED)
pkg_check_modules(TESSERACT REQUIRED tesseract)
qt_standard_project_setup()

set(SOURCES
    main.cpp
    penhub.cpp
    ocrworker.cpp
    session.cpp
)

add_executable(logseq_rm ${SOURCES})
qt_add_qml_module(logseq_rm
    URI LogseqRM
    VERSION 1.0
    QML_FILES
        ../qml/App.qml
        ../qml/Bullet.qml
        ../qml/InkCanvas.qml
)

target_include_directories(logseq_rm PRIVATE ${TESSERACT_INCLUDE_DIRS})
target_link_directories(logseq_rm PRIVATE ${TESSERACT_LIBRARY_DIRS})
target_link_libraries(logseq_rm PRIVATE Qt6::Quick Qt6::Concurrent ${TESSERACT_LIBRARIES} pthread)
