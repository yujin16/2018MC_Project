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

#include "arrow.h"
#include "diagramitem.h"
#include "diagramscene.h"
#include "diagramtextitem.h"
#include "mainwindow.h"
#include "RectVertex.h"
#include "RectWall.h"
#include <QDebug>
#include "Global.h"

#include <QtWidgets>

const int InsertTextButton = 10;


//! [0]
MainWindow::MainWindow()
{
    createActions();
    createToolBox();
    createMenus();

    scene = new DiagramScene(itemMenu, this);
	g_scene = scene;
    scene->setSceneRect(QRectF(0, 0, 5000, 5000));
    connect(scene, SIGNAL(itemInserted(DiagramItem*)),
            this, SLOT(itemInserted(DiagramItem*)));
	connect(scene, SIGNAL(itemInsertedOther(DiagramItem::DiagramType,QGraphicsItem*)),
		this, SLOT(itemInsertedOther(DiagramItem::DiagramType, QGraphicsItem*)));
    connect(scene, SIGNAL(textInserted(QGraphicsTextItem*)),
            this, SLOT(textInserted(QGraphicsTextItem*)));
	connect(scene, SIGNAL(objInserted(DiagramItem*)),
		this, SLOT(objInserted(DiagramItem*)));
    connect(scene, SIGNAL(itemSelected(QGraphicsItem*)),
            this, SLOT(itemSelected(QGraphicsItem*)));
	connect(scene, SIGNAL(valueChanged(QGraphicsItem*)),
		this, SLOT(itemChanged()));
    createToolbars();

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(toolBox);
    view = new QGraphicsView(scene);
    layout->addWidget(view);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

	itemchanged = false;

    setCentralWidget(widget);
    setWindowTitle(tr("Diagramscene"));
    setUnifiedTitleAndToolBarOnMac(true);

	sceneScaleChanged("150%");
	sceneScaleCombo->setCurrentIndex(4);
}
//! [0]

//! [1]
void MainWindow::backgroundButtonGroupClicked(QAbstractButton *button)
{
    QList<QAbstractButton *> buttons = backgroundButtonGroup->buttons();
    foreach (QAbstractButton *myButton, buttons) {
        if (myButton != button)
            button->setChecked(false);
    }
    QString text = button->text();
    if (text == tr("Blue Grid"))
        scene->setBackgroundBrush(QPixmap(":/images/background1.png"));
    else if (text == tr("White Grid"))
        scene->setBackgroundBrush(QPixmap(":/images/background2.png"));
    else if (text == tr("Gray Grid"))
        scene->setBackgroundBrush(QPixmap(":/images/background3.png"));
    else
        scene->setBackgroundBrush(QPixmap(":/images/background4.png"));

    scene->update();
    view->update();
}
//! [1]

//! [2]
void MainWindow::buttonGroupClicked(int id)
{
    QList<QAbstractButton *> buttons = buttonGroup->buttons();
    foreach (QAbstractButton *button, buttons) {
        if (buttonGroup->button(id) != button)
            button->setChecked(false);
    }
    if (id == InsertTextButton) {
		scene->setMode(DiagramScene::InsertText);
	} else if(id == DiagramItem::DiagramType::Washer
		|| id == DiagramItem::DiagramType::Desk
		|| id == DiagramItem::DiagramType::TV
		|| id == DiagramItem::DiagramType::Refrig) {

		DiagramItem::DiagramType type = (DiagramItem::DiagramType)id;

		scene->setItemType(DiagramItem::DiagramType(id));
		switch(type)
		{
		case DiagramItem::Washer:
			scene->setMode(DiagramScene::Mode::InsertWasher);
			break;
		case DiagramItem::Desk:
			scene->setMode(DiagramScene::Mode::InsertDesk);
			break;
		case DiagramItem::TV:
			scene->setMode(DiagramScene::Mode::InsertTV);
			break;
		case DiagramItem::Refrig:
			scene->setMode(DiagramScene::Mode::InsertRefrig);
			break;
		}
	} 
	else {
        scene->setItemType(DiagramItem::DiagramType(id));
        scene->setMode(DiagramScene::InsertItem);
    }
}
//! [2]

