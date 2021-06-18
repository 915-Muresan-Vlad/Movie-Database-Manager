#include <Windows.h>
#include <iomanip>
#include "ConsoleUI.h"
#include "../Persistency/FILERepo/CSVRepo/CsvMoviesRepository.h"
#include "../Persistency/FILERepo/HTMLRepo/HtmlMoviesRepository.h"


ConsoleUI::ConsoleUI(MoviesLocalDBService &moviesService) : _moviesService(moviesService) {}


void ConsoleUI::run()
{
    if (this->setupRepositoryTypes())
        std::cout << "Data loaded succesfully" << "\n";
    else
    {
        std::cout << "Failed trying to load the data" << "\n";
        return;
    }

    while (true)
    {
        mainScreen();
        std::string command;
        std::cout << "Enter your choice: " << "\n";
        std::cin >> command;

        if (command == "x")
        {
            std::cout << "Good bye!\n";
            break;
        }

        try
        {
            int choice_number = stoi(command);
            switch (choice_number)
            {
                case 1:
                    this->uiAdminMode();
                    break;
                case 2:
                    this->uiUserMode();
                    break;
                default:
                    std::cout << "Invalid choice!" << "\n";
            }

        }
        catch (...)
        {
            std::cout << "Invalid input!" << "\n";
        }
    }
}


void ConsoleUI::uiAdminMode()
{
    std::string choice{0};
    while(true)
    {
        ConsoleUI::adminScreen();
        std::cin >> choice;

        if (choice == "x")
            break;

        try
        {
            int choice_number = stoi(choice);
            switch (choice_number)
            {
                case 1:
                    this->uiAddMovie();
                    break;
                case 2:
                    this->uiRemoveMovie();
                    break;
                case 3:
                    this->uiUpdateMovie();
                    break;
                case 4:
                    this->uiPrintAllMovies();
                    break;
                default:
                    std::cout << "Invalid choice!";
            }
        }
        catch (ValidationException &ve) {
            std::cout << ve.what() << "\n";
        }
        catch (RepositoryException &re) {
            std::cout << re.what() << "\n";
        }
        catch (...) {
            std::cout << "Invalid input!" << "\n";
        }
    }
}


void ConsoleUI::uiUserMode()
{
    while(true)
    {
        ConsoleUI::userScreen();
        std::string choice;
        std::cin >> choice;

        if (choice == "x")
            break;
        try
        {
            int choice_number = stoi(choice);
            switch (choice_number)
            {
                case 1:
                    this->browseMovies();
                    break;
                case 2:
                    this->listWatchlist();
                    break;
                case 3:
                    this->openInApp();
                    break;
                default:
                    std::cout << "Invalid choice!" << "\n";
            }
        }
        catch(...)
        {
            std::cout << "Invalid input!" << "\n";
        }
    }
}


void ConsoleUI::uiAddMovie()
{
    std::cout << "\n\n------------------------------------- ADMIN - add movie -------------------------------------\n\n";
    std::string id_str, title, year_str, genre, likes_str, trailer;
    int id, year, likes;

    std::cout << "Enter movie id: " << std::endl;
    std::cin >> id_str;

    try
    {
        id = stoi(id_str);
    }
    catch (...)
    {
        std::cout << "Invalid input for id (expected positive integer)" << "\n";
        return;
    }


    std::cout << "Enter movie title: " << std::endl;
    std::cin.get();
    std::getline(std::cin, title);

    std::cout << "Enter release year: " << std::endl;
    std::cin >> year_str;

    try
    {
        year = stoi(year_str);
    }
    catch (...)
    {
        std::cout << "Invalid input for year (expected positive integer)" << "\n";
        return;
    }

    std::cout << "Enter movie's genre: " << std::endl;
    std::cin >> genre;

    std::cout << "Enter number of likes: " << std::endl;
    std::cin >> likes_str;

    try
    {
        likes = stoi(likes_str);
    }
    catch (...)
    {
        std::cout << "Invalid input for number of likes (expected integer)" << "\n";
        return;
    }

    std::cout << "Enter trailer: " << std::endl;
    std::cin >> trailer;

    this->_moviesService.addMovie(id, title, year, genre, likes, trailer);
    std::cout << "Movie added successfully!" << "\n";
}


void ConsoleUI::uiRemoveMovie()
{
    std::cout << "\n\n------------------------------------ ADMIN - delete movie -----------------------------------\n\n";

    std::string id_str;
    int id;

    std::cout << "Enter movie id: " << std::endl;
    std::cin >> id_str;

    try
    {
        id = stoi(id_str);
    }
    catch (...)
    {
        std::cout << "Invalid input for id (expected positive integer)" << "\n";
        return;
    }

    this->_moviesService.deleteMovie(id);
    std::cout << "Movie removed successfully!" << "\n";
}


