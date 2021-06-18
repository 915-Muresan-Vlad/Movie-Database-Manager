#include <QtWidgets>
#include <windows.h>
#include "GUI.h"
#include "../Persistency/FILERepo/CSVRepo/CsvMoviesRepository.h"
#include "../Persistency/FILERepo/HTMLRepo/HtmlMoviesRepository.h"


GUI::GUI(MoviesLocalDBService& service, QWidget *parent): QMainWindow(parent), _moviesService{service}
{
    this->setupStartScreenGUI();
    this->connectSignalSlots();
}

void GUI::connectSignalSlots()
{
    QObject::connect(this->confirmPushBtn, &QPushButton::clicked, this, &GUI::confirmRepositoryTypeChoice);
}

void GUI::setupLoginScreen()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("Local Movie Database: LOG IN"));

    this->resize(400, 450);
    this->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

    verticalLayoutWidget = new QWidget(this);
    verticalLayoutWidget->setGeometry(QRect(20, 20, 351, 381));

    verticalLayout = new QVBoxLayout(verticalLayoutWidget);
    verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    auto *adminChoiceHLayout = new QHBoxLayout();
    auto *userChoiceHLayout = new QHBoxLayout();

    loginTitleLabel = new QLabel(verticalLayoutWidget);
    adminModePushBtn = new QPushButton(verticalLayoutWidget);
    userModePushBtn = new QPushButton(verticalLayoutWidget);

    QSizePolicy TitleLbl_SPolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    TitleLbl_SPolicy.setHeightForWidth(loginTitleLabel->sizePolicy().hasHeightForWidth());
    loginTitleLabel->setSizePolicy(TitleLbl_SPolicy);
    QFont font;
    font.setFamily(QString::fromUtf8("Malgun Gothic Semilight"));
    font.setPointSize(30);
    font.setBold(true);
    loginTitleLabel->setFont(font);
    loginTitleLabel->setAlignment(Qt::AlignCenter);
    loginTitleLabel->setText(QString::fromUtf8("Log In"));

    QSizePolicy LoginModeBtnSPolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);

    LoginModeBtnSPolicy.setHeightForWidth(adminModePushBtn->sizePolicy().hasHeightForWidth());
    adminModePushBtn->setSizePolicy(LoginModeBtnSPolicy);
    QPixmap pixmap_admin(R"(C:\Users\Asus\Documents\GitHub\OOP\a89-915-Muresan-Vlad\Local Movie Database\cmake-build-debug\admin.png)");
    QIcon adminModePushBtn_Icon(pixmap_admin);
    adminModePushBtn->setIcon(adminModePushBtn_Icon);
    adminModePushBtn->setIconSize(pixmap_admin.rect().size()/4);


    LoginModeBtnSPolicy.setHeightForWidth(userModePushBtn->sizePolicy().hasHeightForWidth());
    userModePushBtn->setSizePolicy(LoginModeBtnSPolicy);
    QPixmap pixmap_user(R"(C:\Users\Asus\Documents\GitHub\OOP\a89-915-Muresan-Vlad\Local Movie Database\cmake-build-debug\user.png)");
    QIcon userModePushBtn_Icon(pixmap_user);
    userModePushBtn->setIcon(userModePushBtn_Icon);
    userModePushBtn->setIconSize(pixmap_user.rect().size()/4);


    auto *adminChoice_h_spacer_l = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    auto *adminChoice_h_spacer_r = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    auto *userChoice_h_spacer_l = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    auto *userChoice_h_spacer_r = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);


    adminChoiceHLayout->addItem(adminChoice_h_spacer_l);
    adminChoiceHLayout->addWidget(adminModePushBtn);
    adminChoiceHLayout->addItem(adminChoice_h_spacer_r);

    userChoiceHLayout->addItem(userChoice_h_spacer_l);
    userChoiceHLayout->addWidget(userModePushBtn);
    userChoiceHLayout->addItem(userChoice_h_spacer_r);

    verticalLayout->addWidget(loginTitleLabel, 0, Qt::AlignHCenter);
    verticalLayout->addLayout(adminChoiceHLayout);
    verticalLayout->addLayout(userChoiceHLayout);

    QObject::connect(this->adminModePushBtn, &QPushButton::clicked, this, &GUI::loggedInAsAdmin);
    QObject::connect(this->userModePushBtn, &QPushButton::clicked, this, &GUI::loggedInAsUser);

    this->setCentralWidget(verticalLayoutWidget);
}

