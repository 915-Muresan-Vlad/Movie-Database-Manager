#include <sstream>
#include <fstream>
#include "HtmlMoviesRepository.h"


HtmlMoviesRepository::HtmlMoviesRepository(const std::string &filename) : FileTRepository<Movie>(filename)
{
    HtmlMoviesRepository::fReadAll();
}

void HtmlMoviesRepository::add(const Movie &movie)
{
    FileTRepository<Movie>::add(movie);
    this->fWriteAll();
}

void HtmlMoviesRepository::remove(const Movie &movie)
{
    FileTRepository<Movie>::remove(movie);
    this->fWriteAll();
}

void HtmlMoviesRepository::update(const Movie &movie)
{
    FileTRepository<Movie>::update(movie);
    this->fWriteAll();
}

const Movie &HtmlMoviesRepository::search(const Movie &movie)
{
    return FileTRepository<Movie>::search(movie);
}

const std::vector<Movie> &HtmlMoviesRepository::getAll()
{
    return FileTRepository<Movie>::getAll();
}

int HtmlMoviesRepository::len() const
{
    return FileTRepository<Movie>::len();
}

void HtmlMoviesRepository::fReadAll()
{
    std::ifstream fin{this->getFilename(), std::ios::in};
    std::string redundant_line;
    if (fin.is_open())
    {
        while (std::getline(fin, redundant_line))
            if(redundant_line.find("</tr>") != std::string::npos)
                break;

        for (const auto& elem : this->getAll())
            this->remove(elem);

        Movie elem;
        while(fin >> std::pair<Movie&, std::string>(elem, "html"))
            InMemoryTRepository<Movie>::add(elem);

        fin.close();
    }
}

void HtmlMoviesRepository::fWriteAll()
{
    std::ofstream fout(this->getFilename(), std::ios::out);
    if (fout.is_open())
    {
        fout << tableHtmlHeader() << "\n";
        fout << Movie::htmlTableHeaderStub() << "\n";
        for (const auto& elem : this->getAll())
        {
            fout << elem.htmlTableRowPrettyPrint() << "\n";
        }
        fout << closingHtmlHeader() << "\n";
        fout.close();
    }
}

std::string HtmlMoviesRepository::tableHtmlHeader()
{
    std::stringstream ss;
    ss << "<!DOCTYPE html>" << "\n"
       << "<html>"  << "\n"
       << "<body>"  << "\n"
       << "<table border=\"1\">";

    return ss.str();
}

std::string HtmlMoviesRepository::closingHtmlHeader()
{
    std::stringstream ss;
    ss << "</table>" << "\n"
       << "</body>"  << "\n"
       << "</html>"  << "\n";

    return ss.str();
}