void ConsoleUI::uiUpdateMovie()
{
    std::cout << "\n\n----------------------------------- ADMIN - update movie ------------------------------------\n\n";
    std::string id_str;
    int id;

    std::cout << "Enter movie id: " << std::endl;
    std::cin >> id_str;

    try
    {
        id = stoi(id_str);
    }
    catch (...)
    {
        std::cout << "Invalid input for id (expected positive integer)" << "\n";
        return;
    }

    Movie movie = this->_moviesService.searchById(id);
    std::cout << movie.consoleTablePrettyPrint() << "\n";

    std::cout << "What do you want to update?" << "\n";
    std::cout << "[1] Title"            << "\n";
    std::cout << "[2] Release year"     << "\n";
    std::cout << "[3] Genre"            << "\n";
    std::cout << "[4] Number of likes"  << "\n";
    std::cout << "[5] Trailer url"      << "\n";
    std::cout << "[s] Save changes"     << "\n";

    std::string choice;
    std::string title = movie.getTitle();
    std::string genre = movie.getGenre();
    std::string trailer = movie.getUrl();
    int year = movie.getYear();
    int likes = movie.getLikes();
    std::string year_str;
    std::string likes_str;

    while (true)
    {
        std::cout << "Update:" << std::endl;
        std::cin >> choice;

        if (choice == "s")
            break;

        int choice_num;
        try
        {
            choice_num = stoi(choice);

            switch (choice_num)
            {
                case 1:
                    std::cout << "Enter new title" << "\n";
                    std::cin.get();
                    std::getline(std::cin, title);
                    break;
                case 2:
                    std::cout << "Enter new year" << "\n";
                    std::cin >> year_str;
                    break;
                case 3:
                    std::cout << "Enter new genre" << "\n";
                    std::cin >> genre;
                    break;
                case 4:
                    std::cout << "Enter new number of likes" << "\n";
                    std::cin >> likes_str;
                    break;
                case 5:
                    std::cout << "Enter new trailer url" << "\n";
                    std::cin >> trailer;
                    break;
                default:
                    std::cout << "Invalid choice" << "\n";
            }
        }
        catch (...)
        {
            std::cout << "Invalid choice input type" << "\n";
        }
    }

    if (!year_str.empty())
    {
        try
        {
            int updated_year = stoi(year_str);
            year = updated_year;
        }
        catch (...)
        {
            std::cout << "Invalid input type for year" << "\n";
        }
    }

    if (!likes_str.empty())
    {
        try
        {
            int updated_likes = stoi(likes_str);
            likes = updated_likes;
        }
        catch (...)
        {
            std::cout << "Invalid input type for number of likes" << "\n";
        }
    }

    this->_moviesService.updateMovie(id, title, year, genre, likes, trailer);
    std::cout << "Movie updated successfully!" << "\n";
}


void ConsoleUI::uiPrintAllMovies()
{
    std::cout << Movie::consoleTableHeaderStub() << "\n";
    for (const auto& elem : this->_moviesService.getAllMovies())
        std::cout << elem.consoleTablePrettyPrint() << "\n";
}


void ConsoleUI::browseMovies()
{
    std::string genre;
    std::cout << "Browse by genre:" << "\n";
    std::cin >> genre;
    std::cin.get();

    std::vector<Movie> filteredMovies = this->_moviesService.filterByGenre(genre);

    if (filteredMovies.empty())
    {
        std::cout << "No movies with this genre in the database at the moment" << "\n";
        return;
    }

    std::cout << "Browsing for " << genre << " movies..." << "\n";
    std::cout << "(type x to stop)" << "\n";
    std::string browsing_state;
    std::string choice;

    for (int i = 0; i < filteredMovies.size(); ++i)
    {
        browsing_state = "";
        choice = "";

        std::cout << filteredMovies[i].consoleTablePrettyPrint() << "\n";
        std::cout << std::setw(filteredMovies[i].consoleTablePrettyPrint().length() -
                                (std::to_string(filteredMovies.size()).size() * 2))
                  << (i+1) << "/" << filteredMovies.size() << "\n";

        std::cout << "Do you add this movie to your watchlist? (Y/n)" << "\n";
        std::getline(std::cin, choice);

        if (choice == "y")
        {
            try
            {
                this->_moviesService.addToWatchlist(filteredMovies[i].getId());
                std::cout << filteredMovies[i].getTitle() << " added to you watchlist!" << "\n";
            }
            catch (RepositoryException& re)
            {
                std::cout << filteredMovies[i].getTitle() << " already in the watchlist" << "\n";
            }
        }

        std::cout << "Next ->\n";
        std::getline(std::cin, browsing_state);
        if (browsing_state == "x")
            return;

        if (i == filteredMovies.size() - 1)
        {
            std::cout << "Reached the end of the selection" << "\n";
            std::cout << "Back to the top!" << "\n\n";
            i = -1;
        }
    }
}