void GUI::setupStartScreenGUI()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("Local Movie Database"));

    this->resize(400, 200);
    this->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

    this->fileChoiceGroupBox = new QGroupBox(this);
    this->fileChoiceGroupBox->setGeometry(QRect(0, 0, 400, 200));
    this->startScreenQueryLabel = new QLabel(this->fileChoiceGroupBox);
    this->startScreenQueryLabel->setGeometry(QRect(70, 30, 281, 41));

    QFont font("Helvetica");
    font.setPointSize(12);
    font.setBold(true);
    this->startScreenQueryLabel->setFont(font);
    this->startScreenQueryLabel->setText(QString::fromUtf8("Chose the file format for the input"));

    this->csvRdBtn = new QRadioButton(this->fileChoiceGroupBox);
    this->csvRdBtn->setGeometry(QRect(60, 100, 85, 20));
    this->csvRdBtn->setText(QString::fromUtf8("CSV"));

    this->htmlRdBtn = new QRadioButton(this->fileChoiceGroupBox);
    this->htmlRdBtn->setText(QString::fromUtf8("HTML"));
    this->htmlRdBtn->setGeometry(QRect(290, 100, 85, 20));

    this->confirmPushBtn = new QPushButton(this->fileChoiceGroupBox);
    this->confirmPushBtn->setGeometry(QRect(160, 130, 91, 31));
    this->confirmPushBtn->setText(QString::fromUtf8("Confirm"));
    this->setCentralWidget(fileChoiceGroupBox);
}