//! [3]
void MainWindow::deleteItem()
{
    foreach (QGraphicsItem *item, scene->selectedItems()) {
        if (item->type() == Arrow::Type) {
            scene->removeItem(item);
            Arrow *arrow = qgraphicsitem_cast<Arrow *>(item);
            arrow->startItem()->removeArrow(arrow);
            arrow->endItem()->removeArrow(arrow);

			//added by #wjw
			for (auto it = Item_List.begin(); it != Item_List.end(); it++)
			{
				if (*it == item)
					Item_List.erase(it);
			}

            delete item;
        }
    }

    foreach (QGraphicsItem *item, scene->selectedItems()) {
         if (item->type() == DiagramItem::Type)
             qgraphicsitem_cast<DiagramItem *>(item)->removeArrows();
         scene->removeItem(item);
         delete item;
     }
}
//! [3]

//! [4]
void MainWindow::pointerGroupClicked(int)
{
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
}
//! [4]

//! [5]
void MainWindow::bringToFront()
{
    if (scene->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = scene->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if (item->zValue() >= zValue && item->type() == DiagramItem::Type)
            zValue = item->zValue() + 0.1;
    }
    selectedItem->setZValue(zValue);
}
//! [5]

//! [6]
void MainWindow::sendToBack()
{
    if (scene->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = scene->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if (item->zValue() <= zValue && item->type() == DiagramItem::Type)
            zValue = item->zValue() - 0.1;
    }
    selectedItem->setZValue(zValue);
}
bool MainWindow::Save()
{
	if (curFile.isEmpty()) {
		return SaveAs();
	}
	else {
		return saveFile(curFile);
	}
}
bool MainWindow::SaveAs()
{
	QFileDialog dialog(this); // file 저장 경로 지정 창 띄우기
	dialog.setWindowModality(Qt::WindowModal);
	dialog.setAcceptMode(QFileDialog::AcceptSave);
	if (dialog.exec() != QDialog::Accepted)
		return false;
	return saveFile(dialog.selectedFiles().first());
}
bool MainWindow::saveFile(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Application"),
			tr("Cannot write file %1:\n%2.")
			.arg(QDir::toNativeSeparators(fileName),
				file.errorString()));
		return false;
	}	
	QTextStream out(&file);
	// out.setVersion(QDataStream::Qt_5_10);
	// QTextStream out(&file);
	// out << textEdit->toPlainText();
	// out << scene->items();  // is this doing alright?? #wjw
	
	QVector<RectWindow*> temp_vector;
	for (int i = 0; i < Item_List.size(); i++)
	{
		out << "item#" << i << "\n";
		out << Item_List[i]->diagramType() << "\n";
		for (int j = 0; j < 4; j++)
			out << Item_List[i]->myPolygon.at(j).x() << "," << Item_List[i]->myPolygon.at(j).y() << "\n";

		if (Item_List[i]->diagramType() != 0)
			continue;
		out << Item_List[i]->GetRectVertexTl()->x() << "," << Item_List[i]->GetRectVertexTl()->y() << "\n";
		out << Item_List[i]->GetRectVertexTr()->x() << "," << Item_List[i]->GetRectVertexTr()->y() << "\n";
		out << Item_List[i]->GetRectVertexBl()->x() << "," << Item_List[i]->GetRectVertexBl()->y() << "\n";
		out << Item_List[i]->GetRectVertexBr()->x() << "," << Item_List[i]->GetRectVertexBr()->y();
		out << "\n#IT:";
		temp_vector = Item_List[i]->GetRectWallT()->Get_Windows();
		if (!temp_vector.isEmpty()) // if non empty
			for (auto it = temp_vector.begin(); it != temp_vector.end(); it++)
				out << (*it)->Get_Center().x() << "," << (*it)->Get_Center().y() << ":";
		out << "\n#IR:";
		temp_vector = Item_List[i]->GetRectWallR()->Get_Windows();
		if (!temp_vector.isEmpty()) // if non empty
			for (auto it = temp_vector.begin(); it != temp_vector.end(); it++)
				out << (*it)->Get_Center().x() << "," << (*it)->Get_Center().y() << ":";
		out << "\n#IB:";
		temp_vector = Item_List[i]->GetRectWallB()->Get_Windows();
		if (!temp_vector.isEmpty()) // if non empty
			for (auto it = temp_vector.begin(); it != temp_vector.end(); it++)
				out << (*it)->Get_Center().x() << "," << (*it)->Get_Center().y() << ":";
		out << "\n#IL:";
		temp_vector = Item_List[i]->GetRectWallL()->Get_Windows();
		if (!temp_vector.isEmpty()) // if non empty
			for (auto it = temp_vector.begin(); it != temp_vector.end(); it++)
				out << (*it)->Get_Center().x() << "," << (*it)->Get_Center().y() << ":";
		out << "\n##";
	}
		
	setCurrentFile(fileName);
	file.close();

	statusBar()->showMessage(tr("File saved"), 2000);
	return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
	curFile = fileName;
	// textEdit->document()->setModified(false);
	setWindowModified(false);

	QString shownName = curFile;
	if (curFile.isEmpty())
		shownName = "untitled.txt";
	setWindowFilePath(shownName);
}

