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

#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H

#include <QGraphicsPixmapItem>
#include <QList>

QT_BEGIN_NAMESPACE
class QPixmap;
class QGraphicsItem;
class QGraphicsScene;
class QTextEdit;
class QGraphicsSceneMouseEvent;
class QMenu;
class QGraphicsSceneContextMenuEvent;
class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;
class QPolygonF;
QT_END_NAMESPACE

class Arrow;
class RectLength;
class RectVertex;
class RectWall;

//! [0]
class DiagramItem : public QGraphicsPolygonItem
{
public:
    enum { Type = UserType + 15 };
	enum DiagramType { Step, Door, StartEnd, Io, Window,Washer, Desk, TV, Refrig };

    DiagramItem(DiagramType diagramType, QMenu *contextMenu, QGraphicsItem *parent = 0);
	~DiagramItem();

    void removeArrow(Arrow *arrow);
    void removeArrows();
    DiagramType diagramType() const { return myDiagramType; }
    QPolygonF polygon() const { return myPolygon; }
    void addArrow(Arrow *arrow);
    QPixmap image() const;
    int type() const override { return Type;}
	int diaType() { return (int)myDiagramType; }

	void UpdateAll();

	RectLength * GetRectLength() const
	{
		return rectLength;
	}

	void SetRectLength(RectLength * rectLength)
	{
		this->rectLength = rectLength;
	}

	RectVertex * GetRectVertexTl() const
	{
		return rectVertexTL;
	}

	void SetRectVertexTl(RectVertex * rectVertexTl)
	{
		rectVertexTL = rectVertexTl;
	}

	RectVertex * GetRectVertexTr() const
	{
		return rectVertexTR;
	}

	void SetRectVertexTr(RectVertex * rectVertexTr)
	{
		rectVertexTR = rectVertexTr;
	}

	RectVertex * GetRectVertexBl() const
	{
		return rectVertexBL;
	}

	void SetRectVertexBl(RectVertex * rectVertexBl)
	{
		rectVertexBL = rectVertexBl;
	}

	RectVertex * GetRectVertexBr() const
	{
		return rectVertexBR;
	}

	void SetRectVertexBr(RectVertex * rectVertexBr)
	{
		rectVertexBR = rectVertexBr;
	}


	RectWall * GetRectWallT() const
	{
		return rectWallT;
	}

	void SetRectWallT(RectWall * rectWallT)
	{
		this->rectWallT = rectWallT;
	}

	RectWall * GetRectWallR() const
	{
		return rectWallR;
	}

	void SetRectWallR(RectWall * rectWallR)
	{
		this->rectWallR = rectWallR;
	}

	RectWall * GetRectWallB() const
	{
		return rectWallB;
	}

	void SetRectWallB(RectWall * rectWallB)
	{
		this->rectWallB = rectWallB;
	}

	RectWall * GetRectWallL() const
	{
		return rectWallL;
	}

	void SetRectWallL(RectWall * rectWallL)
	{
		this->rectWallL = rectWallL;
	}
	//PBW open private to public
    QPolygonF myPolygon;

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;


	void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;


private:
    DiagramType myDiagramType;
    QMenu *myContextMenu;
    QList<Arrow *> arrows;

	RectLength* rectLength = nullptr;

	RectVertex* rectVertexTL;
	RectVertex* rectVertexTR;
	RectVertex* rectVertexBL;
	RectVertex* rectVertexBR;

	RectWall* rectWallT;
	RectWall* rectWallR;
	RectWall* rectWallB;
	RectWall* rectWallL;
};
//! [0]

#endif // DIAGRAMITEM_H

