#include "CsvMoviesRepository.h"
#include <fstream>

CsvMoviesRepository::CsvMoviesRepository(const std::string &filename) : FileTRepository<Movie>(filename)
{
    CsvMoviesRepository::fReadAll();
}

void CsvMoviesRepository::add(const Movie &movie)
{
    FileTRepository<Movie>::add(movie);
    this->fWriteAll();
}

void CsvMoviesRepository::remove(const Movie &movie)
{
    FileTRepository<Movie>::remove(movie);
    this->fWriteAll();
}

void CsvMoviesRepository::update(const Movie &movie)
{
    FileTRepository<Movie>::update(movie);
    this->fWriteAll();
}

const Movie &CsvMoviesRepository::search(const Movie &movie)
{
    return FileTRepository<Movie>::search(movie);
}

const std::vector<Movie> &CsvMoviesRepository::getAll()
{
    return FileTRepository<Movie>::getAll();
}

int CsvMoviesRepository::len() const
{
    return FileTRepository<Movie>::len();
}

void CsvMoviesRepository::fReadAll()
{
    std::ifstream fin(this->getFilename(), std::ios::in);
    if (fin.is_open())
    {
        for (const auto& elem : this->getAll())
            this->remove(elem);

        Movie elem;
        while(fin >> std::pair<Movie&, std::string>(elem, "csv"))
            InMemoryTRepository<Movie>::add(elem);

        fin.close();
    }
}

void CsvMoviesRepository::fWriteAll()
{
    std::ofstream fout(this->getFilename(), std::ios::out);
    if (fout.is_open())
    {
        for (const auto& elem : this->getAll())
        {
            fout << elem.csvPrettyPrint() << "\n";
        }
        fout.close();
    }
}