void GUI::setupAdminGui()
{
    this->resize(1000, 550);
    this->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

    verticalLayoutWidget1 = new QWidget(this);

    verticalLayout1 = new QVBoxLayout(verticalLayoutWidget1);
    topBarHLayout = new QHBoxLayout(verticalLayoutWidget1);
    centralDataHLayout = new QHBoxLayout(verticalLayoutWidget1);
    auto* data_and_actions_vLayout = new QVBoxLayout(verticalLayoutWidget1);
    auto* data_form_layout = new QFormLayout(verticalLayoutWidget1);

    titleLbl = new QLabel(verticalLayoutWidget1);
    backToLoginPushBtn = new QPushButton(verticalLayoutWidget1);
    moviesList =  new QTableWidget(verticalLayoutWidget1);
    movieDetailsGBox = new QGroupBox(verticalLayoutWidget1);
    movieActionsGBox = new QGroupBox(verticalLayoutWidget1);

    id_lineEdit = new QLineEdit(verticalLayoutWidget1);
    title_lineEdit = new QLineEdit(verticalLayoutWidget1);
    year_lineEdit = new QLineEdit(verticalLayoutWidget1);
    genre_lineEdit = new QLineEdit(verticalLayoutWidget1);
    likes_lineEdit = new QLineEdit(verticalLayoutWidget1);
    url_lineEdit = new QLineEdit(verticalLayoutWidget1);

    QFont font;
    font.setFamily(QString::fromUtf8("Malgun Gothic Semilight"));
    font.setPointSize(12);
    font.setBold(true);
    titleLbl->setFont(font);
    titleLbl->setText(QString::fromUtf8("Movie database - admin"));

    backToLoginPushBtn->setText(QString::fromUtf8("back"));

    movieDetailsGBox->setTitle(QString::fromUtf8("Details"));
    movieActionsGBox->setTitle(QString::fromUtf8("Actions"));

    id_lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    id_lineEdit->setMaximumWidth(300);

    title_lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    title_lineEdit->setMaximumWidth(300);

    year_lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    year_lineEdit->setMaximumWidth(300);

    genre_lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    genre_lineEdit->setMaximumWidth(300);

    likes_lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    likes_lineEdit->setMaximumWidth(300);

    url_lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    url_lineEdit->setMaximumWidth(300);

    movieDetailsGBox->setLayout(data_form_layout);
    movieDetailsGBox->setMaximumWidth(300);

    data_form_layout->addRow("Id", id_lineEdit);
    data_form_layout->addRow("Title", title_lineEdit);
    data_form_layout->addRow("Year", year_lineEdit);
    data_form_layout->addRow("Genre", genre_lineEdit);
    data_form_layout->addRow("Likes", likes_lineEdit);
    data_form_layout->addRow("url", url_lineEdit);

    auto* actions_vLayout = new QVBoxLayout(movieActionsGBox);
    addMoviePushBtn =  new QPushButton(verticalLayoutWidget1);
    updateMoviePushBtn =  new QPushButton(verticalLayoutWidget1);
    removeMoviePushBtn =  new QPushButton(verticalLayoutWidget1);

    addMoviePushBtn->setText(QString::fromUtf8("add"));
    updateMoviePushBtn->setText(QString::fromUtf8("update"));
    removeMoviePushBtn->setText(QString::fromUtf8("remove"));

    actions_vLayout->addWidget(addMoviePushBtn);
    actions_vLayout->addWidget(updateMoviePushBtn);
    actions_vLayout->addWidget(removeMoviePushBtn);


    auto* topBar_h_spacer_m = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    topBarHLayout->addWidget(titleLbl);
    topBarHLayout->addItem(topBar_h_spacer_m);
    topBarHLayout->addWidget(backToLoginPushBtn);

    data_and_actions_vLayout->addWidget(movieDetailsGBox);
    data_and_actions_vLayout->addWidget(movieActionsGBox);


    centralDataHLayout->addWidget(moviesList);
    centralDataHLayout->addLayout(data_and_actions_vLayout);

    verticalLayout1->addLayout(topBarHLayout);
    verticalLayout1->addLayout(centralDataHLayout);

    QObject::connect(moviesList, &QTableWidget::itemSelectionChanged, this, [this]()
    {
            int selectedIndex = this->getSelectedIndex();

            if (selectedIndex < 0)
                return;

            Movie movie = this->_moviesService.getAllMovies()[selectedIndex];

            id_lineEdit->setText(QString::fromStdString(std::to_string(movie.getId())));
            title_lineEdit->setText(QString::fromStdString(movie.getTitle()));
            year_lineEdit->setText(QString::fromStdString(std::to_string(movie.getYear())));
            genre_lineEdit->setText(QString::fromStdString(movie.getGenre()));
            likes_lineEdit->setText(QString::fromStdString(std::to_string(movie.getLikes())));
            url_lineEdit->setText(QString::fromStdString(movie.getUrl()));
    });

    QObject::connect(backToLoginPushBtn, &QPushButton::clicked, this, &GUI::setupLoginScreen);

    QObject::connect(addMoviePushBtn, &QPushButton::clicked, this, &GUI::addMovie);
    QObject::connect(removeMoviePushBtn, &QPushButton::clicked, this, &GUI::removeMovie);
    QObject::connect(updateMoviePushBtn, &QPushButton::clicked, this, &GUI::updateMovie);

    this->setCentralWidget(verticalLayoutWidget1);
}

