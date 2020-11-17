#include "ledscreen.h"
#include "ui_ledscreen.h"
#include <QBrush>

ledscreen::ledscreen(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ledscreen)
{


    ui->setupUi(this);
    //ui->labeltext->setTextFormat(Qt::PlainText);

    //setFixedHeight(fontMetrics().height());
    leftMargin = height() / 3;



    connect(&timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));

    timer.setInterval(5);
    qDebug() << "Aledscreen";
}

ledscreen::~ledscreen()
{
    delete ui;
}

void ledscreen::setlabelText(QString str)
{
    QFont font;
    //设置文字字体
    font.setFamily("宋体");
    //设置文字大小为50像素
    font.setPixelSize(50);
    //设置文字为粗体
    font.setBold(true);             //封装的setWeight函数
    //设置文字为斜体
    font.setItalic(true);           //封装的setStyle函数
    //设置文字大小
    font.setPointSize(20);
    //设置文字倾斜
    font.setStyle(QFont::StyleItalic);
    //设置文字粗细//enum Weight 存在5个值
    font.setWeight(QFont::Light);
    //设置文字上划线
    //font.setOverline(true);
    //设置文字下划线
    //font.setUnderline(true);
    //设置文字中划线
    //font.setStrikeOut(true);

    //设置字间距%
    font.setLetterSpacing(QFont::PercentageSpacing,300);          //300%,100为默认
    //设置字间距像素值
    font.setLetterSpacing(QFont::AbsoluteSpacing,20);             //设置字间距为100像素
    //设置首个字母大写（跟参数有关，也可以设置全部大写AllUppercase）
    font.setCapitalization(QFont::Capitalize);


    //通过QFontMetrics获取字体的值
    QFontMetrics fm(font);
    qDebug() << fm.height();            //获取文字高度
    qDebug() << fm.maxWidth();          //获取文字宽度


   // ui->labeltext->setFont(font);
   // ui->labeltext->setText(str);
}

QString ledscreen::text() const
{
    return _text;
}

void ledscreen::setText(QString text)
{
    _text = text;

    updateText();
    update();
}

QString ledscreen::separator() const
{
    return _separator;
}

void ledscreen::setSeparator(QString separator)
{
    _separator = separator;
    updateText();
    update();
}

void ledscreen::setLeftMargin(int pixels)
{
    leftMargin = pixels;
    update();
}

void ledscreen::updateText()
{
    qDebug() << "updateText";
    timer.stop();

    singleTextWidth = fontMetrics().width(_text);
    scrollEnabled = true;//(singleTextWidth > width() - leftMargin);
    qDebug() << "scrollEnabled" << scrollEnabled;
    qDebug() << "_separator : " << _separator;
    if(scrollEnabled)
    {
        scrollPos = -64;
        staticText.setText(_text + _separator);
        timer.start();
    }
    else
        staticText.setText(_text);
    qDebug() << "staticText : " << staticText.text();
    staticText.prepare(QTransform(), font());
    wholeTextSize = QSize(fontMetrics().width(staticText.text()), fontMetrics().height());
}

void ledscreen::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    qDebug() << "paintEvent";
    if(scrollEnabled)
    {
        buffer.fill(qRgba(255, 0, 0, 0));
        QPainter pb(&buffer);
        pb.setPen(p.pen());
        pb.setFont(p.font());
        QBrush brush;
        brush.setColor(QColor(255,255,0,0));
        pb.setBackground(brush);
        int x = qMin(-scrollPos, 0) + leftMargin;
        while(x < width())
        {
            pb.drawStaticText(QPointF(x, (height() - wholeTextSize.height()) / 2) + QPoint(2, 2), staticText);
            x += wholeTextSize.width();
        }

        //Apply Alpha Channel
        pb.setCompositionMode(QPainter::CompositionMode_DestinationIn);
        pb.setClipRect(width() - 15, 0, 15, height());
        pb.drawImage(0, 0, alphaChannel);
        pb.setClipRect(0, 0, 15, height());
        //initial situation: don't apply alpha channel in the left half of the image at all; apply it more and more until scrollPos gets positive
        if(scrollPos < 0)
            pb.setOpacity((qreal)(qMax(-8, scrollPos) + 8) / 8.0);
        pb.drawImage(0, 0, alphaChannel);

        //pb.end();
        p.drawImage(0, 0, buffer);
    }
    else
    {
        p.drawStaticText(QPointF(leftMargin, (height() - wholeTextSize.height()) / 2), staticText);
    }
}

void ledscreen::resizeEvent(QResizeEvent*)
{
    //When the widget is resized, we need to update the alpha channel.

    alphaChannel = QImage(size(), QImage::Format_ARGB32_Premultiplied);
    buffer = QImage(size(), QImage::Format_ARGB32_Premultiplied);

    //Create Alpha Channel:
    if(width() > 64)
    {
        //create first scanline
        QRgb* scanline1 = (QRgb*)alphaChannel.scanLine(0);
        for(int x = 1; x < 16; ++x)
            scanline1[x - 1] = scanline1[width() - x] = qRgba(0, 0, 0, x << 4);
        for(int x = 15; x < width() - 15; ++x)
            scanline1[x] = qRgb(0, 0, 0);
        //copy scanline to the other ones
        for(int y = 1; y < height(); ++y)
            memcpy(alphaChannel.scanLine(y), (uchar*)scanline1, width() * 4);
    }
    else
        alphaChannel.fill(qRgb(0, 0, 0));


    //Update scrolling state
    bool newScrollEnabled = (singleTextWidth > width() - leftMargin);
    if(newScrollEnabled != scrollEnabled)
        updateText();
}

void ledscreen::updateStop()
{
    qDebug() << "updateStop";
    timer.stop();
}


void ledscreen::timer_timeout()
{
    //qDebug() << "timer_timeout";
    scrollPos = (scrollPos + 2)
                % wholeTextSize.width();
    update();

}
