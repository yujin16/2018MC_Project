#include "RectLength.h"


RectLength::RectLength(DiagramItem * rect)
	: rect(rect)
{
	// setFlag(ItemIsMovable);
}

QRectF RectLength::boundingRect() const
{
	return QRectF(rect->boundingRect().x(), rect->boundingRect().y(), rect->boundingRect().width(), rect->boundingRect().height());
}


void RectLength::paint(QPainter *                       painter,
                       const QStyleOptionGraphicsItem * option,
                       QWidget *                        widget)
{
	// painter->eraseRect(rect->boundingRect());
	QRectF rec = boundingRect();
	// painter->drawText(rect->boundingRect(),Qt::AlignHCenter | Qt::AlignTop, QString::number(rect->boundingRect().width()));
	// painter->drawText(rect->boundingRect(), Qt::AlignCenter | Qt::AlignRight, QString::number(rect->boundingRect().height()));
	painter->drawText(rec,Qt::AlignHCenter | Qt::AlignTop, QString::number(rect->boundingRect().width()));
	painter->drawText(rec, Qt::AlignCenter | Qt::AlignRight, QString::number(rect->boundingRect().height()));
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
