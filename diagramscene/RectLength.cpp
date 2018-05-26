#include "RectLength.h"


RectLength::RectLength(DiagramItem * rect)
	: rect(rect)
{
	setFlag(ItemIsMovable);
}

QRectF RectLength::boundingRect() const
{
	return QRectF(0, 0, rect->boundingRect().width(), rect->boundingRect().height());
}

void RectLength::paint(QPainter *                       painter,
                       const QStyleOptionGraphicsItem * option,
                       QWidget *                        widget)
{
	QRectF rec = boundingRect();
	QBrush brush(Qt::blue);

	// painter->fillRect(rec, brush);
	// painter->drawRect(rec);
	painter->drawText(0, 0, "Hello");
}

void RectLength::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	update();
	QGraphicsItem::mousePressEvent(event);
}

void RectLength::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
	update();
	QGraphicsItem::mouseReleaseEvent(event);
}
