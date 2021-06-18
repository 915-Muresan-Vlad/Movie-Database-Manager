#include "MoviesLocalDBService.h"
#include "../Validation/MovieValidator.h"

MoviesLocalDBService::MoviesLocalDBService(FileTRepository<Movie>* moviesRepository,
                                           FileTRepository<Movie>* userRepository)
       : _moviesRepository{moviesRepository},
         _userRepository{userRepository}
         {}


void MoviesLocalDBService::setUserRepository(FileTRepository<Movie>* userRepository)
{
    if (this->_userRepository == userRepository || userRepository == nullptr)
        return;

    free(this->_userRepository);
    this->_userRepository = userRepository;
}


void MoviesLocalDBService::setMoviesRepository(FileTRepository<Movie> *moviesRepository)
{
    if (this->_moviesRepository == moviesRepository || moviesRepository == nullptr)
        return;

    free(this->_moviesRepository);
    this->_moviesRepository = moviesRepository;
}


void MoviesLocalDBService::addMovie(int _id, const std::string &_title, int _year,
                                    const std::string &_genre, int _likes, const std::string &_url)
{
    Movie movie{_id, _title, _year, _genre, _likes, _url};
    MovieValidator::ValidateMovie(movie);

    this->_moviesRepository->add(movie);
}


void MoviesLocalDBService::deleteMovie(int _id)
{
    Movie to_be_movie = this->_moviesRepository->search(Movie(_id));
    this->_moviesRepository->remove(to_be_movie);
}


void MoviesLocalDBService::updateMovie(int _id, const std::string &_title, int _year,
                                       const std::string &_genre, int _likes, const std::string &_url)
{
    Movie updated_movie = Movie(_id, _title, _year, _genre, _likes, _url);
    MovieValidator::ValidateMovie(updated_movie);

    this->_moviesRepository->update(updated_movie);
}


std::vector<Movie> MoviesLocalDBService::filterByGenre(const std::string &genre)
{
    if (genre.empty())
        return this->_moviesRepository->getAll();
    std::vector<Movie> all = this->_moviesRepository->getAll();
    std::vector<Movie> filtered{};

    std::copy_if(all.begin(), all.end(), std::back_inserter(filtered),
                 [genre](const Movie& movie)
                 {
                    return movie.getGenre().find(genre) != std::string::npos;
                 });

    return filtered;
}


std::vector<Movie> MoviesLocalDBService::getAllMovies()
{
    return this->_moviesRepository->getAll();
}


void MoviesLocalDBService::addToWatchlist(int _id)
{
    Movie watchListed = this->_moviesRepository->search(Movie(_id));
    this->_userRepository->add(watchListed);
}


void MoviesLocalDBService::deleteFromWatchlist(int _id, bool liked)
{
    this->_userRepository->remove(Movie(_id));
    if (liked)
    {
        Movie updated_movie = this->_moviesRepository->search(Movie(_id));
        updated_movie.setLikes(updated_movie.getLikes() + 1);
        this->_moviesRepository->update(updated_movie);
    }
}


std::vector<Movie> MoviesLocalDBService::getWatchlist()
{
    return this->_userRepository->getAll();
}

MoviesLocalDBService::~MoviesLocalDBService()
{
    if (this->_moviesRepository != nullptr)
        free(this->_moviesRepository);
    if (this->_userRepository != nullptr)
        free(this->_userRepository);
}

const Movie &MoviesLocalDBService::searchById(int id)
{
    return this->_moviesRepository->search(Movie(id));
}