void GUI::setupUserGui()
{
    this->resize(800, 600);

    verticalLayoutWidget = new QWidget(this);
    verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
    verticalLayoutWidget->setGeometry(QRect(10, 10, 781, 571));
    mainLayoutUser = new QVBoxLayout(verticalLayoutWidget);
    mainLayoutUser->setObjectName(QString::fromUtf8("mainLayoutUser"));
    mainLayoutUser->setContentsMargins(0, 0, 0, 0);
    TopBarLayoutUser = new QHBoxLayout();
    titleLabel2 = new QLabel(verticalLayoutWidget);
    QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);

    sizePolicy.setHeightForWidth(titleLabel2->sizePolicy().hasHeightForWidth());
    titleLabel2->setSizePolicy(sizePolicy);

    TopBarLayoutUser->addWidget(titleLabel2);

    backpushbtn1 = new QPushButton(verticalLayoutWidget);

    TopBarLayoutUser->addWidget(backpushbtn1);


    mainLayoutUser->addLayout(TopBarLayoutUser);

    UserDataLayout = new QVBoxLayout();
    horizontalUserLyaout = new QHBoxLayout();
    verticatLayoutMoviesUser = new QVBoxLayout();
    MoviesLabel = new QLabel(verticalLayoutWidget);

    verticatLayoutMoviesUser->addWidget(MoviesLabel);

    MoviesTable = new QTableWidget(verticalLayoutWidget);

    verticatLayoutMoviesUser->addWidget(MoviesTable);

    GenreLineEdit = new QLineEdit(verticalLayoutWidget);

    verticatLayoutMoviesUser->addWidget(GenreLineEdit);

    filterPushBtn = new QPushButton(verticalLayoutWidget);

    verticatLayoutMoviesUser->addWidget(filterPushBtn);

    groupBox = new QGroupBox(verticalLayoutWidget);
    QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
    groupBox->setSizePolicy(sizePolicy1);
    verticalLayoutWidget_5 = new QWidget(groupBox);
    verticalLayoutWidget_5->setGeometry(QRect(0, 50, 371, 161));
    verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget_5);
    verticalLayout_5->setContentsMargins(0, 0, 0, 0);
    selected_movie_lbl1 = new QLabel(verticalLayoutWidget_5);

    verticalLayout_5->addWidget(selected_movie_lbl1);

    addToWatchlistbtn = new QPushButton(verticalLayoutWidget_5);

    verticalLayout_5->addWidget(addToWatchlistbtn);


    verticatLayoutMoviesUser->addWidget(groupBox);


    horizontalUserLyaout->addLayout(verticatLayoutMoviesUser);

    verticalLayoutWatchlistUser = new QVBoxLayout();
    watchlistLabel = new QLabel(verticalLayoutWidget);

    verticalLayoutWatchlistUser->addWidget(watchlistLabel);

    watchlistTable = new QTableWidget(verticalLayoutWidget);

    verticalLayoutWatchlistUser->addWidget(watchlistTable);

    groupBox_2 = new QGroupBox(verticalLayoutWidget);
    sizePolicy1.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
    groupBox_2->setSizePolicy(sizePolicy1);
    selected_movie_lbl2 = new QLabel(groupBox_2);
    selected_movie_lbl2->setGeometry(QRect(10, 30, 361, 71));
    likedCheckBox = new QCheckBox(groupBox_2);
    likedCheckBox->setGeometry(QRect(260, 150, 91, 41));
    removePushBtn = new QPushButton(groupBox_2);
    removePushBtn->setGeometry(QRect(20, 150, 181, 41));
    watchTrailerBtn = new QPushButton(groupBox_2);
    watchTrailerBtn->setGeometry(QRect(100, 200, 181, 41));

    QFont font;
    font.setFamily(QString::fromUtf8("Malgun Gothic Semilight"));
    font.setPointSize(12);
    font.setBold(true);
    titleLabel2->setFont(font);
    titleLabel2->setText(QString::fromUtf8("Movie database - user"));
    backpushbtn1->setText(QString::fromUtf8("back"));
    watchlistLabel->setText(QString::fromUtf8("Watchlist"));
    MoviesLabel->setText(QString::fromUtf8("Browse by genre"));
    removePushBtn->setText(QString::fromUtf8("Remove"));
    filterPushBtn->setText(QString::fromUtf8("Filter"));
    watchTrailerBtn->setText(QString::fromUtf8("Watch trailer"));
    addToWatchlistbtn->setText(QString::fromUtf8("Add to watchlist"));
    likedCheckBox->setText(QString::fromUtf8("Like"));

    verticalLayoutWatchlistUser->addWidget(groupBox_2);


    horizontalUserLyaout->addLayout(verticalLayoutWatchlistUser);


    UserDataLayout->addLayout(horizontalUserLyaout);


    mainLayoutUser->addLayout(UserDataLayout);


    this->setCentralWidget(verticalLayoutWidget);

    QObject::connect(backpushbtn1, &QPushButton::clicked, this, &GUI::setupLoginScreen);
    QObject::connect(filterPushBtn, &QPushButton::clicked, this, &GUI::populateMovieTable);
    QObject::connect(watchTrailerBtn, &QPushButton::clicked, this, &GUI::watchTrailer);
    QObject::connect(addToWatchlistbtn, &QPushButton::clicked, this, &GUI::addToWatchlist);
    QObject::connect(removePushBtn, &QPushButton::clicked, this, &GUI::removeFromWatchlist);

    QObject::connect(watchlistTable, &QTableWidget::itemSelectionChanged, this, [this]()
    {
        int selectedIndex = this->getSelectedIndexWatchlist();

        if (selectedIndex < 0)
            return;

        Movie movie = this->_moviesService.getWatchlist()[selectedIndex];
        selected_movie_lbl2->setText(QString::fromStdString(movie.getTitle()));
    });
    QObject::connect(MoviesTable, &QTableWidget::itemSelectionChanged, this, [this]()
    {
        int selectedIndex = this->getSelectedIndexMoviesTable();

        if (selectedIndex < 0)
            return;

        Movie movie = this->_moviesService.getAllMovies()[selectedIndex];
        selected_movie_lbl1->setText(QString::fromStdString(movie.getTitle()));
    });

}

