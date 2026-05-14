#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    QMap<QString, QString> lang;

    ui->stackedWidget->setCurrentIndex(0); // Login page
}

MainWindow::~MainWindow()
{
    delete ui;
}

//////////////////////////////////////////////////////
// LOGIN PAGE
//////////////////////////////////////////////////////

void MainWindow::on_loginButton_clicked() //Login into Application
{
    QString username = ui->Username->text();
    QString password = ui->Password->text();

    if (username.isEmpty() || password.isEmpty()) {

        if (currentLang == "fr")
            ui->statusLabel->setText("Veuillez remplir tous les champs");
        else
            ui->statusLabel->setText("Please fill all fields");

        return;
    }

    bool success = auth.login(
        username.toStdString(),
        password.toStdString(),
        currentUser
        );

    if (success) {

        QString name = QString::fromStdString(currentUser.getUsername());

        if (currentLang == "fr") {
            ui->statusLabel->setText("Bienvenue " + name);
            ui->welcomeLabel->setText("Bienvenue " + name);
        }
        else {
            ui->statusLabel->setText("Welcome " + name);
            ui->welcomeLabel->setText("Welcome " + name);
        }

        ui->stackedWidget->setCurrentIndex(1);
    }
    else {

        if (currentLang == "fr")
            ui->statusLabel->setText("Nom d'utilisateur ou mot de passe invalide");
        else
            ui->statusLabel->setText("Invalid username or password");
    }
}


void MainWindow::on_createAccountButton_clicked() //Creating Account
{
    QString username = ui->Username->text();
    QString password = ui->Password->text();

    if (username.isEmpty() || password.isEmpty()) {

        if (currentLang == "fr")
            ui->statusLabel->setText("Remplissez tous les champs");
        else
            ui->statusLabel->setText("Fill all fields");

        return;
    }

    bool created = auth.createAccount(
        username.toStdString(),
        password.toStdString()
        );

    if (created) {

        if (currentLang == "fr")
            ui->statusLabel->setText("Compte créé");
        else
            ui->statusLabel->setText("Account created");

    } else {

        if (currentLang == "fr")
            ui->statusLabel->setText("Erreur lors de la création du compte");
        else
            ui->statusLabel->setText("Error creating account");
    }
}

void MainWindow::on_logout_clicked() //Logging out of Application
{
    ui->stackedWidget->setCurrentIndex(0);

    if (currentLang == "fr")
        ui->statusLabel->setText("Déconnecté");
    else
        ui->statusLabel->setText("Logged out");
}

//////////////////////////////////////////////////////
// MAIN MENU
//////////////////////////////////////////////////////

void MainWindow::on_learn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_finance_clicked()
{
    ui->statusLabel->setText("Finance page opened");
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_fraud_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_quiz_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

//////////////////////////////////////////////////////
// FINANCE TOPICS
//////////////////////////////////////////////////////
void MainWindow::showTopic(const QString& title,const QString& content,const QString& example)
{
    // SAVE where you came from
    previousPage = ui->stackedWidget->currentIndex();

    ui->topicTitle->setText(title);
    ui->topicContent->setText(content);
    ui->topicExamples->setText(example);

    // GO to topic page
    ui->stackedWidget->setCurrentIndex(5);
}

//////////////////////////////////////////////////////
// OPENING LEARNING MATERIAL PAGE AND CONTENT
//////////////////////////////////////////////////////


QStringList MainWindow::loadTopic(const QString& title)
{
    QString path;

    if (currentLang == "fr")
        path = "/Users/khisha/FinanceApp/financetopics_fr.txt";
    else
        path = "/Users/khisha/FinanceApp/financetopics.txt";

    QFile file(path);

    /*if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file:" << path;
        return {};
    }*/

    try {

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            throw QString("Cannot open topic file");
        }

    }
    catch (QString error) {

        qDebug() << error;
        ui->statusLabel->setText(error);

        return {};
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        if (line.startsWith(title + "|")) {
            return line.split("|");
        }
    }
    return {};
}








void MainWindow::on_supplydemand_clicked()
{
    QString key = "Supply & Demand";

    if (currentLang == "fr")
        key = "Offre et demande";

    QStringList t = loadTopic(key);
    if (t.size() == 3)
        showTopic(t[0], t[1], t[2]);
}

void MainWindow::on_interestrates_clicked()
{
    QString key = "Interest Rates";
    if (currentLang == "fr")
        key = "Taux d’Intérêt";

    QStringList t = loadTopic(key);
    if  (t.size() == 3)
        showTopic(t[0], t[1], t[2]);
}

void MainWindow::on_inflation_clicked()
{
    ui->statusLabel->setText("Inflation clicked");
    QString key = "Inflation";
    if (currentLang == "fr")
        key = "Inflation";

    QStringList t = loadTopic(key);
    if (t.size() == 3)
        showTopic(t[0], t[1], t[2]);
}


