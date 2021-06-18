#include <iostream>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>

#include "Business/MoviesLocalDBService.h"
#include "Persistency/RepositoryLibrary/InMemoryTRepository.h"
#include "Persistency/RepositoryLibrary/FileTRepository.h"
#include "Domain/Movie.h"

#include "Presentation/GUI.h"

int main(int argc, char** argv)
{

	QApplication app(argc, argv);

    FileTRepository<Movie>* moviesRepository = nullptr;
    FileTRepository<Movie>* userRepository = nullptr;
    MoviesLocalDBService moviesService{moviesRepository, userRepository};

    GUI ui{moviesService};

    ui.show();

    return app.exec();
}