void MainWindow::Open()
{
	if (maybeSave()) {
		QString fileName = QFileDialog::getOpenFileName(this);
		if (!fileName.isEmpty())
			loadFile(fileName);
	}
}
void MainWindow::loadFile(const QString &fileName)
{
	QList<DiagramItem> list;
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly)) {
		QMessageBox::warning(this, tr("Application"),
			tr("Cannot read file %1:\n%2.")
			.arg(QDir::toNativeSeparators(fileName), file.errorString()));
		return;
	}

	QTextStream in(&file);
	// in.setVersion(QDataStream::Qt_5_10);
	// textEdit->setPlainText(in.readAll());  // reference #wjw http://www.java2s.com/Code/Cpp/Qt/SavingfilewithQDataStream.htm
	// in >> list;  // does this work??
	QString line;
	DiagramItem *item_;
	QStringList substrs;
	while (true)
	{
		in >> line;
		if (line == "##")
			break;
		in >> line;
		item_ = new DiagramItem(DiagramItem::DiagramType(line.toInt()), itemMenu);
		scene->addItem(item_);
		for (int i = 0; i < 4; i++)
		{
			in >> line;
			substrs = line.split(",");
			
			
		}
	}
	file.close();


	setCurrentFile(fileName);
	statusBar()->showMessage(tr("File loaded"), 2000);
}


bool MainWindow::maybeSave()
{
	if (!itemchanged)
		return true;
	const QMessageBox::StandardButton ret
		= QMessageBox::warning(this, tr("Application"),
			tr("The document has been modified.\n"
				"Do you want to save your changes?"),
			QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
	switch (ret) {
	case QMessageBox::Save:
		return Save();
	case QMessageBox::Cancel:
		return false;
	default:
		break;
	}
	return true;
}

void MainWindow::itemInserted(DiagramItem *item)
{
    pointerTypeGroup->button(int(DiagramScene::MoveItem))->setChecked(true);
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
    buttonGroup->button(int(item->diagramType()))->setChecked(false);
	if (item->diagramType() == DiagramItem::DiagramType(1)) // 1 is door
	{
		if (scene->selectedItems().isEmpty())
		{
			item->setSelected(true);
			return;
		}
		else
		{
			item->setPos(scene->selectedItems().first()->x(), scene->selectedItems().first()->y());
		}
		
	}
	Item_List.append(item);
}

void MainWindow::itemInsertedOther(DiagramItem::DiagramType type,
	QGraphicsItem * item)
{
	pointerTypeGroup->button(int(DiagramScene::MoveItem))->setChecked(true);
	scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
	buttonGroup->button(int(type))->setChecked(false);
}
//! [7]

void MainWindow::objInserted(DiagramItem *item)
{
	buttonGroup->button(4)->setChecked(false);
	buttonGroup->button(5)->setChecked(false);
	buttonGroup->button(6)->setChecked(false);
	buttonGroup->button(7)->setChecked(false);
	scene->setMode(DiagramScene::Mode(3));

	char buff[100];
	sprintf(buff, "\ntype : %d\n", pointerTypeGroup->checkedId());
	OutputDebugStringA(buff);


	buttonGroup->button(int(item->diagramType()))->setChecked(false);
	if (item->diagramType() == DiagramItem::DiagramType(1)) // 1 is door
	{
		if (scene->selectedItems().isEmpty())
		{
			item->setSelected(true);
			// deleteItem();
		}
		else
		{
			item->setPos(scene->selectedItems().first()->x(), scene->selectedItems().first()->y());
		}

	}
}

//! [8]
void MainWindow::textInserted(QGraphicsTextItem *)
{
    buttonGroup->button(InsertTextButton)->setChecked(false);
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
}
//! [8]

//! [9]
void MainWindow::currentFontChanged(const QFont &)
{
    handleFontChange();
}
//! [9]

//! [10]
void MainWindow::fontSizeChanged(const QString &)
{
    handleFontChange();
}
//! [10]

//! [11]
void MainWindow::sceneScaleChanged(const QString &scale)
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldMatrix = view->matrix();
    view->resetMatrix();
    view->translate(oldMatrix.dx(), oldMatrix.dy());
    view->scale(newScale, newScale);
}
//! [11]

