#ifndef LOCAL_MOVIE_DATABASE_CUSTOMEXCEPTIONS_H
#define LOCAL_MOVIE_DATABASE_CUSTOMEXCEPTIONS_H


#include <exception>
#include <string>

class CustomExceptions : public std::exception
{
public:
    explicit CustomExceptions(const std::string &errorMessage);

    const char *what() const noexcept override;

private:
    std::string errorMessage;
};

class ValidationException : public CustomExceptions
{
public:
    explicit ValidationException(const std::string &errorMessage)
        : CustomExceptions("Validation Error: " + errorMessage) {}
};

class RepositoryException : public CustomExceptions
{
public:
    explicit RepositoryException(const std::string &errorMessage)
        : CustomExceptions("Repository Error: " + errorMessage) {}
};

#endif //LOCAL_MOVIE_DATABASE_CUSTOMEXCEPTIONS_H