void GUI::confirmRepositoryTypeChoice()
{
    std::string filesPath = R"(C:\Users\Asus\Documents\GitHub\OOP\a89-915-Muresan-Vlad\Local Movie Database\res\files)";

    if (this->csvRdBtn->isChecked())
    {
        delete this->confirmPushBtn;
        this->startScreenQueryLabel->setText(QString::fromUtf8("Loading csv files..."));

        this->_moviesService.setMoviesRepository(new CsvMoviesRepository(filesPath + "\\movies.csv"));
        this->_moviesService.setUserRepository(new CsvMoviesRepository(filesPath + "\\watchlist.csv"));

        this->setupLoginScreen();
    }
    else if (this->htmlRdBtn->isChecked())
    {
        delete this->confirmPushBtn;
        this->startScreenQueryLabel->setText(QString::fromUtf8("Loading html files..."));

        this->_moviesService.setMoviesRepository(new HtmlMoviesRepository(filesPath + "\\movies.html"));
        this->_moviesService.setUserRepository(new HtmlMoviesRepository(filesPath + "\\watchlist.html"));

        this->setupLoginScreen();
    }
    else
    {
        this->startScreenQueryLabel->setText(QString::fromUtf8("No selection made! Try again"));
    }
}

void GUI::loggedInAsAdmin()
{
    this->setupAdminGui();
    this->populateMovieList();
}

void GUI::loggedInAsUser()
{
    this->setupUserGui();
    this->populateWatchlist();
}

