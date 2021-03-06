/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "diagramscene.h"
#include "arrow.h"

#include <QTextCursor>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <Windows.h>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include "RectLength.h"
#include "RectVertex.h"
#include "RectWall.h"
#include "ObjectItem.h"

//! [0]
DiagramScene::DiagramScene(QMenu *itemMenu, QObject *parent)
    : QGraphicsScene(parent)
{
    myItemMenu = itemMenu;
    myMode = MoveItem;
    myItemType = DiagramItem::Step;
    line = 0;
    textItem = 0;
    myItemColor = Qt::white;
    myTextColor = Qt::black;
    myLineColor = Qt::black;
}
//! [0]

//! [1]
void DiagramScene::setLineColor(const QColor &color)
{
    myLineColor = color;
    if (isItemChange(Arrow::Type)) {
        Arrow *item = qgraphicsitem_cast<Arrow *>(selectedItems().first());
        item->setColor(myLineColor);
        update();
    }
}
//! [1]

//! [2]
void DiagramScene::setTextColor(const QColor &color)
{
    myTextColor = color;
    if (isItemChange(DiagramTextItem::Type)) {
        DiagramTextItem *item = qgraphicsitem_cast<DiagramTextItem *>(selectedItems().first());
        item->setDefaultTextColor(myTextColor);
    }
}
//! [2]

//! [3]
void DiagramScene::setItemColor(const QColor &color)
{
    myItemColor = color;
    if (isItemChange(DiagramItem::Type)) {
        DiagramItem *item = qgraphicsitem_cast<DiagramItem *>(selectedItems().first());
        item->setBrush(myItemColor);
    }
}
//! [3]

//! [4]
void DiagramScene::setFont(const QFont &font)
{
    myFont = font;

    if (isItemChange(DiagramTextItem::Type)) {
        QGraphicsTextItem *item = qgraphicsitem_cast<DiagramTextItem *>(selectedItems().first());
        //At this point the selection can change so the first selected item might not be a DiagramTextItem
        if (item)
            item->setFont(myFont);
    }
}


//! [4]

void DiagramScene::setMode(Mode mode)
{
    myMode = mode;
}

void DiagramScene::setItemType(DiagramItem::DiagramType type)
{
    myItemType = type;
}

//! [5]
void DiagramScene::editorLostFocus(DiagramTextItem *item)
{
    QTextCursor cursor = item->textCursor();
    cursor.clearSelection();
    item->setTextCursor(cursor);

    if (item->toPlainText().isEmpty()) {
        removeItem(item);
        item->deleteLater();
    }
}
//! [5]

//! [6]
void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    DiagramItem *item;
    switch (myMode) {
        case InsertItem:
			// #wjw
			// #wjw
			//PBW
			if (myItemType == DiagramItem::DiagramType::Door) 
			{
				// RectWall will handle this
				break;
			}
			// if Window 
			if (myItemType == DiagramItem::DiagramType::Window)
			{
				// RectWall will handle this
				break;
			}
			//PBW
            item = new DiagramItem(myItemType, myItemMenu);
            item->setBrush(myItemColor);
            addItem(item);
            item->setPos(mouseEvent->scenePos());
			if (myItemType == DiagramItem::DiagramType::Step) 
			{
				RectLength* rl = new RectLength(item);
				rl->setPos(mouseEvent->scenePos());
				item->SetRectLength(rl);
				addItem(rl);

				RectWall* rw = new RectWall(item, RectWall::WALL_TOP);
				rw->setPos(mouseEvent->scenePos());
				item->SetRectWallT(rw);
				addItem(rw);
				RectWall* rw2 = new RectWall(item, RectWall::WALL_RIGHT);
				rw2->setPos(mouseEvent->scenePos());
				item->SetRectWallR(rw2);
				addItem(rw2);
				RectWall* rw3 = new RectWall(item, RectWall::WALL_BOTTOM);
				rw3->setPos(mouseEvent->scenePos());
				item->SetRectWallB(rw3);
				addItem(rw3);
				RectWall* rw4 = new RectWall(item, RectWall::WALL_LEFT);
				rw4->setPos(mouseEvent->scenePos());
				item->SetRectWallL(rw4);
				addItem(rw4);

				RectVertex* rv = new RectVertex(item,RectVertex::TOP_LEFT);
				rv->setPos(mouseEvent->scenePos());
				item->SetRectVertexTl(rv);
				addItem(rv);
				RectVertex* rv2 = new RectVertex(item,RectVertex::TOP_RIGHT);
				rv2->setPos(mouseEvent->scenePos());
				item->SetRectVertexTr(rv2);
				addItem(rv2);
				RectVertex* rv3 = new RectVertex(item,RectVertex::BOTTOM_LEFT);
				rv3->setPos(mouseEvent->scenePos());
				item->SetRectVertexBl(rv3);
				addItem(rv3);
				RectVertex* rv4 = new RectVertex(item,RectVertex::BOTTOM_RIGHT);
				rv4->setPos(mouseEvent->scenePos());
				item->SetRectVertexBr(rv4);
				addItem(rv4);


			}

            emit itemInserted(item);
            break;
//! [6] //! [7]
			//PBW Draw Line
        case InsertLine:
            line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                        mouseEvent->scenePos()));
            line->setPen(QPen(myLineColor, 2));
            addItem(line);
            break;
