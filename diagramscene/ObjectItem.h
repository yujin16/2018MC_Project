#pragma once
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QImage>
#include <QPainter>
#include "diagramitem.h"

class ObejectItem :public QGraphicsItem
{
public:
	ObejectItem(DiagramItem* rect);

	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
	QLabel *label;
	QImage image;
	QPixmap buffer;

	DiagramItem* rect;
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};

/*label = new QLabel(parent);

			image.load("images/Washer.png");
			buffer = QPixmap::fromImage(image);

			label->setPixmap(buffer);
			label->show();*/