#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPaintEvent>
#include <QPainter>
#include <QTimer>
#include <QMessageBox>
#include <thread>
#include <chrono>
#include <cmath>

#define _KolFoe_ 10
#define _KolFood_ 24

MainWindow* this1=nullptr;

class Enemy;


class Geometry{
public:
    void Move(double x, double y){
        left+=x;
        top+=y;
    }

    void Resize(double w, double h){
        width=w;
        heigth=h;
    }

    void SetGeometry(double x, double y, double xw, double yh){
        Move(x-left, y-top);
        Resize((int)xw, (int)yh);
    }
    friend Enemy;
    double left=0.0, top=0.0, width=0.0, heigth=0.0;
};

class Speed{
public:
    double xV, yV;
};

class Enemy : public Geometry{
public:

    std::string GType(){
        return Type;
    }

    void SType(std::string Type){
        this->Type=Type;
    }

    void Tick(){
        //QMessageBox::critical(this1, "", "");
        Move((V.xV), (V.yV));
        /*ostX=(V.xV+ostX)-(int)(V.xV+ostX);
        ostY=(V.yV+ostY)-(int)(V.yV+ostY);*/
        if (left+width>this1->width() || left<0.0){
            V.xV*=-1;
        }
        if (top+heigth>this1->height() || top<0.0){
            V.yV*=-1;
        }
        //paintEvent();
    }

    void paintEvent();

    void SSpeed(double xV, double yV){
        V.xV=xV;
        V.yV=yV;
    }

private:

    //double ostX=0.0, ostY=0.0;
    Speed V;
    std::string Type="nonType";
};

int hp=3;
Enemy* Hero=new Enemy;
Enemy* Foe[_KolFoe_];
Enemy* Food[_KolFood_];

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    for (int i=0; i<_KolFood_; i++){
        Food[i]=new Enemy;
    }
    for (int i=0; i<_KolFoe_; i++){
        Foe[i]=new Enemy;
    }
    ui->setupUi(this);
    srand(time(0));
    //QMessageBox::critical(this1, "1", "");
}

bool IsGeometryEquel(Enemy* x, Enemy* y){
    return (pow(x->left+x->width/2-y->left-y->width/2, 2)+pow(x->top+x->width/2-y->top-y->width/2, 2)<pow(x->width/2+y->width/2, 2));
}

QTimer* T1=new QTimer(this1);

int Score=0;

QLabel* Lb;

void MainWindow::MakeFood(){

}

void MainWindow::MakeFoe(){
  for (int i=0; i<_KolFoe_; i++){

      Enemis.push_back(Foe[i]);
      Foe[i]->SType("Foe");
      Foe[i]->SetGeometry(rand()%this->width()-20, rand()%this->height()-20, 15, 15);
      double xV=(double)(rand()+70.0)/100.0, yV=(double)(rand()+70.0)/100.0;
      int kofx=1, kofy=1;
      switch (rand()%4) {
          case 0:{

              break;
          }
          case 1:{
               kofx=-1;
               break;
          }
          case 2:{
               kofy=-1;
               break;
          }
          case 3:{
               kofx=-1;
               kofy=-1;
               break;
          }
      }
      Foe[i]->SSpeed((xV-(int)xV+(int)xV%3)*kofx, (yV-(int)yV+(int)yV%3)*kofy);
  }
}

void MakeFoeS(){
  this1->MakeFoe();
}

void MainWindow::CheckFood(){

}

void MainWindow::CheckFoe(){

}

void MainWindow::X(){
    ui->label_2->setText("hp: "+QString::number(hp));
    ui->pushButton->hide();
    this1=this;
    Lb=new QLabel(this1);
    Lb->show();
    Lb->setText("Score:"+QString::number(Score));
    ui->label->resize(300, 50);
    MakeFoe();
    //std::thread th(MakeFoeS);
    for (int i=0; i<_KolFood_; i++){
        Enemis.push_back(Food[i]);
        Food[i]->SType("Food");
        Food[i]->SetGeometry(rand()%this->width()-20, rand()%this->height()-20, 10, 10);
        Food[i]->SSpeed(0, 0);
    }

    Enemis.push_back(Hero);
    Hero->SType("Hero");
    bool Equel=1;
    //th.join();
    for (int i=0; i<Enemis.size()-1 || Equel==1; i++){
        if (Equel==1){
            i=-1;
            Hero->SetGeometry(abs(rand())%(this->width()-15)+14, abs(rand())%(this->height()-15)+14, 5, 5);
            Equel=0;
        }else {
            if (IsGeometryEquel(Hero, Enemis[i])){
                Equel=1;
            }
        }
    }
    Hero->SSpeed(0, 0);

    connect(T1, SIGNAL(timeout()), this, SLOT(p()));
    connect(Ti2, SIGNAL(timeout()), this, SLOT(EndImune()));
    ui->label->setText("");
    T1->start(10);
    //update();
}

bool q=1;

int a=0;

int left=0, right=0, up=0, down=0;

