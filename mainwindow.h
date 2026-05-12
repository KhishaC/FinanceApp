
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "auth.h"
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    //Login Page
    void on_loginButton_clicked();
    void on_createAccountButton_clicked();
    void on_language_clicked();

    //Main Menu
    void on_logout_clicked();
    void on_learn_clicked();
    void on_learningTrack_clicked();


    //Learning Page
    void on_finance_clicked();
    void on_fraud_clicked();
    void on_back_clicked();
    void on_quiz_clicked();


    //Finance Topics
    void on_supplydemand_clicked();
    void on_interestrates_clicked();
    void on_inflation_clicked();
    void on_recession_clicked();
    void on_gdp_clicked();
    void on_backtofinance_clicked();

    //Fraud Topics
    void on_phishing_clicked();
    void on_identitytheft_clicked();
    void on_investmentfraud_clicked();
    void on_ponzischemes_clicked();
    void on_avoidfraud_clicked();
    void on_backtofraud_clicked();

    //Learning Track
    void on_returnmainmenu_clicked();

    //Quiz
    void on_financequiz_clicked();
    void on_fraudquiz_clicked();
    void on_returnquiz_clicked();


    //Quiz Topics
    void on_answer1_clicked();
    void on_answer2_clicked();
    void on_answer3_clicked();
    void on_returnlearningtrack_clicked();


    //Learning Materials
    void on_returntoFtopics_clicked();



private:
    Ui::MainWindow *ui;
    QString currentLang = "en";
    void setLanguage(const QString& lang);


    Auth auth;
    User currentUser;

    int previousPage;
    void showTopic(const QString& title, const QString& content, const QString& example);
    QStringList loadTopic(const QString& title);

    QStringList loadQuiz(const QString& topic);
    void showQuiz(const QString& topic);

    QString correctAnswer;
    int quizScore = 0;
    int quizTotal = 0;
};


#endif