set(SOURCES
    main.cpp
    penhub.cpp
    ocrworker.cpp
    session.cpp
)

set(HEADERS
    penhub.h
    ocrworker.h
    session.h
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(TESSERACT REQUIRED tesseract)

add_executable(logseq-rm ${SOURCES} ${HEADERS})
target_include_directories(logseq-rm PRIVATE ${TESSERACT_INCLUDE_DIRS})
target_link_directories(logseq-rm PRIVATE ${TESSERACT_LIBRARY_DIRS})
target_link_libraries(logseq-rm Qt5::Core Qt5::Gui Qt5::Quick ${TESSERACT_LIBRARIES})
