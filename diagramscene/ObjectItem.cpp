#include "ObjectItem.h"

ObejectItem::ObejectItem(DiagramItem * rect)
	:rect(rect)
{
	// setFlag(ItemIsMovable);
	/*QPainter *painter();
	QPixmap pixmap("images/Washer.png");
	painter->drawPixmap(0, 0, 100, 100, pixmap);*/
}

QRectF ObejectItem::boundingRect() const
{
	return QRectF(rect->boundingRect().x(), rect->boundingRect().y(), rect->boundingRect().width(), rect->boundingRect().height());
}


void ObejectItem::paint(QPainter *painter,
	const QStyleOptionGraphicsItem * option,
	QWidget *widget)
{
	QRectF rec = boundingRect();
	
	/*label = new QLabel(widget);

	image.load("images/Washer.png");
	buffer = QPixmap::fromImage(image);

	label->setPixmap(buffer);
	label->show();*/

	//QPixmap pixmap("images/Washer.png");
	//painter->drawPixmap(0, 0, 100, 100, pixmap);
	QString s = "debug";

	s = rect->diaType();

	switch (rect->diaType()) {
	case 4: s = "Washer"; break;
	case 5: s = "Desk"; break;
	case 6: s = "TV"; break;
	case 7: s = "Refrig"; break;
	}

	QFont font = painter->font();
	font.setPointSize(5);
	painter->setFont(font);
	painter->drawText(rec, Qt::AlignHCenter | Qt::AlignCenter, s);
	//painter->drawText(rec, Qt::AlignCenter | Qt::AlignRight, QString::number(rect->boundingRect().height()));
}

void ObejectItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	update();
	QGraphicsItem::mousePressEvent(event);
}

void ObejectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
	update();
	QGraphicsItem::mouseReleaseEvent(event);
}