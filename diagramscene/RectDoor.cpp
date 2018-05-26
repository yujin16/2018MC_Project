#include "RectDoor.h"
#include "RectWall.h"
#include <qmath.h>


RectDoor::RectDoor(RectWall * rectWall, const QPointF & center)
	: rectWall(rectWall),
	center(center)
{
	wallExpand = rectWall->wallExpand;
	sumExpand = wallExpand + expand;
	// setFlag(QGraphicsItem::ItemIsMovable, true);
	// setFlag(QGraphicsItem::ItemIsSelectable, true);
	// setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

QRectF RectDoor::boundingRect() const
{
	QPointF diff;
	qreal   tx;
	qreal   ty;
	qreal   twidth;
	qreal   theight;
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
	if (diff.x() > 0)
	{
		tx = rectWall->rect->myPolygon.at(idx).x() - expand;
		twidth = diff.x() + expand * 2;
	}
	else
	{
		tx = rectWall->rect->myPolygon.at(idx).x() + expand;
		twidth = diff.x() - expand * 2;
	}
	if (diff.y() > 0)
	{
		ty = rectWall->rect->myPolygon.at(idx).y() - expand;
		theight = diff.y() + expand * 2;
	}
	else
	{
		ty = rectWall->rect->myPolygon.at(idx).y() + expand;
		theight = diff.y() - expand * 2;
	}
	return QRectF(tx, ty, twidth, theight);

}


void RectDoor::paint(QPainter *                       painter,
	const QStyleOptionGraphicsItem * option,
	QWidget *                        widget)
{
	QRectF boundRec = boundingRect();
	QPen recPen(Qt::gray);
	recPen.setWidth(2);
	recPen.setStyle(Qt::PenStyle::SolidLine);

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
	startX = rectWall->rect->myPolygon.at(idx).x();
	startY = rectWall->rect->myPolygon.at(idx).y();
	endX = rectWall->rect->myPolygon.at(idx + 1).x();
	endY = rectWall->rect->myPolygon.at(idx + 1).y();
	startPos = QPointF(startX, startY);
	endPos = QPointF(endX, endY);

	//Draw Arrow
	QPointF arrow = endPos - startPos;
	QPointF drawS = startPos + arrow*ratio;

	qreal arrowLen = arrow.x()*arrow.x() + arrow.y()*arrow.y();
	qreal divider = qSqrt(winLen*winLen / arrowLen);

	QPointF tarDrawS = drawS + arrow*divider;

	painter->setPen(recPen);
	painter->drawLine(drawS, tarDrawS);

	//Draw Open door

	QTransform transform;
	transform.rotate(270);
	QPointF arrowPerpen = transform.map(arrow);
	QPointF tarPerpen= drawS + arrowPerpen*divider*0.2;

	painter->setPen(recPen);
	painter->drawLine(drawS, tarPerpen);
	painter->drawLine(tarDrawS, tarPerpen);
}

void RectDoor::Move(QPointF pos)
{
	setPos(pos);
}

void RectDoor::SetRatio(QPointF mousePos)
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
	startX = scenePos().x() + rectWall->rect->myPolygon.at(idx).x();
	startY = scenePos().y() + rectWall->rect->myPolygon.at(idx).y();
	endX = scenePos().x() + rectWall->rect->myPolygon.at(idx + 1).x();
	endY = scenePos().y() + rectWall->rect->myPolygon.at(idx + 1).y();

	startPos = QPointF(startX, startY);
	endPos = QPointF(endX, endY);

	QPointF arrow = endPos - startPos;
	qreal   arrowLen = qSqrt(arrow.x() * arrow.x() + arrow.y() * arrow.y());

	QPointF rectStart = QPointF(startX, startY);

	QPointF diffR = mousePos - rectStart;
	qreal   diffLen = qSqrt(diffR.x() * diffR.x() + diffR.y() * diffR.y());

	ratio = diffLen / arrowLen;
}

void RectDoor::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	update();
	QGraphicsItem::mousePressEvent(event);
}

void RectDoor::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
	update();
	QGraphicsItem::mouseReleaseEvent(event);
}
