#include "RectWindow.h"
#include "RectWall.h"
#include <qmath.h>


RectWindow::RectWindow(RectWall * rectWall, const QPointF & center)
	: rectWall(rectWall),
	  center(center)
{
	// setFlag(QGraphicsItem::ItemIsMovable, true);
	// setFlag(QGraphicsItem::ItemIsSelectable, true);
	// setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

QRectF RectWindow::boundingRect() const
{
	return QRectF(rectWall->boundingRect().x(),
	              rectWall->boundingRect().y(),
	              rectWall->boundingRect().width(),
	              rectWall->boundingRect().height());
}


void RectWindow::paint(QPainter *                       painter,
                       const QStyleOptionGraphicsItem * option,
                       QWidget *                        widget)
{
	QRectF boundRec = boundingRect();
	QPen recPen(Qt::blue);
	recPen.setWidth(6);
	recPen.setStyle(Qt::PenStyle::SolidLine);
 //
	// qreal startX = rectWall->scenePos().x() + rectWall->boundingRect().x();
	// qreal startY = rectWall->scenePos().y() + rectWall->boundingRect().y();
	// qreal tarX = rectWall->scenePos().x() + rectWall->boundingRect().x() + rectWall->boundingRect().width();
	// qreal tarY = rectWall->scenePos().y() + rectWall->boundingRect().y() + rectWall->boundingRect().height();
	// QPointF rectStart = QPointF(startX, startY);
	// QPointF rectEnd = QPointF(tarX, tarY);
	// QPointF vec = rectEnd - rectStart;
	qreal startX = rectWall->scenePos().x() + rectWall->boundingRect().x()+3;
	qreal startY = rectWall->scenePos().y() + rectWall->boundingRect().y()+3;
	QPointF rectPos = QPointF(startX, startY);


	QPointF startPos = QPointF(boundRec.x()+3, boundRec.y()+3);
	QPointF endPos = QPointF(boundRec.x() + boundRec.width()-3, boundRec.y() + boundRec.height()-3);;
	QPointF arrow = endPos - startPos;
	QPointF drawS = startPos + arrow*ratio;

	qreal arrowLen = arrow.x()*arrow.x() + arrow.y()*arrow.y();
	qreal divider = qSqrt( winLen*winLen / arrowLen);

	QPointF tarDrawS = drawS + arrow*divider;
	

	painter->setPen(recPen);
	painter->drawLine(drawS, tarDrawS);
}

void RectWindow::Move(QPointF pos)
{
	setPos(pos);
}

void RectWindow::SetRatio(QPointF mousePos)
{

	// qreal startX = rectWall->scenePos().x() + rectWall->boundingRect().x() - rectWall->boundingRect().width() / 2;
	// qreal startY = rectWall->scenePos().y() + rectWall->boundingRect().y() - rectWall->boundingRect().height() / 2;
	// qreal tarX = rectWall->scenePos().x() + rectWall->boundingRect().x() + rectWall->boundingRect().width() / 2;
	// qreal tarY = rectWall->scenePos().y() + rectWall->boundingRect().y() + rectWall->boundingRect().height() / 2;
	// qreal startX = rectWall->scenePos().x() + rectWall->boundingRect().x();
	// qreal startY = rectWall->scenePos().y() + rectWall->boundingRect().y();
	// qreal tarX = rectWall->scenePos().x() + rectWall->boundingRect().x() + rectWall->boundingRect().width();
	// qreal tarY = rectWall->scenePos().y() + rectWall->boundingRect().y() + rectWall->boundingRect().height();
	// QPointF rectStart = QPointF(startX, startY);
	// QPointF rectEnd = QPointF(tarX, tarY);


	QRectF boundRec = boundingRect();
	QPointF startPos = QPointF(boundRec.x()+3, boundRec.y()+3);
	QPointF endPos = QPointF(boundRec.x() + boundRec.width() - 3, boundRec.y() + boundRec.height() - 3);;
	QPointF arrow = endPos - startPos;
	qreal arrowLen = qSqrt(arrow.x()*arrow.x() + arrow.y()*arrow.y());

	qreal startX = rectWall->scenePos().x() + rectWall->boundingRect().x()+3;
	qreal startY = rectWall->scenePos().y() + rectWall->boundingRect().y()+3;
	QPointF rectStart = QPointF(startX, startY);

	QPointF diff = mousePos- rectStart;
	qreal diffLen = qSqrt(diff.x()*diff.x() + diff.y()*diff.y());

	ratio = diffLen/arrowLen;
}

void RectWindow::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	update();
	QGraphicsItem::mousePressEvent(event);
}

void RectWindow::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
	update();
	QGraphicsItem::mouseReleaseEvent(event);
}
