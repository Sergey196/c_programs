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
#include "tbitepanel.h"
#include <QFrame>
#include <QGridLayout>
#include <QSpinBox>
#include <QGuiApplication>
#include <QScreen>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QComboBox>
#include <QStackedWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include "qcustomplot.h"
#include "thexspinbox.h"
#include "tbinaryspinbox.h"
#include "toctalspinbox.h"
#include "tcontroller.h"

TMainWindow::TMainWindow()
{
   pointOnController = TController::getInstance();
   
   QRect screenGeometry = QGuiApplication::screens().at(0)->geometry();
   int x = (screenGeometry.width() - WIDTH) / 2;
   int y = (screenGeometry.height() - HEIGHT) / 2;
   setGeometry(x, y, WIDTH, HEIGHT);
   
   setWindowTitle("Дешифратор МКИО отдел 08 v 2.0");
   
   QFrame *mainFr = new QFrame();
   QGridLayout *mainLay = new QGridLayout(mainFr);
   
   QPushButton *exitButton = new QPushButton("Выход", mainFr);
   QPushButton *printButton = new QPushButton("Печать", mainFr);
   QSpinBox *inputWidjets[COUT_INPUTS];
   inputWidjets[0] = new THexSpinBox(mainFr);
   inputWidjets[1] = new TOctalSpinBox(mainFr);
   inputWidjets[2] = new QSpinBox(mainFr);
   inputWidjets[3] = new TBinarySpinBox(mainFr);
   inputWidjets[2]->setRange(0, MAX_INPUT_VALUE);
   
   
   TBitesPanel *bitesPanel = new TBitesPanel(mainFr);
   
   QCustomPlot *impuls = new QCustomPlot(mainFr);
   impuls->xAxis->setRange(0, COUT_FULL_BITES * 2);
   impuls->yAxis->setRange(0, 1);
   impuls->xAxis->setLabel("Сигнал манчестер 2");
   impuls->xAxis->setTicks(false);
   impuls->yAxis->setTicks(false);
   impuls->setFixedHeight(100);
   
   QLabel *lblTypeWord = new QLabel("Тип слова: ", this);
   lblTypeWord->setAlignment(Qt::AlignCenter);
   QComboBox *cmbWords = new QComboBox(this);
   cmbWords->addItem("Командное слово");
   cmbWords->addItem("Слово данных");
   cmbWords->addItem("Ответное слово");
   
   QTextEdit *textInfo = new QTextEdit(mainFr);
   textInfo->setReadOnly(true);
   
   QLabel *inputLbls[COUT_INPUTS];
   for(int i = 0; i < COUT_INPUTS; i++)
   {
      inputLbls[i] = new QLabel(mainFr);
      inputLbls[i]->setAlignment(Qt::AlignCenter);
   } 
   
   inputLbls[0]->setText("Hex: ");
   inputLbls[1]->setText("Oct: ");
   inputLbls[2]->setText("Dec: ");
   inputLbls[3]->setText("Bin: ");
   
   mainLay->addWidget(lblTypeWord, 0, 0);
   mainLay->addWidget(cmbWords, 0, 1, 1, 4);
   mainLay->addWidget(inputLbls[0], 1, 0);
   mainLay->addWidget(inputLbls[1], 2, 0);
   mainLay->addWidget(inputWidjets[0], 1, 1, 1, 3);
   mainLay->addWidget(inputWidjets[1], 2, 1, 1, 3);
   mainLay->addWidget(inputLbls[2], 1, 4);
   mainLay->addWidget(inputLbls[3], 2, 4);
   mainLay->addWidget(inputWidjets[2], 1, 5, 1, 3);
   mainLay->addWidget(inputWidjets[3], 2, 5, 1, 3);
   mainLay->addWidget(exitButton, 1, 8, 1, 2);
   mainLay->addWidget(printButton, 2, 8, 1, 2);
   
   mainLay->addWidget(bitesPanel, 3, 0, 3, 10);
   mainLay->addWidget(impuls, 6, 0, 1, 10);
   mainLay->addWidget(textInfo, 7, 0, 1, 10);
   
   setCentralWidget(mainFr);
   
   connect(pointOnController, &TController::update, [inputWidjets, impuls, textInfo, this]() {
      if(flagChangeInput)
      {
         return; 
      }
      flagChangeInput = true;
      for(int i = 0; i < COUT_INPUTS; i++)
         inputWidjets[i]->setValue(pointOnController->getMessageValue());

      
      impuls->clearGraphs();
      impuls->addGraph();
      
      for(int i = 0; i < COUT_FULL_BITES; i++)
      {
         int pos = i * 2; 
         if(pointOnController->getImpulsState(i)) {
            impuls->graph(0)->addData(pos, 0); 
            impuls->graph(0)->addData(pos + 1, 0); 
            impuls->graph(0)->addData(pos + 1, 1); 
            impuls->graph(0)->addData(pos + 2, 1); 
         } else {
            impuls->graph(0)->addData(pos, 1); 
            impuls->graph(0)->addData(pos + 1, 1);
            impuls->graph(0)->addData(pos + 1, 0);
            impuls->graph(0)->addData(pos + 2, 0);
         }
      } 

      impuls->replot();
      
      textInfo->setText(QString::fromStdString(pointOnController->getCommandInfo()));
      flagChangeInput = false;
   });
   
   auto setValue = [this](int value) {
      pointOnController->setNewValue(value);
      emit pointOnController->update();
   };   
   
   connect(cmbWords, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [this, bitesPanel](int index) {
      CommandType type { sendData };
      if(index == 1) {
         type = dataWord; ;
      } else if(index == 2) {
         type = requestWord;
      }
      pointOnController->setCommandType(type);
      bitesPanel->setWord(index);
      
      emit pointOnController->update();
   });
   
   connect(printButton, &QPushButton::released, [mainFr, this]() {
      QPrinter printer(QPrinter::HighResolution); //create your QPrinter (don't need to be high resolution, anyway)
      printer.setPageSize(QPageSize(QPageSize::A4));
      printer.setPageOrientation(QPageLayout::Portrait);
      printer.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);
      printer.setFullPage(false);
      //printer.setOutputFileName(QFileDialog::getSaveFileUrl(0, "Сhoose a directory", "") + "/exsport.pdf");
      QString file = QFileDialog::getSaveFileName(this, tr("Save PDF"), "export", tr("PDF (*.pdf);; All Files (*)"));
      
      printer.setOutputFileName(file);
      printer.setOutputFormat(QPrinter::PdfFormat); 
      QPainter painter(&printer); 
      painter.scale(14, 14);
      mainFr->render(&painter);
      if(painter.isActive()) 
      {
         QMessageBox::warning(this, "Внимание", "Файл успешно сохранён");
      } 
      painter.end();
   });
   
   connect(inputWidjets[0], static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), setValue);
   connect(inputWidjets[1], static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), setValue);
   connect(inputWidjets[2], static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), setValue);
   connect(inputWidjets[3], static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), setValue);
   connect(exitButton, &QPushButton::released, this, &QWidget::close);
   
   repaintStyle();
   emit pointOnController->update();
}
//---------------------------------------------------------------------------
void TMainWindow::repaintStyle()
{
   setStyleSheet("TBitesPanel QWidget { border: solid black; } QWidget#Type1{ border-width: 0 0 1px 1px; } QWidget#Type2{ border-width: 1px 0 1px 1px; } QWidget#Type3{ border-width: 1px 1px 1px 1px; } QWidget#Type4 { border-width: 0 0 1px 1px; } QWidget#Type5 { border-width: 0 1px 1px 1px; } QWidget#Type6 { border-width: 0 0 0 1px; }"); 
}
//---------------------------------------------------------------------------
TBitesPanel::TBitesPanel(QWidget *parent):QFrame(parent)
{
   pointOnController = TController::getInstance(); 
   QGridLayout *mainLay = new QGridLayout(this); 
   mainLay->setSpacing(0);
   mainLay->setMargin(0);
   
   QLabel *inputBinaresValueLbl[COUT_FULL_BITES]; 
   QLabel *inputBinaresLbl[COUT_FULL_BITES]; 
   
   for(int i = 0; i < COUT_FULL_BITES; i++)
   {
      if(i > 2 && i != 19) {
         inputBinaresValueLbl[i] = new TBitePanel(i, this);
      } else {
         inputBinaresValueLbl[i] = new QLabel("0", this); 
      }
      inputBinaresValueLbl[i]->setAlignment(Qt::AlignCenter);
   }
   
   for(int i = 0; i < COUT_FULL_BITES; i++)
   {
      inputBinaresLbl[i] = new QLabel(QString::number(i + 1), this);
      inputBinaresLbl[i]->setAlignment(Qt::AlignCenter);
   } 
   
   QFrame *commandWordFr = new QFrame(this);
   QGridLayout *commandWordLay = new QGridLayout(commandWordFr);
   commandWordLay->setMargin(0);
   commandWordLay->setSpacing(0);
   commandWordLay->setColumnStretch(0, 3);
   commandWordLay->setColumnStretch(1, 5);
   commandWordLay->setColumnStretch(2, 1);
   commandWordLay->setColumnStretch(3, 5);
   commandWordLay->setColumnStretch(4, 5);
   commandWordLay->setColumnStretch(5, 1);
   
   QLabel *commandWordLbls[6];
   
   QWidget *freepanel[3];
   
   for(int i = 0; i < 3; i++)
   {
      freepanel[i] = new QWidget(this);
      freepanel[i]->setObjectName("Type6");
   }
   
   commandWordLbls[0] = new QLabel("Синхр.", this);
   commandWordLbls[1] = new QLabel("Адрес ОУ", this);
   commandWordLbls[2] = new QLabel("К", this);
   commandWordLbls[3] = new QLabel("Подадрес/КУ", this);
   commandWordLbls[4] = new QLabel("Число Сд", this);
   commandWordLbls[5] = new QLabel("Р", this);
   
   QSpinBox *commandWordInput[3];
   
   for(int i = 0; i < 3; i++)
   {
      commandWordInput[i] = new QSpinBox(this); 
      commandWordInput[i]->setAlignment(Qt::AlignCenter);
      commandWordInput[i]->setButtonSymbols(QAbstractSpinBox::NoButtons);
   }

   commandWordInput[0]->setRange(0, 31);
   commandWordInput[1]->setRange(0, 31);
   commandWordInput[2]->setRange(0, 31);
   
   for(int i = 0; i < 6; i++)
   {
      commandWordLbls[i]->setAlignment(Qt::AlignCenter);
   } 
   
   commandWordLay->addWidget(commandWordLbls[0], 0, 0);
   commandWordLay->addWidget(commandWordLbls[1], 0, 1);
   commandWordLay->addWidget(commandWordLbls[2], 0, 2);
   commandWordLay->addWidget(commandWordLbls[3], 0, 3);
   commandWordLay->addWidget(commandWordLbls[4], 0, 4);
   commandWordLay->addWidget(commandWordLbls[5], 0, 5);
   commandWordLay->addWidget(commandWordInput[0], 1, 1);
   commandWordLay->addWidget(freepanel[0], 1, 2);
   commandWordLay->addWidget(commandWordInput[1], 1, 3);
   commandWordLay->addWidget(commandWordInput[2], 1, 4);
   commandWordLay->addWidget(freepanel[1], 1, 5);
   
   commandWordLbls[0]->setObjectName("Type4");
   commandWordLbls[1]->setObjectName("Type4");
   commandWordLbls[2]->setObjectName("Type4");
   commandWordLbls[3]->setObjectName("Type4");
   commandWordLbls[4]->setObjectName("Type4");
   commandWordLbls[5]->setObjectName("Type5");
   commandWordInput[0]->setObjectName("Type4");
   commandWordInput[1]->setObjectName("Type4");
   commandWordInput[2]->setObjectName("Type4");
   /////////////
   
   QFrame *dataWordFr = new QFrame(this);
   QHBoxLayout *dataWordLay = new QHBoxLayout(dataWordFr);
   dataWordLay->setMargin(0);
   dataWordLay->setSpacing(0);
   
   QLabel *dataWordLbls[3];
   
   dataWordLbls[0] = new QLabel("Синхр.", this);
   dataWordLbls[1] = new QLabel("Слово данных", this);
   dataWordLbls[2] = new QLabel("Р", this);
   
   for(int i = 0; i < 3; i++)
   {
      dataWordLbls[i]->setAlignment(Qt::AlignCenter); 
   }
   
   dataWordLay->addWidget(dataWordLbls[0], 3); 
   dataWordLay->addWidget(dataWordLbls[1], 16); 
   dataWordLay->addWidget(dataWordLbls[2], 1); 
   
   dataWordLbls[0]->setObjectName("Type4");
   dataWordLbls[1]->setObjectName("Type4");
   dataWordLbls[2]->setObjectName("Type5");
   
   /////////////
   QFrame *requestWordFr = new QFrame(this);
   QGridLayout *requestWordLay = new QGridLayout(requestWordFr);
   requestWordLay->setMargin(0);
   requestWordLay->setSpacing(0);
   requestWordLay->setColumnStretch(0, 3);
   requestWordLay->setColumnStretch(1, 5);
   requestWordLay->setColumnStretch(2, 1);
   requestWordLay->setColumnStretch(3, 1);
   requestWordLay->setColumnStretch(4, 1);
   requestWordLay->setColumnStretch(5, 3);
   requestWordLay->setColumnStretch(6, 1);
   requestWordLay->setColumnStretch(7, 1);
   requestWordLay->setColumnStretch(8, 1);
   requestWordLay->setColumnStretch(9, 1);
   requestWordLay->setColumnStretch(10, 1);
   requestWordLay->setColumnStretch(11, 1);
   
   QLabel *requestWordLbls[12];
   
   requestWordLbls[0] = new QLabel("Синхр.", this);
   requestWordLbls[1] = new QLabel("Адреса ОУ", this);
   requestWordLbls[2] = new QLabel("9", this);
   requestWordLbls[3] = new QLabel("10", this);
   requestWordLbls[4] = new QLabel("11", this);
   requestWordLbls[5] = new QLabel("Резерв", this);
   requestWordLbls[6] = new QLabel("15", this);
   requestWordLbls[7] = new QLabel("16", this);
   requestWordLbls[8] = new QLabel("17", this);
   requestWordLbls[9] = new QLabel("18", this);
   requestWordLbls[10] = new QLabel("19", this);
   requestWordLbls[11] = new QLabel("Р", this);
   
   for(int i = 0; i < 12; i++)
   {
      requestWordLbls[i]->setAlignment(Qt::AlignCenter);
   }
   
   QSpinBox *requestWordInput = new QSpinBox(this); 
   requestWordInput->setAlignment(Qt::AlignCenter);
   requestWordInput->setButtonSymbols(QAbstractSpinBox::NoButtons);
   requestWordInput->setRange(0, 31);
   
   
   requestWordLbls[0]->setObjectName("Type4");
   requestWordLbls[1]->setObjectName("Type4");
   requestWordLbls[2]->setObjectName("Type4");
   requestWordLbls[3]->setObjectName("Type4");
   requestWordLbls[4]->setObjectName("Type4");
   requestWordLbls[5]->setObjectName("Type4");
   requestWordLbls[6]->setObjectName("Type4");
   requestWordLbls[7]->setObjectName("Type4");
   requestWordLbls[8]->setObjectName("Type4");
   requestWordLbls[9]->setObjectName("Type4");
   requestWordLbls[10]->setObjectName("Type4");
   requestWordLbls[11]->setObjectName("Type5");
   
   requestWordInput->setObjectName("Type4");
   
   requestWordLay->addWidget(requestWordLbls[0], 0, 0); 
   requestWordLay->addWidget(requestWordLbls[1], 0, 1); 
   requestWordLay->addWidget(requestWordLbls[2], 0, 2); 
   requestWordLay->addWidget(requestWordLbls[3], 0, 3); 
   requestWordLay->addWidget(requestWordLbls[4], 0, 4); 
   requestWordLay->addWidget(requestWordLbls[5], 0, 5);
   requestWordLay->addWidget(requestWordLbls[6], 0, 6);
   requestWordLay->addWidget(requestWordLbls[7], 0, 7);
   requestWordLay->addWidget(requestWordLbls[8], 0, 8);
   requestWordLay->addWidget(requestWordLbls[9], 0, 9);
   requestWordLay->addWidget(requestWordLbls[10], 0, 10);
   requestWordLay->addWidget(requestWordLbls[11], 0, 11);
   requestWordLay->addWidget(requestWordInput, 1, 1);
   requestWordLay->addWidget(freepanel[2], 1, 2);
   
   
   stack = new QStackedWidget(this);
   stack->addWidget(commandWordFr);
   stack->addWidget(dataWordFr);
   stack->addWidget(requestWordFr);
   
   inputBinaresLbl[0]->setObjectName("Type2");
   inputBinaresLbl[1]->setObjectName("Type2");
   inputBinaresLbl[2]->setObjectName("Type2");
   inputBinaresLbl[3]->setObjectName("Type2");
   inputBinaresLbl[4]->setObjectName("Type2");
   inputBinaresLbl[5]->setObjectName("Type2");
   inputBinaresLbl[6]->setObjectName("Type2");
   inputBinaresLbl[7]->setObjectName("Type2");
   inputBinaresLbl[8]->setObjectName("Type2");
   inputBinaresLbl[9]->setObjectName("Type2");
   inputBinaresLbl[10]->setObjectName("Type2");
   inputBinaresLbl[11]->setObjectName("Type2");
   inputBinaresLbl[12]->setObjectName("Type2");
   inputBinaresLbl[13]->setObjectName("Type2");
   inputBinaresLbl[14]->setObjectName("Type2");
   inputBinaresLbl[15]->setObjectName("Type2");
   inputBinaresLbl[16]->setObjectName("Type2");
   inputBinaresLbl[17]->setObjectName("Type2");
   inputBinaresLbl[18]->setObjectName("Type2");
   inputBinaresLbl[19]->setObjectName("Type3");
   
   inputBinaresValueLbl[0]->setObjectName("Type1");
   inputBinaresValueLbl[1]->setObjectName("Type1");
   inputBinaresValueLbl[2]->setObjectName("Type1");
   inputBinaresValueLbl[3]->setObjectName("Type1");
   inputBinaresValueLbl[4]->setObjectName("Type1");
   inputBinaresValueLbl[5]->setObjectName("Type1");
   inputBinaresValueLbl[6]->setObjectName("Type1");
   inputBinaresValueLbl[7]->setObjectName("Type1");
   inputBinaresValueLbl[8]->setObjectName("Type1");
   inputBinaresValueLbl[8]->setObjectName("Type1");
   inputBinaresValueLbl[9]->setObjectName("Type1");
   inputBinaresValueLbl[10]->setObjectName("Type1");
   inputBinaresValueLbl[11]->setObjectName("Type1");
   inputBinaresValueLbl[12]->setObjectName("Type1");
   inputBinaresValueLbl[13]->setObjectName("Type1");
   inputBinaresValueLbl[14]->setObjectName("Type1");
   inputBinaresValueLbl[15]->setObjectName("Type1");
   inputBinaresValueLbl[15]->setObjectName("Type1");
   inputBinaresValueLbl[16]->setObjectName("Type1");
   inputBinaresValueLbl[17]->setObjectName("Type1");
   inputBinaresValueLbl[18]->setObjectName("Type1");
   inputBinaresValueLbl[19]->setObjectName("Type5");
   
   mainLay->addWidget(inputBinaresLbl[0], 0, 0);
   mainLay->addWidget(inputBinaresLbl[1], 0, 1);
   mainLay->addWidget(inputBinaresLbl[2], 0, 2);
   mainLay->addWidget(inputBinaresLbl[3], 0, 3);
   mainLay->addWidget(inputBinaresLbl[4], 0, 4);
   mainLay->addWidget(inputBinaresLbl[5], 0, 5);
   mainLay->addWidget(inputBinaresLbl[6], 0, 6);
   mainLay->addWidget(inputBinaresLbl[7], 0, 7);
   mainLay->addWidget(inputBinaresLbl[8], 0, 8);
   mainLay->addWidget(inputBinaresLbl[9], 0, 9);
   mainLay->addWidget(inputBinaresLbl[10], 0, 10);
   mainLay->addWidget(inputBinaresLbl[11], 0, 11);
   mainLay->addWidget(inputBinaresLbl[12], 0, 12);
   mainLay->addWidget(inputBinaresLbl[13], 0, 13);
   mainLay->addWidget(inputBinaresLbl[14], 0, 14);
   mainLay->addWidget(inputBinaresLbl[15], 0, 15);
   mainLay->addWidget(inputBinaresLbl[16], 0, 16);
   mainLay->addWidget(inputBinaresLbl[17], 0, 17);
   mainLay->addWidget(inputBinaresLbl[18], 0, 18);
   mainLay->addWidget(inputBinaresLbl[19], 0, 19);
   
   mainLay->addWidget(inputBinaresValueLbl[0], 1, 0);
   mainLay->addWidget(inputBinaresValueLbl[1], 1, 1);
   mainLay->addWidget(inputBinaresValueLbl[2], 1, 2);
   mainLay->addWidget(inputBinaresValueLbl[3], 1, 3);
   mainLay->addWidget(inputBinaresValueLbl[4], 1, 4);
   mainLay->addWidget(inputBinaresValueLbl[5], 1, 5);
   mainLay->addWidget(inputBinaresValueLbl[6], 1, 6);
   mainLay->addWidget(inputBinaresValueLbl[7], 1, 7);
   mainLay->addWidget(inputBinaresValueLbl[8], 1, 8);
   mainLay->addWidget(inputBinaresValueLbl[9], 1, 9);
   mainLay->addWidget(inputBinaresValueLbl[10], 1, 10);
   mainLay->addWidget(inputBinaresValueLbl[11], 1, 11);
   mainLay->addWidget(inputBinaresValueLbl[12], 1, 12);
   mainLay->addWidget(inputBinaresValueLbl[13], 1, 13);
   mainLay->addWidget(inputBinaresValueLbl[14], 1, 14);
   mainLay->addWidget(inputBinaresValueLbl[15], 1, 15);
   mainLay->addWidget(inputBinaresValueLbl[16], 1, 16);
   mainLay->addWidget(inputBinaresValueLbl[17], 1, 17);
   mainLay->addWidget(inputBinaresValueLbl[18], 1, 18);
   mainLay->addWidget(inputBinaresValueLbl[19], 1, 19);
   mainLay->addWidget(stack, 2, 0, 1, 20);
   
   connect(commandWordInput[0], static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this](int value) { pointOnController->setRangeValue(3, 7, value); emit pointOnController->update(); });
   connect(commandWordInput[1], static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this](int value) { pointOnController->setRangeValue(9, 13, value); emit pointOnController->update(); });
   connect(commandWordInput[2], static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this](int value) { pointOnController->setRangeValue(14, 18, value); emit pointOnController->update(); });
   connect(requestWordInput, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this](int value) { pointOnController->setRangeValue(3, 7, value); emit pointOnController->update(); });
   
   connect(pointOnController, &TController::update, [this, inputBinaresValueLbl, commandWordInput, requestWordInput]() { 
      if(flagChangeInput)
      {
         return; 
      }
      flagChangeInput = true;
      for(int i = 0; i < COUT_FULL_BITES; i++)
      {
         inputBinaresValueLbl[i]->setText(QString::number(pointOnController->getImpulsState(i))); 
      } 
      
      if(stack->currentIndex() == 0) {
         commandWordInput[0]->setValue(pointOnController->getRangeValue(3, 7)); 
         commandWordInput[1]->setValue(pointOnController->getRangeValue(9, 13));
         commandWordInput[2]->setValue(pointOnController->getRangeValue(14, 18));
      } else if(stack->currentIndex() == 2) {
         requestWordInput->setValue(pointOnController->getRangeValue(3, 7));  
      }
      flagChangeInput = false;
   });
}
//---------------------------------------------------------------------------
void TBitesPanel::setWord(int index)
{
   stack->setCurrentIndex(index); 
}
