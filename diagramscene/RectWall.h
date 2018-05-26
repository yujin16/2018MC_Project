#pragma once
#include <QRect>
#include <QGraphicsLineItem>
#include <QBrush>
#include <QPainter>
#include "diagramitem.h"

class RectWall :public QGraphicsItem
{
public:
	enum RectWallType
	{
		WALL_TOP,
		WALL_RIGHT,
		WALL_BOTTOM,
		WALL_LEFT
	};
	RectWall(DiagramItem* rect, RectWallType type);

	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
	DiagramItem* rect;
	RectWallType type;
	QPointF mouseStartPos;
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};
