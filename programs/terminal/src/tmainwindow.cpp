/*
 * Copyright 2022 <copyright holder> <email>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "tmainwindow.h"
#include <QGridLayout>
#include <QGuiApplication>
#include <QScreen>
#include <QTreeView>
#include <QFileSystemModel>
#include <iostream>
#include <QSortFilterProxyModel>
#include <QLabel>
#include <errno.h>
#include <string.h>
#include <thread>

TMainWindow::TMainWindow()
{
   QRect screenGeometry = QGuiApplication::screens().at(0)->geometry();
   int x = (screenGeometry.width() - WIDTH) / 2;
   int y = (screenGeometry.height() - HEIGHT) / 2;
   setGeometry(x, y, WIDTH, HEIGHT);
   
   QFrame *mainFr = new QFrame();
   QVBoxLayout *mainLay = new QVBoxLayout(mainFr);
   
   QTreeView *tree = new QTreeView(mainFr);
   QLabel *lbl = new QLabel();
   mainLay->addWidget(lbl);
   mainLay->addWidget(tree);
   
   QString rootPath = "./scripts/";
   QFileSystemModel *model = new QFileSystemModel(this);
   model->setRootPath(rootPath);

   QStringList filters;
   filters << "*.sh";
   model->setNameFilters(filters);
   model->setNameFilterDisables(false);
   
   tree->setModel(model);
   tree->setRootIndex(model->index(rootPath));
   
   tree->hideColumn(1);
   tree->hideColumn(2);
   tree->hideColumn(3);
   
   lbl->setFixedHeight(60);
   lbl->setAlignment(Qt::AlignCenter);
   
   setCentralWidget(mainFr);
   //doubleClicked(const QModelIndex &index);
   connect(tree, &QTreeView::doubleClicked, [lbl](const QModelIndex index) {
      std::thread([index, lbl] { 
         QFileSystemModel* fileSystem = new QFileSystemModel();
         //std::string myPath = fileSystem->filePath(index).toStdString();
         //std::string command = "konsole --noclose -e bash ./parent.sh " + fileSystem->filePath(index).toStdString();
         std::string command = "fly-term --noclose -e bash ./parent.sh " + fileSystem->filePath(index).toStdString();
         //std::string command = "fly-term --noclose -e bash " + fileSystem->filePath(index).toStdString() + " &";
         system(command.c_str());
         
         int result;
         FILE *fptr;
         
         if ((fptr = fopen("./log.txt", "r")) == NULL){
             std::cout << "Error! opening file" << std::endl;
             return;
         }
         
         fscanf(fptr, "%d", &result);
         std::cout << "Value of n = " << result << std::endl;
         fclose(fptr); 
         lbl->setText(getErrorText(result));
      }).detach();
   });
   
   setStyleSheet("QWidget { font-size: 16px; } QLabel { font-size: 18px; font-weight: bold; }");
}
