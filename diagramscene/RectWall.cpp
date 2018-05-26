#include "RectWall.h"
#include "Global.h"
#include "diagramscene.h"
#include <QtWidgets>
#include <QtGUi>
#include <QtCore>
#include <QtMath>



RectWall::RectWall(DiagramItem * rect, RectWallType type)
	: rect(rect),
	type(type)
{
	// setFlag(ItemIsMovable);
	setCursor(Qt::CursorShape::PointingHandCursor);
}

RectWall::~RectWall()
{
	for(auto rw : windows)
	{
		delete rw;
	}
}

QRectF RectWall::boundingRect() const
{
	QPointF diff;
	switch (type)
	{
	case WALL_TOP:
		diff = rect->myPolygon.at(1) - rect->myPolygon.at(0);
		return QRectF(rect->myPolygon.at(0).x()-3,
			rect->myPolygon.at(0).y()-3,
			diff.x()+6,
			diff.y()+6);
		break;
	case WALL_RIGHT:
		diff = rect->myPolygon.at(2) - rect->myPolygon.at(1);
		return QRectF(rect->myPolygon.at(1).x()-3,
			rect->myPolygon.at(1).y()-3,
			diff.x()+6,
			diff.y()+6);
		break;
	case WALL_BOTTOM:
		diff = rect->myPolygon.at(3) - rect->myPolygon.at(2);
		return QRectF(rect->myPolygon.at(2).x()-3,
			rect->myPolygon.at(2).y()-3,
			diff.x()+6,
			diff.y()+6);
		break;
	case WALL_LEFT:
		diff = rect->myPolygon.at(4) - rect->myPolygon.at(3);
		return QRectF(rect->myPolygon.at(3).x()-3,
			rect->myPolygon.at(3).y()-3,
			diff.x()+6,
			diff.y()+6);
		break;
	}
}


void RectWall::paint(QPainter *                       painter,
	const QStyleOptionGraphicsItem * option,
	QWidget *                        widget)
{

}

void RectWall::MoveWindows(QPointF pos)
{
	for (auto rw : windows)
	{
		rw->Move(pos);
	}
}

void RectWall::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	if(g_scene != nullptr)
	{
		if(g_scene->GetMyMode() == DiagramScene::Mode::InsertItem &&  g_scene->GetMyItemType() == DiagramItem::DiagramType::Window)
		{
			RectWindow* newWin = new RectWindow(this, event->pos());
			windows.push_back(newWin);
			g_scene->addItem(newWin);
            newWin->setPos(this->pos());
			newWin->SetRatio(event->scenePos());
			emit g_scene->itemInsertedOther(DiagramItem::DiagramType::Window,newWin);
		}
	}
	mouseStartPos = event->pos();
	update();
	QGraphicsItem::mousePressEvent(event);
}

void RectWall::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
	switch (type)
	{
	case WALL_TOP:
		break;
	case WALL_RIGHT:
		break;
	case WALL_BOTTOM:
		break;
	case WALL_LEFT:
		break;
	}
}

void RectWall::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
	update();
	QGraphicsItem::mouseReleaseEvent(event);
}
