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
	QRectF rec = boundingRect();
	QPointF p0 = rect->myPolygon.at(0);
	QPointF p1 = rect->myPolygon.at(1);
	QPointF p2 = rect->myPolygon.at(2);
	QPointF p3 = rect->myPolygon.at(3);

	qreal p01len= qAbs(p1.x() - p0.x());
	qreal p12len= qAbs(p2.y() - p1.y());
	qreal p23len= qAbs(p3.x() - p2.x());
	qreal p34len= qAbs(p0.y() - p3.y());

	painter->drawText(rec,Qt::AlignHCenter | Qt::AlignTop, QString::number(p01len));
	painter->drawText(rec, Qt::AlignVCenter | Qt::AlignRight, QString::number(p12len));
	painter->drawText(rec, Qt::AlignHCenter | Qt::AlignBottom, QString::number(p23len));
	painter->drawText(rec, Qt::AlignLeft | Qt::AlignVCenter, QString::number(p34len));
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
