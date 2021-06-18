#ifndef LOCAL_MOVIE_DATABASE_HTMLMOVIESREPOSITORY_H
#define LOCAL_MOVIE_DATABASE_HTMLMOVIESREPOSITORY_H

#include "../../RepositoryLibrary/FileTRepository.h"
#include "../../../Domain/Movie.h"


class HtmlMoviesRepository : public FileTRepository<Movie>
{
public:
    explicit HtmlMoviesRepository(const std::string& filename);

    void add(const Movie &movie) override;

    void remove(const Movie &movie) override;

    void update(const Movie &movie) override;

    const Movie &search(const Movie &movie) override;

    const std::vector<Movie> &getAll() override;

    int len() const override;

    void fReadAll() override;

    void fWriteAll() override;

private:
    static std::string tableHtmlHeader();
    static std::string closingHtmlHeader();
};


#endif //LOCAL_MOVIE_DATABASE_HTMLMOVIESREPOSITORY_H
