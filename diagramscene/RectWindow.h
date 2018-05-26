#pragma once
#include <QRect>
#include <QGraphicsLineItem>
#include <QBrush>
#include <QPainter>
#include "diagramitem.h"

class RectWindow :public QGraphicsItem
{
public:

	RectWindow(RectWall * rectWall, const QPointF & center);

	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void Move(QPointF pos);
	void SetRatio(QPointF mousePos);
	QPointF Get_Center() { return center;}

protected:
	RectWall* rectWall;
	QPointF center;
	qreal ratio;
	qreal winLen = 30;
	int wallExpand;
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};
