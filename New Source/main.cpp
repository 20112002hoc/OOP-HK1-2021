#include "DoAnOOP.h"
#include <QtWidgets/QApplication>
#include <QWidget>
#include <QListWidget>
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
#include"Topic.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    DoAnOOP w;
    w.setWindowTitle(QString("E-Learning"));
    w.setWindowIcon(QIcon("Icons/logoWin"));
    w.show();

    return a.exec();
 
}
