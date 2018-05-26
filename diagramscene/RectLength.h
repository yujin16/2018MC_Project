#pragma once
#include <QRect>
#include <QGraphicsLineItem>
#include <QBrush>
#include <QPainter>

class RectLength:public QGraphicsItem
{
public:
	RectLength();

	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	bool Pressed;
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};
