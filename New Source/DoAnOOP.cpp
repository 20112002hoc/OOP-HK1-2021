#include "DoAnOOP.h"
#include <iostream>
#include <QApplication>
#include <QDialog>
#include <QDialogButtonBox>
#include <QEventLoop>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QListView>
#include <QPointer>
#include <QPushButton>
#include <QResizeEvent>
#include <QScrollArea>
#include <QScrollBar>
#include <QSet>
#include <QSettings>
#include <QSortFilterProxyModel>
#include <QSpacerItem>
#include <QStackedLayout>
#include <QTimer>
#include <QPixmap>
#include <QFile>
#include <QTextstream>
#include <QLine>
#include <QPalette>
int checkReturnBackToSignIn = 0;

DoAnOOP::DoAnOOP(QWidget* parent)
    : QMainWindow(parent)
{

    SignUp();
}



void DoAnOOP::displayGrammar(QString path) {
    path.remove(" Tense");
    path.remove(' ');
    QFile file(".\\DataTheory\\" + path + ".txt");
    file.open(QFile::ReadOnly | QFile::Text);
    textArea->setPlainText(file.readAll());
}
//mới thêm vào bởi tường
void DoAnOOP::setUpgpBoxVocabWid()
{
//cài đặt lựa chọn topic
    QStringList topic = { "Animal","Body","Food","Fruit","Job","Sport","Transport" };
    QLabel* label = new QLabel("Choose a vocabulary topic :");
    cbBoxChooseTopic = new QComboBox;
    cbBoxChooseTopic->addItems(topic);
//cài đặt hiển thị hình ảnh
    topicVocab.setTopic("Animal");
    lblImageShow = new QLabel;
    QPixmap image("Data_img/Animal/" + topicVocab.getImageAt(0) + ".jpg");
    lblImageShow->setPixmap(image.scaled(150,150));

    lblMeaningImage = new QLabel();
    lblMeaningImage->setText(topicVocab.getImageAt(0) + " - " + topicVocab.getMeaningAt(0));
    lblMeaningImage->setAlignment(Qt::AlignCenter);
    lblMeaningImage->setFont(QFont("", 15, 10));
    btnLeftMove = new QPushButton("<");
    btnRightMove = new QPushButton(">");

    QHBoxLayout* controlMove = new QHBoxLayout;
    controlMove->addWidget(btnLeftMove);

    controlMove->addWidget(btnRightMove);


    QVBoxLayout* imageLayout = new QVBoxLayout();
    imageLayout->addWidget(lblImageShow,15,Qt::AlignCenter);
    imageLayout->addWidget(lblMeaningImage,Qt::AlignCenter);
    imageLayout->addLayout(controlMove);
    QGroupBox* GroupImg = new QGroupBox;
    GroupImg->setLayout(imageLayout);

//phần luyện tập
    btnPracVocab = new QPushButton("Practice");
    btnTestVocab = new QPushButton("Test");
    btnPracVocab->setToolTip("Take a 5-question practice quiz on this topic.");
    btnTestVocab->setToolTip("Take an overall 10-question test.");

    btnPracVocab->setIcon(QIcon("Icons\\practice.png"));
    btnTestVocab->setIcon(QIcon("Icons\\test.png"));

    QHBoxLayout* pracBtn = new QHBoxLayout;
    pracBtn->addWidget(btnPracVocab, Qt::AlignRight);
    pracBtn->addWidget(btnTestVocab, Qt::AlignRight);


//tạo layout cho trang
    QVBoxLayout* topicLayout = new QVBoxLayout;
    topicLayout->addWidget(label);
    topicLayout->addWidget(cbBoxChooseTopic);
    topicLayout->addWidget(GroupImg);
    topicLayout->addLayout(pracBtn);
    
//cài đặt layout cho trang
    gpBoxVocabWid = new QGroupBox("Topic vocabulary");
    gpBoxVocabWid->setLayout(topicLayout);

}

