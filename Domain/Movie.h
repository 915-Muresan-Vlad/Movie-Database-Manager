#ifndef LOCAL_MOVIE_DATABASE_MOVIE_H
#define LOCAL_MOVIE_DATABASE_MOVIE_H

#include <iostream>
#include <string>
#include <vector>

class Movie
{
public:
    Movie();

    explicit Movie(int id);

    Movie(int id, const std::string& title, int year, const std::string& genre, int likes, const std::string& url);

    // ================================================== getters ======================================================

    int getId() const;

    int getYear() const;

    int getLikes() const;

    const std::string &getTitle() const;

    const std::string &getGenre() const;

    const std::string &getUrl() const;

    // ================================================== setters ======================================================

    void setYear(int year);

    void setLikes(int likes);

    void setTitle(const std::string &title);

    void setGenre(const std::string &genre);

    void setUrl(const std::string &url);

    // ============================================= operator overloading ==============================================

    bool operator == (const Movie& movie) const;

    friend std::ostream& operator << (std::ostream& os, const Movie& movie);

    friend std::istream& operator >> (std::istream& is, std::pair<Movie&, const std::string&> movie_and_format);

    // ============================================== reading by format ================================================

    void readCsvRow(std::istream &is, char delimiter = ',');

    void readHtmlTableRow(std::istream &is);

    // =============================================== printing formats ================================================

    static std::string consoleTableHeaderStub();
    static std::string htmlTableHeaderStub();

    std::string consoleTablePrettyPrint() const;

    std::string htmlTableRowPrettyPrint() const;

    std::string csvPrettyPrint(char delimiter = ',') const;

private:
    // =============================================== input processing ================================================

    static std::vector<std::string> tokenizeFromCsv(std::string& line, char delimiter);
    static std::vector<std::string> tokenizeFromHtml(const std::vector<std::string>& lines);

    // ============================================== output processing ================================================

    struct my_format : public std::numpunct<char>
    {
        explicit my_format(size_t refs = 0) : std::numpunct<char>(refs) {}
        char do_thousands_sep() const override { return '.'; }
        std::string do_grouping() const override { return "\003"; }
    };
    static std::string commaSepNumFormat(int number);

private:
    int _id{};
    int _year{};
    int _likes{};
    std::string _title;
    std::string _genre;
    std::string _url;
};


#endif //LOCAL_MOVIE_DATABASE_MOVIE_H
