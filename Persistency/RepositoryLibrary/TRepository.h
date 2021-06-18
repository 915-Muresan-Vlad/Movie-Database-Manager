#ifndef LOCAL_MOVIE_DATABASE_TREPOSITORY_H
#define LOCAL_MOVIE_DATABASE_TREPOSITORY_H

#include <vector>

template<class TElem>
class TRepository
{
public:
    TRepository()= default;
    virtual ~TRepository() = default;

    /// \description Adds an element
    /// \param TElem
    virtual void add(const TElem&) = 0;

    /// \description Removes an element
    /// \param TElem
    virtual void remove(const TElem&) = 0;

    /// \description Updates an element
    /// \param TElem
    virtual void update(const TElem&) = 0;

    /// \description Searched for an element
    /// \param TElem
    /// \return TElem \verbatim if the element is found \endverbatim
    virtual const TElem& search(const TElem&) = 0;

private:
    /// representation
};

#endif //LOCAL_MOVIE_DATABASE_TREPOSITORY_H
