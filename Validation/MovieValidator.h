#ifndef LOCAL_MOVIE_DATABASE_MOVIEVALIDATOR_H
#define LOCAL_MOVIE_DATABASE_MOVIEVALIDATOR_H

#include "../Domain/Movie.h"

class MovieValidator
{
public:

    /// \description Function validates an instance of class Movie
    /// \param movie        - movie to be validated
    /// \throws ValidationException     - if either of the movie's attributes have invalid values
    static void ValidateMovie(const Movie& movie);
};


#endif //LOCAL_MOVIE_DATABASE_MOVIEVALIDATOR_H