void DoAnOOP::displayVocab(QString topic)
{
    indexImg = 0;
    topicVocab.setTopic(topic);
    QPixmap image("Data_img/" + topic + "/" + topicVocab.getImageAt(0) + ".jpg");
    lblImageShow->setPixmap(image.scaled(150,150));
    lblMeaningImage->setText(topicVocab.getImageAt(0) + " - " + topicVocab.getMeaningAt(0));
}
void DoAnOOP::increaseIndexImg()
{
    if (indexImg < NUMBER_OF_PICTURE - 1) indexImg++;
    QPixmap image("Data_img/" + topicVocab.getTopic() + "/" + topicVocab.getImageAt(indexImg) + ".jpg");
    lblImageShow->setPixmap(image);
    lblMeaningImage->setText(topicVocab.getImageAt(indexImg) + " - " + topicVocab.getMeaningAt(indexImg));
}
void DoAnOOP::decreaseIndexImg()
{
    if (indexImg > 0) indexImg--;
    QPixmap image("Data_img/" + topicVocab.getTopic() + "/" + topicVocab.getImageAt(indexImg) + ".jpg");
    lblImageShow->setPixmap(image.scaled(150,150));
    lblMeaningImage->setText(topicVocab.getImageAt(indexImg) + " - " + topicVocab.getMeaningAt(indexImg));
}
void DoAnOOP::connectToVocab()
{
    stackWid->setCurrentIndex(5);
}
void DoAnOOP::createPracQuizVocab()
{
    pracQuiz = grammarVocab.createPracQuiz(cbBoxChooseTopic->currentIndex());
    stackWid->setCurrentIndex(1);
    score = 0;
    quizProgress = 0;
    displayQuestionVocab();
    lcdTime->display(100);
    timer->start();

    typeOfPrac = 0;
    //tường thêm vào
    btnEnd->setEnabled(1);
    btnReturnToGrm->setDisabled(1);
}
void DoAnOOP::createTestQuizVocab()
{
    testQuiz = grammarVocab.createTestQuiz();
    stackWid->setCurrentIndex(1);
    score = 0;
    quizProgress = 0;
    displayQuestionVocab();
    lcdTime->display(200);
    timer->start();

    typeOfPrac = 0;
    //tường thêm vào
    btnEnd->setEnabled(1);
    btnReturnToGrm->setDisabled(1);
}
void DoAnOOP::displayQuestionVocab()
{
    Exercise* quiz = !testQuiz ? pracQuiz : testQuiz;
    prgBar->setValue(quizProgress * (!testQuiz ? 100 / NUM_OF_QUES_IN_PRAC : 100 / NUM_OF_QUES_IN_TEST));
    QPixmap image("Data_img/" + QString::fromStdString(quiz->getQues(quizProgress)) + ".jpg");
    lblQues->setPixmap(image);
    lblQues->setAlignment(Qt::AlignCenter);

    if (quiz->gettopicVocab(quizProgress) == 0) {    // MC
        stackAns->setCurrentIndex(0);
        btnOpt1->setText(QString::fromStdString(quiz->getOpt(quizProgress, 0)));
        btnOpt2->setText(QString::fromStdString(quiz->getOpt(quizProgress, 1)));
        btnOpt3->setText(QString::fromStdString(quiz->getOpt(quizProgress, 2)));
        btnOpt4->setText(QString::fromStdString(quiz->getOpt(quizProgress, 3)));
    }

    quizProgress++;
}

//kết thúc phần thêm vào
void DoAnOOP::setUpMenu()
{
    // Set up Menu
    btnMenu1 = new QPushButton("Dictionary");
    btnMenu2 = new QPushButton("Grammar");
    btnMenu3 = new QPushButton("Vocabulary");
    btnMenu4 = new QPushButton("About Us");
    btnMenu5 = new QPushButton("Log Out");

    QVBoxLayout* menu = new QVBoxLayout;
    menu->addWidget(btnMenu1, Qt::AlignTop);
    menu->addWidget(btnMenu2, Qt::AlignTop);
    menu->addWidget(btnMenu3, Qt::AlignTop);
    menu->addWidget(btnMenu4, Qt::AlignTop);


    menu->addStretch();
    menu->addWidget(btnMenu5, Qt::AlignBottom);
    btnMenu1->setFixedSize(100, 50);
    btnMenu2->setFixedSize(100, 50);
    btnMenu3->setFixedSize(100, 50);
    btnMenu4->setFixedSize(100, 50);
    btnMenu5->setFixedSize(100, 50);

    btnMenu1->setIcon(QIcon("Icons\\dictionary.png"));
    btnMenu2->setIcon(QIcon("Icons\\book.png"));
    btnMenu3->setIcon(QIcon("Icons\\word.png"));
    btnMenu4->setIcon(QIcon("Icons\\info.png"));
    btnMenu5->setIcon(QIcon("Icons\\exit.png"));

    menuWid = new QWidget;
    menuWid->setLayout(menu);
    menuWid->setMaximumWidth(115);
}

void DoAnOOP::setUpGrammarWid()
{
    // ComboBox and TextEdit
    QStringList listTheory = { "Present Simple Tense", "Present Continuous Tense", "Present Perfect Tense", "Past Simple Tense", "Past Continuous Tense", "Past Perfect Tense", "Future Simple Tense", "Future Continuous Tense", "Future Perfect Tense", "Future Near Tense" };
    QLabel* lblGram = new QLabel("Choose a grammar topic:");
    cbBox = new QComboBox;
    cbBox->addItems(listTheory);
    textArea = new QTextEdit("Content");
    textArea->setReadOnly(true);
    QFile file(".\\DataTheory\\PresentSimple.txt");
    file.open(QFile::ReadOnly | QFile::Text);
    textArea->setPlainText(file.readAll());

    // Buttons
    QHBoxLayout* grammarBtn = new QHBoxLayout;
    btnPrac = new QPushButton("Practice");
    btnTest = new QPushButton("Test");
    btnRank = new QPushButton("Ranking");
    btnPrac->setToolTip("Take a 5-question practice quiz on this topic.");
    btnTest->setToolTip("Take an overall 10-question test.");
    btnRank->setToolTip("See the rankings.");
    btnPrac->setIcon(QIcon("Icons\\practice.png"));
    btnTest->setIcon(QIcon("Icons\\test.png"));
    btnRank->setIcon(QIcon("Icons\\rank.png"));
    grammarBtn->addWidget(btnPrac, Qt::AlignRight);
    grammarBtn->addWidget(btnTest, Qt::AlignRight);
    grammarBtn->addWidget(btnRank, Qt::AlignRight);

    // Overall layout
    grammarWid = new QGroupBox("Grammar Theory");
    QVBoxLayout* right = new QVBoxLayout;
    right->addWidget(lblGram);
    right->addWidget(cbBox);
    right->addWidget(textArea,15);
    right->addLayout(grammarBtn);

    grammarWid->setLayout(right);
    
}

