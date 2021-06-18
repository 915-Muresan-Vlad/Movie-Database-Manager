#ifndef LOCAL_MOVIE_DATABASE_MOVIESLOCALDBSERVICE_H
#define LOCAL_MOVIE_DATABASE_MOVIESLOCALDBSERVICE_H

#include "../Persistency/RepositoryLibrary/FileTRepository.h"
#include "../Domain/Movie.h"

class MoviesLocalDBService
{
public:
    MoviesLocalDBService(FileTRepository<Movie>* moviesRepository, FileTRepository<Movie>* userRepository);


    void setUserRepository(FileTRepository<Movie> *userRepository);


    void setMoviesRepository(FileTRepository<Movie> *moviesRepository);


    /// \description Function creates a new Movie instance and adds it to the persistent memory
    ///
    /// \param _id          - positive integer - uniquely identifier for a movie
    /// \param _title       - movie title
    /// \param _genre       - movie genre
    /// \param _year        - release year
    /// \param _likes       - number of likes
    /// \param _url         - url to movie trailer
    ///
    /// \throws ValidationException     - if the movie's fields are not valid
    /// \throws RepositoryException     - if the movie already exists in memory
    void addMovie(int _id, const std::string& _title, int _year, const std::string& _genre, int _likes, const std::string& _url);


    /// \description Function deletes the Movie instance with a given id
    ///
    /// \param _id          - positive integer - uniquely identifier for a movie
    ///
    /// \throws  RepositoryException    - if the movie doesn't exists in memory
    void deleteMovie(int _id);


    /// \description Function updates the Movie's instance (with a given id)
    ///
    /// \param _id          - uniquely identifier for a movie
    /// \param _title       - updated movie title
    /// \param _year        - updated release year
    /// \param _genre       - updated movie genre
    /// \param _likes       - updated number of likes
    /// \param _url         - updated url to movie trailer
    ///
    /// \throws ValidationException     - if the new values are invalid
    /// \throws RepositoryException     - if the movie already exists in memory
    void updateMovie(int _id, const std::string &_title, int _year, const std::string &_genre, int _likes, const std::string &_url);


    /// \description Function returns an iterable containing all movies whose genre match a given genre
    ///
    /// \param genre        - movie genre
    /// \return             - vector containg movies with the matching genre
    std::vector<Movie> filterByGenre(const std::string& genre);


    /// \description Function returns an iterable containing all movies from the database
    ///
    /// \return             - vector containg all movies from the database
    std::vector<Movie> getAllMovies();


    /// \description Function adds the movie with a given id from memory to the user watchlist
    ///
    /// \param _id          - uniquely identifier for the movie to be added to the watchlist
    ///
    /// \throws RepositoryException     - if the movie doesn't exists in the database /
    ///                                   the movie is already in the watchlist
    void addToWatchlist(int _id);


    /// \description Function removes the Movie instance with a given id from the user watchlist and updates the number
    ///              of likes if the user liked it
    /// \param _id          - uniquely identifier for the movie to be removed from the watchlist
    /// \param liked        - true/false whether the user liked the movie
    ///
    /// \throws RepositoryException     - if the movie doesn't exists in the watchlist
    void deleteFromWatchlist(int _id, bool liked);


    /// \description Function returns an iterable containing all movies from the user's watchlist
    ///
    /// \return             - vector containg all movies from the user's watchlist
    std::vector<Movie> getWatchlist();


    ~MoviesLocalDBService();

    const Movie &searchById(int id);

private:

    FileTRepository<Movie>* _moviesRepository;

    FileTRepository<Movie>* _userRepository;
};


#endif //LOCAL_MOVIE_DATABASE_MOVIESLOCALDBSERVICE_H
