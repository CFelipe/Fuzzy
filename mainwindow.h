#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    QWidget* createEntry();
    QWidget* createRules();
    ~MainWindow();
};

#endif // MAINWINDOW_H