void DoAnOOP::setUpQuesWid()
{
    // Question box
    quesBox = new QGroupBox("Question");
    lblQues = new QLabel("Question ... ?");
    QVBoxLayout* qst = new QVBoxLayout;
    qst->addWidget(lblQues);
    quesBox->setLayout(qst);
    quesBox->setMinimumHeight(120);

    // ProgressBar and LCDTimer
    prgBar = new QProgressBar;
    prgBar->setMaximumWidth(200);
    prgBar->setValue(25);
    lcdTime = new QLCDNumber;
    lcdTime->setFixedSize(130, 70);
    timer = new QTimer;
    timer->setInterval(1000);
    timer->stop();
    QLabel* lblTime = new QLabel("Time remaining:");

    // Buttons
    btnEnd = new QPushButton;
    btnReturnToGrm = new QPushButton;
    btnEnd->setText("End");
    btnEnd->setIcon(QIcon("Icons\\end.png"));
    btnEnd->setMaximumHeight(30);

    btnReturnToGrm->setText("Return");
    btnReturnToGrm->setIcon(QIcon("Icons\\return.png"));
    btnReturnToGrm->setToolTip("Return to Grammar Theory.");
    btnReturnToGrm->setMaximumHeight(30);

    btnOpt1 = new QPushButton;
    btnOpt2 = new QPushButton;
    btnOpt3 = new QPushButton;
    btnOpt4 = new QPushButton;
    btnOpt1->setFixedHeight(40);
    btnOpt2->setFixedHeight(40);
    btnOpt3->setFixedHeight(40);
    btnOpt4->setFixedHeight(40);

    // Answer widgets
    QGridLayout* gridMcAns = new QGridLayout;
    gridMcAns->addWidget(btnOpt1, 0, 0, 1, 2);
    gridMcAns->addWidget(btnOpt2, 0, 2, 1, 2);
    gridMcAns->addWidget(btnOpt3, 1, 0, 1, 2);
    gridMcAns->addWidget(btnOpt4, 1, 2, 1, 2);
    QWidget* mcAnsWid = new QWidget;
    mcAnsWid->setLayout(gridMcAns);
    mcAnsWid->setMaximumHeight(100);
    QHBoxLayout* boxFbAns = new QHBoxLayout;
    QLabel* lblFbAns = new QLabel("Your answer: ");
    ansArea = new QTextEdit;
    ansArea->setMaximumHeight(30);
    btnEnter = new QPushButton("Enter");
    boxFbAns->addWidget(lblFbAns);
    boxFbAns->addWidget(ansArea);
    boxFbAns->addWidget(btnEnter);
    QWidget* fbAnsWid = new QWidget;
    fbAnsWid->setLayout(boxFbAns);
    fbAnsWid->setMaximumHeight(90);
    stackAns = new QStackedLayout;
    stackAns->addWidget(mcAnsWid);
    stackAns->addWidget(fbAnsWid);
    stackAns->setCurrentIndex(0);

    // Overall layout
    QGridLayout* gridQues = new QGridLayout;
    gridQues->addWidget(prgBar, 0, 0, 1, 2, Qt::AlignTop);
    gridQues->addWidget(lblTime, 0, 2, 1, 1, Qt::AlignRight);
    gridQues->addWidget(lcdTime, 0, 3, 1, 1, Qt::AlignRight);
    gridQues->addWidget(quesBox, 2, 0, 1, 4);
    gridQues->addLayout(stackAns, 3, 0, 2, 4);
    gridQues->addWidget(btnEnd, 6, 0, 1, 2, Qt::AlignBottom);
    gridQues->addWidget(btnReturnToGrm, 6, 2, 1, 2, Qt::AlignBottom);

    quesWid = new QGroupBox("Practice Quiz");
    quesWid->setLayout(gridQues);
}

void DoAnOOP::createPracQuiz()
{
    pracQuiz = grammar.createPracQuiz(cbBox->currentIndex());
    stackWid->setCurrentIndex(1);
    score = 0;
    quizProgress = 0;
    displayQuestion();
    lcdTime->display(100);
    timer->start();

    typeOfPrac = 1;         //tường thêm vào

    btnEnd->setEnabled(1);
    btnReturnToGrm->setDisabled(1);
}

