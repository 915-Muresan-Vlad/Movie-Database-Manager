cmake_minimum_required(VERSION 3.17)
project(Local_Movie_Database)

include_directories(include)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "C:/Qt/6.0.2/mingw81_64/lib/cmake")
set(QT_VERSION 6)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Gui Qt6::Widgets)

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

add_executable(Local_Movie_Database
                                    main.cpp
                                    Domain/Movie.cpp
                                    Validation/MovieValidator.cpp
                                    Errors/CustomExceptions.cpp
                                    Persistency/FILERepo/CSVRepo/CsvMoviesRepository.cpp
                                    Persistency/FILERepo/HTMLRepo/HtmlMoviesRepository.cpp
                                    Business/MoviesLocalDBService.cpp
                                    Presentation/GUI.cpp
                )


file(COPY Icons/admin.png
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY Icons/user.png
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
