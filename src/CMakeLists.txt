cmake_minimum_required(VERSION 3.16)

# Source files
set(SOURCES
    main.cpp
    main_window.cpp
    remote_widget.cpp
    transfer_dialog.cpp
    export_dialog.cpp
    progress_dialog.cpp
    job_widget.cpp
    mount_widget.cpp
    stream_widget.cpp
    preferences_dialog.cpp
    icon_cache.cpp
    item_model.cpp
    utils.cpp
    job_options.cpp
    list_of_job_options.cpp
)

# Header files (for MOC)
set(HEADERS
    main_window.h
    remote_widget.h
    transfer_dialog.h
    export_dialog.h
    progress_dialog.h
    job_widget.h
    mount_widget.h
    stream_widget.h
    preferences_dialog.h
    icon_cache.h
    item_model.h
    list_of_job_options.h
    utils.h
    job_options.h
)

# UI files
set(UI_FILES
    main_window.ui
    remote_widget.ui
    transfer_dialog.ui
    export_dialog.ui
    progress_dialog.ui
    job_widget.ui
    mount_widget.ui
    stream_widget.ui
    preferences_dialog.ui
)

# Resource files
set(RESOURCES
    resources.qrc
)

# Platform-specific sources
if(WIN32)
    list(APPEND SOURCES resources.rc)
elseif(APPLE)
    list(APPEND HEADERS osx_helper.h)
    list(APPEND SOURCES osx_helper.mm)
    set(MACOSX_BUNDLE_ICON icon.icns)
    set_source_files_properties(icon.icns PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
endif()

# Create executable
if(WIN32)
    add_executable(RcloneBrowser WIN32
        ${SOURCES}
        ${HEADERS}
        ${UI_FILES}
        ${RESOURCES}
    )
    set(TARGET_NAME RcloneBrowser)
elseif(APPLE)
    add_executable(rclone-browser MACOSX_BUNDLE
        ${SOURCES}
        ${HEADERS}
        ${UI_FILES}
        ${RESOURCES}
        icon.icns
    )
    set(TARGET_NAME rclone-browser)
    set_target_properties(rclone-browser PROPERTIES
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist"
        MACOSX_BUNDLE_ICON_FILE "icon.icns"
    )
else()
    add_executable(rclone-browser
        ${SOURCES}
        ${HEADERS}
        ${UI_FILES}
        ${RESOURCES}
    )
    set(TARGET_NAME rclone-browser)
endif()

# Link Qt libraries
target_link_libraries(${TARGET_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
)

# Platform-specific linking
if(WIN32 AND HAVE_QT_WINEXTRAS)
    target_link_libraries(${TARGET_NAME} PRIVATE Qt5::WinExtras)
elseif(APPLE)
    if(HAVE_QT_MACEXTRAS)
        target_link_libraries(${TARGET_NAME} PRIVATE Qt5::MacExtras)
    endif()
    target_link_libraries(${TARGET_NAME} PRIVATE ${COCOA_LIB})
endif()

# Include directories
target_include_directories(${TARGET_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

# Install rules (Linux only)
if(NOT WIN32 AND NOT APPLE)
    include(GNUInstallDirs)
    
    install(TARGETS rclone-browser
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
    
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/../assets/rclone-browser.svg"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps"
        RENAME "rclone-browser.svg"
    )
    
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/../assets/rclone-browser-32x32.png"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/icons/hicolor/32x32/apps"
        RENAME "rclone-browser.png"
    )
    
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/../assets/rclone-browser-64x64.png"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/icons/hicolor/64x64/apps"
        RENAME "rclone-browser.png"
    )
    
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/../assets/rclone-browser-128x128.png"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/icons/hicolor/128x128/apps"
        RENAME "rclone-browser.png"
    )
    
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/../assets/rclone-browser-256x256.png"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/icons/hicolor/256x256/apps"
        RENAME "rclone-browser.png"
    )
    
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/../assets/rclone-browser-512x512.png"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/icons/hicolor/512x512/apps"
        RENAME "rclone-browser.png"
    )
    
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/../assets/rclone-browser.desktop"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/applications"
    )
    
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/../assets/rclone-browser.appdata.xml"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/metainfo"
    )
endif()
