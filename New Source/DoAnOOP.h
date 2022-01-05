#pragma once

#include <QtWidgets>
#include "Topic.h"
#include "Exercise.h"
#include "User.h"
#include "Result.h"
class DoAnOOP : public QMainWindow
{
    Q_OBJECT

public:
    DoAnOOP(QWidget* parent = Q_NULLPTR);
    void setUpMenu();
    void setUpGrammarWid();
    void setUpQuesWid();
    //thêm vào bởi tường
    void setUpgpBoxVocabWid();
    //thêm bởi phú
    void setUpDict();
    void setUpHistory();
    void setUpSaveImWords();
private slots:
    void displayGrammar(QString);
    void createPracQuiz();
    void displayQuestion();
    void checkQuestion();
    void runLCDTimer();
    void createTestQuiz();

    void returnToGrammar();
    void endQuiz();

    //thêm vào bởi tường
    void displayVocab(QString);
    void increaseIndexImg();
    void decreaseIndexImg();
    void connectToVocab();
    void displayQuestionVocab();  //danh cho phan vocab
    void createPracQuizVocab();   //danh cho phan vocab
    void createTestQuizVocab();   //danh cho phan vocab

    //thêm bởi phú
    void exitMess();
    void signInEvent();
    void returnToSignIn();
    void aboutUs();
    //
    void connectToDict();
    void connectToGrammar();
    //
    void translate();
    void connectToHistory();
    void Save();
    void connectToSaveImWords();
    void translate2();
    //

    void seeRanking();
private:
   

    Grammar grammar;
    Exercise* pracQuiz;
    Exercise* testQuiz;
    int quizProgress;
    int score;

    QWidget cuaSoChinh;
    QStackedLayout* stackWid;
    const int indexGrammarWid = 0;
    const int indexQuesWid = 1;
    const int indexDictionary = 2;
    const int indexHistory = 3;
    const int indexImWords = 4;
    const int indexVocab = 5;

    QWidget* menuWid;
    QPushButton* btnMenu1;
    QPushButton* btnMenu2;
    QPushButton* btnMenu3;
    QPushButton* btnMenu4;
    QPushButton* btnMenu5;
    QPushButton* btnMenu6; //xem tu da luu

    QGroupBox* grammarWid;
    QTextEdit* textArea;
    QPushButton* btnPrac;
    QPushButton* btnTest;
    QPushButton* btnRank;
    QComboBox* cbBox;

    QGroupBox* quesWid;
    QProgressBar* prgBar;
    QTimer* timer;
    QLCDNumber* lcdTime;
    QGroupBox* quesBox;
    QLabel* lblQues;
    QStackedLayout* stackAns;
    QPushButton* btnOpt1;
    QPushButton* btnOpt2;
    QPushButton* btnOpt3;
    QPushButton* btnOpt4;
    QTextEdit* ansArea;
    QPushButton* btnEnter;
    QPushButton* btnEnd;
    QPushButton* btnSubm;

    QPushButton* btnReturnToGrm;

    //tường thêm vào
    QGroupBox* gpBoxVocabWid;
    QLabel* lblImageShow;
    QLabel* lblMeaningImage;
    QComboBox* cbBoxChooseTopic;
    QPushButton* btnLeftMove;
    QPushButton* btnRightMove;
    QPushButton* btnPracVocab;
    QPushButton* btnTestVocab;
    Topic topicVocab;
    int indexImg = 0;

    GrammarVocab grammarVocab;
    bool typeOfPrac; // 0 neu la phan ngu phap va 1 neu la phan tu vung


    //thêm bởi phú
    void SignUp();

    QVBoxLayout* layoutSignIn; // layout chinh phan Sign In
    QWidget widSignIn;  // Widget chinh cuar phan Sign In
    QLabel* lbSignIn; // Ten cua phan mem
    QLineEdit* _id;


    QFormLayout* idForm;
    QPushButton* btnExit;
    QPushButton* btnSignIn;
    QHBoxLayout* qhLayout2Button;
    QWidget wid2btn;
    QPushButton* btnInfo;
   

    // Dictionary Widget
    User* _user;
    QWidget* dictWid;
    QVBoxLayout* qvLayoutDictWid;
    QComboBox* boxLanguage;
    QTextEdit* textDist;
    QPushButton* btnTrans;
    QPushButton* btnSave;
    QHBoxLayout* qhLayoutDict1;
    QPushButton* btnImWords;
    QPushButton* btnHistory;
    QHBoxLayout* qhLayoutDict2;
    QLineEdit* textSrc;
    QHBoxLayout* qhLayoutTrans;
    QTextEdit* textHis;

    // History Widget
    QGroupBox* grBoxHis;
    QWidget* hisWid;
    QVBoxLayout* qvLayoutHisWid;
    QTextEdit* textWord[5];
    QLineEdit* word[5];
    QPushButton* returnBackToDict;

    // Important Words Widget
    QWidget* imWordsWid;
    QGroupBox* grBoxIm;
    QVBoxLayout* qvLayoutImWordsWid;
    QVBoxLayout* qvWords;
    QListWidget* listWords;
    // QTextEdit* listWords;
   //  QComboBox* cbBoxWords;
    QPushButton* btnTranslate;
    QVBoxLayout* qvMeaning;
    QTextEdit* meaning;
    QHBoxLayout* qhLayoutImWordsWid;
    QHBoxLayout* qhTemp;
    QPushButton* returnBackToDict2;

    //thêm bởi Quý
    QDialog* rankingWid;
    QTableWidget* tbRank;
    QPushButton* btnClose;

};
