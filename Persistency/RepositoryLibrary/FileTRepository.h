#ifndef LOCAL_MOVIE_DATABASE_FILETREPOSITORY_H
#define LOCAL_MOVIE_DATABASE_FILETREPOSITORY_H

#include <string>
#include "InMemoryTRepository.h"

template <class TElem>
class FileTRepository : public InMemoryTRepository<TElem>
{
public:

    explicit FileTRepository(const std::string &filename) : _filename(filename) {}

    // ============================================  file specific methods =============================================

    virtual void fReadAll() = 0;

    virtual void fWriteAll() = 0;

    const std::string &getFilename() const;

private:
    std::string _filename;
};

template<class TElem>
const std::string &FileTRepository<TElem>::getFilename() const
{
    return this->_filename;
}


#endif //LOCAL_MOVIE_DATABASE_FILETREPOSITORY_H