void DoAnOOP::displayQuestion()
{
    Exercise* quiz = !testQuiz ? pracQuiz : testQuiz;
    prgBar->setValue(quizProgress * (!testQuiz ? 100 / NUM_OF_QUES_IN_PRAC : 100 / NUM_OF_QUES_IN_TEST));
    lblQues->setText(QString::fromStdString(quiz->getQues(quizProgress)));
    ansArea->clear();
    if (quiz->gettopicVocab(quizProgress) == 0) {    // MC
        stackAns->setCurrentIndex(0);
        btnOpt1->setText(QString::fromStdString(quiz->getOpt(quizProgress, 0)));
        btnOpt2->setText(QString::fromStdString(quiz->getOpt(quizProgress, 1)));
        btnOpt3->setText(QString::fromStdString(quiz->getOpt(quizProgress, 2)));
        btnOpt4->setText(QString::fromStdString(quiz->getOpt(quizProgress, 3)));
    }
    else if (quiz->gettopicVocab(quizProgress) == 1) {
        stackAns->setCurrentIndex(1);
        ansArea->setFocus();
    }
    quizProgress++;
}

void DoAnOOP::checkQuestion()
{
    QObject* sender = QObject::sender();
    QString ans;
    if (sender == btnOpt1) {
        ans = btnOpt1->text();
    }
    else if (sender == btnOpt2) {
        ans = btnOpt2->text();
    }
    else if (sender == btnOpt3) {
        ans = btnOpt3->text();
    }
    else if (sender == btnOpt4) {
        ans = btnOpt4->text();
    }
    else {
        ans = ansArea->toPlainText();
    }
    Exercise* quiz = !testQuiz ? pracQuiz : testQuiz;
    if (ans == QString::fromStdString(quiz->getKey(quizProgress - 1))) {
        score += (!testQuiz ? 100 / NUM_OF_QUES_IN_PRAC : 100 / NUM_OF_QUES_IN_TEST);
    }
    QMessageBox::information(this, QString(QString::fromStdString(to_string(score))), QString::fromStdString(quiz->getKey(quizProgress - 1)));
    if (quizProgress == (!testQuiz ? NUM_OF_QUES_IN_PRAC : NUM_OF_QUES_IN_TEST)) {
        prgBar->setValue(100);
        timer->stop();
        if (pracQuiz) {
            delete pracQuiz;
            pracQuiz = NULL;
        }
        if (testQuiz) {
            delete testQuiz;
            testQuiz = NULL;
            Result(_user->id(), score, 200 - lcdTime->value()).save();
        }
        timer->stop();
        QMessageBox::information(this, score > 50 ? "Congratulation!" : "Not bad!", "Your score: " + QString::fromStdString(to_string(score)));
        
        btnEnd->setDisabled(1);
        btnReturnToGrm->setEnabled(1);
        //if (typeOfPrac) stackWid->setCurrentIndex(0);
        //else stackWid->setCurrentIndex(2);      //tường thêm vào
    }
    else {
        if (typeOfPrac)         //tường thêm vào
        {
            displayQuestion();

        }
        else
        {
            displayQuestionVocab();
        }

    }
}

void DoAnOOP::runLCDTimer()
{
    lcdTime->display((int)lcdTime->value() - 1);
}

void DoAnOOP::createTestQuiz()
{
    testQuiz = grammar.createTestQuiz();
    stackWid->setCurrentIndex(1);
    score = 0;
    quizProgress = 0;
    displayQuestion();
    lcdTime->display(200);
    timer->start();

    typeOfPrac = 1;     //tường thêm vào

    btnEnd->setEnabled(1);
    btnReturnToGrm->setDisabled(1);
}



void DoAnOOP::returnToGrammar()
{
   
    if (typeOfPrac) stackWid->setCurrentIndex(0);
    else stackWid->setCurrentIndex(2);
}

void DoAnOOP::endQuiz()
{
    quizProgress = (!testQuiz ? NUM_OF_QUES_IN_PRAC : NUM_OF_QUES_IN_TEST);
    ansArea->clear();
    checkQuestion();
    btnEnd->setDisabled(1);
    btnReturnToGrm->setEnabled(1);

}

//thêm bởi phú
//SLOT by Phu
void DoAnOOP::exitMess() {
    int traLoi = QMessageBox::question(nullptr, QString::fromWCharArray(L"Thắc mắc"), QString::fromWCharArray(L"Bạn có thật sự muốn thoát không :((( ?"));
    if (traLoi == QMessageBox::Yes) {
        QMessageBox::information(nullptr, QString::fromWCharArray(L"Buồn"), QString::fromWCharArray(L"Hẹn gặp lại bạn ..."));
        QApplication::quit();
    }
    else if (traLoi == QMessageBox::No) {
        QMessageBox::information(nullptr, QString::fromWCharArray(L"Vui vẻ"), QString::fromWCharArray(L"Hehe bạn nhấn nhầm phải hôm"));
    }
}