//! [12]
void MainWindow::textColorChanged()
{
    textAction = qobject_cast<QAction *>(sender());
    fontColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/images/textpointer.png",
                                     qvariant_cast<QColor>(textAction->data())));
    textButtonTriggered();
}
//! [12]

//! [13]
void MainWindow::itemColorChanged()
{
    fillAction = qobject_cast<QAction *>(sender());
    fillColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/images/floodfill.png",
                                     qvariant_cast<QColor>(fillAction->data())));
    fillButtonTriggered();
}
//! [13]

//! [14]
void MainWindow::lineColorChanged()
{
    lineAction = qobject_cast<QAction *>(sender());
    lineColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/images/linecolor.png",
                                     qvariant_cast<QColor>(lineAction->data())));
    lineButtonTriggered();
}
//! [14]

//! [15]
void MainWindow::textButtonTriggered()
{
    scene->setTextColor(qvariant_cast<QColor>(textAction->data()));
}
//! [15]

//! [16]
void MainWindow::fillButtonTriggered()
{
    scene->setItemColor(qvariant_cast<QColor>(fillAction->data()));
}
//! [16]

//! [17]
void MainWindow::lineButtonTriggered()
{
    scene->setLineColor(qvariant_cast<QColor>(lineAction->data()));
}
//! [17]

//! [18]
void MainWindow::handleFontChange()
{
    QFont font = fontCombo->currentFont();
    font.setPointSize(fontSizeCombo->currentText().toInt());
    font.setWeight(boldAction->isChecked() ? QFont::Bold : QFont::Normal);
    font.setItalic(italicAction->isChecked());
    font.setUnderline(underlineAction->isChecked());

    scene->setFont(font);
}
//! [18]

//! [19]
/*
* <text Only>
 * diagramscene itemSelected ->  this method called( by signal/slot)
 */
void MainWindow::itemSelected(QGraphicsItem *item)
{
    DiagramTextItem *textItem =
    qgraphicsitem_cast<DiagramTextItem *>(item);

    QFont font = textItem->font();
    fontCombo->setCurrentFont(font);
    fontSizeCombo->setEditText(QString().setNum(font.pointSize()));
    boldAction->setChecked(font.weight() == QFont::Bold);
    italicAction->setChecked(font.italic());
    underlineAction->setChecked(font.underline());
}
void MainWindow::itemChanged()
{
	itemchanged = true;
}
//! [19]

//! [20]
void MainWindow::about()
{
    QMessageBox::about(this, tr("About Diagram Scene"),
                       tr("The <b>Diagram Scene</b> example shows "
                          "use of the graphics framework."));
}
//! [20]

//! [21]
/*
 * Add Sidebar
 */
