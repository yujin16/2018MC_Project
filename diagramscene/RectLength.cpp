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

	// painter->drawText(0, -1*rect->boundingRect().height()/2+10, QString::number(rect->boundingRect().width()));
	// painter->drawText(rect->boundingRect().width()/2-10, 0, QString::number(rect->boundingRect().height()));
	painter->drawText(rect->boundingRect(),Qt::AlignHCenter | Qt::AlignTop, QString::number(rect->boundingRect().width()));
	painter->drawText(rect->boundingRect(), Qt::AlignCenter | Qt::AlignRight, QString::number(rect->boundingRect().height()));
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
