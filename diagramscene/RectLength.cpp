#include "RectLength.h"

RectLength::RectLength()
{
	Pressed = false;
	setFlag(ItemIsMovable);
}

QRectF RectLength::boundingRect() const
{
	return QRectF(0, 0, 100, 100);
}

void RectLength::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QRectF rec = boundingRect();
	QBrush brush(Qt::blue);

	if (Pressed)
	{
		brush.setColor(Qt::red);
	}
	else
	{
		brush.setColor(Qt::green);
	}

	painter->fillRect(rec, brush);
	painter->drawEllipse(rec);
	painter->drawRect(rec);
}

void RectLength::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	Pressed = true;
	update();
	QGraphicsItem::mousePressEvent(event);
}

void RectLength::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	Pressed = false;
	update();
	QGraphicsItem::mouseReleaseEvent(event);
}

