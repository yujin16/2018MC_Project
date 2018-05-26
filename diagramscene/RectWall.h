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
<<<<<<< HEAD
	void MoveWindows_Doors(QPointF pos);
	void UpdateAll();
=======
	void MoveWindows(QPointF pos);
	QVector<RectWindow*> Get_Windows() { return windows; };
>>>>>>> 81e3d1c98b1b014d9f3422eb75a287c16c8b1925

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
