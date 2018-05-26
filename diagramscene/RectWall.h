#pragma once
#include <QRect>
#include <QGraphicsLineItem>
#include <QBrush>
#include <QPainter>
#include "diagramitem.h"
#include "RectWindow.h"
#include "RectDoor.h"

class DiagramScene;

class RectWall :public QGraphicsItem
{
	
public:
	friend class RectDoor;
	friend class RectWindow;
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
	void MoveWindows_Doors(QPointF pos);
	void UpdateAll();

protected:
	DiagramItem* rect;
	RectWallType type;
	QVector<RectWindow*> windows;
	QVector<RectDoor*> doors;
	QPointF mouseStartPos;
	int wallExpand = 20;
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};