void MainWindow::on_recession_clicked()
{
    QString key = "Recession";
    if (currentLang == "fr")
        key = "Récession";

    QStringList t = loadTopic(key);
    if (t.size() == 3)
        showTopic(t[0], t[1], t[2]);
}


void MainWindow::on_gdp_clicked()
{
    QString key = "GDP";
    if (currentLang == "fr")
        key = "Produit Intérieur Brut (PIB)";

    QStringList t = loadTopic(key);
    if (t.size() == 3)
        showTopic(t[0], t[1], t[2]);
}


void MainWindow::on_language_clicked() {
    currentLang = (currentLang == "en") ? "fr" : "en";
    setLanguage(currentLang);

}


void MainWindow::on_backtofraud_clicked() {
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_backtofinance_clicked() {
    ui->stackedWidget->setCurrentIndex(2);
}
void MainWindow::on_returntoFtopics_clicked()
{

    ui->stackedWidget->setCurrentIndex(previousPage);
}


void MainWindow::on_phishing_clicked()
{
    QString key = "Phishing";
    if (currentLang == "fr")
        key = "Hameçonnage (Phishing)";

    QStringList t = loadTopic(key);
    if (t.size() == 3)
        showTopic(t[0], t[1], t[2]);
}


void MainWindow::on_identitytheft_clicked()
{
    QString key = "Identity Theft";
    if (currentLang == "fr")
        key = "Vol d’Identité";

    QStringList t = loadTopic(key);
    if (t.size() == 3)
        showTopic(t[0], t[1], t[2]);
}


void MainWindow::on_investmentfraud_clicked()
{
    QString key = "Investment Fraud";
    if (currentLang == "fr")
        key = "Fraude à l’Investissement";

    QStringList t = loadTopic(key);
    if (t.size() == 3)
        showTopic(t[0], t[1], t[2]);
}


void MainWindow::on_ponzischemes_clicked()
{
    QString key = "Ponzi Schemes";
    if (currentLang == "fr")
        key = "Système de Ponzi";

    QStringList t = loadTopic(key);
    if (t.size() == 3)
        showTopic(t[0], t[1], t[2]);
}


void MainWindow::on_avoidfraud_clicked()
{
    QString key = "How to Avoid Fraud";
    if (currentLang == "fr")
        key = "Comment Éviter la Fraude";

    QStringList t = loadTopic(key);
        if (t.size() == 3)
            showTopic(t[0], t[1], t[2]);
}



//////////////////////////////////////////////////////
// OPENING AND LOADING QUIZ FILES IN FRENCH OR ENGLISH
//////////////////////////////////////////////////////

QStringList MainWindow::loadQuiz(const QString& topic)
    {
        QString path;

        if (currentLang == "fr")
            path = "/Users/khisha/FinanceApp/quiz_fr.txt";
        else
            path = "/Users/khisha/FinanceApp/quiz.txt";

        QFile file(path);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Quiz file not found";
            return {};
        }

        QTextStream in(&file);

        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();

            QStringList parts = line.split("|");

            if (parts.size() == 6 && parts[0] == topic) {
                return parts;
            }
        }

        qDebug() << "Quiz not found for topic:" << topic;
        return {};
    }

void MainWindow::showQuiz(const QString& topic)
{
    QStringList q = loadQuiz(topic);

    if (q.size() != 6)
        return;

    ui->questionLabel->setText(q[1]);

    ui->answer1->setText(q[2]);
    ui->answer2->setText(q[3]);
    ui->answer3->setText(q[4]);

    correctAnswer = q[5];

    ui->resultLabel->setText("");

    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_financequiz_clicked() //Finance Quiz
{
    showQuiz("GDP");
}



void MainWindow::on_fraudquiz_clicked() //Fraud Quiz
{
    showQuiz("Phishing");
}


void MainWindow::on_returnquiz_clicked()
{
    ui->stackedWidget->setCurrentIndex(previousPage);
}

//////////////////////////////////////////////////////
// ANSWERS  FOR QUIZ
//////////////////////////////////////////////////////

void MainWindow::on_answer1_clicked() //ANSWER 1 OPTION
{
    if (ui->answer1->text() == correctAnswer){

        quizScore++;
        if (currentLang == "fr"){
            ui->resultLabel->setText("Correct !");
        }
        else{
            ui->resultLabel->setText("Correct!");}
    }else{
        if (currentLang == "fr"){
            ui->resultLabel->setText("Faux !");
        }
        else{
                    ui->resultLabel->setText("Wrong!");
            }

ui->scoreLabel->setText(QString::number(quizScore) + "/" + QString::number(quizTotal));
    }
}


void MainWindow::on_answer2_clicked() //ANSWER 2 OPTION
{
    if (ui->answer2->text() == correctAnswer){

        quizScore++;
        if (currentLang == "fr"){
            ui->resultLabel->setText("Correct !");
        }
        else{
            ui->resultLabel->setText("Correct!");}
    }else{
        if (currentLang == "fr"){
            ui->resultLabel->setText("Faux !");
        }
        else{
            ui->resultLabel->setText("Wrong!");
        }
        ui->scoreLabel->setText(QString::number(quizScore) + "/" + QString::number(quizTotal));
    }
}




void MainWindow::on_answer3_clicked() //ANSWER 3 OPTION
{
    if (ui->answer3->text() == correctAnswer){

        quizScore++;
        if (currentLang == "fr"){
            ui->resultLabel->setText("Correct !");
        }
        else{
            ui->resultLabel->setText("Correct!");}
    }else{
        if (currentLang == "fr"){
            ui->resultLabel->setText("Faux !");
        }
        else{
            ui->resultLabel->setText("Wrong!");
        }
        ui->scoreLabel->setText(QString::number(quizScore) + "/" + QString::number(quizTotal));
    }
}


void MainWindow::on_returnlearningtrack_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}


