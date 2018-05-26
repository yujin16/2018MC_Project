#include "RectVertex.h"
#include <QtWidgets>
#include <QtGUi>
#include <QtCore>


RectVertex::RectVertex(DiagramItem * rect, RectVertexType type)
	: rect(rect),
	  type(type)
{
	setFlag(ItemIsMovable);
	switch (type)
	{
	case TOP_LEFT:
		setCursor(Qt::CursorShape::SizeFDiagCursor);
		break;
	case TOP_RIGHT:
		setCursor(Qt::CursorShape::SizeBDiagCursor);
		break;
	case BOTTOM_RIGHT:
		setCursor(Qt::CursorShape::SizeFDiagCursor);
		break;
	case BOTTOM_LEFT:
		setCursor(Qt::CursorShape::SizeBDiagCursor);
		break;
	}
}

QRectF RectVertex::boundingRect() const
{
	switch (type)
	{
	case TOP_LEFT:
		return QRectF(rect->myPolygon.at(0).x() - vertexExpand,
		              rect->myPolygon.at(0).y() - vertexExpand,
		              vertexExpand*2,
		              vertexExpand*2);
	case TOP_RIGHT:
		return QRectF(rect->myPolygon.at(1).x() - vertexExpand,
		              rect->myPolygon.at(1).y() - vertexExpand,
		              vertexExpand*2,
		              vertexExpand*2);
	case BOTTOM_RIGHT:
		return QRectF(rect->myPolygon.at(2).x() - vertexExpand,
		              rect->myPolygon.at(2).y() - vertexExpand,
		              vertexExpand*2,
		              vertexExpand*2);
	case BOTTOM_LEFT:
		return QRectF(rect->myPolygon.at(3).x() - vertexExpand,
		              rect->myPolygon.at(3).y() - vertexExpand,
		              vertexExpand*2,
		              vertexExpand*2);
	}
}


void RectVertex::paint(QPainter *                       painter,
                       const QStyleOptionGraphicsItem * option,
                       QWidget *                        widget)
{
	QRectF rec = boundingRect();

	QPen   pointpen(Qt::red);
	pointpen.setWidth(2);

	painter->setPen(pointpen);
	// painter->drawRect(rec);
	painter->drawPoint(rec.center());

}

void RectVertex::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	mouseStartPos = event->pos();
	update();
	QGraphicsItem::mousePressEvent(event);
}

void RectVertex::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
	// QPointF diff = mouseStartPos - event->pos();
	switch (type)
	{
	case TOP_LEFT:
		rect->myPolygon.replace(0, event->pos());
		rect->myPolygon.replace(4, event->pos());
		break;
	case TOP_RIGHT:
		rect->myPolygon.replace(1, event->pos());
		break;
	case BOTTOM_RIGHT:
		rect->myPolygon.replace(2, event->pos());
		break;
	case BOTTOM_LEFT:
		rect->myPolygon.replace(3, event->pos());
		break;
	}
	rect->setPolygon(rect->myPolygon);
	// rect->UpdateAll();
	// QGraphicsItem::mouseMoveEvent(event);
}

void RectVertex::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
	update();
	QGraphicsItem::mouseReleaseEvent(event);
}
