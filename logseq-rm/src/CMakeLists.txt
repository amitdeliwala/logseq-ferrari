set(SOURCES
    main.cpp
    penhub.cpp
    ocrworker.cpp
)

set(HEADERS
    penhub.h
    ocrworker.h
)

add_executable(logseq-rm ${SOURCES} ${HEADERS})
target_link_libraries(logseq-rm Qt5::Core Qt5::Gui Qt5::Quick)
