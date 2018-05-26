#include "RectWindow.h"
#include "RectWall.h"
#include <qmath.h>


RectWindow::RectWindow(RectWall * rectWall, const QPointF & center)
	: rectWall(rectWall),
	  center(center)
{
	wallExpand = rectWall->wallExpand;
	// setFlag(QGraphicsItem::ItemIsMovable, true);
	// setFlag(QGraphicsItem::ItemIsSelectable, true);
	// setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

QRectF RectWindow::boundingRect() const
{
	return QRectF(rectWall->boundingRect().x(),
	              rectWall->boundingRect().y(),
	              rectWall->boundingRect().width(),
	              rectWall->boundingRect().height());
}


void RectWindow::paint(QPainter *                       painter,
                       const QStyleOptionGraphicsItem * option,
                       QWidget *                        widget)
{
	QRectF boundRec = boundingRect();
	QPen   recPen(Qt::blue);
	recPen.setWidth(4);
	recPen.setStyle(Qt::PenStyle::SolidLine);



	qreal   startX;
	qreal   startY;
	qreal   endX;
	qreal   endY;
	QPointF startPos;
	QPointF endPos;
	QPointF diff;
	int idx;
	switch (rectWall->type)
	{
	case RectWall::WALL_TOP:
		idx = 0;
		break;
	case RectWall::WALL_RIGHT:
		idx = 1;
		break;
	case RectWall::WALL_BOTTOM:
		idx = 2;
		break;
	case RectWall::WALL_LEFT:
		idx = 3;
		break;
	}
	diff = rectWall->rect->myPolygon.at(idx + 1) - rectWall->rect->myPolygon.at(idx);
	startX = rectWall->rect->myPolygon.at(idx).x();
	startY = rectWall->rect->myPolygon.at(idx).y();
	endX = rectWall->rect->myPolygon.at(idx+1).x() ;
	endY = rectWall->rect->myPolygon.at(idx+1).y() ;
	
	startPos = QPointF(startX, startY);
	endPos = QPointF(endX, endY);


	QPointF arrow = endPos - startPos;
	QPointF drawS = startPos + arrow * ratio;

	qreal arrowLen = arrow.x() * arrow.x() + arrow.y() * arrow.y();
	qreal divider  = qSqrt(winLen * winLen / arrowLen);

	QPointF tarDrawS = drawS + arrow * divider;


	painter->setPen(recPen);
	painter->drawLine(drawS, tarDrawS);
	// painter->drawRect(boundRec);
}

void RectWindow::Move(QPointF pos)
{
	setPos(pos);
}

void RectWindow::SetRatio(QPointF mousePos)
{
	QRectF boundRec = boundingRect();
	qreal   startX;
	qreal   startY;
	qreal   endX;
	qreal   endY;
	QPointF startPos;
	QPointF endPos;
	int idx;
	switch (rectWall->type)
	{
	case RectWall::WALL_TOP:
		idx = 0;
		break;
	case RectWall::WALL_RIGHT:
		idx = 1;
		break;
	case RectWall::WALL_BOTTOM:
		idx = 2;
		break;
	case RectWall::WALL_LEFT:
		idx = 3;
		break;
	}
	startX = scenePos().x()+rectWall->rect->myPolygon.at(idx).x();
	startY = scenePos().y()+ rectWall->rect->myPolygon.at(idx).y();
	endX = scenePos().x()+ rectWall->rect->myPolygon.at(idx + 1).x();
	endY = scenePos().y()+ rectWall->rect->myPolygon.at(idx + 1).y();

	startPos = QPointF(startX, startY);
	endPos = QPointF(endX, endY);


	QPointF arrow    = endPos - startPos;
	qreal   arrowLen = qSqrt(arrow.x() * arrow.x() + arrow.y() * arrow.y());

	QPointF rectStart = QPointF(startX, startY);

	QPointF diff    = mousePos - rectStart;
	qreal   diffLen = qSqrt(diff.x() * diff.x() + diff.y() * diff.y());

	ratio = diffLen / arrowLen;
}

void RectWindow::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	update();
	QGraphicsItem::mousePressEvent(event);
}

void RectWindow::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
	update();
	QGraphicsItem::mouseReleaseEvent(event);
}