void GUI::populateMovieList()
{
    this->moviesList->clear();

    std::vector<Movie> movies = this->_moviesService.getAllMovies();

    this->moviesList->setMaximumWidth(600);
    this->moviesList->setColumnCount(6);
    this->moviesList->setRowCount(movies.size());

    QStringList headers = {QString::fromUtf8("ID"),
                          QString::fromUtf8("Title"),
                          QString::fromUtf8("Year"),
                          QString::fromUtf8("Genre"),
                          QString::fromUtf8("Likes"),
                          QString::fromUtf8("Link")};

    this->moviesList->setHorizontalHeaderLabels(headers);
    int row = 0;
    for (auto& movie: movies)
    {
        this->moviesList->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(std::to_string(movie.getId()))));
        this->moviesList->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(movie.getTitle())));
        this->moviesList->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(movie.getYear()))));
        this->moviesList->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(movie.getGenre())));
        this->moviesList->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(std::to_string(movie.getLikes()))));
        this->moviesList->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(movie.getUrl())));

        row++;
    }
}

void GUI::populateMovieTable()
{
    this->MoviesTable->clear();

    std::vector<Movie> movies = this->_moviesService.getAllMovies();

    this->MoviesTable->setMaximumWidth(600);
    this->MoviesTable->setColumnCount(6);
    this->MoviesTable->setRowCount(movies.size());

    QStringList headers = {QString::fromUtf8("ID"),
                           QString::fromUtf8("Title"),
                           QString::fromUtf8("Year"),
                           QString::fromUtf8("Genre"),
                           QString::fromUtf8("Likes"),
                           QString::fromUtf8("Link")};

    this->MoviesTable->setHorizontalHeaderLabels(headers);
    int row = 0;
    for (auto& movie: movies)
    {
        this->MoviesTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(std::to_string(movie.getId()))));
        this->MoviesTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(movie.getTitle())));
        this->MoviesTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(movie.getYear()))));
        this->MoviesTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(movie.getGenre())));
        this->MoviesTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(std::to_string(movie.getLikes()))));
        this->MoviesTable->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(movie.getUrl())));

        row++;
    }
}

int GUI::getSelectedIndex()
{
    auto selectedIndexes = moviesList->selectedItems();
    if (selectedIndexes.empty()) {
        id_lineEdit->clear();
        title_lineEdit->clear();
        year_lineEdit->clear();
        year_lineEdit->clear();
        genre_lineEdit->clear();
        likes_lineEdit->clear();
        url_lineEdit->clear();
        return -1;
    }
    int selectedIndex = selectedIndexes.at(0)->row();
    return selectedIndex;
}


void GUI::populateWatchlist()
{
    this->watchlistTable->clear();

    std::vector<Movie> movies = this->_moviesService.getWatchlist();

    this->watchlistTable->setMaximumWidth(600);
    this->watchlistTable->setColumnCount(6);
    this->watchlistTable->setRowCount(movies.size());

    QStringList headers = {QString::fromUtf8("ID"),
                           QString::fromUtf8("Title"),
                           QString::fromUtf8("Year"),
                           QString::fromUtf8("Genre"),
                           QString::fromUtf8("Likes"),
                           QString::fromUtf8("Link")};

    this->watchlistTable->setHorizontalHeaderLabels(headers);
    int row = 0;
    for (auto& movie: movies)
    {
        this->watchlistTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(std::to_string(movie.getId()))));
        this->watchlistTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(movie.getTitle())));
        this->watchlistTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(movie.getYear()))));
        this->watchlistTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(movie.getGenre())));
        this->watchlistTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(std::to_string(movie.getLikes()))));
        this->watchlistTable->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(movie.getUrl())));

        row++;
    }
}

int GUI::getSelectedIndexWatchlist()
{
    auto selectedIndexes = watchlistTable->selectedItems();
    if (selectedIndexes.empty()) {
        selected_movie_lbl2->clear();
        return -1;
    }
    int selectedIndex = selectedIndexes.at(0)->row();
    return selectedIndex;
}

int GUI::getSelectedIndexMoviesTable()
{
    auto selectedIndexes = MoviesTable->selectedItems();
    if (selectedIndexes.empty()) {
        selected_movie_lbl2->clear();
        return -1;
    }
    int selectedIndex = selectedIndexes.at(0)->row();
    return selectedIndex;
}