void MainWindow::keyPressEvent(QKeyEvent *event){
    if (Enemis.size()>0){
        ui->label->setText(QString::number(event->key()));


        if (event->key()==68){
            right=1;
            if (left==1)
              left=2;
        }
        if (event->key()==87){
            up=1;
            if (down==1)
              down=2;
        }
        if (event->key()==83){
            down=1;
            if (up==1)
              up=2;
        }
        if (event->key()==65){
            left=1;
            if (right==1)
              right=2;
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event){
    if (event->key()==68){
        right=0;
        if (left==2)
          left=1;
    }
    if (event->key()==87){
        up=0;
        if (down==2)
          down=1;
    }
    if (event->key()==83){
        down=0;
        if (up==2)
          up=1;
    }
    if (event->key()==65){
        left=0;
        if (right==2)
          right=1;
    }
    //ui->label->setText(QString::number(++a));
}

bool Imune=0;

void MainWindow::p(){
    if (q){
        q=!q;
        if (right==1 && Hero->left+Hero->width<this->width()){

            Hero->Move(30/Hero->width, 0);
        }
        if (up==1 && Enemis[Enemis.size()-1]->top>0){
            Hero->Move(0, -30/Hero->width);
        }
        if (down==1 && Hero->top+Hero->heigth<this->height()){
            Hero->Move(0, 30/Hero->width);
        }
        if (left==1 && Hero->left>0){
            Hero->Move(-30/Hero->width, 0);
        }
        for (int i=0; i<Enemis.size()-1; i++){
            Enemis[i]->Tick();
        }
        Hero->Tick();
        for (int i=0; ; i++){
            if (i>=Enemis.size()-1) break;
            if (IsGeometryEquel(Hero, Enemis[i])){
                if (Enemis[i]->GType()=="Food"){
                    Hero->Resize(Enemis[Enemis.size()-1]->width+1, Enemis[Enemis.size()-1]->width+1);
                    Lb->setText("Score:"+QString::number(++Score));
                    Enemis[i]->SetGeometry(rand()%this->width()-20, rand()%this->height()-20, 10, 10);
                    if (Score%5==0 && hp<5){
                        hp++;
                        ui->label_2->setText("hp: "+QString::number(hp));
                    }
                }else{
                    if (!Imune){
                        hp--;
                        ui->label_2->setText("hp: "+QString::number(hp));
                        if (hp==0){
                            T1->stop();
                            Enemis.clear();

                            ui->pushButton->show();
                            ui->label->setText("You Die");
                            ui->label->setFont(QFont("Times", 11, 10));
                            break;
                        }
                        Imune=1;
                        Ti2->start(1000);
                    }
                }
            }
        }
        q=!q;
    }
    update();
}

void MainWindow::EndImune(){
    Imune=0;
    Ti2->stop();
}

bool qp=1;

void Enemy::paintEvent(){

    QPainter p(this1);
    p.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    if (this->Type=="Hero"){
        p.setBrush(QBrush(QColor("#3b3b3b"), Qt::SolidPattern));
    }else if (Type=="Foe"){
        p.setBrush(QBrush(QColor("#FF0000"), Qt::SolidPattern));
    }else{
        p.setBrush(QBrush(QColor("#008000"), Qt::SolidPattern));
    }
    p.drawEllipse(left, top, width, heigth);
}

void MainWindow::paintEvent(QPaintEvent* event){

    if (qp && Enemis.size()>0){
        qp=!qp;

        for (int i=0; i<Enemis.size(); i++){
            (Enemis[i])->paintEvent();
        }
        qp=!qp;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Score=0;
    qp=1;
    a=0;
    q=1;
    hp=3;
    ui->label_2->setText("hp: "+QString::number(hp));
    ui->pushButton->hide();
    //this1=this;
    //Lb=new QLabel(this1);
    //Lb->show();
    Lb->setText("Score:"+QString::number(Score));
    ui->label->resize(300, 50);
    for (int i=0; i<_KolFood_; i++){
        Enemis.push_back(Food[i]);
        Enemis[Enemis.size()-1]->SType("Food");
        Enemis[Enemis.size()-1]->SetGeometry(rand()%this->width()-20, rand()%this->height()-20, 10, 10);
        Enemis[Enemis.size()-1]->SSpeed(0, 0);
    }
    for (int i=0; i<_KolFoe_; i++){
        Enemis.push_back(Foe[i]);
        Enemis[Enemis.size()-1]->SType("Foe");
        Enemis[Enemis.size()-1]->SetGeometry(rand()%this->width()-20, rand()%this->height()-20, 15, 15);
        double xV=(double)(rand()+70.0)/100.0, yV=(double)(rand()+70.0)/100.0;
        int kofx=1, kofy=1;
        switch (rand()%4) {
            case 0:{

                break;
            }
            case 1:{
                 kofx=-1;
                 break;
            }
            case 2:{
                 kofy=-1;
                 break;
            }
            case 3:{
                 kofx=-1;
                 kofy=-1;
                 break;
            }
        }
        Enemis[Enemis.size()-1]->SSpeed((xV-(int)xV+(int)xV%3)*kofx, (yV-(int)yV+(int)yV%3)*kofy);
    }
    Enemis.push_back(Hero);
    Hero->SType("Hero");
    bool Equel=1;
    for (int i=0; i<Enemis.size()-1 || Equel==1; i++){
        if (Equel==1){
            i=-1;
            Hero->SetGeometry(abs(rand())%(this->width()-15)+14, abs(rand())%(this->height()-15)+14, 5, 5);
            Equel=0;
        }else {
            if (IsGeometryEquel(Hero, Enemis[i])){
                Equel=1;
            }
        }
    }
    Hero->SSpeed(0, 0);

    //connect(T1, SIGNAL(timeout()), this, SLOT(p()));
    //connect(Ti2, SIGNAL(timeout()), this, SLOT(EndImune()));
    ui->label->setText("");
    T1->start(10);
}
