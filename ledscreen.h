#ifndef LEDSCREEN_H
#define LEDSCREEN_H

#include <QFrame>
#include <QDebug>
#include <QStaticText>
#include <QTimer>
#include <QPainter>

namespace Ui {
class ledscreen;
}

class ledscreen : public QFrame
{
    Q_OBJECT

public:
    explicit ledscreen(QWidget *parent = nullptr);
    ~ledscreen();


private:
    Ui::ledscreen *ui;

    QString _text = "TEST";
    QString _separator = "\n";
    QStaticText staticText;
    int singleTextWidth;
    QSize wholeTextSize;
    int leftMargin;
    bool scrollEnabled;
    int scrollPos;
    QImage alphaChannel;
    QImage buffer;
    QTimer timer;

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void resizeEvent(QResizeEvent *);

public slots:
    QString text() const;
    void setText(QString text);
    void setlabelText(QString str);
    void updateText();
    void updateStop();
    QString separator() const;
    void setSeparator(QString separator);
    void setLeftMargin(int pixels);

private slots:
    void timer_timeout();
};

#endif // LEDSCREEN_H
