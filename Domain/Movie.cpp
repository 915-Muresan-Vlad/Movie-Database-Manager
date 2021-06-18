#include "Movie.h"
#include <cmath>
#include <sstream>
#include <iomanip>
#include <locale>

Movie::Movie() = default;

Movie::Movie(int id) : _id(id) {}

Movie::Movie(int id, const std::string& title, int year, const std::string& genre, int likes, const std::string& url) :
    _id{id},
    _title{title},
    _year{year},
    _genre{genre},
    _likes{likes},
    _url{url}
    {}

// ====================================================== getters ======================================================

int Movie::getId() const
{
    return _id;
}

int Movie::getYear() const
{
    return _year;
}

int Movie::getLikes() const
{
    return _likes;
}

const std::string &Movie::getTitle() const
{
    return _title;
}

const std::string &Movie::getGenre() const
{
    return _genre;
}

const std::string &Movie::getUrl() const
{
    return _url;
}

// ====================================================== setters ======================================================

void Movie::setYear(int year)
{
    _year = year;
}

void Movie::setLikes(int likes)
{
    _likes = likes;
}

void Movie::setTitle(const std::string &title)
{
    _title = title;
}

void Movie::setGenre(const std::string &genre)
{
    _genre = genre;
}

void Movie::setUrl(const std::string &url)
{
    _url = url;
}

// =============================================== operator overloading ================================================

bool Movie::operator==(const Movie& movie) const
{
    return _id == movie._id;
}

std::ostream &operator << (std::ostream& os, const Movie& movie)
{
    os << "id: "      << movie._id        << "\n"
       << "title: "   << movie._title     << "\n"
       << "year: "    << movie._year      << "\n"
       << "genre: "   << movie._genre     << "\n"
       << "likes: "   << movie._likes     << "\n"
       << "url: "     << movie._url;
    return os;
}

std::istream &operator >> (std::istream& is, std::pair<Movie& , const std::string&> movie_and_format)
{
    Movie& movie = movie_and_format.first;
    const std::string& format = movie_and_format.second;

    if (format == "csv")
        movie.readCsvRow(is);
    else if (format == "html")
        movie.readHtmlTableRow(is);

    return is;
}

// ============================================== reading by format ================================================

void Movie::readCsvRow(std::istream &is, char delimiter)
{
    std::string line;
    std::getline(is, line);

    std::vector<std::string> tokens = Movie::tokenizeFromCsv(line, delimiter);

    if (tokens.size() != 6)
        return;

    this->_id = std::stoi(tokens[0]);
    this->_title = tokens[1];
    this->_year = std::stoi(tokens[2]);
    this->_genre = tokens[3];
    this->_likes = std::stoi(tokens[4]);
    this->_url = tokens[5];
}

void Movie::readHtmlTableRow(std::istream &is)
{
    std::string line;
    std::vector<std::string> lines{};

    while (std::getline(is, line))
        if(line.find("<tr>") != std::string::npos)
        {
            while (std::getline(is, line))
                if (line.find("</tr>") != std::string::npos)
                    break;
                else lines.push_back(line);

            break;
        }

    std::vector<std::string> tokens = Movie::tokenizeFromHtml(lines);

    if (tokens.size() != 6)
        return;

    this->_id = std::stoi(tokens[0]);
    this->_title = tokens[1];
    this->_year = std::stoi(tokens[2]);
    this->_genre = tokens[3];
    this->_likes = std::stoi(tokens[4]);
    this->_url = tokens[5];
}

// ================================================= printing formats ==================================================


std::string Movie::consoleTableHeaderStub()
{
    std::stringstream ss;

    ss << std::setw(4)   << std::left << "ID"      << " | "
       << std::setw(30)  << std::left << "Title"   << " | "
       << std::setw(4)   << std::left << "year"    << " | "
       << std::setw(20)  << std::left << "Genre"   << " | "
       << std::setw(10)  << std::left << "likes"   << " | "
       << "Trailer" ;

    return ss.str();
}

std::string Movie::consoleTablePrettyPrint() const
{
    std::stringstream ss;

    ss << std::setw(4)   << std::left << this->_id    << " | "
       << std::setw(30)  << std::left << this->_title << " | "
       << std::setw(4)   << std::left << this->_year  << " | "
       << std::setw(20)  << std::left << this->_genre << " | "
       << std::setw(10)  << std::right << Movie::commaSepNumFormat(this->_likes) << " | "
       << this->_url;

    return ss.str();
}

std::string Movie::csvPrettyPrint(char delimiter) const
{
    std::stringstream ss;

    ss << this->_id    << delimiter
       << this->_title << delimiter
       << this->_year  << delimiter
       << this->_genre << delimiter
       << this->_likes << delimiter
       << this->_url;

    return ss.str();
}

std::string Movie::htmlTableRowPrettyPrint() const
{
    std::stringstream ss;

    ss << "\t" << "<tr>" << "\n";
    ss << "\t\t" << "<td>" << this->_id << "</td>" << "\n";
    ss << "\t\t" << "<td>" << this->_title << "</td>" << "\n";
    ss << "\t\t" << "<td>" << this->_year << "</td>" << "\n";
    ss << "\t\t" << "<td>" << this->_genre << "</td>" << "\n";
    ss << "\t\t" << "<td>" << this->_likes << "</td>" << "\n";
    ss << "\t\t" << "<td><a href=\"" << this->_url << "\">" << "trailer" << "</a></td>" << "\n";
    ss << "\t" << "</tr>";

    return ss.str();
}

// =============================================== input processing ================================================s

std::vector<std::string> Movie::tokenizeFromCsv(std::string& line, char delimiter)
{
    std::stringstream ss(line);

    std::vector<std::string> result;
    std::string token;
    while (std::getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

std::vector<std::string> Movie::tokenizeFromHtml(const std::vector<std::string>& lines)
{
    std::vector<std::string> tokens{};
    std::string token;

    for (const std::string& line : lines)
    {
        unsigned long long start_pos = 0;
        unsigned long long len_substr = 0;
        if (line.find("<a href=\"") != std::string::npos)
        {
            start_pos = line.find("<a href=\"") + 9;
            len_substr = line.find("\">") - start_pos;
        }
        else
        {
            start_pos = line.find("<td>") + 4;
            len_substr = line.find("</td>") - start_pos;
        }

        token = line.substr(start_pos, len_substr);

        if (!token.empty())
            tokens.push_back(token);
    }

    return tokens;
}

// ============================================== output processing ================================================

std::string Movie::commaSepNumFormat(int number)
{
    std::stringstream ss;
    std::locale global;
    std::locale withGroupings(global, new my_format);
    ss.imbue(withGroupings);

    ss << number;
    return ss.str();
}

std::string Movie::htmlTableHeaderStub()
{
    std::stringstream ss;

    ss << "\t" << "<tr>" << "\n";
    ss << "\t\t" << "<td>" << "ID" << "</td>" << "\n";
    ss << "\t\t" << "<td>" << "Title" << "</td>" << "\n";
    ss << "\t\t" << "<td>" << "Year" << "</td>" << "\n";
    ss << "\t\t" << "<td>" << "Genre" << "</td>" << "\n";
    ss << "\t\t" << "<td>" << "Likes" << "</td>" << "\n";
    ss << "\t\t" << "<td>" << "Trailer" << "</td>" << "\n";
    ss << "\t" << "</tr>";

    return ss.str();
}

