#include "RectWall.h"
#include "Global.h"
#include "diagramscene.h"
#include <QtWidgets>
#include <QtGUi>
#include <QtCore>
#include <QtMath>
#include "RectDoor.h"


RectWall::RectWall(DiagramItem * rect, RectWallType type)
	: rect(rect),
	  type(type)
{
	// setFlag(ItemIsMovable);
	setCursor(Qt::CursorShape::PointingHandCursor);
}

RectWall::~RectWall()
{
	for (auto rw : windows)
	{
		delete rw;
	}
	for (auto drs : doors)
	{
		delete drs;
	}
}

QRectF RectWall::boundingRect() const
{
	QPointF diff;
	qreal   tx;
	qreal   ty;
	qreal   twidth;
	qreal   theight;
	int idx;
	switch (type)
	{
	case WALL_TOP:
		idx = 0;
		break;
	case WALL_RIGHT:
		idx = 1;
		break;
	case WALL_BOTTOM:
		idx = 2;
		break;
	case WALL_LEFT:
		idx = 3;
		break;
	}
		diff = rect->myPolygon.at(idx+1) - rect->myPolygon.at(idx);
	if (diff.x() > 0)
	{
		tx     = rect->myPolygon.at(idx).x() - wallExpand;
		twidth = diff.x() + wallExpand * 2;
	}
	else
	{
		tx     = rect->myPolygon.at(idx).x() + wallExpand;
		twidth = diff.x() - wallExpand * 2;
	}
	if (diff.y() > 0)
	{
		ty      = rect->myPolygon.at(idx).y() - wallExpand;
		theight = diff.y() + wallExpand * 2;
	}
	else
	{
		ty      = rect->myPolygon.at(idx).y() + wallExpand;
		theight = diff.y() - wallExpand * 2;
	}
	return QRectF(tx, ty, twidth, theight);
}


void RectWall::paint(QPainter *                       painter,
                     const QStyleOptionGraphicsItem * option,
                     QWidget *                        widget)
{
	QRectF boundRec = boundingRect();
	QPen   recPen(Qt::green);

	painter->setPen(recPen);
	// painter->drawRect(boundRec);
}

void RectWall::MoveWindows_Doors(QPointF pos)
{
	for (auto rw : windows)
	{
		rw->Move(pos);
	}
	for (auto drs : doors)
	{
		drs->Move(pos);
	}
}

void RectWall::UpdateAll()
{
	for (auto rw : windows)
	{
		rw->update();
	}
	for (auto drs : doors)
	{
		drs->update();
	}
}

void RectWall::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	if (g_scene != nullptr)
	{
		if (g_scene->GetMyMode() == DiagramScene::Mode::InsertItem && g_scene->
			GetMyItemType() == DiagramItem::DiagramType::Window)
		{
			RectWindow * newWin = new RectWindow(this, event->pos());
			windows.push_back(newWin);
			g_scene->addItem(newWin);
			newWin->setPos(this->pos());
			newWin->SetRatio(event->scenePos());
			emit g_scene->itemInsertedOther(DiagramItem::DiagramType::Window, newWin);
		}
		if (g_scene->GetMyMode() == DiagramScene::Mode::InsertItem && g_scene->
			GetMyItemType() == DiagramItem::DiagramType::Door)
		{
			RectDoor * newDoor = new RectDoor(this, event->pos());
			doors.push_back(newDoor);
			g_scene->addItem(newDoor);
			newDoor->setPos(this->pos());
			newDoor->SetRatio(event->scenePos());
			emit g_scene->itemInsertedOther(DiagramItem::DiagramType::Door, newDoor);
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
