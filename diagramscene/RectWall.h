#pragma once
#include <QRect>
#include <QGraphicsLineItem>
#include <QBrush>
#include <QPainter>
#include "diagramitem.h"
#include "RectWindow.h"

class DiagramScene;

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
	~RectWall();

	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void MoveWindows(QPointF pos);
	QVector<RectWindow*> Get_Windows() { return windows; };

protected:
	DiagramItem* rect;
	RectWallType type;
	QVector<RectWindow*> windows;
	QPointF mouseStartPos;
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};
