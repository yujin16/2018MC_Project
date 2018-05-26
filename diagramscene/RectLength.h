#pragma once
#include <QRect>
#include <QGraphicsLineItem>
#include <QBrush>
#include <QPainter>
#include "diagramitem.h"

class RectLength:public QGraphicsItem
{
public:
	RectLength(DiagramItem* rect);


	
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
protected:
	DiagramItem* rect;
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};
