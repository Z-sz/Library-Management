#include "resvform.h"

extern qreal dpi;

ResvForm::ResvForm(QWidget *parent):
    QDialog(parent){
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setGeometry(150*dpi,30*dpi,550*dpi,480*dpi);
    this->icon=Q_NULLPTR;
    this->setStyleSheet("background-color:#ebf2fa");

    closeBtn= new ToolButton(this,QColor(0,0,0,0),QColor(0,153,255,255));
    closeBtn->setEnterColor("#ff6666");
    closeBtn->setGeometry(this->width()-29*dpi,1*dpi,29*dpi,29*dpi);
    QPixmap closePix=style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    closeBtn->setIcon(closePix);
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(close()));

    cancelBtn = new ToolButton(this,QColor(204,255,204,255),QColor(0,153,255,255));
    cancelBtn->setGeometry(320*dpi,420*dpi,100*dpi,30*dpi);
    cancelBtn->setPlainColor(QColor(30,136,229,255));
    cancelBtn->setFont(QFont("微软雅黑"));
    cancelBtn->setText("取消");
    connect(cancelBtn,SIGNAL(clicked()),this,SLOT(close()));

    comfirmBtn = new ToolButton(this,QColor(204,255,204,255),QColor(0,153,255,255));
    comfirmBtn->setGeometry(130*dpi,420*dpi,100*dpi,30*dpi);
    comfirmBtn->setPlainColor(QColor(30,136,229,255));
    comfirmBtn->setFont(QFont("微软雅黑"));
    comfirmBtn->setText("确定");
    connect(comfirmBtn,SIGNAL(clicked()),this,SLOT(comfirm()));

    popUp=new MessageBox(this);
    popUp->move(QPoint(100*dpi,100*dpi));
    popUp->setStyleSheet("background-color:white");
    popUp->setText("预约成功");
    popUp->setVisible(false);
    connect(popUp->confirmBtn,SIGNAL(clicked()),this,SLOT(close()));
}

ResvForm::~ResvForm(){
    delete cancelBtn;
    delete comfirmBtn;
    if (icon) delete icon;
}

void ResvForm::setBook(Book * item){
    this->item = item;
}

void ResvForm::setReader(Reader * borrower){
    this->borrower = borrower;
}

void ResvForm::setIcon(QPixmap pixmap){
    if (this->icon)
        delete icon;
    icon = new QPixmap(pixmap);
}

void ResvForm::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QFont textFont("微软雅黑",15);
    //QRect rect(30*dpi,30*dpi,60*dpi,25*dpi);
    painter.setFont(textFont);
    painter.drawText(30*dpi,50*dpi,QString("书名:"));
    //rect.adjust(90*dpi,30*dpi,100*dpi,25*dpi);
    painter.drawText(90*dpi,50*dpi,(this->item->getStringByTag("title")));
    //rect.adjust(200*dpi,30*dpi,60*dpi,25*dpi);
    painter.drawText(30*dpi,85*dpi,QString("编号:"));
    //rect.adjust(260*dpi,30*dpi,100*dpi,25*dpi);
    painter.drawText(90*dpi,85*dpi,(this->item->getStringByTag("id")));
    //rect.adjust(360*dpi,30*pi,60*dpi,25*dpi);
    painter.drawText(300*dpi,85*dpi,QString("类别:"));
    //rect.adjust(420*dpi,30*dpi,100*dpi,25*dpi);
    painter.drawText(360*dpi,85*dpi,(this->item->getStringByTag("category")));

    //rect.adjust(30*dpi,90*dpi,90*dpi,25*dpi);
    painter.drawText(30*dpi,120*dpi,QString("出版社:"));
    //rect.adjust(120*dpi,90*dpi,200*dpi,25*dpi);
    painter.drawText(98*dpi,120*dpi,(this->item->getStringByTag("press")));
    //rect.adjust(350*dpi,90*dpi,60*dpi,25*dpi);
    painter.drawText(30*dpi,155*dpi,QString("作者:"));
    //rect.adjust(410*dpi,90*dpi,80*dpi,25*dpi);
    painter.drawText(90*dpi,155*dpi,(this->item->getStringByTag("author")));

    //rect.adjust(30*dpi,150*dpi,100*dpi,25*dpi);
    painter.drawText(30*dpi,190*dpi,QString("馆藏数量:"));
    //rect.adjust(150*dpi,150*dpi,60*dpi,25*dpi);
    painter.drawText(120*dpi,190*dpi,QString::number(this->item->getIntByTag("total")));
    //rect.adjust(230*dpi,150*dpi,100*dpi,25*dpi);
    painter.drawText(230*dpi,190*dpi,QString("剩余数量:"));
    //rect.adjust(340*dpi,150*dpi,60*dpi,25*dpi);
    painter.drawText(320*dpi,190*dpi,QString::number(this->item->getIntByTag("amount")));

    painter.drawLine(30*dpi,210*dpi,510*dpi,210*dpi);

    //rect.adjust(30*dpi,250*dpi,60*dpi,25*dpi);
    painter.drawText(30*dpi,240*dpi,QString("姓名："));
    //rect.adjust(90*dpi,250*dpi,100*dpi,25*dpi);
    painter.drawText(90*dpi,240*dpi,(this->borrower->getStringByTag("name")));
    //rect.adjust(200*dpi,250*dpi,140*dpi,25*dpi);
    painter.drawText(220*dpi,240*dpi,QString("学号/教师编号:"));
    //rect.adjust(340*dpi,250*dpi,140*dpi,25*dpi);
    painter.drawText(360*dpi,240*dpi,(this->borrower->getStringByTag("id")));
    //rect.adjust(30*dpi,310*dpi,60*dpi,25*dpi);
    painter.drawText(30*dpi,275*dpi,QString("权限:"));
    //rect.adjust(90*dpi,310*dpi,100*dpi,25*dpi);
    painter.drawText(90*dpi,275*dpi,(this->borrower->getStringByTag("authority")));
    //rect.adjust(240*dpi,310*dpi,100*dpi,25*dpi);
    painter.drawText(240*dpi,275*dpi,QString("信用等级:"));
    //rect.adjust(350*dpi,310*dpi,100*dpi,25*dpi);
    painter.drawText(350*dpi,275*dpi,(this->borrower->getStringByTag("credit")));

}

void ResvForm::comfirm(){
    qDebug()<<"Entering function";
    reservation(item,borrower);
    saveXml();
    saveXml2();
    popUp->setVisible(true);

}

void ResvForm::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        //改变并存储鼠标形状
        QCursor cursor;
        cursor.setShape(Qt::ClosedHandCursor);
        QApplication::setOverrideCursor(cursor);

        //计算鼠标位置与界面位置的差值
        offset=event->globalPos()-this->pos();
    }
}

void ResvForm::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton)
    {
        //计算需要移动到的新位置
        QPoint temp;
        temp=event->globalPos()-offset;

        //移动界面
        move(temp);
    }
}

void ResvForm::mouseReleaseEvent(QMouseEvent *event)
{
    //恢复鼠标形状
    QApplication::restoreOverrideCursor();
}