void GUI::addMovie()
{
    int id = id_lineEdit->text().toInt();
    int likes = likes_lineEdit->text().toInt();
    int year = year_lineEdit->text().toInt();
    std::string title = title_lineEdit->text().toStdString();
    std::string genre = genre_lineEdit->text().toStdString();
    std::string trailer = url_lineEdit->text().toStdString();

    try
    {
        this->_moviesService.addMovie(id, title, year, genre, likes, trailer);
    }
    catch (ValidationException &ve) {
        std::cout << ve.what() << "\n";
    }
    catch (RepositoryException &re) {
        std::cout << re.what() << "\n";
    }

    id_lineEdit->clear();
    title_lineEdit->clear();
    year_lineEdit->clear();
    year_lineEdit->clear();
    genre_lineEdit->clear();
    likes_lineEdit->clear();
    url_lineEdit->clear();

    this->populateMovieList();
}

void GUI::updateMovie()
{
    int id = id_lineEdit->text().toInt();
    int likes = likes_lineEdit->text().toInt();
    int year = year_lineEdit->text().toInt();
    std::string title = title_lineEdit->text().toStdString();
    std::string genre = genre_lineEdit->text().toStdString();
    std::string trailer = url_lineEdit->text().toStdString();

    try
    {
        this->_moviesService.updateMovie(id, title, year, genre, likes, trailer);
    }
    catch (ValidationException &ve) {
        std::cout << ve.what() << "\n";
    }
    catch (RepositoryException &re) {
        std::cout << re.what() << "\n";
    }

    id_lineEdit->clear();
    title_lineEdit->clear();
    year_lineEdit->clear();
    year_lineEdit->clear();
    genre_lineEdit->clear();
    likes_lineEdit->clear();
    url_lineEdit->clear();

    this->populateMovieList();
}

void GUI::removeMovie()
{
    int id = id_lineEdit->text().toInt();

    try
    {
        this->_moviesService.deleteMovie(id);
    }
    catch (ValidationException &ve) {
        std::cout << ve.what() << "\n";
    }
    catch (RepositoryException &re) {
        std::cout << re.what() << "\n";
    }

    id_lineEdit->clear();
    title_lineEdit->clear();
    year_lineEdit->clear();
    year_lineEdit->clear();
    genre_lineEdit->clear();
    likes_lineEdit->clear();
    url_lineEdit->clear();

    this->populateMovieList();
}

void GUI::watchTrailer()
{
    int selected = this->getSelectedIndexWatchlist();
    if (selected != -1)
    {
        //ShellExecute(0, 0, (LPCWSTR) this->_moviesService.getWatchlist()[selected].getUrl(), 0, 0 , SW_SHOW );
    }
}

void GUI::addToWatchlist()
{
    int selected = this->getSelectedIndexMoviesTable();
    if (selected != -1)
    {
        try
        {
            this->_moviesService.addToWatchlist(this->_moviesService.getAllMovies()[selected].getId());
        }
        catch (ValidationException &ve) {
            std::cout << ve.what() << "\n";
        }
        catch (RepositoryException &re) {
            std::cout << re.what() << "\n";
        }

        this->populateWatchlist();
    }
}

void GUI::removeFromWatchlist()
{
    int selected = this->getSelectedIndexWatchlist();
    if (selected != -1)
    {
        try{
            bool liked = false;
            if (likedCheckBox->isChecked())
            {
                liked = true;
            }
            this->_moviesService.deleteFromWatchlist(this->_moviesService.getWatchlist()[selected].getId(), liked);
        }
        catch (ValidationException &ve) {
            std::cout << ve.what() << "\n";
        }
        catch (RepositoryException &re) {
            std::cout << re.what() << "\n";
        }

        this->populateMovieTable();
        this->populateWatchlist();
    }


}