void DoAnOOP::signInEvent() {
    QString text = _id->text();
    //if user_id is empty -> can't open
    if (text.toStdString() == "") return;

    _user = new User(text.toStdWString());

    /*   if(Tokens::ws2s(_user->id()) != "NULL")
           QMessageBox::information(nullptr, QString::fromWCharArray(L"ok ok"), QString::fromWCharArray(L"test thui"));*/


    QMessageBox::about(nullptr, QString::fromWCharArray(L"Chào mừng"), QString::fromWCharArray(L"Chào mừng bạn đến với chương trình của tụi mình, ") + text);
    if (!checkReturnBackToSignIn) {

        cuaSoChinh.setFixedSize(700, 500);
        // stackWid = new QStackedLayout;
        setUpMenu();
        setUpDict();
        setUpHistory();
        setUpSaveImWords();
        setUpGrammarWid();
        setUpQuesWid();
        setUpgpBoxVocabWid();
        stackWid = new QStackedLayout;
        stackWid->addWidget(grammarWid);    // index 0
        stackWid->addWidget(quesWid);       // index 1
        stackWid->addWidget(dictWid);       // index 2
        stackWid->addWidget(hisWid);        // index 3
        stackWid->addWidget(imWordsWid);    // index 4
        stackWid->addWidget(gpBoxVocabWid); // index 5
        // Main window include Menu and stackWid
        QGridLayout* gridLayout = new QGridLayout;
        gridLayout->addWidget(menuWid, 0, 0, 1, 1);
        gridLayout->addLayout(stackWid, 0, 1, 1, 3);
        cuaSoChinh.setLayout(gridLayout);
        stackWid->setCurrentIndex(0);
        pracQuiz = NULL;
        testQuiz = NULL;
        rankingWid = NULL;
        // Signal and slots
        connect(cbBox, SIGNAL(currentTextChanged(QString)), this, SLOT(displayGrammar(QString)));
        connect(btnPrac, SIGNAL(clicked()), this, SLOT(createPracQuiz()));
        connect(btnTest, SIGNAL(clicked()), this, SLOT(createTestQuiz()));
        connect(btnOpt1, SIGNAL(clicked()), this, SLOT(checkQuestion()));
        connect(btnOpt2, SIGNAL(clicked()), this, SLOT(checkQuestion()));
        connect(btnOpt3, SIGNAL(clicked()), this, SLOT(checkQuestion()));
        connect(btnOpt4, SIGNAL(clicked()), this, SLOT(checkQuestion()));
        connect(btnEnter, SIGNAL(clicked()), this, SLOT(checkQuestion()));
        connect(timer, SIGNAL(timeout()), this, SLOT(runLCDTimer()));
        connect(btnEnd, SIGNAL(clicked()), this, SLOT(endQuiz()));
        connect(btnReturnToGrm, SIGNAL(clicked()), this, SLOT(returnToGrammar()));
        connect(btnRank, SIGNAL(clicked()), this, SLOT(seeRanking()));
        checkReturnBackToSignIn = 1;


        //them boi tuong
        connect(cbBoxChooseTopic, SIGNAL(currentTextChanged(QString)), this, SLOT(displayVocab(QString)));
        connect(btnRightMove, SIGNAL(clicked()), this, SLOT(increaseIndexImg()));
        connect(btnLeftMove, SIGNAL(clicked()), this, SLOT(decreaseIndexImg()));
        connect(btnPracVocab, SIGNAL(clicked()), this, SLOT(createPracQuizVocab()));
        connect(btnTestVocab, SIGNAL(clicked()), this, SLOT(createTestQuizVocab()));
        //nối cac nut menu
        connect(btnMenu1, SIGNAL(clicked()), this, SLOT(connectToDict()));
        connect(btnMenu2, SIGNAL(clicked()), this, SLOT(connectToGrammar()));
        connect(btnMenu3, SIGNAL(clicked()), this, SLOT(connectToVocab()));
        connect(btnMenu4, SIGNAL(clicked()), this, SLOT(aboutUs()));
        connect(btnMenu5, SIGNAL(clicked()), this, SLOT(returnToSignIn()));
    }

    QPixmap bkgnd("Background/background.jpg");
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    this->takeCentralWidget();
    this->setCentralWidget(&cuaSoChinh);

}



//
void DoAnOOP::returnToSignIn() {
    QPixmap bkgnd("Background/background3.jpg");

    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    this->takeCentralWidget();
    this->setCentralWidget(&widSignIn);
}

void DoAnOOP::aboutUs() {
    QMessageBox::information(nullptr, QString::fromWCharArray(L"Thông tin về phần mềm"), QString::fromWCharArray(L"Đây là phần mềm tiếng anh cơ bản được lập trình bởi 3 sinh viên:\n1. Lương Thanh Hoàng Phú – MSSV: 20120548\n2. Từ Văn Quí – MSSV: 20120561\n3. Trần Thiên Tường – MSSV: 20120620\n"));
}

void DoAnOOP::connectToDict() {
    stackWid->setCurrentIndex(indexDictionary);
}

void DoAnOOP::connectToGrammar() {
    stackWid->setCurrentIndex(indexGrammarWid);
}

void DoAnOOP::translate() {
    QString s = textSrc->text();
    // QMessageBox::information(nullptr, QString::fromWCharArray(L"test"), QString::fromWCharArray(L"test tokens: ") + s);
    wstring tokens = s.toStdWString();
    wstring res = L"NULL";
    res = _user->search(tokens, boxLanguage->currentIndex());
    textDist->setPlainText(QString::fromStdWString(res));
}

