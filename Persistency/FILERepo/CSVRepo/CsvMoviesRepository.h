#ifndef LOCAL_MOVIE_DATABASE_CSVMOVIESREPOSITORY_H
#define LOCAL_MOVIE_DATABASE_CSVMOVIESREPOSITORY_H

#include "../../RepositoryLibrary/FileTRepository.h"
#include "../../../Domain/Movie.h"

class CsvMoviesRepository : public FileTRepository<Movie>
{
public:
    explicit CsvMoviesRepository(const std::string& filename);

    void add(const Movie &movie) override;

    void remove(const Movie &movie) override;

    void update(const Movie &movie) override;

    const Movie &search(const Movie &movie) override;

    const std::vector<Movie> &getAll() override;

    int len() const override;

    void fReadAll() override;
    void fWriteAll() override;
};


#endif //LOCAL_MOVIE_DATABASE_CSVMOVIESREPOSITORY_H
