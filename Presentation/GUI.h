#ifndef LOCAL_MOVIE_DATABASE_GUI_H
#define LOCAL_MOVIE_DATABASE_GUI_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QCheckBox>

#include "../Business/MoviesLocalDBService.h"

class GUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit GUI(MoviesLocalDBService&, QWidget *parent = Q_NULLPTR);

private:
    MoviesLocalDBService& _moviesService;

    // ======================================== start screen graphical elements ========================================

    QWidget *verticalLayoutWidget{};
    QVBoxLayout *verticalLayout{};
    QLabel *loginTitleLabel{};
    QPushButton *adminModePushBtn{};
    QPushButton *userModePushBtn{};

    // ======================================== start screen graphical elements ========================================
    QLabel* startScreenQueryLabel{};
    QGroupBox* fileChoiceGroupBox{};
    QRadioButton *csvRdBtn{}, *htmlRdBtn{};
    QPushButton* confirmPushBtn{};

    // ============================================ user graphical elements ============================================

    QVBoxLayout *mainLayoutUser;
    QHBoxLayout *TopBarLayoutUser;
    QLabel *titleLabel2;
    QPushButton *backpushbtn1;
    QVBoxLayout *UserDataLayout;
    QHBoxLayout *horizontalUserLyaout;
    QVBoxLayout *verticatLayoutMoviesUser;
    QLabel *MoviesLabel;
    QTableWidget *MoviesTable;
    QLineEdit *GenreLineEdit;
    QPushButton *filterPushBtn;
    QGroupBox *groupBox;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *verticalLayout_5;
    QLabel *selected_movie_lbl1;
    QPushButton *addToWatchlistbtn;
    QVBoxLayout *verticalLayoutWatchlistUser;
    QLabel *watchlistLabel;
    QTableWidget *watchlistTable;
    QGroupBox *groupBox_2;
    QLabel *selected_movie_lbl2;
    QCheckBox *likedCheckBox;
    QPushButton *removePushBtn;
    QPushButton *watchTrailerBtn;


    // ============================================ admin graphical elements ===========================================

    QWidget *verticalLayoutWidget1{};
    QVBoxLayout *verticalLayout1{};
    QHBoxLayout *topBarHLayout;
    QLabel *titleLbl;
    QPushButton *backToLoginPushBtn;
    QHBoxLayout *centralDataHLayout;
    QTableWidget *moviesList;
    QGroupBox *movieDetailsGBox;
    QGroupBox *movieActionsGBox;
    QPushButton *addMoviePushBtn, *updateMoviePushBtn, *removeMoviePushBtn;

    QLineEdit *id_lineEdit;
    QLineEdit *title_lineEdit, *year_lineEdit, *genre_lineEdit, *likes_lineEdit, *url_lineEdit;


    void setupLoginScreen();
    void setupStartScreenGUI();

    void setupAdminGui();
    void setupUserGui();

    void connectSignalSlots();

    int getSelectedIndex();

private slots:
    void confirmRepositoryTypeChoice();
    void loggedInAsUser();
    void loggedInAsAdmin();
    void populateMovieList();
    void populateMovieTable();
    void populateWatchlist();

    void addMovie();
    void updateMovie();
    void removeMovie();
    void watchTrailer();

    void addToWatchlist();
    void removeFromWatchlist();


    int getSelectedIndexWatchlist();
    int getSelectedIndexMoviesTable();

};


#endif //LOCAL_MOVIE_DATABASE_GUI_H