void DoAnOOP::connectToHistory() {
    wstring dir = L"Users/" + _user->id() + L"/History";
    vector<wstring> files;
    for (auto& p : filesystem::recursive_directory_iterator(Tokens::ws2s(dir).c_str()))
    {
        wstring temp = filesystem::absolute(p.path()).wstring();
        files.push_back(temp);
    }
    files = file::SortDate(files);
    for (int i = 0; i < files.size(); i++)
    {
        wstring temp = files[i];
        temp.erase(temp.length() - 4);
        word[i]->setText(QString::fromStdWString(temp));
        textWord[i]->setText(QString::fromStdWString(file::readAFile(dir + L"/" + files[i])));
    }
    stackWid->setCurrentIndex(indexHistory);
}

void DoAnOOP::Save() {
    wstring token = textSrc->text().toStdWString();

    wstring fsrc, fdst;
    fdst = L"Users/" + _user->id() + L"/ImportantWords/" + token + L".txt";
    if (!boxLanguage->currentIndex())
        fsrc = L"Dictionary/Anh-Viet/" + token + L".txt";
    else
        fsrc = L"Dictionary/Viet-Anh/" + token + L".txt";

    ifstream src(fsrc, ios::binary);
    ofstream dst(fdst, ios::binary);

    dst << src.rdbuf();
}


void DoAnOOP::connectToSaveImWords() {

    while (listWords->count() > 0)
    {
        listWords->takeItem(0);
    }

    wstring dir = L"Users/" + _user->id() + L"/ImportantWords";
    vector<wstring> files;
    for (auto& p : filesystem::recursive_directory_iterator(Tokens::ws2s(dir).c_str()))
    {
        wstring temp = filesystem::absolute(p.path()).wstring();
        files.push_back(temp);
    }
    files = file::SortDate(files);

    for (int i = 0; i < files.size(); i++)
    {
        wstring temp = to_wstring(i) + L". " + files[i];
        temp.erase(temp.length() - 4);
        listWords->addItem(QString::fromStdWString(temp));

    }
    stackWid->setCurrentIndex(indexImWords);
}


void DoAnOOP::translate2() {
    wstring dir = L"Users/" + _user->id() + L"/ImportantWords/";
    wstring text = listWords->currentItem()->text().toStdWString() + L".txt";
    // "12. hoc 123"
    int pos = text.find(L". ");
    text.erase(0, pos + 2);
    meaning->setText(QString::fromStdWString(file::readAFile(dir + text)));

}


//set Up func by Phu

void DoAnOOP::setUpDict() {
    dictWid = new QWidget;
    dictWid->setToolTip("Dictionary");
    qvLayoutDictWid = new QVBoxLayout;
    QStringList listLanguage = { "English - Vietnamese", "Vietnamese - English" };
    QLabel* lbDict = new QLabel("Choose language:");
    boxLanguage = new QComboBox;
    boxLanguage->addItems(listLanguage);
    qvLayoutDictWid->addWidget(boxLanguage);

    
    btnTrans = new QPushButton("Translate");
    btnTrans->setIcon(QIcon("Icons/translation.png"));
    btnTrans->setToolTip(QString::fromWCharArray(L"Nhấn để dịch"));
    connect(btnTrans, SIGNAL(clicked()), this, SLOT(translate()));
    textSrc = new QLineEdit;
    textSrc->setToolTip(QString::fromWCharArray(L"Nhập từ bạn muốn dịch"));
    textSrc->setText("Hello");

    QLabel* lbTextSrc = new QLabel("Enter keywords:");
    qhLayoutTrans = new QHBoxLayout;
    qhLayoutTrans->addWidget(textSrc);
    qhLayoutTrans->addWidget(btnTrans);
    qvLayoutDictWid->addWidget(lbTextSrc);
    qvLayoutDictWid->addLayout(qhLayoutTrans);
    
    QLabel* lbTextDist = new QLabel("Result:");
    qvLayoutDictWid->addWidget(lbTextDist);
    qhLayoutDict1 = new QHBoxLayout;
    
    btnSave = new QPushButton("Save");
    btnSave->setToolTip(QString::fromWCharArray(L"Lưu vào danh sách từ quan trọng"));
    btnSave->setIcon(QIcon("Icons/saveWords.png"));
    connect(btnSave, SIGNAL(clicked()), this, SLOT(Save()));
    textDist = new QTextEdit();
    QFile fDist("Dictionary/Anh-Viet/hello.txt");
    fDist.open(QFile::ReadOnly | QFile::Text);
    textDist->setReadOnly(true);
    textDist->setPlainText(fDist.readAll());
    qhLayoutDict1->addWidget(textDist);
    qhLayoutDict1->addWidget(btnSave);
    qvLayoutDictWid->addLayout(qhLayoutDict1);

    qhLayoutDict2 = new QHBoxLayout;
    btnImWords = new QPushButton("Important Words");
    btnImWords->setToolTip(QString::fromWCharArray(L"Danh sách các từ quan trọng"));
    btnImWords->setIcon(QIcon("Icons/imW.png"));
    btnImWords->setFixedSize(200, 35);
    connect(btnImWords, SIGNAL(clicked()), this, SLOT(connectToSaveImWords()));
    btnHistory = new QPushButton("History");
    btnHistory->setToolTip(QString::fromWCharArray(L"Lịch sử 5 từ gần nhất"));
    btnHistory->setIcon(QIcon("Icons/History.png"));
    btnHistory->setFixedSize(200, 35);
    connect(btnHistory, SIGNAL(clicked()), this, SLOT(connectToHistory()));
    qhLayoutDict2->addWidget(btnImWords);
    qhLayoutDict2->addWidget(btnHistory);
    qvLayoutDictWid->addLayout(qhLayoutDict2);


    dictWid->setLayout(qvLayoutDictWid);
    
}