void MainWindow::createToolBox()
{
    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(false);
    connect(buttonGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(buttonGroupClicked(int)));
    QGridLayout *layout = new QGridLayout;
	// PBW
    layout->addWidget(createCellWidget(tr("Door"), DiagramItem::Door), 0, 0);
    layout->addWidget(createIconWidget(tr("Window"), DiagramItem::Window, ":/images/window.png"),0, 1);
    layout->addWidget(createCellWidget(tr("Room"), DiagramItem::Step),1, 0);
    
	layout->addWidget(createCellWidget(tr("Washer"), DiagramItem::Washer), 2, 0);
	layout->addWidget(createCellWidget(tr("TV"), DiagramItem::TV), 2, 1);
	layout->addWidget(createCellWidget(tr("Desk"), DiagramItem::Desk), 3, 0);
	layout->addWidget(createCellWidget(tr("Refrigator"), DiagramItem::Refrig), 3, 1);
	
	//layout->addWidget(createCellWidget(tr("Refrigator"), DiagramItem::Refrig), 4, 0);
	//layout->addWidget(createCellWidget(tr("Refrigator"), DiagramItem::Refrig), 4, 1);

	// layout->addWidget(createCellWidget(tr("Input/Output"), DiagramItem::Io), 1, 0);
//! [21]

	// itemWidget -> layout -> textWidget -> textLayout -> textButton
    QToolButton *textButton = new QToolButton;
    textButton->setCheckable(true);
    buttonGroup->addButton(textButton, InsertTextButton);
    textButton->setIcon(QIcon(QPixmap(":/images/textpointer.png")));
    textButton->setIconSize(QSize(50, 50));
    QGridLayout *textLayout = new QGridLayout;
    textLayout->addWidget(textButton, 0, 0, Qt::AlignHCenter);
    textLayout->addWidget(new QLabel(tr("Text")), 1, 1, Qt::AlignCenter);
    QWidget *textWidget = new QWidget;
    textWidget->setLayout(textLayout);
    layout->addWidget(textWidget, 1, 1);

    layout->setRowStretch(3, 10);
    layout->setColumnStretch(2, 10);

    QWidget *itemWidget = new QWidget;
    itemWidget->setLayout(layout);

	// backgroundWidget -> bglayout
    backgroundButtonGroup = new QButtonGroup(this);
    connect(backgroundButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)),
            this, SLOT(backgroundButtonGroupClicked(QAbstractButton*)));

    QGridLayout *backgroundLayout = new QGridLayout;
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("Blue Grid"),
                                                           ":/images/background1.png"), 0, 0);
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("White Grid"),
                                                           ":/images/background2.png"), 0, 1);
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("Gray Grid"),
                                                           ":/images/background3.png"), 1, 0);
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("No Grid"),
                                                           ":/images/background4.png"), 1, 1);

    backgroundLayout->setRowStretch(2, 10);
    backgroundLayout->setColumnStretch(2, 10);

    QWidget *backgroundWidget = new QWidget;
    backgroundWidget->setLayout(backgroundLayout);


//! [22]
    toolBox = new QToolBox;
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    toolBox->setMinimumWidth(itemWidget->sizeHint().width());
    toolBox->addItem(itemWidget, tr("Objects"));
    toolBox->addItem(backgroundWidget, tr("Backgrounds"));
}
//! [22]

//! [23]
/*
 * Add Edit Actions
 */