//! [7] //! [8]
        case InsertText:
            textItem = new DiagramTextItem();
            textItem->setFont(myFont);
            textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
            textItem->setZValue(1000.0);
            connect(textItem, SIGNAL(lostFocus(DiagramTextItem*)),
                    this, SLOT(editorLostFocus(DiagramTextItem*)));
            connect(textItem, SIGNAL(selectedChange(QGraphicsItem*)),
                    this, SIGNAL(itemSelected(QGraphicsItem*)));
            addItem(textItem);
            textItem->setDefaultTextColor(myTextColor);
            textItem->setPos(mouseEvent->scenePos());
            emit textInserted(textItem);
			break;
		case InsertWasher: case InsertTV: case InsertDesk: case InsertRefrig:
			item = new DiagramItem(myItemType, myItemMenu);
			item->setBrush(myItemColor);
			addItem(item);
			item->setPos(mouseEvent->scenePos());
			{

				char buff[100];
				sprintf(buff, "%d", myItemType);
				OutputDebugStringA(buff);

				ObejectItem* obj = new ObejectItem(item);
				obj->setPos(mouseEvent->scenePos());
				//item->SetRectLength(obj);
				addItem(obj);
			}
			emit objInserted(item);

			/*QImage image("images/Washer.png");

			QGraphicsPixmapItem item(QPixmap::fromImage(image));
			addItem(&item);
			QGraphicsView view = new QGraphicsView();
			view.show();

			QPixmap buf = QPixmap::fromImage(image);

			buf = buf.scaled(50, 50);


			QGraphicsScene* scene = new QGraphicsScene;
			graphicsView->setScene(scene);

			scene->addPixmap(buf);*/




			//widget = new QWidget;
			/*label = new QLabel();

			image.load("images/Washer.png");
			buffer = QPixmap::fromImage(image);

			label->setPixmap(buffer);
			widget->move(200, 200);
			label->show();*/


			//objItem = new ObjectItem(this);

			//objItem->setImage("images/Washer.png");
			//addItem(objItem);

			//emit objInserted(item);

			//label->setPixmap(buffer);
			//label->show();
			//라벨 생성해서 이미지 띄우기


			break;
		case MoveItem:
			OutputDebugString(L"Move Item");
			break;
//! [8] //! [9]
    default:
        ;
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}
//! [9]

//! [10]
void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (myMode == InsertLine && line != 0) {
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
    } else if (myMode == MoveItem) {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}
//! [10]

//! [11]
void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (line != 0 && myMode == InsertLine) {
        QList<QGraphicsItem *> startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line)
            endItems.removeFirst();

        removeItem(line);
        delete line;
//! [11] //! [12]

        if (startItems.count() > 0 && endItems.count() > 0 &&
            startItems.first()->type() == DiagramItem::Type &&
            endItems.first()->type() == DiagramItem::Type &&
            startItems.first() != endItems.first()) {
            DiagramItem *startItem = qgraphicsitem_cast<DiagramItem *>(startItems.first());
            DiagramItem *endItem = qgraphicsitem_cast<DiagramItem *>(endItems.first());
            Arrow *arrow = new Arrow(startItem, endItem);
            arrow->setColor(myLineColor);
            startItem->addArrow(arrow);
            endItem->addArrow(arrow);
            arrow->setZValue(-1000.0);
            addItem(arrow);
            arrow->updatePosition();
        }
    }
//! [12] //! [13]
    line = 0;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
//! [13]

//! [14]
bool DiagramScene::isItemChange(int type)
{
    foreach (QGraphicsItem *item, selectedItems()) {
        if (item->type() == type)
            return true;
    }
    return false;
}
//! [14]