void DoAnOOP::setUpHistory() {
    hisWid = new QWidget;
    hisWid->setToolTip(QString::fromWCharArray(L"Lịch sử 5 từ gần nhất"));
    qvLayoutHisWid = new QVBoxLayout;
    grBoxHis = new QGroupBox("History");
    //QLabel *lb = new QLabel("History:");
    //QFont f = lb->text();
    //f.setBold(true);
    //lb->setFont(f);
    //qvLayoutHisWid->addWidget(lb);
    for (int i = 0; i < 5; i++) {
        textWord[i] = new QTextEdit("NULL");
        textWord[i]->setReadOnly(1);
        word[i] = new QLineEdit("NULL");
        word[i]->setReadOnly(1);
    }
    for (int i = 0; i < 5; i++) {
        qvLayoutHisWid->addWidget(word[i]);
        qvLayoutHisWid->addWidget(textWord[i]);
    }
    returnBackToDict = new QPushButton("Return");
    returnBackToDict->setToolTip(QString::fromWCharArray(L"Quay về Thư viện"));
    returnBackToDict->setIcon(QIcon("Icons/undo-button.png"));
    returnBackToDict->setFixedSize(100, 30);
    QHBoxLayout* returnQV = new QHBoxLayout;
    returnQV->addWidget(returnBackToDict);
    returnQV->setAlignment(Qt::AlignRight);
    qvLayoutHisWid->addLayout(returnQV);
    connect(returnBackToDict, SIGNAL(clicked()), this, SLOT(connectToDict()));
   // qvLayoutHisWid->addWidget(returnBackToDict);
   
    grBoxHis->setLayout(qvLayoutHisWid);
    QVBoxLayout* temp = new QVBoxLayout;
    temp->addWidget(grBoxHis);
    hisWid->setLayout(temp);
}

void DoAnOOP::setUpSaveImWords() {
    imWordsWid = new QWidget;
    imWordsWid->setToolTip(QString::fromWCharArray(L"Lưu các từ mà bạn coi là quan trọng"));
    grBoxIm = new QGroupBox("Important Words ");

    qvLayoutImWordsWid = new QVBoxLayout;
    // qvLayoutImWordsWid->addWidget(lb);

    qvWords = new QVBoxLayout;
    QLabel* lb1 = new QLabel("List:");
    qvWords->addWidget(lb1);
    listWords = new QListWidget;
    listWords->setToolTip(QString::fromWCharArray(L"Danh sách các từ quan trọng"));
    qvWords->addWidget(listWords);
    qvWords->setAlignment(Qt::AlignCenter);

    btnTranslate = new QPushButton("Translate");
    btnTranslate->setIcon(QIcon("Icons/translation.png"));
    btnTranslate->setToolTip(QString::fromWCharArray(L"Nhấn để dịch"));
    connect(btnTranslate, SIGNAL(clicked()), this, SLOT(translate2()));

    qvMeaning = new QVBoxLayout;
    QLabel* lb2 = new QLabel("Meaning: ");
    qvMeaning->addWidget(lb2);
    meaning = new QTextEdit;
    meaning->setToolTip(QString::fromWCharArray(L"Nghĩa của từ: "));
    meaning->setReadOnly(true);
    meaning->setText("NULL");
    qvMeaning->addWidget(meaning);
    qvMeaning->setAlignment(Qt::AlignCenter);

    qhLayoutImWordsWid = new QHBoxLayout;
    qhLayoutImWordsWid->addLayout(qvWords);
    qhLayoutImWordsWid->addWidget(btnTranslate);

    qhLayoutImWordsWid->addLayout(qvMeaning);

    qvLayoutImWordsWid->addLayout(qhLayoutImWordsWid);
    qhTemp = new QHBoxLayout;
    returnBackToDict2 = new QPushButton("Return");
    returnBackToDict2->setToolTip(QString::fromWCharArray(L"Quay về Thư viện"));
    returnBackToDict2->setIcon(QIcon("Icons/undo-button.png"));
    returnBackToDict2->setFixedSize(100, 30);
    connect(returnBackToDict2, SIGNAL(clicked()), this, SLOT(connectToDict()));
    qhTemp->addWidget(returnBackToDict2);
    qhTemp->setAlignment(Qt::AlignRight);
    qvLayoutImWordsWid->addLayout(qhTemp);

    grBoxIm->setLayout(qvLayoutImWordsWid);
    QVBoxLayout* temp = new QVBoxLayout;
    temp->addWidget(grBoxIm);
    imWordsWid->setLayout(temp);

}


