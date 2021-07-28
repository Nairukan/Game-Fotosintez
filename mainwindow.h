#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class Enemy;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent* event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent* event);
    std::vector <Enemy*> Enemis;
    void X();
    QTimer* Ti2=new QTimer;
    void MakeFood();
    void MakeFoe();
    void CheckFood();
    void CheckFoe();
public slots:
    void p();
private slots:
    void on_pushButton_clicked();
    void EndImune();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
