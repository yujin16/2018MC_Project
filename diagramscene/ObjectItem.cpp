#include "ObjectItem.h"

ObjectItem::ObjectItem(QGraphicsItem *parent)
	: QGraphicsTextItem(parent)
{
	setFlag(QGraphicsItem::ItemIsMovable);
	setFlag(QGraphicsItem::ItemIsSelectable);
}

void ObjectItem::setImage(QString path) {
	image.load(path);
	buffer = QPixmap::fromImage(image);
}