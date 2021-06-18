#include "MovieValidator.h"
#include "../Errors/CustomExceptions.h"
#include <sstream>
#include <regex>

void MovieValidator::ValidateMovie(const Movie &movie)
{
    std::stringstream errorBuffer;
    std::regex url_format{"^(http://www.|https://www.|http://https://)?[a-z0-9]+([-.]{1}[a-z0-9]+)*.[a-z]{2,5}(:[0-9]{1,5})?(/.*)?$"};
    std::regex genre{"^(action|drama|crime|comedy|adventure|romance|thriller|horror|western|sf)?([|](action|drama|crime|comedy|adventure|romance|thriller|horror|western|sf))*"};

    if (movie.getId() < 0)
        errorBuffer << "Invalid id: must be a positive integer!\n";
    if (movie.getTitle().empty())
        errorBuffer << "Invalid title : can't be an empty string!\n";
    if (movie.getYear() < 1888)
        errorBuffer << "Invalid year : fun fact - the earliest surviving motion-picture film dates to 1888\n";
    if (!std::regex_match(movie.getGenre(), genre))
        errorBuffer << "Invalid genre!\n";
    if (!std::regex_match(movie.getUrl(), url_format))
        errorBuffer << "Invalid link format!\n";

    if (!errorBuffer.str().empty())
        throw ValidationException(errorBuffer.str());
}