void MainWindow::on_returnmainmenu_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}


void MainWindow::on_learningTrack_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);

}

//////////////////////////////////////////////////////
// Changing Language
//////////////////////////////////////////////////////
void MainWindow::setLanguage(const QString& lang)
{
    if (lang == "fr") //Changing into French
    {
        // LOGIN PAGE
        ui->loginButton->setText("Connexion");
        ui->createAccountButton->setText("Créer Compte");

        // MAIN MENU
        ui->learn->setText("Apprendre");
        ui->finance->setText("Finance");
        ui->fraud->setText("Fraude");
        ui->quiz->setText("Tester Vos Connaissances");
        ui->learningTrack->setText("Progression");
        ui->logout->setText("Déconnexion");
        ui->back->setText("Retour");

        // FINANCE PAGE
        ui->supplydemand->setText("Offre et Demande");
        ui->interestrates->setText("Taux d’Intérêt");
        ui->inflation->setText("Inflation");
        ui->recession->setText("Récession");
        ui->gdp->setText("PIB");

        // FRAUD PAGE
        ui->phishing->setText("Hameçonnage");
        ui->identitytheft->setText("Vol d’Identité");
        ui->investmentfraud->setText("Fraude Financière");
        ui->ponzischemes->setText("Systèmes de Ponzi");
        ui->avoidfraud->setText("Éviter les Fraudes");

        // QUIZ
        ui->financequiz->setText("Quiz Finance");
        ui->fraudquiz->setText("Quiz Fraude");

        // QUIZ ANSWERS
        ui->answer1->setText("Réponse 1");
        ui->answer2->setText("Réponse 2");
        ui->answer3->setText("Réponse 3");

        // NAVIGATION
        ui->returnmainmenu->setText("Menu Principal");
        ui->returnlearningtrack->setText("Retour Progression");
        ui->returntoFtopics->setText("Retour");
        ui->backtofinance->setText("Retour");
        ui->backtofraud->setText("Retour");
        ui->returnquiz->setText("Retour");

        ui->statusLabel->setText("Langue : Français");//Show what language we switch to
    }
    else //Leaving in English
    {
        // LOGIN PAGE
        ui->loginButton->setText("Login");
        ui->createAccountButton->setText("Create Account");

        // MAIN MENU
        ui->learn->setText("Learn");
        ui->finance->setText("Finance");
        ui->fraud->setText("Fraud");
        ui->quiz->setText("Test Your Knowledge");
        ui->learningTrack->setText("Learning Track");
        ui->logout->setText("Logout");
        ui->back->setText("Back");

        // FINANCE PAGE
        ui->supplydemand->setText("Supply & Demand");
        ui->interestrates->setText("Interest Rates");
        ui->inflation->setText("Inflation");
        ui->recession->setText("Recession");
        ui->gdp->setText("GDP");

        // FRAUD PAGE
        ui->phishing->setText("Phishing");
        ui->identitytheft->setText("Identity Theft");
        ui->investmentfraud->setText("Investment Fraud");
        ui->ponzischemes->setText("Ponzi Schemes");
        ui->avoidfraud->setText("How to Avoid Fraud");

        // QUIZ
        ui->financequiz->setText("Finance Quiz");
        ui->fraudquiz->setText("Fraud Quiz");

        // QUIZ ANSWERS
        ui->answer1->setText("Answer 1");
        ui->answer2->setText("Answer 2");
        ui->answer3->setText("Answer 3");

        // NAVIGATION
        ui->returnmainmenu->setText("Main Menu");
        ui->returnlearningtrack->setText("Return Learning Track");
        ui->returntoFtopics->setText("Back");
        ui->backtofinance->setText("Back");
        ui->backtofraud->setText("Back");
        ui->returnquiz->setText("Back");

        ui->statusLabel->setText("Language: English");//Show what language we switch to
    }
}


