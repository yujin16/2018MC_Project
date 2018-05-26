#include "RectVertex.h"
#include <QtWidgets>
#include <QtGUi>
#include <QtCore>


RectVertex::RectVertex(DiagramItem * rect, RectVertexType type)
	: rect(rect), type(type)
{
	setCursor(Qt::CursorShape::SizeAllCursor);
}

QRectF RectVertex::boundingRect() const
{
	switch(type)
	{
	case TOP_LEFT:
		return QRectF(rect->boundingRect().x(), rect->boundingRect().y(), 3,3);
	case TOP_RIGHT:
		return QRectF(rect->boundingRect().x()+ rect->boundingRect().width(), rect->boundingRect().y(), 3,3);
	case BOTTOM_LEFT:
		return QRectF(rect->boundingRect().x(), rect->boundingRect().y()+rect->boundingRect().height(), 3,3);
	case BOTTOM_RIGHT:
		return QRectF(rect->boundingRect().x()+ rect->boundingRect().width(), rect->boundingRect().y() + rect->boundingRect().height(), 3,3);
	}
}


void RectVertex::paint(QPainter *                       painter,
	const QStyleOptionGraphicsItem * option,
	QWidget *                        widget)
{
	QRectF rec = boundingRect();
	QPen pointpen(Qt::red);
	pointpen.setWidth(3);

	painter->setPen(pointpen);
	painter->drawPoint(QPoint(rec.x(), rec.y()));
}

void RectVertex::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	update();
	QGraphicsItem::mousePressEvent(event);
}

void RectVertex::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
	update();
	QGraphicsItem::mouseReleaseEvent(event);
}
