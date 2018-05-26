#pragma once
#include <QLabel>
#include "diagramitem.h"

class ObjectItem : public QGraphicsTextItem
{
public:
	ObjectItem(QGraphicsItem *parent = 0);
	QImage image;
	QPixmap buffer;

	void setImage(QString path);

protected:
	//void mousePressEvent(QGraphicsSceneMouseEvent *event);
	//void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
	//void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};