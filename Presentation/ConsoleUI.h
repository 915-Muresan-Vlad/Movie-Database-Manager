#ifndef LOCAL_MOVIE_DATABASE_CONSOLEUI_H
#define LOCAL_MOVIE_DATABASE_CONSOLEUI_H

#include "../Business/MoviesLocalDBService.h"

class ConsoleUI
{
public:
    explicit ConsoleUI(MoviesLocalDBService &moviesService);

    void run();

private:
    MoviesLocalDBService& _moviesService;
    std::string fileType{};


    static void mainScreen();
    static void adminScreen();
    static void userScreen();

    void uiAdminMode();

    void uiUserMode();

    void uiAddMovie();

    void uiRemoveMovie();

    void uiUpdateMovie();

    void uiPrintAllMovies();

    void browseMovies();

    void listWatchlist();


    bool setupRepositoryTypes();

    void openInApp();
};


#endif //LOCAL_MOVIE_DATABASE_CONSOLEUI_H
