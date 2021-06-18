#ifndef LOCAL_MOVIE_DATABASE_INMEMORYTREPOSITORY_H
#define LOCAL_MOVIE_DATABASE_INMEMORYTREPOSITORY_H

#include <algorithm>
#include "TRepository.h"
#include "../../Errors/CustomExceptions.h"

template<class TElem>
class InMemoryTRepository : public TRepository<TElem>
{
public:
    InMemoryTRepository() = default;
    virtual ~InMemoryTRepository() = default;

    virtual void add(const TElem &) override;

    virtual void remove(const TElem &) override;

    virtual void update(const TElem &) override;

    virtual const TElem &search(const TElem &) override;

    virtual const std::vector<TElem> &getAll();

    virtual int len() const;

private:
    std::vector<TElem> _elements;
};

template<class TElem>
void InMemoryTRepository<TElem>::add(const TElem& elem)
{
    auto it = std::find(this->_elements.begin(), this->_elements.end(), elem);
    if (it != this->_elements.end())
        throw RepositoryException("The element already exists in the list!\n");
    this->_elements.push_back(elem);
}

template<class TElem>
void InMemoryTRepository<TElem>::remove(const TElem& elem)
{
    auto it = std::find(this->_elements.begin(), this->_elements.end(), elem);
    if (it == this->_elements.end())
        throw RepositoryException("The element doesnt exists in the list!\n");

    this->_elements.erase(it);
}

template<class TElem>
void InMemoryTRepository<TElem>::update(const TElem& elem)
{
    auto it = std::find(this->_elements.begin(), this->_elements.end(), elem);
    if (it == this->_elements.end())
        throw RepositoryException("The element doesnt exists in the list!\n");
    this->_elements[it - this->_elements.begin()] = elem;
}

template<class TElem>
const TElem &InMemoryTRepository<TElem>::search(const TElem& elem)
{
    auto it = std::find(this->_elements.begin(), this->_elements.end(), elem);
    if (it == this->_elements.end())
        throw RepositoryException("The element doesnt exists in the list!\n");
    return *it;
}

template<class TElem>
int InMemoryTRepository<TElem>::len() const
{
    return this->_elements.size();
}

template<class TElem>
const std::vector<TElem> &InMemoryTRepository<TElem>::getAll()
{
    return this->_elements;
}


#endif //LOCAL_MOVIE_DATABASE_INMEMORYTREPOSITORY_H