void MainWindow::createActions()
{
    toFrontAction = new QAction(QIcon(":/images/bringtofront.png"),
                                tr("Bring to &Front"), this);
    toFrontAction->setShortcut(tr("Ctrl+F"));
    toFrontAction->setStatusTip(tr("Bring item to front"));
    connect(toFrontAction, SIGNAL(triggered()), this, SLOT(bringToFront()));
//! [23]

    sendBackAction = new QAction(QIcon(":/images/sendtoback.png"), tr("Send to &Back"), this);
    sendBackAction->setShortcut(tr("Ctrl+T"));
    sendBackAction->setStatusTip(tr("Send item to back"));
    connect(sendBackAction, SIGNAL(triggered()), this, SLOT(sendToBack()));

    deleteAction = new QAction(QIcon(":/images/delete.png"), tr("&Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete item from diagram"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteItem()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quit Scenediagram example"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    boldAction = new QAction(tr("Bold"), this);
    boldAction->setCheckable(true);
    QPixmap pixmap(":/images/bold.png");
    boldAction->setIcon(QIcon(pixmap));
    boldAction->setShortcut(tr("Ctrl+B"));
    connect(boldAction, SIGNAL(triggered()), this, SLOT(handleFontChange()));

    italicAction = new QAction(QIcon(":/images/italic.png"), tr("Italic"), this);
    italicAction->setCheckable(true);
    italicAction->setShortcut(tr("Ctrl+I"));
    connect(italicAction, SIGNAL(triggered()), this, SLOT(handleFontChange()));

    underlineAction = new QAction(QIcon(":/images/underline.png"), tr("Underline"), this);
    underlineAction->setCheckable(true);
    underlineAction->setShortcut(tr("Ctrl+U"));
    connect(underlineAction, SIGNAL(triggered()), this, SLOT(handleFontChange()));

    aboutAction = new QAction(tr("A&bout"), this);
    aboutAction->setShortcut(tr("F1"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

	saveAction = new QAction(tr("S&ave"), this);
	aboutAction->setShortcut(tr("Ctrl+S"));
	connect(saveAction, SIGNAL(triggered()), this, SLOT(Save()));

	saveAsAction = new QAction(tr("S&ave As"), this);
	aboutAction->setShortcut(tr("Ctrl+Shift+S"));
	connect(saveAsAction, SIGNAL(triggered()), this, SLOT(SaveAs()));
}

//! [24]
/*
 * Add File, Item Help Options
 */
void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(saveAction);
	fileMenu->addAction(saveAsAction);
	fileMenu->addAction(exitAction);
	

    itemMenu = menuBar()->addMenu(tr("&Item"));
    itemMenu->addAction(deleteAction);
    itemMenu->addSeparator();
    itemMenu->addAction(toFrontAction);
    itemMenu->addAction(sendBackAction);

    aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutAction);
}
//! [24]

//! [25]
/*
 * Font Edit top Actions(ex Font, Scale)
 */
void MainWindow::createToolbars()
{
//! [25]
    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(deleteAction);
    editToolBar->addAction(toFrontAction);
    editToolBar->addAction(sendBackAction);

    fontCombo = new QFontComboBox();
    connect(fontCombo, SIGNAL(currentFontChanged(QFont)),
            this, SLOT(currentFontChanged(QFont)));

    fontSizeCombo = new QComboBox;
    fontSizeCombo->setEditable(true);
    for (int i = 8; i < 30; i = i + 2)
        fontSizeCombo->addItem(QString().setNum(i));
    QIntValidator *validator = new QIntValidator(2, 64, this);
    fontSizeCombo->setValidator(validator);
    connect(fontSizeCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(fontSizeChanged(QString)));

    fontColorToolButton = new QToolButton;
    fontColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    fontColorToolButton->setMenu(createColorMenu(SLOT(textColorChanged()), Qt::black));
    textAction = fontColorToolButton->menu()->defaultAction();
    fontColorToolButton->setIcon(createColorToolButtonIcon(":/images/textpointer.png", Qt::black));
    fontColorToolButton->setAutoFillBackground(true);
    connect(fontColorToolButton, SIGNAL(clicked()),
            this, SLOT(textButtonTriggered()));

//! [26]
    fillColorToolButton = new QToolButton;
    fillColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    fillColorToolButton->setMenu(createColorMenu(SLOT(itemColorChanged()), Qt::white));
    fillAction = fillColorToolButton->menu()->defaultAction();
    fillColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/images/floodfill.png", Qt::white));
    connect(fillColorToolButton, SIGNAL(clicked()),
            this, SLOT(fillButtonTriggered()));
//! [26]

    lineColorToolButton = new QToolButton;
    lineColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    lineColorToolButton->setMenu(createColorMenu(SLOT(lineColorChanged()), Qt::black));
    lineAction = lineColorToolButton->menu()->defaultAction();
    lineColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/images/linecolor.png", Qt::black));
    connect(lineColorToolButton, SIGNAL(clicked()),
            this, SLOT(lineButtonTriggered()));

    textToolBar = addToolBar(tr("Font"));
    textToolBar->addWidget(fontCombo);
    textToolBar->addWidget(fontSizeCombo);
    textToolBar->addAction(boldAction);
    textToolBar->addAction(italicAction);
    textToolBar->addAction(underlineAction);

    colorToolBar = addToolBar(tr("Color"));
    colorToolBar->addWidget(fontColorToolButton);
    colorToolBar->addWidget(fillColorToolButton);
    colorToolBar->addWidget(lineColorToolButton);

    QToolButton *pointerButton = new QToolButton;
    pointerButton->setCheckable(true);
    pointerButton->setChecked(true);
    pointerButton->setIcon(QIcon(":/images/pointer.png"));

	// PBW
    // QToolButton *linePointerButton = new QToolButton;
    // linePointerButton->setCheckable(true);
    // linePointerButton->setIcon(QIcon(":/images/linepointer.png"));

	// PBW
    pointerTypeGroup = new QButtonGroup(this);
    pointerTypeGroup->addButton(pointerButton, int(DiagramScene::MoveItem));
    // pointerTypeGroup->addButton(linePointerButton, int(DiagramScene::InsertLine));
    connect(pointerTypeGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(pointerGroupClicked(int)));

    sceneScaleCombo = new QComboBox;
    QStringList scales;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%") << tr("200%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(2);
    connect(sceneScaleCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(sceneScaleChanged(QString)));

    pointerToolbar = addToolBar(tr("Pointer type"));
    pointerToolbar->addWidget(pointerButton);
    pointerToolbar->addWidget(sceneScaleCombo);
//! [27]
}
//! [27]

//! [28]
QWidget *MainWindow::createBackgroundCellWidget(const QString &text, const QString &image)
{
    QToolButton *button = new QToolButton;
    button->setText(text);
    button->setIcon(QIcon(image));
    button->setIconSize(QSize(50, 50));
    button->setCheckable(true);
    backgroundButtonGroup->addButton(button);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}
//! [28]

//! [29]
QWidget *MainWindow::createCellWidget(const QString &text, DiagramItem::DiagramType type)
{
	DiagramItem item(type, itemMenu);
	QIcon icon(item.image());
	QToolButton *button = new QToolButton;

	switch (type) {
	case DiagramItem::Step: case DiagramItem::Door:
		button->setIcon(icon);
		buttonGroup->addButton(button, int(type));
		break;
	case DiagramItem::Washer:
		button->setIcon(QIcon(QPixmap("images/Washer.png")));
		buttonGroup->addButton(button, DiagramItem::DiagramType::Washer);
		OutputDebugString(L"washer\n");
		break;
	case DiagramItem::TV:
		button->setIcon(QIcon(QPixmap("images/CableTV.png")));
		buttonGroup->addButton(button, DiagramItem::DiagramType::TV);
		OutputDebugString(L"tv\n");
		break;
	case DiagramItem::Desk:
		button->setIcon(QIcon(QPixmap("images/Desk.png")));
		buttonGroup->addButton(button, DiagramItem::DiagramType::Desk);
		OutputDebugString(L"desk\n");
		break;
	case DiagramItem::Refrig:
		button->setIcon(QIcon(QPixmap("images/Refrigerator.png")));
		buttonGroup->addButton(button, DiagramItem::DiagramType::Refrig);
		OutputDebugString(L"refrigerator\n");
		break;
	}

	button->setCheckable(true);
	button->setIconSize(QSize(50, 50));

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(button, 0, 0, Qt::AlignHCenter);
	layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	return widget;
}
QWidget *MainWindow::createIconWidget(const QString &text, DiagramItem::DiagramType type, const QString &image)
{

	DiagramItem item(type, itemMenu);
	QIcon icon(item.image());

	QToolButton *button = new QToolButton;
	button->setIcon(QIcon(image));
	button->setIconSize(QSize(50, 50));
	button->setCheckable(true);
	buttonGroup->addButton(button, int(type));

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(button, 0, 0, Qt::AlignHCenter);
	layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	return widget;
}
//! [29]

//! [30]
QMenu *MainWindow::createColorMenu(const char *slot, QColor defaultColor)
{
    QList<QColor> colors;
    colors << Qt::black << Qt::white << Qt::red << Qt::blue << Qt::yellow;
    QStringList names;
    names << tr("black") << tr("white") << tr("red") << tr("blue")
          << tr("yellow");

    QMenu *colorMenu = new QMenu(this);
    for (int i = 0; i < colors.count(); ++i) {
        QAction *action = new QAction(names.at(i), this);
        action->setData(colors.at(i));
        action->setIcon(createColorIcon(colors.at(i)));
        connect(action, SIGNAL(triggered()), this, slot);
        colorMenu->addAction(action);
        if (colors.at(i) == defaultColor)
            colorMenu->setDefaultAction(action);
    }
    return colorMenu;
}
//! [30]

//! [31]
QIcon MainWindow::createColorToolButtonIcon(const QString &imageFile, QColor color)
{
    QPixmap pixmap(50, 80);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPixmap image(imageFile);
    // Draw icon centred horizontally on button.
    QRect target(4, 0, 42, 43);
    QRect source(0, 0, 42, 43);
    painter.fillRect(QRect(0, 60, 50, 80), color);
    painter.drawPixmap(target, image, source);

    return QIcon(pixmap);
}
//! [31]

//! [32]
QIcon MainWindow::createColorIcon(QColor color)
{
    QPixmap pixmap(20, 20);
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.fillRect(QRect(0, 0, 20, 20), color);

    return QIcon(pixmap);
}
//! [32]