void ConsoleUI::listWatchlist()
{
    std::cout << Movie::consoleTableHeaderStub() << "\n";
    for (const auto& elem : this->_moviesService.getWatchlist())
        std::cout << elem.consoleTablePrettyPrint() << "\n";
    std::string choice;

    while (true)
    {
        std::cout << "Want to remove any movie from watchlist? (y/n)" << "\n";
        std::cin >> choice;
        if (choice == "y")
        {
            std::string id_str;
            int id;
            bool liked = false;

            std::cout << "Enter movie id: " << std::endl;
            std::cin >> id_str;

            try
            {
                id = stoi(id_str);
            }
            catch (...)
            {
                std::cout << "Invalid input for id (expected positive integer)" << "\n";
                return;
            }

            std::cout << "Did you like the movie? (y/n)" << "\n";
            std::string liked_choice;
            std::cin >> liked_choice;
            if (liked_choice == "y")
                liked = true;

            this->_moviesService.deleteFromWatchlist(id, liked);
        }
        else break;
    }
}


bool ConsoleUI::setupRepositoryTypes()
{
    std::cout << "Configuring your app..." << "\n";
    while (true)
    {
        std::cout << "Chose the type of file you want to start:" << "\n";
        std::cout << "[1] CSV"      << "\n";
        std::cout << "[2] Html"     << "\n";

        std::string choice;
        std::cin >> choice;
        if (choice == "1")
        {
            this->_moviesService.setMoviesRepository(new CsvMoviesRepository("C:\\Users\\Asus\\Documents\\Facultate frate\\OOP\\Assignments\\Local Movie Database\\movies.csv"));
            this->_moviesService.setUserRepository(new CsvMoviesRepository("C:\\Users\\Asus\\Documents\\Facultate frate\\OOP\\Assignments\\Local Movie Database\\watchlist.csv"));

            this->fileType = "csv";

            return true;
        }
        if (choice == "2")
        {
            this->_moviesService.setMoviesRepository(new HtmlMoviesRepository("C:\\Users\\Asus\\Documents\\Facultate frate\\OOP\\Assignments\\Local Movie Database\\movies.html"));
            this->_moviesService.setUserRepository(new HtmlMoviesRepository("C:\\Users\\Asus\\Documents\\Facultate frate\\OOP\\Assignments\\Local Movie Database\\watchlist.html"));

            this->fileType = "html";

            return true;
        }
        else std::cout << "Invalid choice!" << "\n";
    }
}


void ConsoleUI::mainScreen()
{
    std::cout << "\n\n-------------------------- Local Movie Database ---------------------------\n\n";
    std::cout << "Login as"  << "\n";
    std::cout << "[1] Admin" << "\n";
    std::cout << "[2] User"  << "\n";
    std::cout << "[x] exit"  << "\n\n\n";
}


void ConsoleUI::adminScreen()
{
    std::cout << "\n\n------------------------------ Admin mode --------------------------------\n\n";
    std::cout << "Actions:" << "\n";
    std::cout << "[1] Add new movie"        << "\n";
    std::cout << "[2] Delete movie"         << "\n";
    std::cout << "[3] Update movie"         << "\n";
    std::cout << "[4] Print all movies"     << "\n";
    std::cout << "[x] exit to main screen"  << "\n";
}


void ConsoleUI::userScreen()
{
    std::cout << "\n\n------------------------------- User mode --------------------------------\n\n";
    std::cout << "[1] Browse movie by genre"            << "\n";
    std::cout << "[2] Watchlist"                        << "\n";
    std::cout << "[3] Open watchlist in designated app" << "\n";
    std::cout << "[x] exit to main screen"              << "\n";
}

void ConsoleUI::openInApp()
{
    if (this->fileType == "csv")
        ShellExecuteA(nullptr, nullptr,
                      R"(C:\Users\Asus\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\WPS Office\WPS Office)",
                      R"("C:\Users\Asus\Documents\Facultate frate\OOP\Assignments\Local Movie Database\watchlist.csv")",
                      nullptr, SW_SHOWMAXIMIZED);
    else if (this->fileType == "html")
        ShellExecuteA(nullptr, nullptr,
                  R"(C:\ProgramData\Microsoft\Windows\Start Menu\Programs\Brave)",
                  R"("C:\Users\Asus\Documents\Facultate frate\OOP\Assignments\Local Movie Database\watchlist.html")",
                  nullptr, SW_SHOWMAXIMIZED);
}