void DoAnOOP::SignUp() {
    widSignIn.setFixedSize(700, 500);


    layoutSignIn = new QVBoxLayout;
    lbSignIn = new QLabel;
    lbSignIn->setText("E-Learning");
    QFont font = lbSignIn->font();
    font.setPointSize(64);
    lbSignIn->setFont(font);
    lbSignIn->setAlignment(Qt::AlignCenter);
    // QPixmap pix("Icons/logo22.jpg");
     //_hinhAnh = new QLabel;
     //_hinhAnh->setPixmap(pix);
     //_hinhAnh->setAlignment(Qt::AlignCenter);
    _id = new QLineEdit;
    _id->setFixedSize(500, 30);
    _id->setToolTip(QString::fromWCharArray(L"Mời bạn nhập ID để đăng nhập vào phần mềm..."));
    idForm = new QFormLayout;

    QString textId(QString::fromWCharArray(L"Mời bạn nhập ID: "));
    QFont f = textId;
    f.setBold(1);
    idForm->addRow(QString::fromWCharArray(L"Mời bạn nhập ID: "), _id);
    idForm->setAlignment(Qt::AlignCenter);
    //  _layoutChinh->addWidget(_hinhAnh);
    layoutSignIn->addSpacing(150);
    layoutSignIn->addWidget(lbSignIn);
    layoutSignIn->addLayout(idForm);

    btnExit = new QPushButton(QString::fromWCharArray(L"Thoát"));
    btnExit->setToolTip(QString::fromWCharArray(L"Nhấn để thoát"));
    btnExit->setIcon(QIcon("Icons/exitApp.png"));
    btnExit->setFixedSize(150, 40);
    connect(btnExit, SIGNAL(clicked()), this, SLOT(exitMess()));
    btnSignIn = new QPushButton(QString::fromWCharArray(L"Đăng nhập"));
    btnSignIn->setToolTip(QString::fromWCharArray(L"Nhấn vào để đăng nhập..."));
    btnSignIn->setIcon(QIcon("Icons/signin.png"));
    btnSignIn->setFixedSize(150, 40);
    connect(btnSignIn, SIGNAL(clicked()), this, SLOT(signInEvent()));

    qhLayout2Button = new QHBoxLayout;
    qhLayout2Button->addWidget(btnExit);
    qhLayout2Button->addWidget(btnSignIn);
    qhLayout2Button->setAlignment(Qt::AlignCenter);
    wid2btn.setLayout(qhLayout2Button);

    layoutSignIn->addWidget(&wid2btn);

    btnInfo = new QPushButton(QString::fromWCharArray(L"Thông tin"));
    btnInfo->setToolTip(QString::fromWCharArray(L"Nhấn vào để xem thông tin về phần mềm"));
    btnInfo->setIcon(QIcon("Icons/info.png"));
    btnInfo->setFixedSize(100, 30);
    connect(btnInfo, SIGNAL(clicked()), this, SLOT(aboutUs()));
    layoutSignIn->addWidget(btnInfo);
    widSignIn.setLayout(layoutSignIn);

    QPixmap bkgnd("Background/background3.jpg");

    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    this->setCentralWidget(&widSignIn);

}

//thêm bởi Quý
void DoAnOOP::seeRanking()
{
    if (!rankingWid) {
        QVBoxLayout* layoutRank = new QVBoxLayout;
        tbRank = new QTableWidget;
        tbRank->setRowCount(5);
        tbRank->setColumnCount(4);
        QStringList listHeader = { "Rank", "User", "Score", "Time" };
        tbRank->setHorizontalHeaderLabels(listHeader);
        tbRank->verticalHeader()->hide();
        btnClose = new QPushButton("Close");
        btnClose->setFixedSize(70, 30);
        QHBoxLayout* layoutBtnReturn = new QHBoxLayout;
        layoutBtnReturn->addStretch();
        layoutBtnReturn->addWidget(btnClose, Qt::AlignRight);
        layoutRank->addWidget(tbRank, Qt::AlignTop);
        layoutRank->addLayout(layoutBtnReturn, Qt::AlignBottom);
        rankingWid = new QDialog();
        rankingWid->setLayout(layoutRank);
        rankingWid->setWindowTitle("Top Rankings");
        rankingWid->setFixedSize(430, 240);
        rankingWid->setWindowIcon(QIcon("Icons\\rank.png"));
        rankingWid->setModal(1);
    }
    vector<Result> rank = Result::loadTopRanking();
    for (int i = 0; i < NUM_OF_TOP_RESULT; i++) {
        QTableWidgetItem* item0 = new QTableWidgetItem(QString::number(i + 1));
        QTableWidgetItem* item1 = new QTableWidgetItem(QString::fromStdWString(rank[i].User()));
        QTableWidgetItem* item2 = new QTableWidgetItem(QString::number(rank[i].Score()));
        QTableWidgetItem* item3 = new QTableWidgetItem(QString::number(rank[i].Time()));
        tbRank->setItem(i, 0, item0);
        tbRank->setItem(i, 1, item1);
        tbRank->setItem(i, 2, item2);
        tbRank->setItem(i, 3, item3);
    }
    connect(btnClose, SIGNAL(clicked()), rankingWid, SLOT(close()));
    rankingWid->exec();
}