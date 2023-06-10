#include "logowidget.h"
#include <QPainter>

LogoWidget::LogoWidget(QWidget *parent)
    : QWidget(parent)
{  
}



void LogoWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    // Drawing black background
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, width(), height());

    int field = 10;

    // Set pen to white for drawing the border
    QPen pen(Qt::white);

    // Set the width of the pen
    int penWidth = 10;
    pen.setWidth(penWidth);

    // Assign the pen to the painter
    painter.setPen(pen);

    // Draw a rectangle as border with the field
    QRect rectangle(field, field, width() - 2*field, height() - 2*field);
    painter.drawRect(rectangle);

    // Set font color to turquoise
    painter.setPen(Qt::cyan);

    // Set the font size, weight and style
    QFont font("Open Sans", 150);
    font.setBold(true);
    painter.setFont(font);

    // Drawing the letter 'S' in the middle of the rectangle
    painter.drawText(rectangle, Qt::AlignCenter, "S");
}
